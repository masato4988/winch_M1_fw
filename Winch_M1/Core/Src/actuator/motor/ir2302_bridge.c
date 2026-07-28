/*
 * pwm.c
 *
 *  Created on: Jul 28, 2026
 *      Author: miyab
 */


#include <actuator/motor/ir2302_bridge.h>
#include "tim.h"
#include "gpio.h"

#include "config/config_motor.h"

void IR2302bridge_Init(void)
{
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);

	__HAL_TIM_SET_PRESCALER(&htim1, MOTOR_PWM_PRESCALER);
	__HAL_TIM_SET_AUTORELOAD(&htim1, MOTOR_PWM_PERIOD);

	/* 新しいARRを反映 */
	htim1.Instance->EGR = TIM_EGR_UG;

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

void IR2302bridge_Enable(void)
{
    HAL_GPIO_WritePin(H_SD1_GPIO_Port,
                      H_SD1_Pin,
                      GPIO_PIN_SET);

    HAL_GPIO_WritePin(H_SD2_GPIO_Port,
                      H_SD2_Pin,
                      GPIO_PIN_SET);
}

void IR2302bridge_Disable(void)
{
    HAL_GPIO_WritePin(H_SD1_GPIO_Port,
                      H_SD1_Pin,
                      GPIO_PIN_RESET);

    HAL_GPIO_WritePin(H_SD2_GPIO_Port,
                      H_SD2_Pin,
                      GPIO_PIN_RESET);
}

void IR2302Bridge_SetHB1Duty(uint16_t duty)
{
    if(duty > MOTOR_PWM_MAX_DUTY)
    {
        duty = MOTOR_PWM_MAX_DUTY;
    }

    __HAL_TIM_SET_COMPARE(&htim1,
                          TIM_CHANNEL_1,
                          duty);
}

void IR2302Bridge_SetHB2Duty(uint16_t duty)
{
    if(duty > MOTOR_PWM_MAX_DUTY)
    {
        duty = MOTOR_PWM_MAX_DUTY;
    }

    __HAL_TIM_SET_COMPARE(&htim1,
                          TIM_CHANNEL_2,
                          duty);
}
