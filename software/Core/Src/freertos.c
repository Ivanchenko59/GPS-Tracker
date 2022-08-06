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
#include "gsm.h"
#include "nmea.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
nmea_t gps;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

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
  .stack_size = 512 * 4,
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
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task_gps */
osThreadId_t task_gpsHandle;
const osThreadAttr_t task_gps_attributes = {
  .name = "task_gps",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void start_task_gsm(void *argument);
void start_task_send_gsm(void *argument);
void start_task_nmea(void *argument);
void start_task_gps(void *argument);

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

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

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

  /* creation of task_gps */
  task_gpsHandle = osThreadNew(start_task_gps, NULL, &task_gps_attributes);

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
  for(;;)
  {
    osDelay(1);
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
  for(;;)
  {
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
	gsm_waitForRegister(30);
//	gsm_msg_send("+380666874820", "TEST MSG 1");
  /* Infinite loop */
  for(;;)
  {
    osDelay(20000);
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
	osDelay(1);
  }
  /* USER CODE END start_task_nmea */
}

/* USER CODE BEGIN Header_start_task_gps */
/**
* @brief Function implementing the task_gps thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_task_gps */
void start_task_gps(void *argument)
{
  /* USER CODE BEGIN start_task_gps */
	uint8_t time_h;
  /* Infinite loop */
  for(;;)
  {
	if (nmea_available(&gps)) {
		nmea_gnss_time_h(&gps, &time_h);
		nmea_available_reset(&gps);
	}
	osDelay(5000);
  }
  /* USER CODE END start_task_gps */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
