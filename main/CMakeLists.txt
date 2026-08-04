idf_component_register(
  SRCS "main.c"
    "../src/os.c"
    "../src/display/display.c"
    "../src/ui/home.c"
    "../src/ui/light_control.c"
    "../src/ui/ui.c"
    "../src/light/light.c"
    "../src/sound/sound.c"
    "../src/storage/storage.c"

  INCLUDE_DIRS "../src"
    "../src/display"
    "../src/light"
    "../src/sound"
    "../src/storage"
    "../src/ui"

  REQUIRES esp_lcd esp_timer
)
