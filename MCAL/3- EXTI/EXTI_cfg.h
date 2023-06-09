#ifndef EXTI_CFG_H
#define EXTI_CFG_H


/* Configure INT0 trigger 1- LOW_LEVEL
* 						  2- ON_CHANGE
* 						  3- FALLING_EDGE
* 						  4- RISING_EDGE
* 						 */
#define EXTI_u8INT0_TRIG_SRC			FALLING_EDGE

/* Configure INT1 trigger 1- LOW_LEVEL
* 						  2- ON_CHANGE
* 						  3- FALLING_EDGE
* 						  4- RISING_EDGE
* 						 */
#define EXTI_u8INT1_TRIG_SRC			FALLING_EDGE

/* Configure INT2 trigger 1- FALLING_EDGE
* 						  2- RISING_EDGE
* 						 */
#define EXTI_u8INT2_TRIG_SRC			FALLING_EDGE     // OPTIONS:: 1- FALLING_EDGE 2- RISING_EDGE


/* Configure INT0 initial state 1- ENABLED
* 						 	   	2- DISABLED
**/
#define EXTI_u8INT0_INIT_STATE			ENABLED

/* Configure INT1 initial state 1- ENABLED
* 						 	   	2- DISABLED
**/
#define EXTI_u8INT1_INIT_STATE			ENABLED

/* Configure INT2 initial state 1- ENABLED
* 						 	   	2- DISABLED
**/
#define EXTI_u8INT2_INIT_STATE			DISABLED

#endif
