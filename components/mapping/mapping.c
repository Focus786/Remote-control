#include "mapping.h"

void differential_drive(int throttle, int steering, int *left_out, int *right_out)
{
    int left  = throttle + steering;
    int right = throttle - steering;

    /* 限制在 ±OUTPUT_MAX 范围内（joystick 层已限制为 ±30） */
    if (left > Limit_Positive)   left = Limit_Positive;
    if (left < Limit_Negative)  left = Limit_Negative;
    if (right > Limit_Positive)  right = Limit_Positive;
    if (right < Limit_Negative) right = Limit_Negative;

    *left_out  = left;
    *right_out = right;
}


int motor_to_pwm(int motor_val)
{
    return PWM_MID_US + motor_val * (PWM_MAX_US - PWM_MIN_US) / 200;
}
