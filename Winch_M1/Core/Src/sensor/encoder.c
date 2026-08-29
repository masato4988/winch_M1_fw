/*
 * encoder.c
 *
 *  Created on: Aug 1, 2026
 *      Author: miyab
 */

#include "sensor/encoder.h"

#include "config/config_encoder.h"
#include "config/config_control.h"

#include "tim.h"
#include <math.h>

/*------------------------------------------------------------------*/
/* private                                                          */
/*------------------------------------------------------------------*/

typedef struct
{
    int32_t count;

    float position;      /* [rad] */
    float speed;         /* [rad/s] */
    float acceleration;  /* [rad/s^2] */

} EncoderState_t;

static EncoderState_t s_encoder;

static int16_t s_prev_count = 0;
static int32_t s_continuous_count = 0;
static float   s_prev_speed = 0.0f;

static int32_t s_count_history[ENCODER_SPEED_FIT_POINTS];
static uint8_t s_count_history_valid = 0;

/*------------------------------------------------------------------*/
/* public                                                           */
/*------------------------------------------------------------------*/

void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

    Encoder_Reset();
}

void Encoder_Reset(void)
{
	Encoder_ResetPosition(0.0f);
}

void Encoder_ResetPosition(float position)
{
    int32_t count;

    count = (int32_t)lroundf(position / ENCODER_RAD_PER_COUNT);

    __HAL_TIM_SET_COUNTER(&htim3, (uint16_t)count);

    s_encoder.count = count;
    s_encoder.position = count * ENCODER_RAD_PER_COUNT;

    s_encoder.speed = 0.0f;
    s_encoder.acceleration = 0.0f;

    s_prev_count = count;
    s_prev_speed = 0.0f;

    for(uint8_t i = 0; i < 5; i++)
    {
        s_count_history[i] = s_continuous_count;
    }

    s_count_history_valid = 0;
}

void Encoder_Update(float dt)
{
	int16_t cnt;
	int16_t prev;
	int16_t delta;

	cnt = (int16_t)__HAL_TIM_GET_COUNTER(&htim3);
	prev = s_prev_count;

	/*
	 * 16bitカウンタの循環を考慮した差分
	 *
	 * 例：
	 *   32767 → -32768
	 *   delta = +1
	 *
	 *   -32768 → 32767
	 *   delta = -1
	 */
	delta = (int16_t)(cnt - prev);

	/*
	 * 16bitカウンタの差分を積算し、
	 * 連続したカウント値を作る
	 */
	s_continuous_count += delta;

	s_encoder.count = cnt;

	/*
	 * positionは従来通り現在の16bitカウンタ値から計算
	 *
	 * ※必要なら将来的にs_continuous_countから
	 *   絶対位置を計算することもできる
	 */
	s_encoder.position =
		(float)cnt * ENCODER_RAD_PER_COUNT;

	/*--------------------------------------------------------------*/
	/* count履歴を更新                                              */
	/*--------------------------------------------------------------*/

	for(uint8_t i = 0; i < ENCODER_SPEED_FIT_POINTS - 1U; i++)
	{
	    s_count_history[i] = s_count_history[i + 1U];
	}

	s_count_history[ENCODER_SPEED_FIT_POINTS - 1U] =
	    s_continuous_count;

	if(s_count_history_valid < ENCODER_SPEED_FIT_POINTS)
	{
	    s_count_history_valid++;
	}

	/*--------------------------------------------------------------*/
	/* 5点一次近似による速度推定                                    */
	/*--------------------------------------------------------------*/

	if(s_count_history_valid >= ENCODER_SPEED_FIT_POINTS)
	{
	    float sum_t = 0.0f;
	    float sum_x = 0.0f;
	    float numerator = 0.0f;
	    float denominator = 0.0f;

	    /*
	     * 時刻を
	     *
	     * 0, dt, 2dt, ...
	     *
	     * とする
	     */
	    for(uint8_t i = 0; i < ENCODER_SPEED_FIT_POINTS; i++)
	    {
	        float t = (float)i * dt;
	        float x = (float)s_count_history[i];

	        sum_t += t;
	        sum_x += x;
	    }

	    float mean_t =
	        sum_t / (float)ENCODER_SPEED_FIT_POINTS;

	    float mean_x =
	        sum_x / (float)ENCODER_SPEED_FIT_POINTS;

	    for(uint8_t i = 0; i < ENCODER_SPEED_FIT_POINTS; i++)
	    {
	        float t = (float)i * dt;
	        float x = (float)s_count_history[i];

	        numerator +=
	            (t - mean_t) * (x - mean_x);

	        denominator +=
	            (t - mean_t) * (t - mean_t);
	    }

	    /* 傾き = count/s */
	    float slope = numerator / denominator;

	    /* rad/sへ変換 */
	    s_encoder.speed =
	        slope * ENCODER_RAD_PER_COUNT;
	}
	else
	{
	    s_encoder.speed = 0.0f;
	}

	/*--------------------------------------------------------------*/
	/* 角加速度                                                     */
	/*--------------------------------------------------------------*/

	s_encoder.acceleration =
		(s_encoder.speed - s_prev_speed) / dt;

	s_prev_count = cnt;
	s_prev_speed = s_encoder.speed;
    /* デバッグ */
//	printf("cnt=%ld delta=%ld dt=%d speed=%d\r\n",
//		   cnt,
//		   delta,
//		   (int)(dt * 1000),
//		   (int)(s_encoder.speed * 1000)
//		   );
}

int32_t Encoder_GetRawCount(void)
{
    return (int32_t)(int16_t)__HAL_TIM_GET_COUNTER(&htim3);
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

