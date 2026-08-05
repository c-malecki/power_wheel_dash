idf_component_register(
  SRCS "main.c"
    "../src/drivers/display.c"
    "../src/drivers/light.c"
    "../src/drivers/sound.c"
    "../src/drivers/storage.c"
    "../src/os/os.c"
    "../src/os/view_manager.c"
    "../src/ui/ui.c"
    "../src/ui/element/home_button.c"
    "../src/ui/element/nav_button.c"
    "../src/ui/view/home.c"
    "../src/ui/view/lights.c"

  INCLUDE_DIRS "../src"
    "../src/drivers"
    "../src/os"
    "../src/ui"
    "../src/ui/element"
    "../src/ui/view"

  REQUIRES esp_lcd esp_timer
)
