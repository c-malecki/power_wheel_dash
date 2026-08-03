idf_component_register(
  SRCS "main.c"
    "../core/os.c"
    "../peripherals/display.c" "../peripherals/light.c" "../peripherals/sound.c" "../peripherals/storage.c"
    "../screens/home.c" "../screens/light_control.c"

  INCLUDE_DIRS "."
    "../core"
    "../peripherals"
    "../screens"

  REQUIRES esp_lcd
)
