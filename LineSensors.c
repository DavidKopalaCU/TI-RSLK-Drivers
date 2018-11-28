#include "../MazeDrivers/LineSensors.h"

// Initialization Function
void Init_LineSensors(void) {
    line_sensor_count = 8;
    int i = 0;
    for (i = 0; i < line_sensor_count; i++) {
        line_sensors_add(line_sensors[i], P7, 1<<i);
    }
}

// Add a line sensor based on a PORT and a PIN
void line_sensors_add(line_sensor_t* line_sensor, DIO_PORT_Odd_Interruptable_Type* port, uint8_t bit) {
    line_sensor->port = port;
    line_sensor->bit = bit;

    line_sensors_add_sensor(line_sensor);
}

// Add a line sensor based on an already created struct
void line_sensors_add_sensor(line_sensor_t *line_sensor) {
    // Configure PIN to be GPIO
    line_sensor->port->SEL0 &= ~(line_sensor->bit);
    line_sensor->port->SEL1 &= ~(line_sensor->bit);

    // Configure PIN to be INPUT
    line_sensor->port->DIR &= ~(line_sensor->bit);

//    if (line_sensor_count+1 == MAX_LINE_SENSORS) {
//        printf("CANNOT ADD ANOTHER LINE SENSOR; Already at maximum quantity\n");
//        return;
//    }
//    line_sensors[line_sensor_count++] = line_sensor;
}

// Add line sensors that have all been configured on the same port
inline void line_sensors_add_port(DIO_PORT_Odd_Interruptable_Type* port) {
    int i;
    for (i = 0; i < 8; i++) {
        line_sensor_t line_sensor;
        line_sensors_add(&line_sensor, port, 1<<i);
    }
}

// Configure the IR LED
void line_sensor_config_ir_led(ir_led_t *ir, DIO_PORT_Odd_Interruptable_Type* port, uint8_t bit) {
    ir->port = port;
    ir->bit = bit;

    // Configure PIN to be GPIO
    ir->port->SEL0 &= ~(ir->bit);
    ir->port->SEL1 &= ~(ir->bit);

    // Configure PIN
    ir->port->DIR &= ~(ir->bit);

    // Set initially to HIGH
    ir->port->OUT |= ir->bit;

    ir_led = ir;
}

// Reset a line sensor; Allow the capacitor to recharge
void line_sensor_reset(line_sensor_t *line_sensor) {
    int i;  // FOR COUNTER

    // Set pin as OUTPUT
    line_sensor->port->DIR |= line_sensor->bit;

    // Set pin as HIGH
    line_sensor->port->OUT |= line_sensor->bit;

    // Turn off the ir_led
    if (ir_led != 0) {
        ir_led->port->OUT &= ~(ir_led->bit);
    }

    // Wait for the capacitor to recharge
    for(i = 0; i < 200; i++) {}

    // Turn ON the ir_led
    if (ir_led != 0) {
        ir_led->port->OUT |= ir_led->bit;
    }

    // Set PIN as INPUT
    line_sensor->port->DIR &= ~(line_sensor->bit);
}

// Reset ALL line sensors
void line_sensor_reset_all(void) {
    int i;
    for (i = 0; i < line_sensor_count; i++) {
        line_sensor_reset(line_sensors[i]);
    }
}

uint32_t line_sensor_read(line_sensor_t *line_sensor) {
    uint16_t start, stop;

    line_sensor_reset(line_sensor);

    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;

    start = 0;//SysTick->VAL;
    while(1) {
        if ((~(line_sensor->port->IN)) & (line_sensor->bit)) {
            stop = start - SysTick->VAL;
            break;
        }
    }

    return (stop - start);
}

uint8_t line_sensor_get_count() {
    return line_sensor_count;
}

line_sensor_t **line_sensors_get() {
    return line_sensors;
}
