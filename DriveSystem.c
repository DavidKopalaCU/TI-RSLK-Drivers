/*
 * DriveSystem.c
 *
 *  Created on: Dec 7, 2018
 *      Author: davidkopala
 */

#include "../MazeDrivers/DriveSystem.h"

static motor_encoder_t *left_encoder_p = 0;
static motor_encoder_t *right_encoder_p = 0;

static uint32_t motor_period = 0xFFF;

void DriveSystem_Init(uint32_t duty_period) {
    motor_period = duty_period;

    MotorEncoder_Init();
    left_encoder_p = motor_encoder_get_left();
    right_encoder_p = motor_encoder_get_right();
    PWM_Init12(motor_period, 0, 0);
}


void drive_forward_cm(uint32_t cm, float speed) {
    float right_on = speed, left_on = speed;

    while (1) {
        if ((left_encoder_p->count - right_encoder_p->count) > 50) {
            left_on -= 0.01;
            right_on += 0.01;
        } else if ((right_encoder_p->count - left_encoder_p->count) > 50) {
            right_on -= 0.01;
            left_on += 0.01;
        }

        if (left_on >= 0.5) {
            left_on = 0.5;
        }
        if (left_on <= 0) {
            left_on = 0;
        }
        if (right_on >= 0.5) {
            right_on = 0.5;
        }
        if (right_on <= 0) {
            right_on = 0;
        }

        PWM_Duty1(left_on * motor_period);
        PWM_Duty2(right_on * motor_period);
    }

}
