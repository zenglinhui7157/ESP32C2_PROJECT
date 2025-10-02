#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_display.h"
static void app_display_task(void *pvParameters)
{
	while (1) {
		// 循环执行显示操作，可根据实际需求修改
		st7789_fill_screen(COLOR_RED);
		vTaskDelay(pdMS_TO_TICKS(1000));
		st7789_fill_screen(COLOR_GREEN);
		vTaskDelay(pdMS_TO_TICKS(1000));
		st7789_fill_screen(COLOR_BLUE);
		vTaskDelay(pdMS_TO_TICKS(1000));
		st7789_fill_screen(COLOR_WHITE);
		vTaskDelay(pdMS_TO_TICKS(1000));
		st7789_fill_screen(COLOR_BLACK);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


void app_display_init(void)
{
	ESP_LOGI(APP_DISPLAY_INIT_TAG, "app_display_init called");
	esp_err_t ret = st7789_init();
	if (ret == ESP_OK) {
		ESP_LOGI(APP_DISPLAY_INIT_TAG, "st7789_init success");
	} else {
		ESP_LOGE(APP_DISPLAY_INIT_TAG, "st7789_init failed: %d", ret);
	}
}

void app_display_fill(uint16_t color)
{
	ESP_LOGI(APP_DISPLAY_INIT_TAG, "fill screen color: 0x%04X", color);
	esp_err_t ret = st7789_fill_screen(color);
	if (ret == ESP_OK) {
		ESP_LOGI(APP_DISPLAY_INIT_TAG, "st7789_fill_screen success");
	} else {
		ESP_LOGE(APP_DISPLAY_INIT_TAG, "st7789_fill_screen failed: %d", ret);
	}
}
void app_display_start(void)
{
	app_display_init();
	xTaskCreate(app_display_task, "app_display_task", 4096, NULL, 5, NULL);
}
