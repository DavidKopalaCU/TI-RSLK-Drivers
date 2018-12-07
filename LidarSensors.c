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
}

uint32_t lidar_right_read(void) {
    return ADC_In15();
}

uint32_t lidar_straight_read(void) {
    return 0;
}

uint32_t lidar_left_read(void) {
    return 0;
}
