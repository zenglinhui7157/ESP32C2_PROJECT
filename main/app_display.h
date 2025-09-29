#ifndef _APP_DISPLAY_H_
#define _APP_DISPLAY_H_

#include "esp_log.h"
#include "ST7789/st7789.h"

#define APP_DISPLAY_INIT_TAG "app_display_init"

void app_display_init(void);
void app_display_fill(uint16_t color);

#endif
