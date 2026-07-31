/*
 * encoder.c
 *
 *  Created on: Aug 1, 2026
 *      Author: miyab
 */


#include "sensor/encoder.h"
#include "config/config_encoder.h"

#include "tim.h"

/*------------------------------------------------------------------*/
/* private                                                          */
/*------------------------------------------------------------------*/

typedef struct
{
    int32_t count;

    float position;
    float speed;
    float acceleration;

} EncoderState_t;

static EncoderState_t s_encoder;

static int32_t s_prev_count = 0;
static float   s_prev_speed = 0.0f;

/*------------------------------------------------------------------*/
/* public                                                           */
/*------------------------------------------------------------------*/

void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

    Encoder_Reset();
}

void Encoder_Update(void)
{
	int32_t cnt;
	int32_t delta;

	float speed;
	float position;

	/* 現在カウント取得 */
	cnt = (int16_t)__HAL_TIM_GET_COUNTER(&htim3);

	/* 差分 */
	delta = cnt - s_prev_count;

	/* 保存 */
	s_encoder.count = cnt;

	/* 角度(rad) */
	position = (2.0f * 3.14159265359f * (float)cnt) / ENCODER_PPR;
	s_encoder.position = position;

	/* 角速度(rad/s) */
	speed = (2.0f * 3.14159265359f * (float)delta)
			/ (ENCODER_PPR * ENCODER_CONTROL_PERIOD_S);

	s_encoder.speed = speed;

	/* 角加速度(rad/s²) */
	s_encoder.acceleration =
		(speed - s_prev_speed) / ENCODER_CONTROL_PERIOD_S;

	/* 次回用保存 */
	s_prev_count = cnt;
	s_prev_speed = speed;
}

int32_t Encoder_GetCount(void)
{
    return s_encoder.count;
}

void Encoder_SetCount(int32_t count)
{
    __HAL_TIM_SET_COUNTER(&htim3, (uint32_t)count);

    s_encoder.count = count;

    s_prev_count = count;
}

void Encoder_Reset(void)
{
    Encoder_SetCount(0);
}

float Encoder_GetPosition(void)
{
    return s_encoder.position;
}

float Encoder_GetSpeed(void)
{
    return s_encoder.speed;
}

float Encoder_GetAcceleration(void)
{
    return s_encoder.acceleration;
}
