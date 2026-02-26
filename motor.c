#include <stdint.h>
#include <avr/io.h>

#define L_motor PD5
#define R_motor PD6

#define ADC_LEFT 0
#define ADC_RIGHT 1

#define IN4 PD7
#define IN3 PD4
#define IN2 PD3
#define IN1 PD2



uint16_t adc_read(uint8_t adcx);


int main(void){

    ADCSRA |= _BV(ADEN);    // enable adc
    ADMUX |= _BV(REFS0);    // set V_ref to 5V

    //set adc prescaler selection division factor as 130
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    


    DDRD |= _BV(L_motor) | _BV(R_motor);    // port d motor pins as output
   
    DDRD |= _BV(IN1) | _BV(IN2) | _BV(IN3) | _BV(IN4);



    TCCR0A |= _BV(WGM01) | _BV(WGM00);      // fast pwm mode 

    TCCR0A |= _BV(COM0A1) | _BV(COM0B1);  // clear OC0A on compare match & set OC0A at BOTTOM(non-inverting mode)

    TCCR0B |= _BV(CS01) | _BV(CS00);    // set clock / 64 (from prescaler)




    for(;;){

        uint8_t left = adc_read(ADC_LEFT)/4;
        uint8_t right = adc_read(ADC_RIGHT)/4;

        OCR0B= left;    // otuput compare register b
        OCR0A = right;  //output compare register a 


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


