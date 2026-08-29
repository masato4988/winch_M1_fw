/*
 * speed_controller.c
 *
 *  Created on: Aug 1, 2026
 *      Author: miyab
 */

#include "actuator/motor/speed_controller.h"

#include "sensor/encoder.h"
#include "actuator/motor/motor_driver.h"

//#include "config/config_control.h"
#include "config/config_speed.h"

static float s_targetSpeed = 0.0f;
static float s_integral    = 0.0f;
static float s_prevError   = 0.0f;

static float s_error       = 0.0f;
static float s_output      = 0.0f;

void SpeedController_Init(void)
{
    SpeedController_Reset();
}

void SpeedController_Reset(void)
{
    s_targetSpeed = 0.0f;
    s_integral    = 0.0f;
    s_prevError   = 0.0f;

    s_error       = 0.0f;
    s_output      = 0.0f;
}

void SpeedController_SetTargetSpeed(float target)
{
    if(target > SPEED_CTRL_TARGET_MAX)
    {
        target = SPEED_CTRL_TARGET_MAX;
    }

    if(target < -SPEED_CTRL_TARGET_MAX)
    {
        target = -SPEED_CTRL_TARGET_MAX;
    }

    s_targetSpeed = target;
}

float SpeedController_GetTargetSpeed(void)
{
    return s_targetSpeed;
}

float SpeedController_GetCurrentSpeed(void)
{
    return Encoder_GetSpeed();
}

float SpeedController_GetError(void)
{
    return s_error;
}

float SpeedController_GetOutput(void)
{
    return s_output;
}

void SpeedController_Update(float dt)
{
    float speed;
    float error;
    float derivative;
    float output;

    /* 異常なdtを除外 */
    if(dt <= 0.0f)
    {
        return;
    }

    speed = Encoder_GetSpeed();

    /* 速度誤差 */
    error = s_targetSpeed - speed;

    /* I項 */
    s_integral += error * dt;

    if(s_integral > SPEED_CTRL_INTEGRAL_MAX)
    {
        s_integral = SPEED_CTRL_INTEGRAL_MAX;
    }

    if(s_integral < -SPEED_CTRL_INTEGRAL_MAX)
    {
        s_integral = -SPEED_CTRL_INTEGRAL_MAX;
    }

    /* D項 */
    derivative =
        (error - s_prevError) / dt;

    /* PID演算 */
    output =
          SPEED_CTRL_KP * error
        + SPEED_CTRL_KI * s_integral
        + SPEED_CTRL_KD * derivative;

    s_prevError = error;

    /* 出力制限 */
    if(output > SPEED_CTRL_OUTPUT_MAX)
    {
        output = SPEED_CTRL_OUTPUT_MAX;
    }

    if(output < -SPEED_CTRL_OUTPUT_MAX)
    {
        output = -SPEED_CTRL_OUTPUT_MAX;
    }

    /* デバッグ用に保存 */
    s_error  = error;
    s_output = output;

    /* モータドライバへ出力 */
    MotorDriver_SetDuty(s_output);
}
