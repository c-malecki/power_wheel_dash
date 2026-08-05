#include "car_manager.h"
#include "led.h"

// todo: relay control, switches for lights

static Car_Manager_t car_manager;

void Car_Manager_Init(void) {
  car_manager.hll_strip_id = LED_STRIP_HL_L_ID;
  car_manager.hlr_strip_id = LED_STRIP_HL_R_ID;
  car_manager.body_strip_id = LED_STRIP_BODY_ID;
}

void Car_Manager_SetLED(DATA_TYPE_ID_LEDStrips led_strip_id,
                        DATA_TYPE_ID_LEDColors led_color_id,
                        bool led_strip_on) {
  LED_SetColor(led_strip_id, led_color_id);

  switch (led_strip_id) {
  case LED_STRIP_HL_L_ID:
    car_manager.hll_strip_id = led_color_id;
    car_manager.hll_is_on = led_strip_on;
    break;

  case LED_STRIP_HL_R_ID:
    car_manager.hlr_strip_id = led_color_id;
    car_manager.hlr_is_on = led_strip_on;
    break;

  case LED_STRIP_BODY_ID:
    car_manager.body_strip_id = led_color_id;
    car_manager.body_is_on = led_strip_on;
    break;
  }
}