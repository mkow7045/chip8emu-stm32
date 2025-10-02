#include "altMain.hpp"
#include "main.h"
#include "common.h"
#include "interpreter.h"
#include "games.h"

#define ROW_PORTS {ROW1_GPIO_Port, ROW2_GPIO_Port, ROW3_GPIO_Port, ROW4_GPIO_Port}
#define ROW_PINS  {ROW1_Pin, ROW2_Pin, ROW3_Pin, ROW4_Pin}

#define COL_PORTS {COL1_GPIO_Port, COL2_GPIO_Port, COL3_GPIO_Port, COL4_GPIO_Port}
#define COL_PINS  {COL1_Pin, COL2_Pin, COL3_Pin, COL4_Pin}

std::array<std::array<bool, 32>, 64> g_Display;

uint8_t update60Hz = 0;
uint8_t update30Hz = 0;
uint8_t update1000Hz = 0;

uint8_t screen_tick = 0;

uint8_t current_game = 1;
uint8_t check_game = 0;

extern "C"
{
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim6)
    {
        update60Hz = 1;

        ++screen_tick;
        if (screen_tick > 2)
        {
            update30Hz = 1;
            screen_tick = 0;
        }
    }

    if (htim == &htim7)
    {
        update1000Hz = 1;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
    if (GPIO_PIN == B1_Pin)
    {
        ++current_game;
        check_game = 1;
    }
}
}

void clear_screen()
{
    for (int row = 0; row < g_Display.front().size(); ++row)
    {
        for (int col = 0; col < g_Display.size(); ++col)
        {
           g_Display[col][row] = 0;
        }
    }
}

void setup()
{
    HAL_TIM_Base_Start_IT(&htim6);
    HAL_TIM_Base_Start_IT(&htim7);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    ssd1306_Init();
    keypad_InitTypeDef keypad =
    { .row_ports = ROW_PORTS, .row_pins = ROW_PINS, .col_ports = COL_PORTS,
            .col_pins = COL_PINS };

    Keypad_init(&keypad);
    RetargetInit(&huart2);
}

void loop()
{
    Interpreter interpreter
    { };
    interpreter.loadGame(game1, game1_size);

    while (1)
    {
        if (check_game)
        {
            clear_screen();
            switch (current_game)
            {
            case 0:
                interpreter = Interpreter();
                clear_screen();
                interpreter.loadGame(game1, game1_size);
                ++current_game;
                break;
            case 1:
                interpreter = Interpreter();
                clear_screen();
                interpreter.loadGame(game2, game2_size);
                ++current_game;
                break;
            case 2:
                interpreter = Interpreter();
                clear_screen();
                interpreter.loadGame(game3, game3_size);
                current_game = 0;
                break;
            default:
                break;
            }
        }

        if (update60Hz)
        {
            interpreter.decreaseDT();
            interpreter.decreaseST();
            update60Hz = 0;
        }

        if (interpreter.getST() > 0)
        {
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 900);
        }
        else
        {
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
        }

        Keypad_scan();

        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                if (Keypad_keyIsRising(row, col))
                {
                    interpreter.setKey(row * 4 + col, 1);
                }
            }
        }

        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                if (Keypad_keyIsFalling(row, col))
                {
                    interpreter.setKey(row * 4 + col, 0);
                }
            }
        }

        if (update1000Hz)
        {
            interpreter.executeCycles(10);
            update1000Hz = 0;
        }

        if (update30Hz)
        {
            ssd1306_Fill(Black);
            for (int row = 0; row < g_Display.front().size(); ++row)
            {
                for (int col = 0; col < g_Display.size(); ++col)
                {
                    if (g_Display[col][row] == 1)
                    {
                        ssd1306_DrawPixel(col * 2, row * 2, White);
                        ssd1306_DrawPixel((col * 2) + 1, row * 2, White);
                        ssd1306_DrawPixel(col * 2, (row * 2) + 1, White);
                        ssd1306_DrawPixel((col * 2) + 1, (row * 2) + 1, White);
                    }
                }
            }
            ssd1306_UpdateScreen();
            update30Hz = 0;
        }
    };
}
