#include <stdint.h>
#include <avr/io.h>


#define ADC_PIN_0 0
#define ADC_PIN_1 1
#define ADC_PIN_2 2
#define ADC_PIN_3 3
#define ADC_PIN_4 4

#define LED_PIN PB0

#define ADC_THRESHOLD 512

uint16_t adc_read(uint8_t adcx);

int main(void){

    //enable ADC 
    ADCSRA |= _BV(ADEN);

    //port b data direction manager
    DDRB |= _BV(LED_PIN);

    for(;;){

        if(adc_read(ADC_PIN_0) > ADC_THRESHOLD){
            PORTB |= _BV(LED_PIN);
        }
        else {
            PORTB &= ~_BV(LED_PIN);
        }
    }

}




uint16_t adc_read(uint8_t adcx){

    // set adc pin number that I want to read
    ADMUX &= 0xf0;
    ADMUX |= adcx;

    //start conversion
    ADCSRA |= _BV(ADSC);

    //when adc is enabled & conversion is enabled
    while((ADCSRA & _BV(ADSC)));

    //return converted value 
    return ADC; 


}