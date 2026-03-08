#ifndef PINS_H
#define PINS_H

#include <avr/io.h>

// LED Pin
#define LED_PIN PB0  

// L298N Control Pins
#define L_motor PD5
#define L_FOR  PD2
#define L_BACK PD3

#define R_motor PD6
#define R_FOR PD4
#define R_BACK PD7

// IR Reflectance Sensor Pins
#define SENSOR_1 PC0
#define SENSOR_2 PC1
#define SENSOR_3 PC2
#define SENSOR_4 PC3


#endif