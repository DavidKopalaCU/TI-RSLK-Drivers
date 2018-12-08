/*
 * LidarSensors.c
 *
 *  Created on: Dec 7, 2018
 *      Author: davidkopala
 */

// Right Sensor -> A6 Pin 6.0

#include "../MazeDrivers/LidarSensors.h"
#include "../inc/ADC14.h"

void LidarSensors_Init(void) {
    ADC0_InitSWTriggerCh15();
    ADC0_InitSWTriggerCh14();
    ADC0_InitSWTriggerCh16();
}

uint32_t lidar_forward_read(void) {
    return ADC_In15();
}

uint32_t lidar_right_read(void) {
    return ADC_In16();
}

uint32_t lidar_left_read(void) {
    return ADC_In14();
}
