 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: DC Motor Driver
 *
 * Author: Ahmed Alaa
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LEFT_NODE_PORT_ID	1
#define LEFT_NODE_PIN_ID	0

#define RIGHT_NODE_PORT_ID	1
#define RIGHT_MODE_PIN_ID	1
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum {
	CW, ACW, OFF
} DcMotor_State;

typedef struct {
	uint8 speed; /* The speed of the dc motor (Percentage) */
	DcMotor_State state; /* The state of the Motor */
} DcMotor_ConfigType;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void);
/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 * Input:
 * 			state: The required DC Motor state, it should be CW or A-CW or stop. DcMotor_State data type should be declared as enum or uint8.
 * 			speed: decimal value for the required motor speed, it should be from 0 : 100. For example, if the input is 50, The motor should rotate with 50% of its maximum speed.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
#endif /* DC_MOTOR_H_ */
