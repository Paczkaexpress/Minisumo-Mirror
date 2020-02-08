
#define MOTOR_LEFT_BACK         		PORTE |=  (1<<2)
#define MOTOR_LEFT_GO         			PORTE &=  ~(1<<2)
#define MOTOR_LEFT_PHA_OUT          	DDRE  |=  (1<<2)

#define MOTOR_LEFT_EN_SET         		PORTE |=  (1<<3)
#define MOTOR_LEFT_EN_CLR         		PORTE &=  ~(1<<3)
#define MOTOR_LEFT_EN_OUT          		DDRE  |=  (1<<3)

#define MOTOR_RIGHT_EN_SET         		PORTE |=  (1<<4)
#define MOTOR_RIGHT_EN_CLR         		PORTE &=  ~(1<<4)
#define MOTOR_RIGHT_EN_OUT          	DDRE  |=  (1<<4)

#define MOTOR_RIGHT_GO	         		PORTE |=  (1<<5)
#define MOTOR_RIGHT_BACK		        PORTE &=  ~(1<<5)
#define MOTOR_RIGHT_PHA_OUT          	DDRE  |=  (1<<5)

#define MAX_PWM  						255
