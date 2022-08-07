/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_dma.h"

#include "stm32f4xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN_Pin GPIO_PIN_0
#define BTN_GPIO_Port GPIOA
#define GSM_UART_TX_Pin GPIO_PIN_2
#define GSM_UART_TX_GPIO_Port GPIOA
#define GSM_USART_RX_Pin GPIO_PIN_3
#define GSM_USART_RX_GPIO_Port GPIOA
#define W25_CS_Pin GPIO_PIN_4
#define W25_CS_GPIO_Port GPIOA
#define W25_SCK_Pin GPIO_PIN_5
#define W25_SCK_GPIO_Port GPIOA
#define W25_MISO_Pin GPIO_PIN_6
#define W25_MISO_GPIO_Port GPIOA
#define W25_MOSI_Pin GPIO_PIN_7
#define W25_MOSI_GPIO_Port GPIOA
#define SD_DETECT_Pin GPIO_PIN_12
#define SD_DETECT_GPIO_Port GPIOB
#define SD_SCK_Pin GPIO_PIN_13
#define SD_SCK_GPIO_Port GPIOB
#define SD_MISO_Pin GPIO_PIN_14
#define SD_MISO_GPIO_Port GPIOB
#define SD_MOSI_Pin GPIO_PIN_15
#define SD_MOSI_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_8
#define SD_CS_GPIO_Port GPIOA
#define GPS_USART_TX_Pin GPIO_PIN_6
#define GPS_USART_TX_GPIO_Port GPIOB
#define GPS_USART_RX_Pin GPIO_PIN_7
#define GPS_USART_RX_GPIO_Port GPIOB
#define PWRKEY_GSM_Pin GPIO_PIN_9
#define PWRKEY_GSM_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
