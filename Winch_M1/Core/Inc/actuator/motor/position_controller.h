/*
 * position_controller.h
 *
 *  Created on: Aug 29, 2026
 *      Author: miyab
 */

#ifndef INC_ACTUATOR_MOTOR_POSITION_CONTROLLER_H_
#define INC_ACTUATOR_MOTOR_POSITION_CONTROLLER_H_

#include <stdint.h>

/*--------------------------------------------------------------*/
/* Position Controller Mode                                     */
/*--------------------------------------------------------------*/

typedef enum
{
    POSITION_CTRL_MODE_POSITION = 0,
    POSITION_CTRL_MODE_TRACKING

} PositionControllerMode_t;


/*--------------------------------------------------------------*/
/* Initialization                                               */
/*--------------------------------------------------------------*/

void PositionController_Init(void);

/* PID / 制御状態リセット */
void PositionController_Reset(void);


/*--------------------------------------------------------------*/
/* Mode                                                         */
/*--------------------------------------------------------------*/

void PositionController_SetMode(PositionControllerMode_t mode);

PositionControllerMode_t PositionController_GetMode(void);


/*--------------------------------------------------------------*/
/* Target                                                       */
/*--------------------------------------------------------------*/

/* 目標位置 [rad] */
void PositionController_SetTargetPosition(float target);

/* 目標位置 [rad] */
float PositionController_GetTargetPosition(void);


/*--------------------------------------------------------------*/
/* Control                                                      */
/*--------------------------------------------------------------*/

/* 周期制御 */
void PositionController_Update(float dt);


/*--------------------------------------------------------------*/
/* Debug                                                        */
/*------------------------------------------------------------*/

/* 位置誤差 [rad] */
float PositionController_GetError(void);

/* 速度指令 [rad/s] */
float PositionController_GetOutput(void);

#endif /* INC_ACTUATOR_MOTOR_POSITION_CONTROLLER_H_ */
