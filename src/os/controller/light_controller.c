#include "light_controller.h"
#include "global.h"
#include "led.h"
#include "os_event.h"

static bool headlight_on = false;
static G_Color_ID headlight_color = G_COLOR_NONE;
static bool bodylight_on = false;
static G_Color_ID bodylight_color = G_COLOR_NONE;

void Light_Controller_Init(void) { LED_SetHeadlights(G_COLOR_NONE); }

// todo: add select which light and not just default to one selection
void Light_Controller_RX(OS_Event_t *os_event) {
  switch (os_event->event_id) {
  case OS_EVENT_LIGHT_SELECT:
    LED_SetHeadlights((G_Color_ID)os_event->payload);
    break;

  default:
    break;
  }

  // os_event->payload = Light_G_Color_ID
}
