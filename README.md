# CHIP-8 Emulator on STM32  
*A CHIP-8 emulator, ported to the STM32 F446RE microcontroller.*  

[Watch the showcase video](https://youtu.be/00CG12AI1-k)

## Overview  
This project implements an emulator for the CHIP‑8 language. The CHIP-8 was designed in the 1970s and uses simple graphics (64×32 pixels) and keypad input.  
In this version, the emulator is deployed on the STM32F446RE microcontroller (Cortex-M4), using STM32 HAL.

## Hardware & Software Requirements  
- **MCU**: STM32F446RE board (e.g., Nucleo-F446RE)
- **Build**: STM32CubeIDE  
- **Flash**: Use ST-Link or other supported programmer to upload to MCU  

### How to run
1. Open the `.ioc` project file with STM32CubeIDE
2. Ensure peripherals are configured (GPIO and I2C)  
3. Build the project and flash the binary to the MCU via ST-Link  
4. Connect keypad,display and speaker

## Emulation Details & Notes  
- The interpreter fetches a 16-bit opcode every cycle from memory starting at 0x200.  
- The `delay_timer` and `sound_timer` decrement at 60 Hz
- Graphics buffer: 64×32 monochrome, each pixel is either on/off. On STM32 target this uses a simple buffer and sends it to display via I2C.  
- 16 button keypad for input
- Sound via active buzzer.
- Known limitations: does not yet implement game switching, won't work with programs starting at 0x600.

## Why I built this  
As part of my embedded systems and firmware work I wanted to deepen my understanding of how interpreted virtual machines map onto constrained hardware. By building the CHIP-8 emulator first on desktop and then porting it to a microcontroller, I sharpened my skills in: pointer and memory management, hardware timers, low-level C++ logic, and cross‐platform toolchains.  

## Future Work  
- Add support for SCHIP (Super-CHIP) extensions (128×64 display, additional opcodes)  
- Add game switching and support for multiple games in memory

## License  
This project is open-source under the MIT License – see [LICENSE](LICENSE) file for details.


