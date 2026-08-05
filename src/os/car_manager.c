#include "car_manager.h"
#include "led.h"

// todo: relay control, switches for lights

static Car_Manager_t car_manager;

void Car_Manager_Init(void) {
  car_manager.headlight_left.light_id = CAR_LIGHT_ID_HLL;
  car_manager.headlight_right.light_id = CAR_LIGHT_ID_HLR;
  car_manager.bodylight.light_id = CAR_LIGHT_ID_BODY;
}

void Car_Manager_SetLight(Car_Light_IDs car_light_id,
                          Car_Light_Color_IDs car_light_color_id,
                          bool car_light_on) {
  LED_SetColor(car_light_id, car_light_color_id);

  switch (car_light_id) {
  case CAR_LIGHT_ID_HLL:
    car_manager.headlight_left.color_id = car_light_color_id;
    car_manager.headlight_left.is_on = car_light_on;
    break;

  case CAR_LIGHT_ID_HLR:
    car_manager.headlight_right.color_id = car_light_color_id;
    car_manager.headlight_right.is_on = car_light_on;
    break;

  case CAR_LIGHT_ID_BODY:
    car_manager.bodylight.color_id = car_light_color_id;
    car_manager.bodylight.is_on = car_light_on;
    break;
  }
}