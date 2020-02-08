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


void motor(int LeftMotor, int RightMotor)
{
	if(LeftMotor >= 0)
	{
		MOTOR_LEFT_GO;
		OCR3A = (LeftMotor) * MAX_PWM / 100;	//ustawiam PWM pierwszego silnika
	}
	else
	{
		MOTOR_LEFT_BACK;
		OCR3A = (-LeftMotor) * MAX_PWM / 100;	//ustawiam PWM pierwszego silnika
	}

	if(RightMotor >= 0)
	{
		MOTOR_RIGHT_GO;
		OCR3B = (RightMotor) * MAX_PWM / 100;   //ustawiam PWM drugiego silnika
	}
	else
	{
		MOTOR_RIGHT_BACK;
		OCR3B  = (-RightMotor) * MAX_PWM / 100;   //ustawiam PWM drugiego silnika
	}


}
