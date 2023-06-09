#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "DIO_interface.h"

#include "SSD_interface.h"

uint8 SSD_NUMBER[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
uint8 SSD_u8SetNumber(const SSD_Config_t* copy_SSDobject, uint8 Number) //type / port/pinA/ ENport//ENpin
{
	uint8 Local_u8ErrorStatus = OK;
	if(copy_SSDobject != NULL)
	{
		DIO_u8SetPinDirection(copy_SSDobject->Port, copy_SSDobject->LEDApin, DIO_PIN_OUTPUT);
		DIO_u8SetPinDirection(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN1, DIO_PIN_OUTPUT);
		DIO_u8SetPinDirection(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN2, DIO_PIN_OUTPUT);
		DIO_u8SetPinDirection(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN3, DIO_PIN_OUTPUT);
		DIO_u8SetPinDirection(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN4, DIO_PIN_OUTPUT);
		DIO_u8SetPinDirection(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN5, DIO_PIN_OUTPUT);
		DIO_u8SetPinDirection(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN6, DIO_PIN_OUTPUT);
		DIO_u8SetPinDirection(copy_SSDobject->EnablePort, copy_SSDobject->EnablePin, DIO_PIN_OUTPUT);
		uint8 num;
		if((copy_SSDobject->CommType == CATHODE) || (copy_SSDobject->CommType == ETA_KIT))
		{
			num = 0;
		}
		else if (copy_SSDobject->CommType == ANODE)
		{
			num = 1;
		}
		else Local_u8ErrorStatus = NOK;
		DIO_u8SetPinValue(copy_SSDobject->Port, copy_SSDobject->LEDApin, num ^ GET_BIT(SSD_NUMBER[Number],0));
		DIO_u8SetPinValue(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN1, num ^ GET_BIT(SSD_NUMBER[Number],1));
		DIO_u8SetPinValue(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN2, num ^ GET_BIT(SSD_NUMBER[Number],2));
		DIO_u8SetPinValue(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN3, num ^ GET_BIT(SSD_NUMBER[Number],3));
		DIO_u8SetPinValue(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN4, num ^ GET_BIT(SSD_NUMBER[Number],4));
		DIO_u8SetPinValue(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN5, num ^ GET_BIT(SSD_NUMBER[Number],5));
		DIO_u8SetPinValue(copy_SSDobject->Port, (copy_SSDobject->LEDApin)+DIO_PIN6, num ^ GET_BIT(SSD_NUMBER[Number],6));

	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}
	return Local_u8ErrorStatus;
}


uint8 SSD_u8Enable(const SSD_Config_t* copy_SSDobject)
{
	uint8 Local_u8ErrorStatus = OK;
	if(copy_SSDobject != NULL)
	{
		DIO_u8SetPinDirection(copy_SSDobject->EnablePort, copy_SSDobject->EnablePin, DIO_PIN_OUTPUT);
		if((copy_SSDobject->CommType == CATHODE) )
		{
			DIO_u8SetPinValue(copy_SSDobject->EnablePort, copy_SSDobject->EnablePin, DIO_PIN_HIGH);
		}
		else if ((copy_SSDobject->CommType == ANODE) || (copy_SSDobject->CommType == ETA_KIT))
		{
			DIO_u8SetPinValue(copy_SSDobject->EnablePort, copy_SSDobject->EnablePin, DIO_PIN_LOW);
		}
		else Local_u8ErrorStatus = NOK;

	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}
	return Local_u8ErrorStatus;
}


uint8 SSD_u8Disable(const SSD_Config_t* copy_SSDobject)
{
	uint8 Local_u8ErrorStatus = OK;
	if(copy_SSDobject != NULL)
	{
		DIO_u8SetPinDirection(copy_SSDobject->EnablePort, copy_SSDobject->EnablePin, DIO_PIN_OUTPUT);
		if((copy_SSDobject->CommType == CATHODE) )
		{
			DIO_u8SetPinValue(copy_SSDobject->EnablePort, copy_SSDobject->EnablePin, DIO_PIN_LOW);
		}
		else if ((copy_SSDobject->CommType == ANODE) || (copy_SSDobject->CommType == ETA_KIT))
		{
			DIO_u8SetPinValue(copy_SSDobject->EnablePort, copy_SSDobject->EnablePin, DIO_PIN_HIGH);
		}
		else Local_u8ErrorStatus = NOK;

	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}
	return Local_u8ErrorStatus;
}
