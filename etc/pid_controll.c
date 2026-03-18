#include<stdio.h>
#include<unistd.h>

#define DT 0.1f


typedef struct {
    float Kp;   // p gain
    float Ki;   // i gain
    float Kd;   // d gain
    float setpoint;     // value we aim
    float integral;     
    float prev_error;

}  PIDController;

void PID_Init(PIDController *pid, float Kp, float Ki, float Kd, float setpoint){

    pid -> Kp = Kp;
    pid -> Ki = Ki;
    pid -> Kd = Kd;
    pid -> setpoint = setpoint;
    pid -> integral = 0.0f;
    pid -> prev_error = 0.0f;

}

float PID_Compute(PIDController *pid, float current_value, float dt){
    float error = pid -> setpoint - current_value;
    pid -> integral += error * dt;
    float derivative = (error - pid -> prev_error) / dt;

    float output = (pid -> Kp * error) + (pid -> Ki * pid -> integral ) + (pid -> Kd * derivative);
    pid -> prev_error = error;

    return output;
}

int main(){

    PIDController pid;
    PID_Init(&pid, 1.0f, 0.1f, 0.05f, 100.0f); // Kp, Ki, Kd, setpoint 

    float current_value = 0.0f;
    float control_signal;

    printf("Step\t Current Value\t Control Signal\n");
    
    for(int step = 0; step <1000; step++){
        
        control_signal = PID_Compute(&pid, current_value, DT);

        current_value += control_signal * DT;

        printf("%d\t , %.2f\t, %.2f\n",step, current_value, control_signal);

        usleep(DT * 100000);


    }

    return 0;

}