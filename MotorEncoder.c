#include "../MazeDrivers/MotorEncoder.h"


void MotorEncoder_Init(void) {

    left_encoder.count = 0;
    right_encoder.count = 0;

    // Set up as IO pins
    P2SEL0 &= ~(BIT7 | BIT6);
    P2SEL1 &= ~(BIT7 | BIT6);

    // 0 - Input
    P2DIR &= ~(BIT7 | BIT6);

    // Interrupt thing?
    P2OUT |= (BIT7 | BIT6);

    // Interrupt enable
    P2IE |= (BIT7 | BIT6);

    // Interrupt on falling edge
    P2IES |= (BIT7 | BIT6);

    // Enable pull-up resistor
    P2REN |= (BIT7 | BIT6);

    // Clear the interrupt flag
    P2IFG = 0;

    // Allow interrupts to happen
    NVIC_EnableIRQ(PORT2_IRQn);
    __enable_interrupt();

    return;

    TIMER_A0->CTL &= ~0x003;       // halt Timer A0
    // bits15-10=XXXXXX, reserved
    // bits9-8=10,       clock source to SMCLK
    // bits7-6=00,       input clock divider /4
    // bits5-4=00,       stop mode
    // bit3=X,           reserved
    // bit2=0,           set this bit to clear
    // bit1=X,           interrupt on timer
    // bit0=0,           clear interrupt flag

    TIMER_A0->CCR[3] = 0xFFF;
    TIMER_A0->CCR[4] = 0xFFF;

    // Pin 2.7
    P2->DIR &= ~(BIT7);
    P2->SEL1  &= ~(BIT7);
    P2->SEL0 |= BIT7;
    P2->REN |= (BIT7);
    TIMER_A0->CCTL[3] = 0x4DBA;// = 0x0280;
    // bits15-14=0X,     no capture mode
    // bits13-12=00,     capture on CCI0A
    // bit11=X,          synchronize capture source
    // bit10=X,          synchronized capture/compare input
    // bit9=X,           reserved
    // bit8=1,           enable capture
    // bits7-5=XXX,      output mode
    // bit4=1,           enable capture/compare interrupt on CCIFG
    // bit3=X,           read capture/compare input from here
    // bit2=0,           output this value in output mode 0
    // bit1=X,           capture overflow status
    // bit0=0,           clear capture/compare interrupt pending

    // Pin 2.6
    P2->DIR &= ~(BIT6);
    P2->SEL1  &= ~(BIT6);
    P2->SEL0 |= BIT6;
    P2->REN |= (BIT6);
    TIMER_A0->CCTL[4] = 0x4DBA;//0x0280;
    // bits15-14=0X,     no capture mode
    // bits13-12=X0,     capture on CCI3A
    // bit11=X,          synchronize capture source
    // bit10=X,          synchronized capture/compare input
    // bit9=X,           reserved
    // bit8=1,           enable capture
    // bits7-5=XXX,      output mode
    // bit4=1,           enable capture/compare interrupt on CCIFG
    // bit3=X,           read capture/compare input from here
    // bit2=0,           output this value in output mode 0
    // bit1=X,           capture overflow status
    // bit0=0,           clear capture/compare interrupt pending

    TIMER_A0->CTL = 0x7E2A;
    // bits 15-10=XXXXX,    reserved
    // bits 9-8=X0,         SMCLK
    // bits 7-6=00,         divider = 1
    // bits 5-4=10          continuous mode
    // bit 3=X              reserved
    // bit2=0,           set this bit to clear
    // bit1=X,           interrupt on timer
    // bit0=0,           clear interrupt flag

//    NVIC_EnableIRQ(TA0_N_IRQn);

}

motor_encoder_t* motor_encoder_get_right() {
    return &right_encoder;
}
motor_encoder_t* motor_encoder_get_left() {
    return &left_encoder;
}

void PORT2_IRQHandler(void) {
    uint8_t read = P2IFG;
    P2IFG = 0;
    if (read & BIT7) {
        right_encoder.count += 1;
    }
    if (read & BIT6) {
        left_encoder.count += 1;
    }
}

void TA0_N_IRQHandler(void) {
    // Clear the interrupt flag
    TIMER_A0->CTL &= ~1;

    // Find the channel that was interrupted
    if (TIMER_A0->IV & 0x6) { // Channel 1
        // Pin 2.7 was high
        uint32_t duration = TIMER_A0->CCR[3];
        left_encoder.count += 1;
        left_encoder.frequency = duration;
    } else if (TIMER_A0->IV & 0x8) {
        // Pin 2.6 was high
        uint32_t duration = TIMER_A0->CCR[4];
        right_encoder.count += 1;
        right_encoder.frequency = duration;
    }
}


