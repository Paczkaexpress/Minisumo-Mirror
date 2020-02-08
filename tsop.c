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

volatile short int RC5[14];					//otrzymywany ci�g bit�w z pilota
volatile short int RC5_temp[28];				//otrzymany ci�g p�bit�w z pilota
volatile short int RC5_Start = FALSE;		//czy by� pocz�tek transmisji
volatile short int RC5_Err = FALSE;			//by� b��d
volatile short int RC5_counter = 0;			//d�ugosc danego p�bitu
volatile short int RC5_poz = 0;				//numer otrzymanego bitu
volatile short int RC5_val = 2;				//stan tsopa
volatile short int RC5_StartBit = 0;				//3 bity pocz�tkowe
volatile short int RC5_Adress = 0;				//5 bit�w adresu
volatile short int RC5_Command = 0;				//6 bit�w komend
volatile short int RC5_Dohyo = 0;				//numer dohyo
volatile short int RC5_ProgramOK = FALSE;//Czy pokazywa�em poprawne zaprogramowanie modu�u
volatile short int RC5_state = 0;
volatile short int RC5_interrupt = FALSE;

/*
 * sprawdzam czy nadszed� sygna� pocz�tku transmisji
 */
void RC5_waitForStart(uint8_t state)
{
	if (state == 0)
	{
		RC5_Start = TRUE;
		RC5_val = state;
		RC5_temp[0] = state;
		RC5_poz++;
		RC5_counter = 0;
		RC5_Err = FALSE;
	}
}

/*
 * obs�uga paczek otrzymywanych z plilota
 */
void RC5_DataHandler(uint8_t state)
{

	if (RC5_Start == TRUE)
	{

		if (RC5_val != state)
		{
			RC5_val = state;
			if (RC5_counter > 30) //je�eli sygna� jest d�u�szy od 40 cykli zegorowych oznacza to b��d w odbiorze bit�w
			{
			    RC5_Start = FALSE; //wy��czam transmisj�
			}
			else if (RC5_counter >= 6) //je�eli odebrany sygna� zawiera si� w tym przedziale to zosta�y odebrane dwa bity
			{
				RC5_temp[RC5_poz] = state;
				RC5_poz++;
				RC5_temp[RC5_poz] = state;
				RC5_poz++;
			}
			else if (RC5_counter >= 2)
			{
				RC5_temp[RC5_poz] = state;
				RC5_poz++;
			}
			RC5_counter = 0;
		}
		else
		{
			RC5_counter++;
			if (RC5_counter > 250)
			{
				RC5_counter = 250;
			}
		}

		if ((RC5_poz >= 27) || (RC5_Err == TRUE))
		{

			RC5_poz = 0;
			RC5_counter = 0;
			RC5_Start = FALSE;
			RC5_Err = FALSE;

			int i = 0;

			for (i = 0; i < 14; i++)
			{
				if (RC5_temp[2 * i] == 0 && RC5_temp[2 * i + 1] == 1)
					RC5[i] = 0;
				else if (RC5_temp[2 * i] == 1 && RC5_temp[2 * i + 1] == 0)
					RC5[i] = 1;
				else
					RC5[i] = 2;

			}

			//Troch� s�aby jest ten zapis bit�w ale co zrobic, tak jest najprosciej
			RC5_StartBit = (RC5[0]<<2) + (RC5[1]<<1) + (RC5[2]);
			RC5_Command = (RC5[3]<<4) + (RC5[4]<<3) + (RC5[5]<<2) + (RC5[6]<<1) + RC5[7];
			RC5_Adress = (RC5[8]<<5) + (RC5[9]<<4) + (RC5[10]<<3) + (RC5[11]<<2) + (RC5[12]<<1) + RC5[13];

			if (RC5_Command == 0x0B) //bit programowania
			{
				RC5_ProgramOK = FALSE;		//wchod� tylko jak jest komenda programowania
				RC5_Dohyo = RC5_Adress;
				 //eeprom_write_byte (0, RC5_Dohyo);
			}
			else if(RC5_Command == 0x07)
			{

			}
			else
			{
				if(RC5_Command & 0x0100)
					RC5_Command = 0x07;

			}
			_delay_ms(10);
			BUTTON2_OUT;
			 for(i=0;i<28;i++)
			 {
				 if(RC5_temp[i] == 1)
				 {
					 BUTTON2_SET;
				 }
				 else
				 {
					 BUTTON2_CLR;
				 }

			 _delay_us(800);
			 RC5_temp[i] = 0;
			 }
			 _delay_ms(1);
			 BUTTON2_IN;
		}
	}
	else
	{
		RC5_waitForStart(state);
	}
}
