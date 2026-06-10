#ifndef _ESPNOW_PWM_H_
#define _ESPNOW_PWM_H_

#include <stdint.h>
#include "esp_err.h"

void espnow_init(void);
void espnow_send(uint16_t throttle_us, uint16_t steering_us);

#endif
