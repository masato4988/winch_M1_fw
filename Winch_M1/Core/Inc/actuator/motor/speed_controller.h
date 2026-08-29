/*
 * speed_controller.h
 *
 *  Created on: Aug 1, 2026
 *      Author: miyab
 */

#ifndef INC_ACTUATOR_MOTOR_SPEED_CONTROLLER_H_
#define INC_ACTUATOR_MOTOR_SPEED_CONTROLLER_H_


#include <stdint.h>

void SpeedController_Init(void);

/* PIDリセット */
void SpeedController_Reset(void);

/* 目標速度 [count/s] */
void SpeedController_SetTargetSpeed(float target);

/* 目標速度 [count/s] */
float SpeedController_GetTargetSpeed(void);

/* 現在速度 [count/s] */
float SpeedController_GetCurrentSpeed(void);

/* 速度誤差 [count/s] */
float SpeedController_GetError(void);

/* コントローラ出力 */
float SpeedController_GetOutput(void);

/* 周期制御 */
void SpeedController_Update(float dt);

#endif /* INC_ACTUATOR_MOTOR_SPEED_CONTROLLER_H_ */
