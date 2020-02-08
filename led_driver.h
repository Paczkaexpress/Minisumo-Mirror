
#define LED_CLK_OUT             DDRD  |=  (1<<4)
#define LED_CLK_SET             PORTD |=  (1<<4)
#define LED_CLK_CLR             PORTD &=  ~(1<<4)

#define LED_LA_OUT              DDRG  |=  (1<<4)
#define LED_LA_SET              PORTG |=  (1<<4)
#define LED_LA_CLR              PORTG &=  ~(1<<4)

#define LED_DATA_OUT            DDRD  |=  (1<<5)
#define LED_DATA_SET            PORTD |=  (1<<5)
#define LED_DATA_CLR            PORTD &=  ~(1<<5)
