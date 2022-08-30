/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs.h"
#include "gsm.h"
#include "nmea.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
nmea_t gps = {0};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
FATFS 	fs;  // file system
FIL 	fil; // File
FILINFO fno;
FRESULT fresult;  // result
UINT 	br, bw;  // File read/write count

char pcWriteBuffer[1024];
uint32_t freemem;
extern uint8_t gps_is_ready;
uint8_t vbat;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task_gsm */
osThreadId_t task_gsmHandle;
const osThreadAttr_t task_gsm_attributes = {
  .name = "task_gsm",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task_send_gsm */
osThreadId_t task_send_gsmHandle;
const osThreadAttr_t task_send_gsm_attributes = {
  .name = "task_send_gsm",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task_nmea */
osThreadId_t task_nmeaHandle;
const osThreadAttr_t task_nmea_attributes = {
  .name = "task_nmea",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task_get_gps */
osThreadId_t task_get_gpsHandle;
const osThreadAttr_t task_get_gps_attributes = {
  .name = "task_get_gps",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow4,
};
/* Definitions for task_sdcard */
osThreadId_t task_sdcardHandle;
const osThreadAttr_t task_sdcard_attributes = {
  .name = "task_sdcard",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal7,
};
/* Definitions for gnss_queue */
osMessageQueueId_t gnss_queueHandle;
const osMessageQueueAttr_t gnss_queue_attributes = {
  .name = "gnss_queue"
};
/* Definitions for sender_num_queue */
osMessageQueueId_t sender_num_queueHandle;
const osMessageQueueAttr_t sender_num_queue_attributes = {
  .name = "sender_num_queue"
};
/* Definitions for send_sms_sem */
osSemaphoreId_t send_sms_semHandle;
const osSemaphoreAttr_t send_sms_sem_attributes = {
  .name = "send_sms_sem"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
int bufsize(char *buf);
uint8_t is_sd_detect(void);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void start_task_gsm(void *argument);
void start_task_send_gsm(void *argument);
void start_task_nmea(void *argument);
void start_task_get_gps(void *argument);
void start_task_sdcard(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of send_sms_sem */
  send_sms_semHandle = osSemaphoreNew(1, 1, &send_sms_sem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  osSemaphoreAcquire(send_sms_semHandle, osWaitForever);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of gnss_queue */
  gnss_queueHandle = osMessageQueueNew (2, sizeof(nmea_t), &gnss_queue_attributes);

  /* creation of sender_num_queue */
  sender_num_queueHandle = osMessageQueueNew (1, sizeof(msg_data_t), &sender_num_queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of task_gsm */
  task_gsmHandle = osThreadNew(start_task_gsm, NULL, &task_gsm_attributes);

  /* creation of task_send_gsm */
  task_send_gsmHandle = osThreadNew(start_task_send_gsm, NULL, &task_send_gsm_attributes);

  /* creation of task_nmea */
  task_nmeaHandle = osThreadNew(start_task_nmea, NULL, &task_nmea_attributes);

  /* creation of task_get_gps */
  task_get_gpsHandle = osThreadNew(start_task_get_gps, NULL, &task_get_gps_attributes);

  /* creation of task_sdcard */
  task_sdcardHandle = osThreadNew(start_task_sdcard, NULL, &task_sdcard_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;) {
	  freemem = xPortGetFreeHeapSize();
	  vTaskList(pcWriteBuffer);
	  osDelay(2000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_start_task_gsm */
/**
* @brief Function implementing the task_gsm thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_task_gsm */
void start_task_gsm(void *argument)
{
  /* USER CODE BEGIN start_task_gsm */
	gsm_init();
	gsm_power(true);
  /* Infinite loop */
	for(;;) {
		gsm_loop();
		osDelay(10);
	}
  /* USER CODE END start_task_gsm */
}

/* USER CODE BEGIN Header_start_task_send_gsm */
/**
  * @brief  Function implementing the task_send_gsm thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_start_task_send_gsm */
void start_task_send_gsm(void *argument)
{
  /* USER CODE BEGIN start_task_send_gsm */
	msg_data_t user_data = {};
	char sms_to_send[64];
	gsm_waitForRegister(30);

//	gsm_gprs_setApName("internet");
//	while (gsm_gprs_connect() == 0) {
//		osDelay(5000);
//	}
//	while (gsm_gprs_mqttConnect("broker.mqttdashboard.com", 1883, 1, "sim800", 60, NULL, NULL, 30) == 0) {
//		osDelay(5000);
//	}
//	gsm_gprs_mqttSubscribe("testtopic/bababui", 1);
//	gsm_gprs_mqttPublish("testtopic/bababui", 1, 0, "hello");

  /* Infinite loop */
	for (;;) {

		osSemaphoreAcquire(send_sms_semHandle, osWaitForever);
		osMessageQueueGet(sender_num_queueHandle, &user_data, 0, osWaitForever);

		if (strcmp(user_data.msg, "GET GPS") == 0) {
			sprintf(sms_to_send, "https://www.google.com/maps/@%.7f,%.7f", gps.gnss.latitude_deg, gps.gnss.longitude_deg);
		} else if (strcmp(user_data.msg, "GET BATTERY") == 0) {
				sprintf(sms_to_send, "Battery voltage: %f,V", vbat);
		} else if (strcmp(user_data.msg, "GET SOMETHING") == 0) {

		}
//		gsm_msg_send(user_data.number, sms_to_send);

		memset(sms_to_send, '\0', 64);
		memset(&user_data, '\0', sizeof(user_data));
	}
  /* USER CODE END start_task_send_gsm */
}

/* USER CODE BEGIN Header_start_task_nmea */
/**
* @brief Function implementing the task_nmea thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_task_nmea */
void start_task_nmea(void *argument)
{
  /* USER CODE BEGIN start_task_nmea */
	nmea_init(&gps, USART1, 1024);
  /* Infinite loop */
	for(;;)
	{
		nmea_loop(&gps);
		osDelay(100);
	}
  /* USER CODE END start_task_nmea */
}

/* USER CODE BEGIN Header_start_task_get_gps */
/**
* @brief Function implementing the task_get_gps thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_task_get_gps */
void start_task_get_gps(void *argument)
{
  /* USER CODE BEGIN start_task_get_gps */
  /* Infinite loop */
	for (;;) {
		if (gps_is_ready && nmea_available(&gps)) {
			osMessageQueuePut(gnss_queueHandle, &gps, 0, osWaitForever);
			nmea_available_reset(&gps);
		}
		osDelay(2000);
	}
  /* USER CODE END start_task_get_gps */
}

/* USER CODE BEGIN Header_start_task_sdcard */
/**
* @brief Function implementing the task_sdcard thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_task_sdcard */
void start_task_sdcard(void *argument)
{
  /* USER CODE BEGIN start_task_sdcard */
	nmea_t gnss_data = {};
	int index = 1;
	char buffer[64];
  /* Infinite loop */
	for (;;) {
		if (is_sd_detect() && osMessageQueueGetCount(gnss_queueHandle)) {

			osMessageQueueGet(gnss_queueHandle, &gnss_data, 0, osWaitForever);

			fresult = f_mount(&fs, "", 0);
			if (fresult != FR_OK) {
				printf("Mount failed\n");
			}

			fresult = f_open(&fil, "data.txt", FA_OPEN_ALWAYS | FA_WRITE);
			if (fresult != FR_OK) {
				printf("File wasn't create\n");
			}
			memset(buffer, '\0', sizeof(buffer));

			sprintf(buffer, "%d.\t%.7f\t%.7f\n", index, gnss_data.gnss.latitude_deg, gnss_data.gnss.longitude_deg);
			f_lseek(&fil, f_size(&fil));
			f_puts(buffer, &fil);
			fresult = f_close(&fil);
			if (fresult != FR_OK) {
				printf("File wasn't close\n");
			}

			fresult = f_mount(NULL, "", 1);

			index++;
		}

		osDelay(1000);
	}
  /* USER CODE END start_task_sdcard */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
int bufsize(char *buf)
{
	int i = 0;
	while (*buf++ != '\0')
		i++;
	return i;
}
/*
 * @brief Function for detecting SD card
 * @retval Returns 1 if SD detect and 0 if not
 */
uint8_t is_sd_detect(void)
{
	return !HAL_GPIO_ReadPin(SD_DETECT_GPIO_Port, SD_DETECT_Pin);
}

/*
 * @brief Function for knowing when GPS 3d fix ready
 * @retval Returns 1 if ready and 0 if not
 */
uint8_t is_gps_ready(void)
{
//	return !HAL_GPIO_ReadPin(SD_DETECT_GPIO_Port, SD_DETECT_Pin);
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
