#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "pins.h"

int main(void)
{
   
	// Pinmode OUTPUT
    DDRB |= _BV(LED_PIN);

    DDRD |= _BV(MOT_ENA_PIN);
    DDRD |= _BV(MOT_IN1_PIN);
    DDRD |= _BV(MOT_IN2_PIN);

	// Write 0 to MOT_ENA_PIN
    PORTD &=  ~_BV(MOT_ENA_PIN);   
	
	// Toggle LED's and Motor IN Pins.
    while (1) {
        PORTB |=  _BV(LED_PIN);   
    	PORTD |=  _BV(MOT_IN1_PIN);   
    	PORTD |=  _BV(MOT_IN2_PIN);   

        _delay_ms(500);

        PORTB &= ~_BV(LED_PIN);   
    	PORTD &= ~_BV(MOT_IN1_PIN);   
    	PORTD &= ~_BV(MOT_IN2_PIN);   
        _delay_ms(500);
    }
}
