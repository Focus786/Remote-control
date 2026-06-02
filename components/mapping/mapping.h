#ifndef _MAPPING_H_
#define _MAPPING_H_

#define PWM_MIN_US  1000
#define PWM_MID_US  1500
#define PWM_MAX_US  2000

void differential_mix(int throttle, int steering, int *motor_l, int *motor_r);
int  motor_to_pwm(int motor_val);

#endif
