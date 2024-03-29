/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f0xx_hal.h"

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
#define GPIO_LED_1_Pin GPIO_PIN_6
#define GPIO_LED_1_GPIO_Port GPIOA
#define GPIO_LED_2_Pin GPIO_PIN_7
#define GPIO_LED_2_GPIO_Port GPIOA
#define GPIO_LED_3_Pin GPIO_PIN_0
#define GPIO_LED_3_GPIO_Port GPIOB
#define GPIO_LED_4_Pin GPIO_PIN_1
#define GPIO_LED_4_GPIO_Port GPIOB
#define GPIO_BTN_0_Pin GPIO_PIN_3
#define GPIO_BTN_0_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define GPIO_LED_1 GPIO_LED_1_GPIO_Port, GPIO_LED_1_Pin
#define GPIO_LED_2 GPIO_LED_2_GPIO_Port, GPIO_LED_2_Pin
#define GPIO_LED_3 GPIO_LED_3_GPIO_Port, GPIO_LED_3_Pin
#define GPIO_LED_4 GPIO_LED_4_GPIO_Port, GPIO_LED_4_Pin
#define GPIO_BTN_0 GPIO_BTN_0_GPIO_Port, GPIO_BTN_0_Pin
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
