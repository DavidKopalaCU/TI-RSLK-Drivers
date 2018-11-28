/*
 * LineSensors.h
 *
 *  Created on: Nov 14, 2018
 *      Author: davidkopala
 */


#ifndef LINESENSORS_H_
#define LINESENSORS_H_

#include <stdint.h>

#include "msp.h"
#include "../inc/SysTick.h"

#define MAX_LINE_SENSORS 8

typedef struct line_sensor {
    DIO_PORT_Odd_Interruptable_Type* port;
    uint8_t bit;

    uint32_t cal_value;
} line_sensor_t;

typedef struct ir_led {
    DIO_PORT_Odd_Interruptable_Type* port;
    uint8_t bit;
} ir_led_t;

// Initialization Function
void Init_LineSensors(void);

// Add a line sensor based on a PORT and a PIN
void line_sensors_add(line_sensor_t* line_sensor, DIO_PORT_Odd_Interruptable_Type* port, uint8_t bit);

// Add a line sensor based on an already created struct
void line_sensors_add_sensor(line_sensor_t *sensor);

// Add line sensors that have all been configured on the same port
inline void line_sensors_add_port(DIO_PORT_Odd_Interruptable_Type* port);

// Configure the IR LED
void line_sensor_config_ir_led(ir_led_t *ir_led, DIO_PORT_Odd_Interruptable_Type* port, uint8_t bit);

// Reset a line sensor; Allow the capacitor to recharge
void line_sensor_reset(line_sensor_t *line_sensor);

// Reset ALL line sensors
void line_sensor_reset_all(void);

uint32_t line_sensor_read(line_sensor_t *line_sensor);

static volatile  uint8_t line_sensor_count = 0;
uint8_t line_sensor_get_count();
static line_sensor_t *line_sensors[MAX_LINE_SENSORS];
line_sensor_t **line_sensors_get();

ir_led_t *ir_led;


#endif /* LINESENSORS_H_ */
