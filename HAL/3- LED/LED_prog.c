#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "DIO_interface.h"

#include "LED_interface.h"

uint8 LED_u8SetON(const LED_Config_t * copy_LEDobject ) // port pin activity
{
	uint8 Local_u8ErrorStatus = OK;

	if(copy_LEDobject != NULL)
	{
		DIO_u8SetPinDirection(copy_LEDobject->Port, copy_LEDobject->Pin, DIO_PIN_OUTPUT);
		if(copy_LEDobject-> ActiveType == ACTIVE_LOW)
		{
			DIO_u8SetPinValue(copy_LEDobject->Port, copy_LEDobject->Pin, DIO_PIN_LOW);
		}
		else if (copy_LEDobject-> ActiveType == ACTIVE_HIGH)
		{
			DIO_u8SetPinValue(copy_LEDobject->Port, copy_LEDobject->Pin, DIO_PIN_HIGH);
		}
		else Local_u8ErrorStatus = NOK;
	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}

	return Local_u8ErrorStatus;
}
uint8 LED_u8SetOFF(const LED_Config_t * copy_LEDobject )
{
	uint8 Local_u8ErrorStatus = OK;

	if(copy_LEDobject != NULL)
	{
		DIO_u8SetPinDirection(copy_LEDobject->Port, copy_LEDobject->Pin, DIO_PIN_OUTPUT);
		if(copy_LEDobject-> ActiveType == ACTIVE_LOW)
		{
			DIO_u8SetPinValue(copy_LEDobject->Port, copy_LEDobject->Pin, DIO_PIN_HIGH);
		}
		else if (copy_LEDobject-> ActiveType == ACTIVE_HIGH)
		{
			DIO_u8SetPinValue(copy_LEDobject->Port, copy_LEDobject->Pin, DIO_PIN_LOW);
		}
		else Local_u8ErrorStatus = NOK;
	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}

	return Local_u8ErrorStatus;
}
uint8 LED_u8SetToggle(const LED_Config_t * copy_LEDobject )
{
	uint8 Local_u8ErrorStatus = OK;

	if(copy_LEDobject != NULL)
	{
		DIO_u8SetPinDirection(copy_LEDobject->Port, copy_LEDobject->Pin, DIO_PIN_OUTPUT);
		DIO_u8TogglePinValue(copy_LEDobject->Port, copy_LEDobject->Pin);
	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}

	return Local_u8ErrorStatus;
}

