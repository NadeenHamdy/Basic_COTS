#ifndef SWITCH_INTERFACE_H
#define SWITCH_INTERFACE_H


typedef enum
{
	PULL_DOWN,
	PULL_UP
}SWITCH_Pull_t;

typedef struct
{
	DIO_Port_t	Port;
	DIO_Pin_t Pin;
	SWITCH_Pull_t PullType;
}SWITCH_Config_t;

uint8 SWITCH_u8GetState(const SWITCH_Config_t * copy_SwitchObject , uint8 * copy_SwitchState);

#endif
