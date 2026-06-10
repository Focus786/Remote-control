#ifndef _MAPPING_H_
#define _MAPPING_H_

#define PWM_MIN_US  1000
#define PWM_MID_US  1500
#define PWM_MAX_US  2000


extern int Limit_Positive;
extern int Limit_Negative;

int  motor_to_pwm(int motor_val);
void differential_drive(int throttle, int steering, int *left_out, int *right_out);


#endif
