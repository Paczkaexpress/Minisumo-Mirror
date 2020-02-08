#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/signal.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "main.h"
#include "motor.h"
#include "led_driver.h"
#include "Sensors.h"
#include "fight.h"
#include "tsop.h"

extern int Stop_Fight; 		//Zmienna informuj¹ca czy robot otrzyma³ sygna³ koñcowy walki
extern int Start_Fight;	//Zmienna informuj¹ca czy robot otrzyma³ sygna³ startowy
extern volatile short int RC5_Adress;				//5 bitów adresu
extern volatile short int RC5_Command;				//6 bitów komend
extern volatile short int RC5_Dohyo ;				//numer dohyo
int8_t LeftMotor = 50;
int8_t RightMotor = 50;


void standartFight()
{
	if(SHARP3_ON && SHARP4_ON)
	{
		motor(100,100);
		_delay_ms(5);
	}

	else if(SHARP3_ON)
	{
		motor(100,90);
		LeftMotor = 70;
		RightMotor = 50;
		_delay_ms(5);
	}
	else if(SHARP4_ON)
	{
		motor(90,100);
		LeftMotor = 50;
		RightMotor = 70;
		_delay_ms(5);
	}
	else if(SHARP5_ON)
	{
		motor(90,40);
		LeftMotor = 70;
		RightMotor = 40;
		_delay_ms(5);
	}
	else if(SHARP2_ON)
	{
		motor(40,90);
		LeftMotor = 40;
		RightMotor = 70;
		_delay_ms(5);
	}
	else if(SHARP6_ON)
	{
		motor(100,-100);
		LeftMotor = 80;
		RightMotor = -80;
		_delay_ms(5);
	}
	else if(SHARP1_ON)
	{
		motor(-100,100);
		LeftMotor = -80;
		RightMotor = 80;
		_delay_ms(5);
	}
	else
	{
		motor(LeftMotor,RightMotor);
	}


}

void backLine()
{
	if(KTIR1_ON || KTIR2_ON)
	{
		motor(-100,-100);
		_delay_ms(50);
		motor(-60,-100);
		_delay_ms(60);
		motor(-100,-100);
		_delay_ms(30);
	}
	else if(KTIR3_ON || KTIR4_ON)
	{
		motor(-100,-100);
		_delay_ms(50);
		motor(-100,-60);
		_delay_ms(60);
		motor(-100,-100);
		_delay_ms(30);
	}
}
