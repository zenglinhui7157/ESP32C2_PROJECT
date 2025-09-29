#include "app_ble.h"
#include "app_btn.h"
#include "app_led.h"
#include "app_sensor.h"
#include "app_wifi.h"
#include "nvs_flash.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
	// 初始化 NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	app_ble_start();
	app_btn_start();
	app_led_start();
	app_sensor_start();
	app_wifi_start();

	while (1) {
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
