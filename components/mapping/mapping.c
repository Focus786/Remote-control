#include "mapping.h"

int motor_to_pwm(int motor_val)
{
    return PWM_MID_US + motor_val * (PWM_MAX_US - PWM_MIN_US) / 200;
}
