// name: Color LCD library
//
// file: display.c
//
//


#include "display.h"
#include "font.h"


//-------------------------------------------------------------------------------------------------
void delay_ms(uint16_t val)  //delay, milliseconds
	{
	while(val--) __delay_ms(1);
	}


//-------------------------------------------------------------------------------------------------
void lcd_send(uint8_t mode, uint8_t byte)  //send data or command
	{
	mode ? LCD_RS_SET : LCD_RS_CLR;  //LCD line RS  //mode==1 - data  //mode==0 - command
	//LCD_CK_CLR;	
	for(uint8_t mask=0b10000000; mask>0; mask>>=1)  //send byte
		{ 
		(byte & mask) ? LCD_DT_SET : LCD_DT_CLR;
		LCD_CK_SET;  //send the bit on rising edge of clock signal
		//NOP();
		LCD_CK_CLR;
		} 
	}


//-------------------------------------------------------------------------------------------------
void lcd_comm(uint8_t comm) //send command byte
	{
	lcd_send(0, comm);
	}


//-------------------------------------------------------------------------------------------------
void lcd_data(uint8_t data) //send data byte
	{
	lcd_send(1, data);
	}
	

//-------------------------------------------------------------------------------------------------
void lcd_init(void)	
	{	
//	LCD_LIGHT_ON;    //backlight switch ON
	LCD_POWER_ON;    //+2.9V power supply ON
	LCD_PORT_ON;     //init pins for LCD port
	
	delay_ms(50);    //wait for the hardware reset
	LCD_RE_SET;
	delay_ms(50);
	
	lcd_comm(0x01);  //software reset
	lcd_comm(0x36);  //memory access control
	lcd_data(0x00);  //VHR=0b000XXXXX
	lcd_comm(0x11);  //wakeup
	delay_ms(20); 
	lcd_comm(0x3a);  //palette 
	lcd_data(0x05);  //65536 colors  //0x02 for 256 colors
	delay_ms(20); 
	lcd_comm(0x29);  //enable
	}


//-------------------------------------------------------------------------------------------------
void lcd_area(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
	{
	lcd_comm(0x2A);  //X
	lcd_data(x1);
	lcd_data(x2);

	lcd_comm(0x2B);  //Y
	lcd_data(y1); 
	lcd_data(y2);

	lcd_comm(0x2C);  //start write
	}


//-------------------------------------------------------------------------------------------------
void lcd_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color)  //draw rectangle
	{                                // width 1..132  // height 1..176
	lcd_area(x, x+(w-1), y, y+(h-1));

	for(uint16_t i=0; i<(w*h); i++)  //fill area
		{
		lcd_data(color >> 8);
		lcd_data(color);
		}
	}


//-------------------------------------------------------------------------------------------------
void lcd_pixel(uint8_t x, uint8_t y, uint16_t color)  //x - 0..131  //y - 0..175  //set pixel color
	{
	lcd_area( x, x, y, y );
 	
	lcd_data(color>>8);
	lcd_data(color);
	}
	

//-------------------------------------------------------------------------------------------------
void lcd_char(uint8_t x, uint8_t y, uint16_t color, uint8_t sign) //draw symbol 5x7
	{
	if(sign<32 || sign>127) sign=128; //filling field for invalid characters

	for(uint8_t a=0; a<5; a++) //x5
		{
		uint8_t  mask = 0b00000001;
		
		for(uint8_t b=0; b<7; b++) //x7
			{
			if(font5x7[(5*(sign-32))+a] & mask) lcd_pixel(x+a, y+b, color);  //write
			mask<<=1;
			}
		}
	}


//-------------------------------------------------------------------------------------------------
void lcd_print(uint8_t x, uint8_t y, uint16_t color, const char *string) //print string
	{
	for(uint8_t k=0; *string; k++) lcd_char(x+k*6, y, color, *string++);
	}

