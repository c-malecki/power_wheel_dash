#include "controller_light.h"
#include "driver_led.h"

static bool headlight_on = false;
static Sys_Color_ID headlight_color = G_COLOR_NONE;

static bool bodylight_on = false;
static Sys_Color_ID bodylight_color = G_COLOR_NONE;

void Light_Controller_Init(void) { LEDDriver_SetHeadlights(G_COLOR_NONE); }

// todo: add select which light and not just default to one selection
void Light_Controller_RX(Sys_Event_t *sys_event) {
  switch (sys_event->event_id) {
  case SYS_EVENT_LIGHT_SELECT: {
    // ESP_LOGI("LIGHT_CONTROLLER", "event received: SYS_EVENT_LIGHT_SELECT");
    headlight_color = (Sys_Color_ID)sys_event->payload;
    LEDDriver_SetHeadlights((Sys_Color_ID)sys_event->payload);
    break;
  }

  default:
    break;
  }
}
