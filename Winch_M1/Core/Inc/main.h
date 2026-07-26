/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define SW_LIMIT_Pin GPIO_PIN_14
#define SW_LIMIT_GPIO_Port GPIOC
#define NTC_MOT_Pin GPIO_PIN_0
#define NTC_MOT_GPIO_Port GPIOC
#define NTC_FET_Pin GPIO_PIN_1
#define NTC_FET_GPIO_Port GPIOC
#define GPIO_EX_8_Pin GPIO_PIN_2
#define GPIO_EX_8_GPIO_Port GPIOC
#define GPIO_EX_9_Pin GPIO_PIN_3
#define GPIO_EX_9_GPIO_Port GPIOC
#define SERVO_PWM_Pin GPIO_PIN_0
#define SERVO_PWM_GPIO_Port GPIOA
#define H_CURRENT_Pin GPIO_PIN_1
#define H_CURRENT_GPIO_Port GPIOA
#define GPIO_EX_1_Pin GPIO_PIN_4
#define GPIO_EX_1_GPIO_Port GPIOA
#define GPIO_EX_2_Pin GPIO_PIN_5
#define GPIO_EX_2_GPIO_Port GPIOA
#define ENC_A_Pin GPIO_PIN_6
#define ENC_A_GPIO_Port GPIOA
#define ENC_B_Pin GPIO_PIN_7
#define ENC_B_GPIO_Port GPIOA
#define VIN_SENCE_Pin GPIO_PIN_4
#define VIN_SENCE_GPIO_Port GPIOC
#define GPIO_EX_10_Pin GPIO_PIN_5
#define GPIO_EX_10_GPIO_Port GPIOC
#define GPIO_EX_3_Pin GPIO_PIN_0
#define GPIO_EX_3_GPIO_Port GPIOB
#define GPIO_EX_4_Pin GPIO_PIN_1
#define GPIO_EX_4_GPIO_Port GPIOB
#define GPIO_EX_5_Pin GPIO_PIN_2
#define GPIO_EX_5_GPIO_Port GPIOB
#define GPIO_EX_6_Pin GPIO_PIN_11
#define GPIO_EX_6_GPIO_Port GPIOB
#define GPIO_EX_7_Pin GPIO_PIN_13
#define GPIO_EX_7_GPIO_Port GPIOB
#define LOADCELL_Pin GPIO_PIN_14
#define LOADCELL_GPIO_Port GPIOB
#define RGB_R_Pin GPIO_PIN_6
#define RGB_R_GPIO_Port GPIOC
#define RGB_G_Pin GPIO_PIN_7
#define RGB_G_GPIO_Port GPIOC
#define RGB_B_Pin GPIO_PIN_8
#define RGB_B_GPIO_Port GPIOC
#define H_PWM1_Pin GPIO_PIN_8
#define H_PWM1_GPIO_Port GPIOA
#define H_PWM2_Pin GPIO_PIN_9
#define H_PWM2_GPIO_Port GPIOA
#define CAN_STBY_Pin GPIO_PIN_10
#define CAN_STBY_GPIO_Port GPIOA
#define H_SD1_Pin GPIO_PIN_11
#define H_SD1_GPIO_Port GPIOC
#define H_SD2_Pin GPIO_PIN_12
#define H_SD2_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
