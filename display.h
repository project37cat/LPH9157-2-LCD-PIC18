// name: Color LCD interface with PIC18
//
// file: display.h  25-Feb-2016
//
// compiler: "HI-TECH C PRO for the PIC18 MCU Family  V9.63PL3"
//
//
// PIC18LF4320 MCU 12MHz +5V
//
// 132*176 LCD "LPH9157-2" ("Siemens ME75" cell phone)
//
// @@@@@@@@@@@@
// @0         @
// @   LCD    @
// @        1 @
// @        7 @
// @        6 @
// @    132   @
// @@@@@@@@@@@@
//  ||||||||||
// 10         1
//
// 10-wire interface:
//
// 01 RS   <- 16k--12k <- MCU PORTD7 (digital output)
// 02 RST  <- 16k--12k <- MCU PORTD6 (digital output)
// 03 CS   <- GND
// 04 SYNC -- NOT USED
// 05 CLK  <- 16k--12k <- MCU PORTD4 (digital output)
// 06 DAT  <- 16k--12k <- MCU PORTD3 (digital output)
// 07 Vdd  <- +2.9V TL431 <- MCU PORTC0 (digital output)
// 08 GND  <- GND
// 09 LED+ <- +12V booster <- MCU PORTC1 (CCP2 PWM output ~3kHz)
// 10 LED- <- GND
//


#define _XTAL_FREQ 12000000

#include <htc.h>


// brightness of LCD Backlight //30-min. comfort  //max. tested 70 - 13V  //for 3 kHz
#define PWM 30
// ~20us

// pin for LCD power supply (circuit with TL431, output: +2.9V, 1mA)
#define LCD_PWR_PIN   0
#define LCD_PWR_PORT  PORTC
#define LCD_PWR_TRIS  TRISC

// pin for backlight +12V booster (PWM out to the base of power transistor)
#define LCD_VBS_PIN   1
#define LCD_VBS_PORT  PORTC
#define LCD_VBS_TRIS  TRISC


//////////////////////////////// LCD Interface ////////////////////////////////

// RS  // data/command
#define LCD_RS_PIN   7
#define LCD_RS_PORT  PORTD
#define LCD_RS_TRIS  TRISD

// RESET  // hardware reset
#define LCD_RE_PIN   6
#define LCD_RE_PORT  PORTD
#define LCD_RE_TRIS  TRISD

// CS -> GND

// CLK
#define LCD_CK_PIN   4
#define LCD_CK_PORT  PORTD
#define LCD_CK_TRIS  TRISD

// DAT
#define LCD_DT_PIN   3
#define LCD_DT_PORT  PORTD
#define LCD_DT_TRIS  TRISD

///////////////////////////////////////////////////////////////////////////////


#define BIT_IS_SET(reg, bit) ((reg>>bit)&1)

#define SET_BIT(reg, bit) (reg |= (1<<bit))
#define CLR_BIT(reg, bit) (reg &= (~(1<<bit)))


#define LCD_PWR_CLR     CLR_BIT(LCD_PWR_PORT, LCD_PWR_PIN)
#define LCD_PWR_SET     SET_BIT(LCD_PWR_PORT, LCD_PWR_PIN)
#define LCD_PWR_OUTPUT  CLR_BIT(LCD_PWR_TRIS, LCD_PWR_PIN)
#define LCD_PWR_INPUT   SET_BIT(LCD_PWR_TRIS, LCD_PWR_PIN)

#define LCD_VBS_CLR     CLR_BIT(LCD_VBS_PORT, LCD_VBS_PIN)
#define LCD_VBS_SET     SET_BIT(LCD_VBS_PORT, LCD_VBS_PIN)
#define LCD_VBS_OUTPUT  CLR_BIT(LCD_VBS_TRIS, LCD_VBS_PIN)
#define LCD_VBS_INPUT   SET_BIT(LCD_VBS_TRIS, LCD_VBS_PIN)


