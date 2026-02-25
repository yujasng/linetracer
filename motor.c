#include <stdint.h>
#include <avr/io.h>

#define L_motor PD5
#define R_motor PD6

#define ADC_LEFT 0
#define ADC_RIGHT 1

#define ADC_THRESHOLD 512


uint16_t adc_read(uint8_t adcx);


int main(void){

    ADCSRA |= _BV(ADEN);    // enable adc

    DDRD |= _BV(L_motor);    // port d motor pins as output
    DDRD |= _BV(R_motor);
    

    for(;;){


        if(adc_read(ADC_LEFT) > ADC_THRESHOLD){
            PORTD |= _BV(L_motor);
        }
        else{
            PORTD &= ~_BV(L_motor);
        }
        


        if(adc_read(ADC_RIGHT) > ADC_THRESHOLD){
            PORTD |= _BV(R_motor);
        }
        else{
            PORTD &= ~_BV(R_motor);
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


