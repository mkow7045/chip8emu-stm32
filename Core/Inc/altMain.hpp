#ifndef INC_ALTMAIN_HPP_
#define INC_ALTMAIN_HPP_


#ifdef __cplusplus
extern "C"
{
#endif
// START C-BLOCK IN C++ CODE

/* Includes ------------------------------------------------------------------*/
#include "ssd1306.h"
#include "ssd1306_tests.h"
#include "matrix_keypad.h"
#include "usart.h"
#include "tim.h"
#include "retarget.h"
#include "stm32f4xx_hal.h"
#include "gpio.h"
// YOUR INCLUDES


/* Functions -----------------------------------------------------------------*/
void setup();
void loop();
// YOUR FUNCTIONS


// END C-BLOCK IN C++ CODE
#ifdef __cplusplus
}
#endif


#endif /* INC_ALTMAIN_HPP_ */
