idf_component_register(
  SRCS "main.c"
    "../src/drivers/display.c"
    "../src/drivers/led.c"
    "../src/drivers/sound.c"
    "../src/drivers/storage.c"
    "../src/os/os_kernel.c"
    "../src/os/os_manager.c"
    "../src/os/os_event.c"
    "../src/light_controller/light_controller.c"
    "../src/ui_controller/ui_controller.c"
    "../src/ui_controller/ui_definitions.c"


  INCLUDE_DIRS "../src"
    "../src/drivers"
    "../src/os"
    "../src/light_controller"
    "../src/ui_controller"

  REQUIRES esp_lcd esp_timer
)
