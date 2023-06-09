#ifndef ADC_CFG_H
#define ADC_CFG_H

/*Configure ADC prescaler division factor: 1- DIVISION_BY_2
 * 										   1- DIVISION_BY_4
 * 										   1- DIVISION_BY_8
 * 										   1- DIVISION_BY_16
 * 										   1- DIVISION_BY_12
 * 										   1- DIVISION_BY_64
 * 										   1- DIVISION_BY_128
**/

#define ADC_u8PRESCALER			DIVISION_BY_128

/*Configure ADC resolution, option:   1- EIGHT_BITS
 * 									  2- TEN_BITS
 * 									  */

#define ADC_u8RESOLUTION			TEN_BITS

#define ADC_u32TIMEOUT_COUNT		5000UL

#endif
