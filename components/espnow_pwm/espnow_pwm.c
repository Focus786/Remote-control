#include "espnow_pwm.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include <string.h>

#define TAG "ESPNOW"

/* 接收端 MAC 地址，按实际修改 */
static const uint8_t RX_MAC[] = {0x28, 0x84, 0x85, 0x48, 0x47, 0x7c};

typedef struct {
    uint16_t throttle_us;
    uint16_t steering_us;
} __attribute__((packed)) espnow_data_t;

static void send_cb(const esp_now_send_info_t *tx_info, esp_now_send_status_t status)
{
    if (status != ESP_NOW_SEND_SUCCESS) {
        ESP_LOGW(TAG, "send failed");
    }
}

void espnow_init(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_send_cb(send_cb));

    esp_now_peer_info_t peer = {
        .channel = 0,
        .ifidx   = WIFI_IF_STA,
        .encrypt = false,
    };
    memcpy(peer.peer_addr, RX_MAC, 6);
    ESP_ERROR_CHECK(esp_now_add_peer(&peer));
}

void espnow_send(uint16_t throttle_us, uint16_t steering_us)
{
    espnow_data_t data = {
        .throttle_us = throttle_us,
        .steering_us = steering_us,
    };
    esp_err_t ret = esp_now_send(RX_MAC, (uint8_t *)&data, sizeof(data));
    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "esp_now_send failed: %s", esp_err_to_name(ret));
    }
}
