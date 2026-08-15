#include "light_controller.h"
#include "led.h"

static bool headlight_on = false;
static LED_Color_ID headlight_color = LED_COLOR_NONE;
static bool bodylight_on = false;
static LED_Color_ID bodylight_color = LED_COLOR_NONE;

void Light_Controller_Init(void) {}

void Light_Controller_RX(OS_Event_t *os_event) {
  LED_Color_ID color_id;

  // os_event->payload = Light_LED_Color_ID
}
