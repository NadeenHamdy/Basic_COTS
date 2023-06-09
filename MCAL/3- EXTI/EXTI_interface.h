#ifndef EXTI_interface_H
#define EXTI_interface_H

typedef enum
{
	EXTI_INT0,
	EXTI_INT1,
	EXTI_INT2
}EXTI_IntNum_t;

typedef enum
{
	EXTI_LOW_LEVEL,
	EXTI_ON_CHANGE,
	EXTI_FALLING_EDGE,
	EXTI_RISING_EDGE

}EXTI_SenseCtrl_t;

void EXTI_voidInit(void);
uint8 EXTI_u8SetSenseCtrl(EXTI_IntNum_t copy_IntNum, EXTI_SenseCtrl_t copy_SenseCtrl);
uint8 EXTI_u8IntEnable(EXTI_IntNum_t copy_IntNum);
uint8 EXTI_u8IntDisable(EXTI_IntNum_t copy_IntNum);

#endif
