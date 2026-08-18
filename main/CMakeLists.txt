idf_component_register(
  SRCS "main.c"
    "../src/global.c"
    "../src/drivers/driver_display.c"
    "../src/drivers/driver_led.c"
    "../src/drivers/driver_sound.c"
    "../src/drivers/driver_storage.c"
    "../src/os/os_kernel.c"
    "../src/os/os_manager.c"
    "../src/os/controller/controller_light.c"
    "../src/os/controller/controller_sound.c"
    "../src/os/controller/controller_ui.c"
    "../src/ui/ui_definitions.c"
    "../src/ui/ui_tables.c"
    "../src/ui/screen/screen_home.c"
    "../src/ui/screen/screen_light.c"
    "../src/ui/screen/screen_sound.c"
    "../src/ui/widget/color_picker.c"

  INCLUDE_DIRS "../src"
    "../src/drivers"
    "../src/os"
    "../src/os/controller"
    "../src/ui"
    "../src/ui/screen"
    "../src/ui/widget"

  REQUIRES esp_lcd esp_timer esp_driver_sdmmc esp_driver_i2s fatfs
)
