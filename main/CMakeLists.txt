idf_component_register(
  SRCS "main.c"
    "../src/drivers/display.c"
    "../src/drivers/led.c"
    "../src/drivers/sound.c"
    "../src/drivers/storage.c"
    "../src/os/os_kernel.c"
    "../src/os/os_manager.c"
    "../src/os/os_event.c"
    "../src/os/controller/light_controller.c"
    "../src/os/controller/ui_controller.c"
    "../src/ui/ui_definitions.c"
    "../src/ui/ui_tables.c"
    "../src/ui/screen/screen_home.c"
    "../src/ui/screen/screen_light_select.c"
    "../src/ui/widget/color_picker.c"

  INCLUDE_DIRS "../src"
    "../src/drivers"
    "../src/os"
    "../src/os/controller"
    "../src/ui"
    "../src/ui/screen"
    "../src/ui/widget"

  REQUIRES esp_lcd esp_timer
)
