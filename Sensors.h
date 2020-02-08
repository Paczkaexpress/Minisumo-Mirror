#define SHARP1_IN          		DDRF  &=  ~(1<<1)
#define SHARP1_SET         		PORTF |=  (1<<1)
#define SHARP1_ON          		!(PINF & (1<<1))

#define SHARP2_IN          		DDRF  &=  ~(1<<2)
#define SHARP2_SET         		PORTF |=  (1<<2)
#define SHARP2_ON          		!(PINF & (1<<2))

#define SHARP3_IN          		DDRF  &=  ~(1<<3)
#define SHARP3_SET         		PORTF |=  (1<<3)
#define SHARP3_ON          		!(PINF & (1<<3))

#define SHARP6_IN          		DDRA  &=  ~(1<<2)
#define SHARP6_SET         		PORTA |=  (1<<2)
#define SHARP6_ON          		!(PINA & (1<<2))

#define SHARP5_IN          		DDRA  &=  ~(1<<3)
#define SHARP5_SET         		PORTA |=  (1<<3)
#define SHARP5_ON          		!(PINA & (1<<3))

#define SHARP4_IN          		DDRA  &=  ~(1<<4)
#define SHARP4_SET         		PORTA |=  (1<<4)
#define SHARP4_ON 	    		!(PINA & (1<<4))

#define KTIR1_SET        		PORTF |=  (1<<4)
#define KTIR1_CLR       		PORTF &= ~(1<<4)
#define KTIR1_IN   				DDRF  &= ~(1<<4)
#define KTIR1_ON				Get_ADC(4)<TRESHOLD

#define KTIR2_SET        		PORTF |=  (1<<5)
#define KTIR2_CLR       		PORTF &= ~(1<<5)
#define KTIR2_IN   				DDRF  &= ~(1<<5)
#define KTIR2_ON				Get_ADC(5)<TRESHOLD

#define KTIR3_SET        		PORTF |=  (1<<6)
#define KTIR3_CLR       		PORTF &= ~(1<<6)
#define KTIR3_IN   				DDRF  &= ~(1<<6)
#define KTIR3_ON				Get_ADC(6)<TRESHOLD

#define KTIR4_SET        		PORTF |=  (1<<7)
#define KTIR4_CLR       		PORTF &= ~(1<<7)
#define KTIR4_IN   				DDRF  &= ~(1<<7)
#define KTIR4_ON				Get_ADC(7)<TRESHOLD

#define TRESHOLD				100
