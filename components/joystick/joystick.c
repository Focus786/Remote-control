#include "joystick.h"


#define ADC_UNIT        ADC_UNIT_1
#define ADC_CHANNEL_L   ADC_CHANNEL_6       // 油门
#define ADC_CHANNEL_R   ADC_CHANNEL_7       // 转向
#define ADC_ATTEN       ADC_ATTEN_DB_12     // 0 ~ ~2900 mV
#define ADC_BITWIDTH    ADC_BITWIDTH_DEFAULT // 12 位 (0 ~ 4095)

#define ADC_MAX         4095
#define ADC_CENTER      (ADC_MAX / 2)       // 2047
#define DEAD_ZONE       200                 // 死区阈值
#define OUTPUT_MAX      100                 // 输出范围 ±100

static adc_oneshot_unit_handle_t adc_handle;


void adc_init(void)
{
    // 1. 创建 ADC 单元
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id = ADC_UNIT,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&unit_cfg, &adc_handle));

    // 2. 配置通道
    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH,
        .atten    = ADC_ATTEN,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_L, &chan_cfg));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_R, &chan_cfg));
}

/* 将原始ADC值映射到 -OUTPUT_MAX ~ OUTPUT_MAX，带死区 */
static int map_adc(int raw)
{
    int diff = raw - ADC_CENTER;

    if (diff > DEAD_ZONE) {
        return (diff - DEAD_ZONE) * OUTPUT_MAX / (ADC_MAX - ADC_CENTER - DEAD_ZONE);
    } else if (diff < -DEAD_ZONE) {
        return (diff + DEAD_ZONE) * OUTPUT_MAX / (ADC_CENTER - DEAD_ZONE);
    }
    return 0;
}

int joystick_get_throttle(void)
{
    int raw;
    adc_oneshot_read(adc_handle, ADC_CHANNEL_L, &raw);
    return map_adc(raw);
}

int joystick_get_steering(void)
{
    int raw;
    adc_oneshot_read(adc_handle, ADC_CHANNEL_R, &raw);
    return map_adc(raw);
}