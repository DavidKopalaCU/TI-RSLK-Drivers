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
    P4->SEL0 &= ~pin_mask;
    P4->SEL1 &= ~pin_mask;

    //Input
    P4->DIR &= ~pin_mask;

    // Pull-Up Resistor PAGE 678
    P4->REN |= pin_mask;
    P4->OUT |= pin_mask;

    // Interrupt Enable
    P4->IE |= pin_mask;
    // Interrupt on FALLING edge
    P4->IES &= ~pin_mask;

    // Clear Interrupt Flag
    P4->IFG = 0;

    // Allow interrupts to happen
    NVIC_EnableIRQ(PORT4_IRQn);
//    __enable_interrupt();
}

void PORT4_IRQHandler(void) {
    bump_trigger_val |= P4->IFG;
    P4->IFG = 0;
}


uint8_t bump_is_triggered(void) {
    return bump_trigger_val;
}
void bump_clear_trigger(void) {
    bump_trigger_val = 0;
}
