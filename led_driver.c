#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/signal.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "led_driver.h"
#include "Sensors.h"

void ledDriver(unsigned int temp)
{
	unsigned int data = 0;

	//redefiniowanie zapalanej diody
	if(temp & 0x01)
	{
		data |= 0x01;
	}
	if(temp & 0x02)
	{
		data |= 0x02;
	}
	if(temp & 0x04)
	{
		data |= 0x04;
	}
	if(temp & 0x08)
	{
		data |= 0x08;
	}
	if(temp & 0x10)
	{
		data |= 0x10;
	}
	if(temp & 0x20)
	{
		data |= 0x20;
	}
	if(temp & 0x40)
	{
		data |= 0x40;
	}
	if(temp & 0x80)
	{
		data |= 0x80;
	}
	if(temp & 0x100)
	{
		data |= 0x8000;
	}
	if(temp & 0x200)
	{
		data |= 0x4000;
	}
	if(temp & 0x400)
	{
		data |= 0x800;
	}
	if(temp & 0x800)
	{
		data |= 0x400;
	}
	if(temp & 0x1000)
	{
		data |= 0x200;
	}
	if(temp & 0x2000)
	{
		data |= 0x100;
	}
	if(temp & 0x4000)
	{
		data |= 0x2000;
	}
	if(temp & 0x8000)
	{
		data |= 0x1000;
	}

	LED_LA_CLR; //otwieram rejestr przesuwany

	int i=0;
	for(i=0;i<16;i++) // przesy³am dane
	{

	    if(data%2==1)
	    {
	    	LED_DATA_SET;
	    }
	    else
	    {
	    	LED_DATA_CLR;
	    }

	    data = data >> 1;
	    _delay_us(1);
	    LED_CLK_SET;
	    _delay_us(1);
	    LED_CLK_CLR;
	}

	LED_LA_SET; //zamykam rejestr przesuwany
}

void ledInit()
{
	int i =0;
	for(i=0;i<15;i++)
	{

		ledDriver(1<<i);
		_delay_ms(50);
	}

	for(i=15;i>=0;i--)
	{

		ledDriver(1<<i);
		_delay_ms(50);
	}

	ledDriver(0);
}

void showSensorState(char LedState)
{
	int data = 0;

	if(SHARP1_ON)
	{
		data |= 0x100;
	}
	if(SHARP2_ON)
	{
		data |= 0x200;
	}
	if(SHARP3_ON)
	{
		data |= 0x400;
	}
	if(SHARP4_ON)
	{
		data |= 0x800;
	}
	if(SHARP5_ON)
	{
		data |= 0x1000;
	}
	if(SHARP6_ON)
	{
		data |= 0x2000;
	}

	if(KTIR1_ON)
	{
		data |= 0x40;
	}

	if(KTIR2_ON)
	{
		data |= 0x80;
	}
	if(KTIR3_ON)
	{
		data |= 0x4000;
	}

	if(KTIR4_ON)
	{
		data |= 0x8000;
	}

	data += LedState;

	ledDriver(data);

}
