#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "mapping.h"

void adc_init(void);
int  joystick_get_throttle(void);
int  joystick_get_steering(void);

#endif

