/*
 * LiderSensors.h
 *
 *  Created on: Dec 7, 2018
 *      Author: davidkopala
 */

#include <stdint.h>

#ifndef LIDARSENSORS_H_
#define LIDARSENSORS_H_

void LidarSensors_Init(void);

uint32_t lidar_right_read(void);
uint32_t lidar_forward_read(void);
uint32_t lidar_left_read(void);

#endif /* LIDARSENSORS_H_ */
