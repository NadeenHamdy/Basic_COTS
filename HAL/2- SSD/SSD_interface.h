#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H


typedef enum
{
	CATHODE,
	ANODE,
	ETA_KIT
}SSD_COMMON_t;

typedef struct
{
	SSD_COMMON_t	CommType;
	DIO_Port_t 		Port;
	DIO_Pin_t 		LEDApin;
	DIO_Port_t 		EnablePort;
	DIO_Pin_t 		EnablePin;
}SSD_Config_t;

uint8 SSD_u8SetNumber(const SSD_Config_t* copy_SSDobject, uint8 Number);
uint8 SSD_u8Enable(const SSD_Config_t* copy_SSDobject);
uint8 SSD_u8Disable(const SSD_Config_t* copy_SSDobject);
#endif
