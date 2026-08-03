idf_component_register(SRCS "main.c" "../core/os.c" "../core/home_screen.c"
                    "../controllers/display.c" "../controllers/light.c" "../controllers/sound.c" "../controllers/storage.c"
                    INCLUDE_DIRS "." "../core" "../controllers"
                    REQUIRES esp_lcd)
