//Testing Color LCD
//25-Feb-2016


#include "display.h"


#include <htc.h>


void setup(void);


//-------------------------------------------------------------------------------------------------
void interrupt handler(void)
	{
	
	}
	

//---------------------------------------------------------------------------------------
void setup(void) //init
	{
	IRCF2=1; IRCF1=1; IRCF0=1; //8MHz internal RC oscillator
	
	SWDTEN=0; //disable watchdog timer
	
	ADCON1=0b1111; //disable analog inputs
	
	RBPU=1; //disable pull-up on PORTB

	
	//TMR0ON T08BIT T0CS T0SE PSA T0PS2 T0PS1 T0PS0
	T0CON=0b00000000;	
	TMR0IE=0; //timer0 overflow intterrupt
	
	//RD16 T1RUN T1CKPS1 T1CKPS0 T1OSCEN T1SYNC TMR1CS TMR1ON
	T1CON=0b00000000;
	TMR1IE=0;
	
	CCP2CON=0b1100;  //CCP in PWM mmode
	CCPR2=PWM;       //PWM duty cycle
	
	//bit0-unused T2OUTPS3 T2OUTPS2 T2OUTPS1 T2OUTPS0 TMR2ON T2CKPS1 T2CKPS0
	T2CON=0b00000101;  //Timer2 On (for PWM)  //01 - prescaler for ~3 kHz PWM
	TMR2IE=0;
	
	//RD16 T3CCP2 T3CKPS1 T3CKPS0 T3CCP1 T3SYNC TMR3CS TMR3ON
	T3CON=0b00000110;
	TMR3IE=0;

	PEIE=0;
	GIE=0; //enable/disable interrupts
	}


//---------------------------------------------------------------------------------------
int main(void)
	{
	setup();
	
	lcd_init();
	
	lcd_rect(0, 0, 132, 176, SKY);  //fill screen
	
	LCD_LIGHT_ON; //backlight ON
	
	lcd_rect(0, 160, 132, 16, NAVY);
	
	lcd_rect(20, 33, 102, 62, BLACK);  //draw window
	lcd_rect(15, 28, 104, 64, NAVY);
	lcd_rect(17, 30, 100, 60, BLUE);
	
	lcd_print(27, 50, YELLOW, "Hello World!");
	
	
	///////////////// Display OFF ///////////////////
	// 
	// LCD_LIGHT_OFF;  // backlight switch OFF
	// LCD_PORT_OFF;   // LCD port OFF
	// LCD_POWER_OFF;  // +2.9V power supply OFF
	//
	/////////////////////////////////////////////////
	
	
	for(;;) //main loop
		{

		}
	}

