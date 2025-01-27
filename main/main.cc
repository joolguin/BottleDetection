#include "main_functions.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_main.h"



#if CLI_ONLY_INFERENCE
#include "esp_cli.h"
#endif

void tf_main(void) {
  setup();
#if CLI_ONLY_INFERENCE
  esp_cli_start();
  vTaskDelay(portMAX_DELAY);
#else
  while (true) {
    loop();
  }
#endif
}

extern "C" void app_main() {
  xTaskCreate((TaskFunction_t)&tf_main, "tf_main", 4 * 1024, NULL, 8, NULL);
  vTaskDelete(NULL);
}
