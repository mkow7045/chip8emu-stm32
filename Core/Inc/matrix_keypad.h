#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

typedef struct {
    bool pressed;
    bool rising;
    bool falling;
} key_flags_t;

typedef struct{
    GPIO_TypeDef* row_ports[KEYPAD_ROWS];
    uint16_t row_pins[KEYPAD_ROWS];
    GPIO_TypeDef* col_ports[KEYPAD_COLS];
    uint16_t col_pins[KEYPAD_COLS];
}keypad_InitTypeDef;

void Keypad_init(keypad_InitTypeDef* keypad);

void Keypad_scan();

bool Keypad_keyIsPressed(uint8_t rows, uint8_t cols);

bool Keypad_keyIsRising(uint8_t rows, uint8_t cols);

bool Keypad_keyIsFalling(uint8_t rows, uint8_t cols);


#endif
