idf_component_register(
  SRCS "main.c"
    "../src/data_types.c"
    "../src/drivers/display.c"
    "../src/drivers/led.c"
    "../src/drivers/sound.c"
    "../src/drivers/storage.c"
    "../src/os/os.c"
    "../src/os/car_manager.c"
    "../src/os/event_manager.c"
    "../src/os/media_manager.c"
    "../src/os/view_manager.c"
    "../src/ui/element/home_button.c"
    "../src/ui/element/nav_button.c"
    "../src/ui/view/home.c"
    "../src/ui/view/light_menu.c"
    "../src/ui/view/light_control.c"

  INCLUDE_DIRS "../src"
    "../src/drivers"
    "../src/os"
    "../src/ui"
    "../src/ui/element"
    "../src/ui/view"

  REQUIRES esp_lcd esp_timer
)
