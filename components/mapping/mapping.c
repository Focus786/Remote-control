#include "mapping.h"

static int clamp(int val, int min, int max)
{
    if (val > max) return max;
    if (val < min) return min;
    return val;
}

void differential_mix(int throttle, int steering, int *motor_l, int *motor_r)
{
    *motor_l = clamp(throttle + steering, -100, 100);
    *motor_r = clamp(throttle - steering, -100, 100);
}

int motor_to_pwm(int motor_val)
{
    return PWM_MID_US + motor_val * (PWM_MAX_US - PWM_MIN_US) / 200;
}
