#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "EXTI_prv.h"
#include "EXTI_cfg.h"
#include "EXTI_reg.h"
#include "EXTI_interface.h"


void EXTI_voidInit(void)
{
	// check for INT0 state
#ifdef EXTI_u8INT0_TRIG_SRC == FALLING_EDGE
	// configure INTO as falling edge
	CLR_BIT(MCUCR, MCUCR_ISC00);
	SET_BIT(MCUCR, MCUCR_ISC10);

#elif EXTI_u8INT0_TRIG_SRC == RISING_EDGE
	// configure INTO as Rising edge
	SET_BIT(MCUCR, MCUCR_ISC00);
	SET_BIT(MCUCR, MCUCR_ISC10);

#elif EXTI_u8INT0_TRIG_SRC == ON_CHANGE

	// configure INTO as ON_CHANGE
	SET_BIT(MCUCR, MCUCR_ISC00);
	CLR_BIT(MCUCR, MCUCR_ISC10);

#elif EXTI_u8INT0_TRIG_SRC == LOW_LEVEL

	// configure INTO as LOW_LEVEL
	CLR_BIT(MCUCR, MCUCR_ISC00);
	CLR_BIT(MCUCR, MCUCR_ISC10);

#else
#error "Wrong EXTI_u8INT0_TRIG_SRC configuration option"
#endif

#ifdef EXTI_u8INT1_TRIG_SRC == FALLING_EDGE
	// configure INT1 as falling edge
	SET_BIT(MCUCR, MCUCR_ISC11);
	CLR_BIT(MCUCR, MCUCR_ISC10);

#elif EXTI_u8INT1_TRIG_SRC == RISING_EDGE
	// configure INT1 as Rising edge
	SET_BIT(MCUCR, MCUCR_ISC11);
	SET_BIT(MCUCR, MCUCR_ISC10);


#elif EXTI_u8INT1_TRIG_SRC == ON_CHANGE
	// configure INT1 as ON_CHANGE
	CLR_BIT(MCUCR, MCUCR_ISC11);
	SET_BIT(MCUCR, MCUCR_ISC10);

#elif EXTI_u8INT1_TRIG_SRC == LOW_LEVEL
	// configure INT1 as LOW_LEVEL
	CLR_BIT(MCUCR, MCUCR_ISC11);
	CLR_BIT(MCUCR, MCUCR_ISC10);

#else
#error "Wrong EXTI_u8INT1_TRIG_SRC configuration option"
#endif

#ifdef EXTI_u8INT2_TRIG_SRC == FALLING_EDGE
	// configure INT2 as falling edge
	CLR_BIT(MCUCR, MCUCSR_ISC2);

#elif EXTI_u8INT2_TRIG_SRC == RISING_EDGE
	// configure INT2 as rising edge
	SET_BIT(MCUCR, MCUCSR_ISC2);

#else
#error "Wrong EXTI_u8INT2_TRIG_SRC configuration option"
#endif

#if EXTI_u8INT0_INIT_STATE == DISABLED
	CLR_BIT(GICR, GICR_INT0);
#elif EXTI_u8INT0_INIT_STATE == ENABLED
	SET_BIT(GICR, GICR_INT0);
#else
#error "Wrong EXTI_u8INT0_INIT_STATE configuration option"
#endif

#if EXTI_u8INT1_INIT_STATE == DISABLED
	CLR_BIT(GICR, GICR_INT1);
#elif EXTI_u8INT1_INIT_STATE == ENABLED
	SET_BIT(GICR, GICR_INT1);
#else
#error "Wrong EXTI_u8INT1_INIT_STATE configuration option"
#endif

#if EXTI_u8INT2_INIT_STATE == DISABLED
	CLR_BIT(GICR, GICR_INT2);
#elif EXTI_u8INT2_INIT_STATE == ENABLED
	SET_BIT(GICR, GICR_INT2);
#else
#error "Wrong EXTI_u8INT2_INIT_STATE configuration option"
#endif
}

uint8 EXTI_u8SetSenseCtrl(EXTI_IntNum_t copy_IntNum, EXTI_SenseCtrl_t copy_SenseCtrl)
{
	uint8 Local_u8ErrorState = OK;
	if (copy_IntNum == EXTI_INT0)
	{
		switch (copy_SenseCtrl){
		case EXTI_LOW_LEVEL: 	CLR_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC10); break;
		case EXTI_ON_CHANGE: 	SET_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC10); break;
		case EXTI_FALLING_EDGE: CLR_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC10); break;
		case EXTI_RISING_EDGE:  SET_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC10); break;
		default : Local_u8ErrorState = NOK; break;
		}
	}

	if (copy_IntNum == EXTI_INT1)
	{
		switch (copy_SenseCtrl){
		case EXTI_LOW_LEVEL: 	CLR_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case EXTI_ON_CHANGE: 	SET_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case EXTI_FALLING_EDGE: CLR_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		case EXTI_RISING_EDGE:  SET_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		default : Local_u8ErrorState = NOK; break;
		}
	}

	if (copy_IntNum == EXTI_INT2)
	{
		switch (copy_SenseCtrl){
		case EXTI_FALLING_EDGE: CLR_BIT(MCUCSR, MCUCSR_ISC2); break;
		case EXTI_RISING_EDGE:  SET_BIT(MCUCSR, MCUCSR_ISC2); break;
		default : Local_u8ErrorState = NOK; break;
		}
	}

	return Local_u8ErrorState;
}

uint8 EXTI_u8IntEnable(EXTI_IntNum_t copy_IntNum)
{
	uint8 Local_u8ErrorState =OK;
	switch (copy_IntNum)
	{
	case EXTI_INT0: SET_BIT(GICR, GICR_INT0); break;
	case EXTI_INT1: SET_BIT(GICR, GICR_INT1); break;
	case EXTI_INT2: SET_BIT(GICR, GICR_INT2); break;
	default: Local_u8ErrorState = NOK; break;
	}
	return Local_u8ErrorState;
}

uint8 EXTI_u8IntDisable(EXTI_IntNum_t copy_IntNum)
{
	uint8 Local_u8ErrorState =OK;
	switch (copy_IntNum)
	{
	case EXTI_INT0: CLR_BIT(GICR, GICR_INT0); break;
	case EXTI_INT1: CLR_BIT(GICR, GICR_INT1); break;
	case EXTI_INT2: CLR_BIT(GICR, GICR_INT2); break;
	default: Local_u8ErrorState = NOK; break;
	}
	return Local_u8ErrorState;
}


