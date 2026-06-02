#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "joystick.h"
#include "mapping.h"
#include "espnow_pwm.h"

#define TAG "MAIN"

void app_main(void)
{
    adc_init();
    espnow_init();

    int tick = 0;

    while (1) {
        int throttle = joystick_get_throttle();
        int steering = joystick_get_steering();

        uint16_t throttle_us = motor_to_pwm(throttle);
        uint16_t steering_us = motor_to_pwm(steering);
        espnow_send(throttle_us, steering_us);

        if (++tick >= 25) {
            tick = 0;
            ESP_LOGI(TAG, "THR:%d(%dus) STR:%d(%dus)",
                     throttle, throttle_us, steering, steering_us);
        }

        vTaskDelay(pdMS_TO_TICKS(20)); // 50Hz
    }
}
