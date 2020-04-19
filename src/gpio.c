/*
 * gpio.c
 *
 *  Created on: Dec 12, 2018
 *      Author: Dan Walkes
 */
#include "gpio.h"
#include "em_gpio.h"
#include <string.h>
#include "ble.h"
#include "gatt_db.h"
#include "em_core.h"
#include <stdbool.h>


/**
 * TODO: define these.  See the radio board user guide at https://www.silabs.com/documents/login/user-guides/ug279-brd4104a-user-guide.pdf
 * and GPIO documentation at https://siliconlabs.github.io/Gecko_SDK_Doc/efm32g/html/group__GPIO.html
 */

#define LED_port (gpioPortB)
#define LED_pin (12)
#define PB_port (gpioPortB)
#define PB_pin (11)

bool button_status = false;

void gpioInit()
{
	GPIO_DriveStrengthSet(LED_port, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(LED_port, LED_pin, gpioModeDisabled, true);
	GPIO_PinModeSet(PB_port, PB_pin, gpioModeInputPullFilter, true);

	// Enable IRQ for even numbered GPIO pins
	  NVIC_EnableIRQ(GPIO_ODD_IRQn);

	  // Enable both edge interrupts for PB0 pin
	  GPIO_IntConfig(PB_port, PB_pin, 1, 0, true);

}

void GPIO_ODD_IRQHandler(void)
{
  // Clear all odd pin interrupt flags
  GPIO_IntClear(_GPIO_IF_MASK);

  button_status = !button_status;

  if(button_status == true)GPIO_PinModeSet(LED_port, LED_pin, gpioModePushPull, true);
  else GPIO_PinModeSet(LED_port, LED_pin, gpioModeDisabled, false);


}
