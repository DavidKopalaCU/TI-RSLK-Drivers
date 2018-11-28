/*
 * MotorEncoder.h
 *
 *  Created on: Nov 28, 2018
 *      Author: davidkopala
 */

#include <stdint.h>

#ifndef MOTORENCODER_H_
#define MOTORENCODER_H_

typedef struct motor_encoder {
    DIO_PORT_Odd_Interruptable_Type* port;
    uint8_t bit;
} motor_encoder_t;



#endif /* MOTORENCODER_H_ */
