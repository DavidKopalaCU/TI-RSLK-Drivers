/*
 * BumpSwitch.c
 *
 *  Created on: Dec 7, 2018
 *      Author: davidkopala
 */

#include "../MazeDrivers/BumpSwitch.h"

static uint8_t pin_mask = (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7); // 0xFF -> All Pins

void bump_def_handler(uint8_t b) {}
void (*bump_task)(uint8_t) = bump_def_handler;

void BumpSwitches_Init(void(*task)(uint8_t)) {
    bump_task = task;

    // GPIO
    PORT_NUM->SEL0 &= ~pin_mask;
    PORT_NUM->SEL1 &= ~pin_mask;

    //Input
    PORT_NUM->DIR &= ~pin_mask;

    // Pull-Up Resistor PAGE 678
    PORT_NUM->REN |= pin_mask;
    PORT_NUM->OUT |= pin_mask;

    // Interrupt Enable
    PORT_NUM->IE |= pin_mask;
    // Interrupt on FALLING edge
    PORT_NUM->IES &= ~pin_mask;

    // Clear Interrupt Flag
    PORT_NUM->IFG = 0;

    // Allow interrupts to happen
    NVIC_EnableIRQ(PORT_IRQn);
    __enable_interrupt();
}

void PORT4_IRQHandler(void) {
    uint8_t read = PORT_NUM->IFG;
    PORT_NUM->IFG = 0;

    bump_task(read);
}
