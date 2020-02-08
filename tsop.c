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

volatile short int RC5[14];					//otrzymywany ci¹g bitów z pilota
volatile short int RC5_temp[28];				//otrzymany ci¹g pó³bitów z pilota
volatile short int RC5_Start = FALSE;		//czy by³ pocz¹tek transmisji
volatile short int RC5_Err = FALSE;			//by³ b³¹d
volatile short int RC5_counter = 0;			//d³ugosc danego pó³bitu
volatile short int RC5_poz = 0;				//numer otrzymanego bitu
volatile short int RC5_val = 2;				//stan tsopa
volatile short int RC5_StartBit = 0;				//3 bity pocz¹tkowe
volatile short int RC5_Adress = 0;				//5 bitów adresu
volatile short int RC5_Command = 0;				//6 bitów komend
volatile short int RC5_Dohyo = 0;				//numer dohyo
volatile short int RC5_ProgramOK = FALSE;//Czy pokazywa³em poprawne zaprogramowanie modu³u
volatile short int RC5_state = 0;
volatile short int RC5_interrupt = FALSE;

/*
 * sprawdzam czy nadszed³ sygna³ pocz¹tku transmisji
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
 * obs³uga paczek otrzymywanych z plilota
 */
void RC5_DataHandler(uint8_t state)
{

	if (RC5_Start == TRUE)
	{

		if (RC5_val != state)
		{
			RC5_val = state;
			if (RC5_counter > 30) //je¿eli sygna³ jest d³u¿szy od 40 cykli zegorowych oznacza to b³¹d w odbiorze bitów
			{
			    RC5_Start = FALSE; //wy³¹czam transmisjê
			}
			else if (RC5_counter >= 6) //je¿eli odebrany sygna³ zawiera siê w tym przedziale to zosta³y odebrane dwa bity
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

			//Trochê s³aby jest ten zapis bitów ale co zrobic, tak jest najprosciej
			RC5_StartBit = (RC5[0]<<2) + (RC5[1]<<1) + (RC5[2]);
			RC5_Command = (RC5[3]<<4) + (RC5[4]<<3) + (RC5[5]<<2) + (RC5[6]<<1) + RC5[7];
			RC5_Adress = (RC5[8]<<5) + (RC5[9]<<4) + (RC5[10]<<3) + (RC5[11]<<2) + (RC5[12]<<1) + RC5[13];

			if (RC5_Command == 0x0B) //bit programowania
			{
				RC5_ProgramOK = FALSE;		//wchodŸ tylko jak jest komenda programowania
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
