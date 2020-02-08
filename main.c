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

extern volatile short int RC5_Adress;				//5 bitów adresu
extern volatile short int RC5_Command;				//6 bitów komend
extern volatile short int RC5_Dohyo ;				//numer dohyo
extern volatile short int RC5_ProgramOK;//Czy pokazywa³em poprawne zaprogramowanie modu³u
extern volatile short int RC5_state;
extern volatile short int RC5_interrupt;

int Stop_Fight = TRUE; 		//Zmienna informuj¹ca czy robot otrzyma³ sygna³ koñcowy walki
int Start_Fight = FALSE;	//Zmienna informuj¹ca czy robot otrzyma³ sygna³ startowy
short int Eeprom_del = FALSE;

char fightInit = FALSE;
char figthStartRotateLeft = FALSE;
char fightOption = 0;

char LedState = 0;

int main()
{
	initialize();

	//je¿eli by³ w³¹czony pilot kontynu³uj walkê
	if(TSOP1_ON) //ustawiam, ¿e walka siê juz zaczela
	{
		Start_Fight = TRUE;
		Stop_Fight = FALSE;
	}

	else
	{
		ledInit();
	}

	while (1)
	{
		//obs³uga pilota
		if (TSOP1_ON && !Start_Fight)
		{
			Start_Fight = TRUE;
			Stop_Fight = FALSE;
		}
		else if (!TSOP1_ON && Start_Fight)
		{
			Start_Fight = TRUE;
			Stop_Fight = TRUE;
		}

		if(BUTTON2_ON)
		{


			_delay_ms(50);
			if(fightOption <= 0) fightOption = 0;
			else fightOption--;

			switch(fightOption)
			{
				case 0:
					ledDriver(0b11);
					_delay_ms(200);
					ledDriver(0);
					break;
				case 1:
					ledDriver(0b1100);
					_delay_ms(200);
					ledDriver(0);
					break;
				case 2:
					ledDriver(0b110000);
					_delay_ms(200);
					ledDriver(0);
					break;
				case 3:
					ledDriver(0b11000000);
					_delay_ms(200);
					ledDriver(0);
					break;
				default:
					break;
			}

		}
		else if(BUTTON3_ON)
		{

			fightOption++;
			_delay_ms(50);

			if(fightOption > 3) fightOption = 3;

			switch(fightOption)
			{
				case 0:
					ledDriver(0b11);
					_delay_ms(200);
					ledDriver(0);
					break;
				case 1:
					ledDriver(0b1100);
					_delay_ms(200);
					ledDriver(0);
					break;
				case 2:
					ledDriver(0b110000);
					_delay_ms(200);
					ledDriver(0);
					break;
				case 3:
					ledDriver(0b11000000);
					_delay_ms(200);
					ledDriver(0);
					break;
				default:
					break;
			}
		}

		if(Start_Fight == TRUE && Stop_Fight == FALSE)
		{
			if(fightInit == FALSE)
			{
				int i;
				LedState = 0x03;
				fightInit = TRUE;
				int m;

				if(fightOption == 0)
				{
					motor(100,-80);

					for(m = 0;m<26;m++)
					{
						if(SHARP3_ON || SHARP4_ON)
							break;
						_delay_ms(5);
					}

					motor(100,100);
					for(m = 0;m<20;m++)
					{
						if(SHARP3_ON || SHARP4_ON || SHARP1_ON || SHARP2_ON || SHARP5_ON || SHARP6_ON)
							break;
						_delay_ms(5);
					}

				}
				else if(fightOption == 1)
				{
					motor(-80,100);
					for(m = 0;m<26;m++)
					{
						if(SHARP3_ON || SHARP4_ON)
							break;
						_delay_ms(5);
					}

					motor(100,100);
					for(m = 0;m<20;m++)
					{
						if(SHARP3_ON || SHARP4_ON || SHARP1_ON || SHARP2_ON || SHARP5_ON || SHARP6_ON)
							break;
						_delay_ms(5);
					}
				}

				else if(fightOption == 2)
				{
					motor(100,-80);
					for(m = 0;m<13;m++)
					{
						//if(SHARP3_ON || SHARP4_ON)
							//break;
						_delay_ms(5);
					}

					motor(100,100);
					for(m = 0;m<20;m++)
					{
						if(KTIR1_ON || KTIR2_ON || KTIR3_ON || KTIR4_ON)
							break;
						_delay_ms(5);
					}

					motor(100,-100);
					for(m = 0;m<40;m++)
					{
						//if(SHARP1_ON || SHARP2_ON || SHARP3_ON || SHARP4_ON || SHARP5_ON || SHARP6_ON)
						//	break;
						_delay_ms(5);
					}
				}
				else if(fightOption == 3)
				{
					motor(-80,100);
					for(m = 0;m<13;m++)
					{
						//if(SHARP3_ON || SHARP4_ON)
							//break;
						_delay_ms(5);
					}

					motor(100,100);
					for(m = 0;m<20;m++)
					{
							if(KTIR1_ON || KTIR2_ON || KTIR3_ON || KTIR4_ON)
								break;
						_delay_ms(5);
					}

					motor(-100,100);
					for(m = 0;m<40;m++)
					{
						if(SHARP1_ON || SHARP2_ON || SHARP3_ON || SHARP4_ON || SHARP5_ON || SHARP6_ON)
							break;
						_delay_ms(5);
					}

				}
			}


			if(KTIR1_ON || KTIR2_ON || KTIR3_ON || KTIR4_ON)
			{
				backLine();
			}

			standartFight();
			_delay_ms(10);
		}
		else if(Start_Fight == TRUE && Stop_Fight == TRUE)
		{
			motor(0,0);
		}


		showSensorState(LedState);

	}
}

void initialize()
{

	LED_CLK_OUT;
	LED_DATA_OUT;
	LED_LA_OUT;

	BUTTON1_IN;
	BUTTON2_IN;
	BUTTON3_IN;
	TSOP_IN;

	//inicjalizacja czujników
	KTIR1_IN;
	KTIR2_IN;
	KTIR3_IN;
	KTIR4_IN;

	/*
	 * Inicjalizacja PWM
	 */
	MOTOR_LEFT_EN_OUT;
	MOTOR_LEFT_PHA_OUT;
	MOTOR_RIGHT_EN_OUT;
	MOTOR_RIGHT_PHA_OUT;

	motor(0,0);

	TCCR3A |= (1 << COM3B1) | (1 << COM3A1) | (1 << WGM30);
	TCCR3B |= (1 << WGM32) | (1 << CS30) | (1 << CS31);
	/*
	 * Inicjalizacja przerwania wewnêtrznego
	 *
	 */
	TCCR0 |= (1 << CS02);           //ustawienie preskalera na 64
	TIMSK |= (1 << TOIE0);      //w³¹czenie przerwania od przepe³nienia licznika
	TCNT0 = 230;                    //wartosc pocz¹tkowa timera

	sei();
	//W³¹cznie przerwañ

	//zczytywanie wartosci numeru dohyo z eeprom
	//eeprom_busy_wait();
	//RC5_Dohyo = eeprom_read_byte(0);

	return;
}

SIGNAL(SIG_OVERFLOW0)                // przerwabnia generowane od timera0
{
	//TCNT0 = 230; 				//wartosc pocz¹tkowa timera
	//RC5_interrupt = TRUE;
	//RC5_state = TSOP_ON;
	//RC5_DataHandler(RC5_state);
	//RC5_DataHandler(TSOP_ON);
}
