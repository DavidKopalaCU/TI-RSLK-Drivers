/*
 * BumpSwitch.h
 *
 *  Created on: Dec 7, 2018
 *      Author: davidkopala
 */

#include <stdint.h>

#include "msp.h"

#ifndef BUMPSWITCH_H_
#define BUMPSWITCH_H_

void BumpSwitches_Init(void(*task)(uint8_t));

#endif /* BUMPSWITCH_H_ */