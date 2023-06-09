#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "DIO_interface.h"

#include "SWITCH_interface.h"




uint8 SWITCH_u8GetState(const SWITCH_Config_t * copy_SwitchObject , uint8 * copy_SwitchState)
{
	uint8 Local_u8ErrorStatus = OK;
	uint8 Local_SwitchVal;

	if( (copy_SwitchObject != NULL) && (copy_SwitchState != NULL))
	{

		DIO_u8SetPinDirection(copy_SwitchObject->Port, copy_SwitchObject->Pin, DIO_PIN_INPUT);
		DIO_u8GetPinValue(copy_SwitchObject->Port, copy_SwitchObject->Pin, &Local_SwitchVal);
		if(copy_SwitchObject-> PullType == PULL_UP)
		{
			*copy_SwitchState = Local_SwitchVal;
			*copy_SwitchState = !Local_SwitchVal;
		}
		else if (copy_SwitchObject-> PullType == PULL_DOWN)
		{
			*copy_SwitchState = !Local_SwitchVal;
			*copy_SwitchState = Local_SwitchVal;
		}
		else Local_u8ErrorStatus = NOK;
	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}

	return Local_u8ErrorStatus;
}



