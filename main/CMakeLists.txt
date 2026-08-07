idf_component_register(
  SRCS "main.c"
    "../src/drivers/display.c"
    "../src/drivers/led.c"
    "../src/drivers/sound.c"
    "../src/drivers/storage.c"
    "../src/system/system_controller.c"
    "../src/system/ui_controller.c"
    "../src/system/light_controller.c"

  INCLUDE_DIRS "../src"
    "../src/drivers"
    "../src/system"

  REQUIRES esp_lcd esp_timer
)
