idf_component_register(SRCS "main.c"
                    "../lib/display/display.c" "../lib/display/home_screen.c" "../lib/display/ui.c"
                    "../lib/light/light.c"
                    "../lib/sound/sound.c"
                    INCLUDE_DIRS "." "../lib/display" "../lib/light" "../lib/sound"
                    REQUIRES esp_lcd)
