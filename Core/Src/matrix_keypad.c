#include "matrix_keypad.h"

static keypad_InitTypeDef keypad_hw;
static volatile key_flags_t key_states[KEYPAD_ROWS][KEYPAD_COLS];
static volatile key_flags_t key_states_prev[KEYPAD_ROWS][KEYPAD_COLS];
static volatile bool key_raw_state[KEYPAD_ROWS][KEYPAD_COLS];
static volatile uint32_t key_last_time[KEYPAD_ROWS][KEYPAD_COLS];
static const uint32_t debounce_ms = 50;

void Keypad_init(keypad_InitTypeDef *keypad)
{
    keypad_hw = *keypad;
    for (uint8_t row = 0; row < KEYPAD_ROWS; ++row)
    {
        for (uint8_t col = 0; col < KEYPAD_COLS; ++col)
        {
            key_states[row][col].pressed = 0;
            key_states[row][col].rising = 0;
            key_states[row][col].falling = 0;
            key_states_prev[row][col].pressed = 0;
            key_states_prev[row][col].rising = 0;
            key_states_prev[row][col].falling = 0;
            key_last_time[row][col] = 0;
            key_raw_state[row][col] = 0;
        }
    }
}

void Keypad_scan()
{
    uint32_t current_time = HAL_GetTick();
    for (uint8_t row = 0; row < KEYPAD_ROWS; ++row)
    {
        HAL_GPIO_WritePin(keypad_hw.row_ports[row], keypad_hw.row_pins[row], GPIO_PIN_SET);
    }
    for (uint8_t row = 0; row < KEYPAD_ROWS; ++row)
    {
        HAL_GPIO_WritePin(keypad_hw.row_ports[row], keypad_hw.row_pins[row], GPIO_PIN_RESET);

        HAL_Delay(1);

        for (uint8_t col = 0; col < KEYPAD_COLS; ++col)
        {
            bool raw_pin_state = HAL_GPIO_ReadPin(keypad_hw.col_ports[col], keypad_hw.col_pins[col])
                    == GPIO_PIN_RESET;
            if (raw_pin_state != key_raw_state[row][col])
            {
                key_raw_state[row][col] = raw_pin_state;
                key_last_time[row][col] = current_time;
            }

            if (HAL_GetTick() - key_last_time[row][col] >= debounce_ms)
            {
                key_states_prev[row][col].pressed =
                                        key_states[row][col].pressed;

                key_states[row][col].pressed = raw_pin_state;

                key_states[row][col].rising =
                        (!key_states_prev[row][col].pressed && raw_pin_state);

                key_states[row][col].falling =
                        (key_states_prev[row][col].pressed && !raw_pin_state);
            }
            else
            {
                key_states[row][col].rising = false;
                key_states[row][col].falling = false;
            }
        }
        HAL_GPIO_WritePin(keypad_hw.row_ports[row], keypad_hw.row_pins[row], GPIO_PIN_SET);
    }


}

bool Keypad_keyIsPressed(uint8_t rows, uint8_t cols)
{
    return key_states[rows][cols].pressed;
}

bool Keypad_keyIsRising(uint8_t rows, uint8_t cols)
{
    return key_states[rows][cols].rising;
}

bool Keypad_keyIsFalling(uint8_t rows, uint8_t cols)
{
    return key_states[rows][cols].falling;
}

