#define BUTTON1_IN          	DDRB  &=  ~(1<<6)
#define BUTTON1_SET         	PORTB |=  (1<<6)
#define BUTTON1_ON          	!(PINB & (1<<6))

#define BUTTON2_IN              DDRB  &=  ~(1<<7)
#define BUTTON2_SET             PORTB |=  (1<<7)
#define BUTTON2_CLR             PORTB &=  ~(1<<7)
#define BUTTON2_ON              !(PINB & (1<<7))
#define BUTTON2_OUT             DDRB  |=  (1<<7)

#define BUTTON3_IN              DDRG  &=  ~(1<<3)
#define BUTTON3_SET             PORTG |=  (1<<3)
#define BUTTON3_ON              !(PING & (1<<3))

#define TSOP_IN                 DDRD  &=  ~(1<<7)
#define TSOP_OUT                DDRD  |=  (1<<7)
#define TSOP_SET                PORTD |=  (1<<7)
#define TSOP_CLR                PORTD &=  ~(1<<7)
#define TSOP_ON                 !(PIND & (1<<7))

#define TSOP1_IN                 DDRD  &=  ~(1<<2)
#define TSOP1_OUT                DDRD  |=  (1<<2)
#define TSOP1_SET                PORTD |=  (1<<2)
#define TSOP1_CLR                PORTD &=  ~(1<<2)
#define TSOP1_ON                 (PIND & (1<<2))

#define Start_Phrase            0
#define Fight_Phrase            1
#define FALSE		            0
#define TRUE 		            1
