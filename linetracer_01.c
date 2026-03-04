#include <stdint.h>
#include <avr/io.h>
#include <pins.h>

#define THRESHOLD 128

#define forward_val 200
#define turn_left_val 200
#define turn_right_val 200
#define backward_val 200 




void setup(){

    ADCSRA |= _BV(ADEN);    // enable adc
    ADMUX |= _BV(REFS0);    // set V_ref to 6V

    //set adc prescaler selection division factor as 128
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    


    DDRD |= _BV(L_motor) | _BV(R_motor);    // port d motor pins as output
    
    DDRD |= _BV(R_BACK) | _BV(R_FOR) | _BV(L_BACK) | _BV(L_FOR);



    TCCR0A |= _BV(WGM01) | _BV(WGM00);      // fast pwm mode 

    TCCR0A |= _BV(COM0A1) | _BV(COM0B1);  // clear OC0A on compare match & set OC0A at BOTTOM(non-inverting mode)

    TCCR0B |= _BV(CS01) | _BV(CS00);    // set clock / 64 (from prescaler)



}



void loop(){

    uint8_t sensor_1 = adc_read(SENSOR_1);
    uint8_t sensor_2 = adc_read(SENSOR_2);
    uint8_t sensor_3 = adc_read(SENSOR_3);
    uint8_t sensor_4 = adc_read(SENSOR_4);

    if(sensor_1 >THRESHOLD || sensor_2 > THRESHOLD){
        if(sensor_3<THRESHOLD && sensor_4 <THRESHOLD){
            turn_right();
        }
        else {
            forward(); 
        }

    }
    else {
        if(sensor_3 > THRESHOLD || sensor_4 > THRESHOLD){
            turn_left();
        }
        else{
            forward();
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

void forward(){

    PORTD |= _BV(L_FOR);
    PORTD &= ~_BV(L_BACK);

    PORTD |= _BV(R_FOR);
    PORTD &= ~_BV(R_BACK);

    OCR0B = forward_val;
    OCR0A = forward_val;

}

void turn_left (){

    PORTD |= _BV(L_FOR);
    PORTD &= ~_BV(L_BACK);

    PORTD &= ~_BV(R_FOR);
    PORTD &= ~_BV(R_BACK);

    OCR0B = turn_left_val;

}

void turn_right (){

    PORTD &= ~_BV(L_FOR);
    PORTD &= ~_BV(L_BACK);

    PORTD |= _BV(R_FOR);
    PORTD &= ~_BV(R_BACK);

    OCR0A = turn_right_val;

}

void backward(){

    PORTD &= ~_BV(L_FOR);
    PORTD |= _BV(L_BACK);

    PORTD &= ~_BV(R_FOR);
    PORTD |= _BV(R_BACK);

    OCR0B = backward_val;
    OCR0A = backward_val;

}
