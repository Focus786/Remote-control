# 统一管理所有 components 的源文件
idf_component_register(
    SRCS
        "joystick/joystick.c"
        "mapping/mapping.c"
        "espnow_pwm/espnow_pwm.c"
    INCLUDE_DIRS
        "joystick"
        "mapping"
        "espnow_pwm"
    REQUIRES
        esp_adc
        esp_wifi
        nvs_flash
)