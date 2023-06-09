#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_reg.h"

void GIE_voidEnableGlobal(void)
{
	// insert assemply instruction in c code (volatile is to make compiler cancel optimization)
	__asm volatile ("SEI");
	/*SET_BIT(SREG, SREG_I);*/
}
void GIE_voidDisableGlobal(void)
{
	// insert assemply instruction in c code
	__asm volatile ("CLI");
	/*CLR_BIT(SREG, SREG_I);*/
}
