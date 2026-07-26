/*
 * RGBLED.c
 *
 *  Created on: Jul 26, 2026
 *      Author: miyab
 */


#include "actuator/RGBLED.h"

#include "tim.h"

#define RGBLED_PWM_MAX    (__HAL_TIM_GET_AUTORELOAD(&htim8))

void RGBLED_Init(void)
{
    /* PWM開始 */
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
    /* 消灯 */
    RGBLED_SetColor(RGBLED_COLOR_OFF);
}

void RGBLED_SetRGB(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t r_pwm = (uint32_t)r * RGBLED_PWM_MAX / 255;
    uint32_t g_pwm = (uint32_t)g * RGBLED_PWM_MAX / 255;
    uint32_t b_pwm = (uint32_t)b * RGBLED_PWM_MAX / 255;

    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, r_pwm);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, g_pwm);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, b_pwm);
}

void RGBLED_SetColor(RGBLED_Color_t color)
{
    switch(color)
    {
    case RGBLED_COLOR_OFF:
        RGBLED_SetRGB(0,0,0);
        break;

    case RGBLED_COLOR_RED:
        RGBLED_SetRGB(255,0,0);
        break;

    case RGBLED_COLOR_GREEN:
        RGBLED_SetRGB(0,255,0);
        break;

    case RGBLED_COLOR_BLUE:
        RGBLED_SetRGB(0,0,255);
        break;

    case RGBLED_COLOR_YELLOW:
        RGBLED_SetRGB(255,255,0);
        break;

    case RGBLED_COLOR_CYAN:
        RGBLED_SetRGB(0,255,255);
        break;

    case RGBLED_COLOR_MAGENTA:
        RGBLED_SetRGB(255,0,255);
        break;

    case RGBLED_COLOR_WHITE:
        RGBLED_SetRGB(255,255,255);
        break;

    default:
        RGBLED_SetRGB(0,0,0);
        break;
    }
}
