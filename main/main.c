#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "joystick.h"
#include "mapping.h"
#include "espnow_pwm.h"

#define TAG "MAIN"


const int OUTPUT_MAX = 30;
const int Limit_Positive = OUTPUT_MAX;
const int Limit_Negative = -OUTPUT_MAX;


void app_main(void)
{
    adc_init();
    espnow_init();

    int tick = 0;

    while (1) {
        int throttle = joystick_get_throttle();   // 范围 ±30
        int steering = joystick_get_steering();   // 范围 ±30

        int left_val, right_val;
        differential_drive(throttle, steering, &left_val, &right_val);

        uint16_t throttle_us = motor_to_pwm(left_val);
        uint16_t steering_us = motor_to_pwm(right_val);
        espnow_send(throttle_us, steering_us);

        if (++tick >= 25) {
            tick = 0;
            ESP_LOGI(TAG, "THR:%d STR:%d | L:%d(%dus) R:%d(%dus)",
                     throttle, steering, left_val, throttle_us, right_val, steering_us);
        }

        vTaskDelay(pdMS_TO_TICKS(20)); // 50Hz
    }
}
