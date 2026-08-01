/*
 * RGBLED.c
 *
 *  Created on: Jul 26, 2026
 *      Author: miyab
 */


#include "actuator/RGBLED.h"

#include "tim.h"

#define RGBLED_PWM_MAX    (__HAL_TIM_GET_AUTORELOAD(&htim8))

float brightness = 0.02f;

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
	uint8_t R = 0;
	uint8_t G = 0;
	uint8_t B = 0;

    switch(color)
    {
    case RGBLED_COLOR_OFF:
    	R = 0;
    	G = 0;
    	B = 0;
        break;

    case RGBLED_COLOR_RED:
    	R = (uint8_t)(256 * brightness);
    	G = 0;
    	B = 0;
        break;

    case RGBLED_COLOR_GREEN:
    	R = 0;
    	G = (uint8_t)(256 * brightness);
    	B = 0;
        break;

    case RGBLED_COLOR_BLUE:
    	R = 0;
    	G = 0;
    	B = (uint8_t)(256 * brightness);
        break;

    case RGBLED_COLOR_YELLOW:
    	R = (uint8_t)(256 * brightness);
    	G = (uint8_t)(256 * brightness);
    	B = 0;
        break;

    case RGBLED_COLOR_CYAN:
    	R = 0;
    	G = (uint8_t)(256 * brightness);
    	B = (uint8_t)(256 * brightness);

        break;

    case RGBLED_COLOR_MAGENTA:
    	R = (uint8_t)(256 * brightness);
    	G = 0;
    	B = (uint8_t)(256 * brightness);
        break;

    case RGBLED_COLOR_WHITE:
    	R = (uint8_t)(256 * brightness);
    	G = (uint8_t)(256 * brightness);
    	B = (uint8_t)(256 * brightness);
        break;

    default:
    	R = 0;
    	G = 0;
    	B = 0;
        break;
    }
	RGBLED_SetRGB(R,G,B);
}
