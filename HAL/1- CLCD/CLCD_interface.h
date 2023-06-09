#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

void CLCD_voidSendCommand(uint8 copy_u8Command);
void CLCD_voidSendData(uint8 copy_u8Data);
void CLCD_voidSendString(uint8 copy_u8string[]);
void CLCD_voidSendNumber(sint32 copy_s32number);
void CLCD_voidInit(void);

void CLCD_voidGotoXY(uint8 copy_u8XPos, uint8 copy_u8YPos);
uint8 CLCD_u8writeSpecialCharacter(uint8 copy_u8PatternNumber, uint8 copy_pu8PatternArr[], uint8 copy_u8XPos, uint8 copy_u8YPos);

#endif
