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

int Get_ADC(char number)
{
	ADMUX &= ~(1<<0) & ~(1<<1) & ~(1<<2);
	ADMUX |= (1<<REFS0) | (1<<ADLAR); //porównuje z AVCC,  AREF--||--GND
	ADMUX |= number;

    ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADPS1)|(1<<ADPS2);
    while(ADCSRA & (1 << ADSC));
    return ADCH;
}
