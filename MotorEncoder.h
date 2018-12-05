/*
 * MotorEncoder.h
 *
 *  Created on: Nov 28, 2018
 *      Author: davidkopala
 */


#ifndef MOTORENCODER_H_
#define MOTORENCODER_H_

#include <stdint.h>

#include "msp.h"
#include "../inc/SysTick.h"

typedef struct motor_encoder {
    DIO_PORT_Odd_Interruptable_Type* port;
    uint8_t bit;

    uint32_t count;
    uint16_t frequency;
    uint32_t last_trigger;
} motor_encoder_t;

static motor_encoder_t left_encoder;
static motor_encoder_t right_encoder;

motor_encoder_t* motor_encoder_get_right();
motor_encoder_t* motor_encoder_get_left();

void MotorEncoder_Init(void);
void PORT2_IRQHandler(void);


#endif /* MOTORENCODER_H_ */
