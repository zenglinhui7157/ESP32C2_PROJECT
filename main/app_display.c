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
