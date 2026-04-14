# STM32_LL_LCD_Driver
Hi!
I'm trying to make Driver for the LCD ST7735S Display. I'm doing it on STM32F401RE Nucleo board using LL libraries.

The problem is that LCD doesn't work as intended.
Right now it only works properly when Logic analyzer is also connected to the
board. When it's not connected, it displays only white screen. I connected the Logic analyzer to all the signal pins.

## Connections 

<img width="1950" height="1174" alt="image" src="https://github.com/user-attachments/assets/33e789ec-dc2d-4e42-83ee-e940f9923703" />

VCC - 3.3V
GND - GND
DIN - PA6 (MISO)
CLK - PA5 (SCK)
CS - PA9
DC - PA1
RST - PA3

Screen from the logic analyzer, right after clicking reset on the board:

<img width="2170" height="341" alt="image" src="https://github.com/user-attachments/assets/3d7f7c0d-808d-4376-a95b-28bbc28a15ed" />
