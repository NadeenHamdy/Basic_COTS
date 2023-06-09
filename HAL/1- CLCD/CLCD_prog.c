#include "STD_TYPES.h"
#include <util/delay.h>
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"

#if CLCD_u8CONNECTION_MODE == FOUR_BIT
static void voidSetHalfDataPort(uint8 copy_u8FourBitData)
{
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D4_PIN, GET_BIT(copy_u8FourBitData,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D5_PIN, GET_BIT(copy_u8FourBitData,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D6_PIN, GET_BIT(copy_u8FourBitData,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D7_PIN, GET_BIT(copy_u8FourBitData,3));
}
#endif
static void voidSendEnablePulse(void)
{
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_PIN_LOW);

}

void CLCD_voidSendCommand(uint8 copy_u8Command)
{
	/* 1- set RS pin to low for command */
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_PIN_LOW);
	/* 2- set RW pin to low for write */
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_PIN_LOW);
#endif

#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	/* send the command */
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, copy_u8Command );
	/* Send enable pulse */
	voidSendEnablePulse();

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT

	/* Send the Higher 4 bits of the command */
	voidSetHalfDataPort(copy_u8Command >> 4u);
	/* Send enable pulse */
	voidSendEnablePulse();

	/* Send the lower 4 bits of the command */
	voidSetHalfDataPort(copy_u8Command);
	/* Send enable pulse */
	voidSendEnablePulse();
#endif
}

void CLCD_voidSendData(uint8 copy_u8Data)
{
	/* 1- set RS pin to high for data */
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_PIN_HIGH);

	/* 2- set RW pin to low for write */
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_PIN_LOW);
#endif

#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	/* send the data */
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, copy_u8Data );
	/* Send enable pulse */
	voidSendEnablePulse();

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT

	/* Send the Higher 4 bits of the data */
	voidSetHalfDataPort(copy_u8Data >> 4u);
	/* Send enable pulse */
	voidSendEnablePulse();

	/* Send the lower 4 bits of the data */
	voidSetHalfDataPort(copy_u8Data);
	/* Send enable pulse */
	voidSendEnablePulse();
#endif
}

void CLCD_voidSendString(uint8 copy_u8string[])
{
	uint16 i=0;
	while(copy_u8string[i] != '\0')
	{
		CLCD_voidSendData(copy_u8string[i]);
		i++;
	}
}

void CLCD_voidSendNumber(sint32 copy_s32number)
{
	char Local_chNumber[10];
	uint8 Local_u8RightDigit, Local_u8Counter1 = 0;
	sint8 Local_s8Counter2;
	if(copy_s32number == 0)
	{
		CLCD_voidSendData('0');
		return;
	}
	else if(copy_s32number < 0)
	{
		//-ve number
		CLCD_voidSendData ('-');
		copy_s32number *= -1;
	}
	while(copy_s32number != 0)
	{
		Local_u8RightDigit = copy_s32number % 10; // get right most digit
		copy_s32number /= 10;                    // get rid of the right most digit
		Local_chNumber[Local_u8Counter1++] = Local_u8RightDigit + '0';
	}
	for(Local_s8Counter2 = (sint8)Local_u8Counter1 -1 ;  Local_s8Counter2 >= 0; Local_s8Counter2--)
	{
		CLCD_voidSendData(Local_chNumber[(uint8)Local_s8Counter2]);
	}
}

void CLCD_voidInit(void)
{
	/*1- Wait for more than 30ms after power on*/
	_delay_ms(40);

	/*2- Fn set command: 2 lines, font size */
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	CLCD_voidSendCommand(0b00111000); // for the wait delay already delayed in send command func
#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b1000); // NFXX
	voidSendEnablePulse();
#endif

	/*3- Display on/off control: Display on, Cursor off, Blink cursor off */
	CLCD_voidSendCommand(0b00001100);

	/*3- Display clear */
	CLCD_voidSendCommand(1);
}

void CLCD_voidGotoXY(uint8 copy_u8XPos, uint8 copy_u8YPos)
{
	uint8 Local_u8DDRamAdd = (copy_u8YPos * 0x40) + copy_u8XPos;

	/*if (copy_u8YPos == 0u)
	 * {
	 * 		Local_u8DDRamAdd = copy_u8XPos;
	 * }
	 * else
	 * {
	 * 		Local_u8DDRamAdd = copy_u8XPos +0x40u;
	 * }
	 */

	/*Set bit 7 for setting DRam add command */
	SET_BIT(Local_u8DDRamAdd,7u);

	/*Send the setting DDRam add command*/
	CLCD_voidSendCommand(Local_u8DDRamAdd);
}

uint8 CLCD_u8writeSpecialCharacter(uint8 copy_u8PatternNumber, uint8 copy_pu8PatternArr[], uint8 copy_u8XPos, uint8 copy_u8YPos)
{
	uint8 Local_u8ErrorStatus = OK;

	if(copy_pu8PatternArr != NULL)
	{
		uint8 Local_u8CGRAMAdd = copy_u8PatternNumber * 8u;
		uint8 Local_u8iterator;

		/*Set bit6/ Clr bit7 - for setting CGRAM address command */
		SET_BIT(Local_u8CGRAMAdd, 6u);

		/*Set CGRAM Address*/
		CLCD_voidSendCommand(Local_u8CGRAMAdd);

		/*Write the pattern inside CGRAM*/
		for(Local_u8iterator; Local_u8iterator < 8u; Local_u8iterator++)
		{
			CLCD_voidSendData(copy_pu8PatternArr[Local_u8iterator]);
		}

		/*Set DDRAM Address*/
		CLCD_voidGotoXY(copy_u8XPos, copy_u8XPos);

		/*write the corresponding pattern number*/
		CLCD_voidSendData(copy_u8PatternNumber);
	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}

	return Local_u8ErrorStatus;
}









