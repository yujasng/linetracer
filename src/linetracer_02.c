#include <stdint.h>
#include <avr/io.h>
#include <pins.h>
#include <pi.c>


// sens type for each sensor  
typedef struct{
    uint16_t sensorVal;
    uint16_t norm_sensorVal;
    uint8_t weight;
}sens;


// norm type for calibration & normalization

typedef struct{
    uint16_t min;
    uint16_t max;
}norm;


typedef struct {
    uint16_t Kp;   // p gain
    uint16_t Ki;   // i gain
    uint16_t setpoint;     // value we aim
    uint16_t integral;     
    uint16_t prev_error;

}  PIController;



// read sensor (ADC)
uint16_t adc_read(uint8_t adcx){

    // set adc pin number that I want to read
    ADMUX &= 0xf0;

    ADMUX |= adcx;

    //start conversion
    ADCSRA |= _BV(ADSC);

    //when adc is enabled & conversion is enabled
    while((ADCSRA & _BV(ADSC)));
    
    return ADC;


}


void normalization(norm standard, sens* sensor){
    sensor->norm_sensorVal = ((sensor->sensorVal - standard.min )/ (standard.max - standard.min)) * 100; 

}

// calibration - noralizing sensor values between 0~100 
norm calibration(sens* sensor){
    
    
    norm cali[10];  
    norm ans; 

    for(uint8_t j = 0; j<10; j++){
        for(uint8_t i = 0; i<4; i++){
            sensor[i].sensorVal = adc_read(SENSOR[i]);
        }

        for(uint8_t i= 1 ; i<4; i++){    
            if(sensor[i].sensorVal > cali[j].max){
                cali[j].max = sensor[i].sensorVal;
            }
            else if(sensor[i].sensorVal < cali[j].min){
                cali[j].min = sensor[i].sensorVal;
            }

        }

        ans.max += cali[j].max;
        ans.min += cali[j].min;
    }

    ans.max /= 10;
    ans.min /= 10;

    return ans;

}

// Initializing PI control related values
void PI_Init(PIDController *pid, uint16_t Kp, uint16_t Ki, uint16_t Kd, uint16_t setpoint){

    pid -> Kp = Kp;
    pid -> Ki = Ki;
    pid -> setpoint = setpoint;
    pid -> integral = 0;
    pid -> prev_error = 0;

}


uint16_t PI_Compute(PIDController *pid, uint16_t current_value, uint16_t dt){
    uint16_t error = pid -> setpoint - current_value;
    pid -> integral += error * dt;
    uint16_t derivative = (error - pid -> prev_error) / dt;

    uint16_t output = (pid -> Kp * error) + (pid -> Ki * pid -> integral);
    pid -> prev_error = error;

    return output;
}

void run_Lmotor(uint16_t error){
    if(error > 0){

    }
}

void run_Rmotor(uint16_t error){

}

int main(){

    ADCSRA |= _BV(ADEN);    // enable adc
    ADMUX |= _BV(REFS0);    // set V_ref to 6V

    //set adc prescaler selection division factor as 128
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    


    DDRD |= _BV(L_motor) | _BV(R_motor);    // port d motor pins as output
    
    DDRD |= _BV(R_BACK) | _BV(R_FOR) | _BV(L_BACK) | _BV(L_FOR);



    TCCR0A |= _BV(WGM01) | _BV(WGM00);      // fast pwm mode 

    TCCR0A |= _BV(COM0A1) | _BV(COM0B1);  // clear OC0A on compare match & set OC0A at BOTTOM(non-inverting mode)

    TCCR0B |= _BV(CS01) | _BV(CS00);    // set clock / 64 (from prescaler)

    sens sensor[4];
    norm standard;
    PIController pi;

    for(uint8_t i = 0; i<4; i++){
        sensor[i].weight = -3 + 2*i;
    }    

    standard = calibration(sensor);


    for(uint16_t i = 0; i<4; i++){    
        normalization(standard,sensor+i);
        pi.setpoint += sensor[i].norm_sensorVal * sensor[i].weight;
    }    

    uint16_t Kp = ;
    uint16_t Ki = ;
    uint16_t Kd = ;
    uint16_t dt = ;

    PI_Init(&pi, Kp, Ki, Kd, pi.setpoint);

    for(;;){
        uint16_t current_Value = 0 ;
        
        for(uint8_t i = 0; i<4; i++){
            sensor[i].sensorVal = adc_read(SENSOR[i]);
            sensor[i].norm_sensorVal = normalization(standard, sensor+i);
            current_Value += sensor[i].norm_sensorVal * sensor[i].weight;
        }


        uint16_t result = PI_Compute(&pi, current_Value, dt);
        uint16_t error = result - pi.setpoint;

        // error > 0 -> line tracer is too 
        
        run_Lmotor(error);
        run_Rmotor(error);


    }



}






