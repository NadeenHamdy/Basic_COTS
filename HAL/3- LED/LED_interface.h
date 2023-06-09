#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H


typedef enum
{
	ACTIVE_LOW,
	ACTIVE_HIGH
}LED_Act_t;

typedef struct
{
	DIO_Port_t	Port;
	DIO_Pin_t Pin;
	LED_Act_t ActiveType;
}LED_Config_t;

uint8 LED_u8SetON(const LED_Config_t * copy_LEDobject );
uint8 LED_u8SetOFF(const LED_Config_t * copy_LEDobject );
uint8 LED_u8SetToggle(const LED_Config_t * copy_LEDobject );

#endif
