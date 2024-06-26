#include "detection_responder.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "esp_main.h"
#include "driver/gpio.h"

// Definir el pin del flash (ajusta el pin según tu configuración)
#define FLASH_PIN GPIO_NUM_33

#if DISPLAY_SUPPORT
#include "image_provider.h"
#include "bsp/esp-bsp.h"

#define IMG_WD (96 * 2)
#define IMG_HT (96 * 2)

static lv_obj_t *camera_canvas = NULL;
static lv_obj_t *bottle_indicator = NULL;
static lv_obj_t *label = NULL;

static void create_gui(void)
{
  bsp_display_start();
  bsp_display_backlight_on();
  bsp_display_lock(0);
  camera_canvas = lv_canvas_create(lv_scr_act());
  assert(camera_canvas);
  lv_obj_align(camera_canvas, LV_ALIGN_TOP_MID, 0, 0);

  bottle_indicator = lv_led_create(lv_scr_act());
  assert(bottle_indicator);
  lv_obj_align(bottle_indicator, LV_ALIGN_BOTTOM_MID, -70, 0);
  lv_led_set_color(bottle_indicator, lv_palette_main(LV_PALETTE_GREEN));

  label = lv_label_create(lv_scr_act());
  assert(label);
  lv_label_set_text_static(label, "Bottle detected");
  lv_obj_align_to(label, bottle_indicator, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
  bsp_display_unlock();
}
#endif // DISPLAY_SUPPORT

void setup_flash() {
    gpio_reset_pin(FLASH_PIN);
    gpio_set_direction(FLASH_PIN, GPIO_MODE_OUTPUT);
}

void RespondToDetection(float bottle_score, float no_bottle_score) {
    int bottle_score_int = static_cast<int>((bottle_score * 100) + 0.5);

    printf("Bottle Score: %d, No Bottle Score: %d\n", bottle_score_int, static_cast<int>(no_bottle_score * 100));

#if DISPLAY_SUPPORT
    if (!camera_canvas) {
        create_gui();
    }

    uint16_t *buf = (uint16_t *) image_provider_get_display_buf();

    bsp_display_lock(0);
    if (bottle_score_int < 60) {
        lv_led_off(bottle_indicator);
        gpio_set_level(FLASH_PIN, 0); // Apagar el flash
        printf("Flash OFF\n");
    } else {
        lv_led_on(bottle_indicator);
        gpio_set_level(FLASH_PIN, 1); // Encender el flash
        printf("Flash ON\n");
    }
    lv_canvas_set_buffer(camera_canvas, buf, IMG_WD, IMG_HT, LV_IMG_CF_TRUE_COLOR);
    bsp_display_unlock();
#else
    if (bottle_score_int < 60) {
        gpio_set_level(FLASH_PIN, 0); // Apagar el flash
        printf("Flash OFF\n");
    } else {
        gpio_set_level(FLASH_PIN, 1); // Encender el flash
        printf("Flash ON\n");
    }
#endif // DISPLAY_SUPPORT

}
