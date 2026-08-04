idf_component_register(
  SRCS "main.c"
    "../src/drivers/display.c"
    "../src/drivers/light.c"
    "../src/drivers/sound.c"
    "../src/drivers/storage.c"
    "../src/os/os.c"
    "../src/os/ui/style.c"
    "../src/os/ui/ui_manager.c"
    "../src/os/ui/view.c"

  INCLUDE_DIRS "../src"
    "../src/drivers"
    "../src/os"
    "../src/os/ui"

  REQUIRES esp_lcd esp_timer
)
