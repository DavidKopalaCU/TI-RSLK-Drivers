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

    // Enable both motors
//    P3->SEL0 &= ~(BIT7 | BIT6);  // GPIO
//    P3->SEL1 &= ~(BIT7 | BIT6);  // GPIO
//    P3->DIR |= (BIT7 | BIT6);
//    P3->OUT &= ~(BIT6 | BIT6);
//
    // Set forward direction
    P1->SEL0 &= ~(BIT7 | BIT6);  // GPIO
    P1->SEL1 &= ~(BIT7 | BIT6);  // GPIO
    P1->DIR |= (BIT7 | BIT6);    // Output
    P1->OUT &= ~(BIT7 | BIT6);    // FORWARD

    PWM_Init12(motor_period, 0, 0);
}


void drive_forward_cm(float cm, float speed) {
    float right_on = speed, left_on = speed;

    uint32_t count = (cm / 22.0) * 360.0;

    uint32_t first_left_cnt = left_encoder_p->count;
    uint32_t first_right_cnt = right_encoder_p->count;

    while (1) {
        uint32_t left_diff = left_encoder_p->count - first_left_cnt;
        uint32_t right_diff = right_encoder_p->count - first_right_cnt;

        if (left_diff > count && right_diff > count) {
            PWM_Duty1(0);
            PWM_Duty2(0);
            break;
        }

        if ((left_diff - right_diff) > 50) {
            left_on -= 0.01;
            right_on += 0.01;
        } else if ((right_diff - left_diff) > 50) {
            right_on -= 0.01;
            left_on += 0.01;
        }

        if (left_on >= 0.5) {
            left_on = 0.5;
        }
        if (left_on <= 0.01) {
            left_on = 0.01;
        }
        if (right_on >= 0.5) {
            right_on = 0.5;
        }
        if (right_on <= 0.01) {
            right_on = 0.01;
        }

        PWM_Duty1(left_on * motor_period);
        PWM_Duty2(right_on * motor_period);
    }
}


void drive_turn_right(void) {
    // Turn left forward
    // Turn right backward
    P1->OUT |= (BIT6);

    uint32_t target_cnt = (11.0 / 22.0) * 360.0; // 180

    uint32_t first_left_cnt = left_encoder_p->count;
    uint32_t first_right_cnt = right_encoder_p->count;
    PWM_Duty1(0.1 * motor_period);
    PWM_Duty2(0.1 * motor_period);
    while (1) {
        uint32_t left_diff = left_encoder_p->count - first_left_cnt;
        uint32_t right_diff = right_encoder_p->count - first_right_cnt;
        if (left_diff >= target_cnt) {
            PWM_Duty2(0);
        }
        if (right_diff >= target_cnt) {
            PWM_Duty1(0);
        }
        if ((right_diff >= target_cnt) && (left_diff >= target_cnt)) {
            break;
        }
    }

    // Right wheel forward
    P1->OUT &= ~(BIT6);
}

void drive_turn_left(void) {
    // Turn left forward
    // Turn right backward
    P1->OUT |= (BIT7);

    uint32_t target_cnt = (11.0 / 22.0) * 360.0; // 180

    uint32_t first_left_cnt = left_encoder_p->count;
    uint32_t first_right_cnt = right_encoder_p->count;
    PWM_Duty1(0.1 * motor_period);
    PWM_Duty2(0.1 * motor_period);
    while (1) {
        uint32_t left_diff = left_encoder_p->count - first_left_cnt;
        uint32_t right_diff = right_encoder_p->count - first_right_cnt;
        if (left_diff >= target_cnt) {
            PWM_Duty2(0);
        }
        if (right_diff >= target_cnt) {
            PWM_Duty1(0);
        }
        if ((right_diff >= target_cnt) && (left_diff >= target_cnt)) {
            break;
        }
    }

    // Right wheel forward
    P1->OUT &= ~(BIT7);
}

void drive_pivot_cw(uint16_t degrees) {
    // Turn left forward
    // Turn right backward
    P1->OUT |= (BIT6);

    uint32_t target_cnt = (degrees / 180.0) * 360.0; // 180

    uint32_t first_left_cnt = left_encoder_p->count;
    uint32_t first_right_cnt = right_encoder_p->count;
    PWM_Duty1(0.1 * motor_period);
    PWM_Duty2(0.1 * motor_period);
    while (1) {
        uint32_t left_diff = left_encoder_p->count - first_left_cnt;
        uint32_t right_diff = right_encoder_p->count - first_right_cnt;
        if (left_diff >= target_cnt) {
            PWM_Duty2(0);
        }
        if (right_diff >= target_cnt) {
            PWM_Duty1(0);
        }
        if ((right_diff >= target_cnt) && (left_diff >= target_cnt)) {
            break;
        }
    }

    // Right wheel forward
    P1->OUT &= ~(BIT6);
}
void drive_pivot_ccw(uint16_t degrees) {
    P1->OUT |= (BIT7);

    uint32_t target_cnt = (degrees / 180.0) * 360.0;

    uint32_t first_left_cnt = left_encoder_p->count;
    uint32_t first_right_cnt = right_encoder_p->count;
    PWM_Duty1(0.1 * motor_period);
    PWM_Duty2(0.1 * motor_period);
    while (1) {
       uint32_t left_diff = left_encoder_p->count - first_left_cnt;
       uint32_t right_diff = right_encoder_p->count - first_right_cnt;
       if (left_diff >= target_cnt) {
           PWM_Duty2(0);
       }
       if (right_diff >= target_cnt) {
           PWM_Duty1(0);
       }
       if ((right_diff >= target_cnt) && (left_diff >= target_cnt)) {
           break;
       }
    }

    // Right wheel forward
    P1->OUT &= ~(BIT7);
}

void drive_left_speed(float speed) {
    PWM_Duty2(motor_period * speed);
}

void drive_right_speed(float speed) {
    PWM_Duty1(motor_period * speed);
}
