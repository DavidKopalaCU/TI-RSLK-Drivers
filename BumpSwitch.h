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

#define PORT_NUM P4
#define PORT_IRQn PORT4_IRQn

void BumpSwitches_Init(void(*task)(uint8_t));

static uint8_t bump_trigger_val = 0;
uint8_t bump_is_triggered(void);
void bump_clear_trigger(void);

#endif /* BUMPSWITCH_H_ */
