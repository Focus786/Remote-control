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

        int motor_l, motor_r;
        differential_mix(throttle, steering, &motor_l, &motor_r);

        uint16_t pwm_l = motor_to_pwm(motor_l);
        uint16_t pwm_r = motor_to_pwm(motor_r);
        espnow_send(pwm_l, pwm_r);

        if (++tick >= 25) {
            tick = 0;
            ESP_LOGI(TAG, "THR:%d STR:%d | L:%d(%dus) R:%d(%dus)",
                     throttle, steering,
                     motor_l, pwm_l, motor_r, pwm_r);
        }

        vTaskDelay(pdMS_TO_TICKS(20)); // 50Hz
    }
}
