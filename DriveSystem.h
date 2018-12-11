/*
 * DriveSystem.h
 *
 *  Created on: Dec 7, 2018
 *      Author: davidkopala
 */

#include "../MazeDrivers/MotorEncoder.h"

#include "../inc/PWM.h"

#ifndef DRIVESYSTEM_H_
#define DRIVESYSTEM_H_

void DriveSystem_Init(uint32_t duty_period);

void drive_pivot_cw(uint16_t degrees);
void drive_pivot_ccw(uint16_t degrees);
void drive_turn_right(void);
void drive_turn_left(void);

void drive_straight_cm(float cm, float speed);
void drive_forward_cm(float cm, float speed);
void drive_backward_cm(float cm, float speed);

void drive_left_speed(float speed);
void drive_right_speed(float speed);

#endif /* DRIVESYSTEM_H_ */
