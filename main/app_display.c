#include "app_display.h"

void app_display_init(void)
{
	ESP_LOGI(APP_DISPLAY_INIT_TAG, "app_display_init called");
	st7789_init();
}

void app_display_fill(uint16_t color)
{
	ESP_LOGI(APP_DISPLAY_INIT_TAG, "fill screen color: 0x%04X", color);
	st7789_fill_screen(color);
}
void app_display_start(void)
{
	app_display_init();

	// 依次填充不同颜色，便于观察
	st7789_fill_screen(COLOR_RED);
	vTaskDelay(pdMS_TO_TICKS(500));
	st7789_fill_screen(COLOR_GREEN);
	vTaskDelay(pdMS_TO_TICKS(500));
	st7789_fill_screen(COLOR_BLUE);
	vTaskDelay(pdMS_TO_TICKS(500));
	st7789_fill_screen(COLOR_WHITE);
	vTaskDelay(pdMS_TO_TICKS(500));
	st7789_fill_screen(COLOR_BLACK);

	// 画点测试
	for (int i = 0; i < 20; i++) {
		st7789_draw_pixel(10 + i * 10, 10 + i * 10, COLOR_RED);
	}
}
