#ifndef PINS_H
#define PINS_H

#include <avr/io.h>

// LED Pin
#define LED_PIN PB0  

// L298N Control Pins
#define MOT_ENA_PIN PD5
#define MOT_IN1_PIN PD2
#define MOT_IN2_PIN PD3

#define MOT_ENB_PIN PD6
#define MOT_IN3_PIN PD4
#define MOT_IN4_PIN PD7

// IR Reflectance Sensor Pins
#define SENS1_PIN PC0
#define SENS2_PIN PC1
#define SENS3_PIN PC2
#define SENS4_PIN PC3

#endif