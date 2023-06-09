#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "ADC_interface.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_reg.h"

static uint16* ADC_pu16DigResult = NULL;

static void ( *ADC_pu16NotificationFunc)(void) = NULL;

static uint8 ADC_u8BusyFlag = IDLE;

void ADC_voidInit(void)
{
	/*Reference selection: AVCC PIN*/
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

	/*Activate left adjust result for 8-bit resulution*/
#if ADC_u8RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_u8RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#else
#error wrong ADC_u8RESOLUTION Configuration value
#endif

	/*check on prescaler configuration setting*/
	ADCSRA &= PRESCALER_MASK;			// Clear the prescaler bits
	ADCSRA |= ADC_u8PRESCALER;

	/*ADC Enable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

uint8 ADC_u8StartConvertionSynch(ADC_Channel_t copy_Channel, uint16* copy_pu16DigResult)
{
	uint8 Local_u8ErrorState = OK;
	if(copy_pu16DigResult != NULL)
	{
		if (ADC_u8BusyFlag == IDLE)
		{
			uint32 Local_u8Counter = 0u;

			// ADC IS NOW BUSY
			ADC_u8BusyFlag = BUSY;

			/*Set the required channel*/
			ADMUX &= CHANNEL_SELECTION_MASK;  // clear the channel selection bits
			ADMUX |= copy_Channel;

			/*Start the conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*WAIT (block) until conversion is completed or the timeout has not passed yet*/
			while(((GET_BIT(ADCSRA, ADCSRA_ADIF)) == 0) && (Local_u8Counter < ADC_u32TIMEOUT_COUNT))
			{
				Local_u8Counter++;
			}
			if(Local_u8Counter == ADC_u32TIMEOUT_COUNT)
			{
				/*Loop is broken because timeout has passed*/
				Local_u8ErrorState = TIMEOUT_ERR;
			}
			else // loop is broken because flag is raised
			{
				/*Clear the conversion flag ""set bit""*/
				SET_BIT(ADCSRA, ADCSRA_ADIF);

#if ADC_u8RESOLUTION == EIGHT_BITS
				*copy_pu16DigResult = (uint16)ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
				*copy_pu16DigResult = ADC;
#endif
				// Task is done ADC IS NOW IDLE
				ADC_u8BusyFlag = IDLE;
			}
		}
		else
		{
			Local_u8ErrorState = BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

uint8 ADC_u8StartConvertionASynch(ADC_Channel_t copy_Channel, uint16* copy_pu16DigResult, void(*copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;

	if((copy_pu16DigResult != NULL) && (copy_pvNotificationFunc != NULL))
	{
		if(ADC_u8BusyFlag == IDLE)
		{
			// ADC IS NOW BUSY
			ADC_u8BusyFlag = BUSY;

			/*Convert the digital result and the notification func local variables into global*/
			ADC_pu16DigResult = copy_pu16DigResult;
			ADC_pu16NotificationFunc = copy_pvNotificationFunc;

			/*Set the required channel*/
			ADMUX &= CHANNEL_SELECTION_MASK;  // clear the channel selection bits
			ADMUX |= copy_Channel;

			/*Start the conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable ADC conversion complete interrupt*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);

		}
		else
		{
			Local_u8ErrorState = BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

/*ADC conversion complete ISR*/
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
#if ADC_u8RESOLUTION == EIGHT_BITS
	*ADC_pu16DigResult = (uint16)ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
	*ADC_pu16DigResult = ADC;
#endif

	/*ADC interrupt disable*/
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

	// Task is done ADC IS NOW IDLE
	ADC_u8BusyFlag = IDLE;

	/*invoke the callback notification function*/
	if(ADC_pu16NotificationFunc != NULL)
	{
		ADC_pu16NotificationFunc();
	}
	else
	{
		// do nothing
	}
}