#define LCD_RS_CLR     CLR_BIT(LCD_RS_PORT, LCD_RS_PIN)
#define LCD_RS_SET     SET_BIT(LCD_RS_PORT, LCD_RS_PIN)
#define LCD_RS_OUTPUT  CLR_BIT(LCD_RS_TRIS, LCD_RS_PIN)
#define LCD_RS_INPUT   SET_BIT(LCD_RS_TRIS, LCD_RS_PIN)

#define LCD_RE_CLR     CLR_BIT(LCD_RE_PORT, LCD_RE_PIN)
#define LCD_RE_SET     SET_BIT(LCD_RE_PORT, LCD_RE_PIN)
#define LCD_RE_OUTPUT  CLR_BIT(LCD_RE_TRIS, LCD_RE_PIN)
#define LCD_RE_INPUT   SET_BIT(LCD_RE_TRIS, LCD_RE_PIN)

#define LCD_CK_CLR     CLR_BIT(LCD_CK_PORT, LCD_CK_PIN)
#define LCD_CK_SET     SET_BIT(LCD_CK_PORT, LCD_CK_PIN)
#define LCD_CK_OUTPUT  CLR_BIT(LCD_CK_TRIS, LCD_CK_PIN)
#define LCD_CK_INPUT   SET_BIT(LCD_CK_TRIS, LCD_CK_PIN)

#define LCD_DT_CLR     CLR_BIT(LCD_DT_PORT, LCD_DT_PIN)
#define LCD_DT_SET     SET_BIT(LCD_DT_PORT, LCD_DT_PIN)
#define LCD_DT_OUTPUT  CLR_BIT(LCD_DT_TRIS, LCD_DT_PIN)
#define LCD_DT_INPUT   SET_BIT(LCD_DT_TRIS, LCD_DT_PIN)


//backlight control
#define LCD_LIGHT_OFF  LCD_VBS_INPUT
#define LCD_LIGHT_ON   LCD_VBS_OUTPUT; \
                       LCD_VBS_CLR

//power supply
#define LCD_POWER_OFF  LCD_PWR_INPUT
#define LCD_POWER_ON   LCD_PWR_OUTPUT; \
                       LCD_PWR_SET

//interface pins
#define LCD_PORT_ON    LCD_RE_OUTPUT; \
                       LCD_RE_CLR; \
                       LCD_RS_OUTPUT; \
                       LCD_RS_CLR; \
                       LCD_CK_OUTPUT; \
                       LCD_CK_CLR; \
                       LCD_DT_OUTPUT; \
                       LCD_DT_CLR

#define LCD_PORT_OFF   LCD_RE_INPUT; \
                       LCD_RS_INPUT; \
                       LCD_CK_INPUT; \
                       LCD_DT_INPUT


// 16-bit colors  (RGB565)
#define  BLACK         0x0000
#define  WHITE         0xFFFF
#define  GRAY          0xE79C
#define  LIGHT_GRAY    0xC618
#define  DARK_GRAY     0x7BEF
#define  RED           0xF800
#define  PINK          0xF97F
#define  DARK_PINK     0xF80E
#define  MAROON        0x7800
#define  GREEN         0x07E0
#define  YELLOW        0xFFE0
#define  GREEN_YELLOW  0xAFE5
#define  DARK_GREEN    0x03E0
#define  LIGHT_GREEN   0x07EC
#define  BLUE          0x001F
#define  MAGENTA       0xF81F
#define  PURPLE        0x780F
#define  CYAN          0x07FF
#define  DARK_CYAN     0x03EF
#define  NAVY          0x000F
#define  SKY           0x5D1C
#define  VIOLET        0x9199
#define  ORANGE        0xFC00
#define  BROWN         0x8200
#define  OLIVE         0x7BE0


typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed int int16_t;
typedef unsigned int uint16_t;


void delay_ms(uint16_t val);

void lcd_init(void);
void lcd_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
void lcd_pixel(uint8_t x, uint8_t y, uint16_t color);
void lcd_char(uint8_t x, uint8_t y, uint16_t color, uint8_t sign);
void lcd_print(uint8_t x, uint8_t y, uint16_t color, const char *string);
