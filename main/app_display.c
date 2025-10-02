#include "LVGL/lvgl_port.h"
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_display.h"

static void app_display_task(void *pvParameters)
{
    // 等待LVGL完全初始化
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    ESP_LOGI("display", "Creating UI elements...");
    
    // 创建标签
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "LVGL Dynamic Test");
    
    // 设置标签样式 - 使用正确的部分选择器
    lv_obj_set_style_text_color(label, lv_color_hex(0xFF0000), LV_PART_MAIN);
    lv_obj_set_style_bg_color(label, lv_color_hex(0x00FF00), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(label, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_pad_all(label, 10, LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
    
    // 设置屏幕背景
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, LV_PART_MAIN);
    
    // 强制第一次刷新
    lv_refr_now(NULL);
    
    ESP_LOGI("display", "Starting dynamic update loop...");
    
    static int bg_toggle = 0;
    static int color_val = 0;
    static int count = 0;
    
    while (1) {
        count++;
        
        // 切换屏幕背景色
        bg_toggle = !bg_toggle;
        lv_color_t bg_color = bg_toggle ? lv_color_hex(0x0000FF) : lv_color_hex(0x800080);
        lv_obj_set_style_bg_color(lv_scr_act(), bg_color, LV_PART_MAIN);
        
        // 动态改变标签文字颜色
        color_val = (color_val + 10) % 256;
        lv_color_t text_color = lv_color_make(color_val, 255 - color_val, color_val);
        lv_obj_set_style_text_color(label, text_color, LV_PART_MAIN);
        
        // 动态改变标签背景颜色
        lv_color_t label_bg = lv_color_make(255 - color_val, color_val, 128);
        lv_obj_set_style_bg_color(label, label_bg, LV_PART_MAIN);
        
        // 更新标签文字显示当前状态
        char buffer[64];
        snprintf(buffer, sizeof(buffer), "Count: %d\nColor: %d\nBG: %s", 
                 count, color_val, bg_toggle ? "BLUE" : "PURPLE");
        lv_label_set_text(label, buffer);
        
        // 强制刷新 - 使用多种方法确保刷新
        lv_obj_invalidate(label);
        lv_obj_invalidate(lv_scr_act());
        lv_refr_now(NULL);
        
        ESP_LOGI("display", "Update - Count: %d, Color: %d, BG: %s", 
                 count, color_val, bg_toggle ? "BLUE" : "PURPLE");
        
        vTaskDelay(pdMS_TO_TICKS(2000)); // 2秒间隔更明显
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
    lvgl_port_init();
    lvgl_port_start();
    
    // 增大堆栈大小
    xTaskCreate(app_display_task, "app_display_task", 8192, NULL, 4, NULL);
}