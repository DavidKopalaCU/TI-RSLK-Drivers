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
    P2->SEL0 &= ~pin_mask;
    P2->SEL1 &= ~pin_mask;

    //Input
    P2->DIR &= ~pin_mask;

    // Pull-Up Resistor PAGE 678
    P2->REN |= pin_mask;
    P2->OUT |= pin_mask;

    // Interrupt Enable
    P2->IE |= pin_mask;
    // Interrupt on FALLING edge
    P2->IES &= ~pin_mask;

    // Clear Interrupt Flag
    P2->IFG = 0;

    // Allow interrupts to happen
    NVIC_EnableIRQ(PORT2_IRQn);
    __enable_interrupt();
}

void PORT3_IRQHandler(void) {
    uint8_t read = P3->IFG;
    P3->IFG = 0;

    bump_task(read);
}
