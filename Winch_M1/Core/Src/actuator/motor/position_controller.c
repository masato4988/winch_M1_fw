/*
 * position_controller.c
 *
 *  Created on: Aug 29, 2026
 *      Author: miyab
 */


#include "actuator/motor/position_controller.h"

#include "sensor/encoder.h"
#include "actuator/motor/speed_controller.h"

#include "config/config_position.h"


/*------------------------------------------------------------------*/
/* private                                                          */
/*------------------------------------------------------------------*/

static PositionControllerMode_t s_mode =
    POSITION_CTRL_MODE_POSITION;

static float s_targetPosition = 0.0f;

static float s_error  = 0.0f;
static float s_output = 0.0f;


/*------------------------------------------------------------------*/
/* public                                                           */
/*------------------------------------------------------------------*/

void PositionController_Init(void)
{
    PositionController_Reset();
}


void PositionController_Reset(void)
{
    s_targetPosition = Encoder_GetPosition();

    s_error = 0.0f;
    s_output = 0.0f;

    SpeedController_SetTargetSpeed(0.0f);
}


void PositionController_SetMode(PositionControllerMode_t mode)
{
    s_mode = mode;
}


PositionControllerMode_t PositionController_GetMode(void)
{
    return s_mode;
}


void PositionController_SetTargetPosition(float target)
{
    if(target > POSITION_CTRL_TARGET_MAX)
    {
        target = POSITION_CTRL_TARGET_MAX;
    }

    if(target < -POSITION_CTRL_TARGET_MAX)
    {
        target = -POSITION_CTRL_TARGET_MAX;
    }

    s_targetPosition = target;
}


float PositionController_GetTargetPosition(void)
{
    return s_targetPosition;
}


float PositionController_GetError(void)
{
    return s_error;
}


float PositionController_GetOutput(void)
{
    return s_output;
}


void PositionController_Update(float dt)
{
    float position;
    float error;
    float output;

    (void)dt;

    position = Encoder_GetPosition();

    error = s_targetPosition - position;

    s_error = error;


    /*----------------------------------------------------------*/
    /* Position control                                         */
    /*----------------------------------------------------------*/

    output =
        POSITION_CTRL_KP * error;


    /*----------------------------------------------------------*/
    /* Output limit                                             */
    /*----------------------------------------------------------*/

    if(output > POSITION_CTRL_OUTPUT_MAX)
    {
        output = POSITION_CTRL_OUTPUT_MAX;
    }

    if(output < -POSITION_CTRL_OUTPUT_MAX)
    {
        output = -POSITION_CTRL_OUTPUT_MAX;
    }

    s_output = output;


    /*----------------------------------------------------------*/
    /* Speed Controller                                         */
    /*----------------------------------------------------------*/

    SpeedController_SetTargetSpeed(output);
}
