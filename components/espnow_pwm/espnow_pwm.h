#ifndef _ESPNOW_PWM_H_
#define _ESPNOW_PWM_H_

#include <stdint.h>
#include "esp_err.h"

void espnow_init(void);
void espnow_send(uint16_t motor_l_us, uint16_t motor_r_us);

#endif
