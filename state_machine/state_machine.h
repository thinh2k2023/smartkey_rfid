/************************************************************************/
/* PROGRAM		: SIMULATION BOARD										*/
/* FILE			: adc_input_app.h										 */
/* DESCRIPTION	: 														*/
/* CPU GROUP    : STM32F407VGT6											*/
/* DATE         : 2023/07/18											*/
/* Copyright    : Diamond Electric Vietnam Co.,Ltd.						*/
/************************************************************************/

#ifndef __KEY_SCAN_H__
#define __KEY_SCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "stm32f1xx_hal.h"

/***********************************************************************************************************************
Type definition
***********************************************************************************************************************/


/***********************************************************************************************************************
Macro definition
***********************************************************************************************************************/


/***********************************************************************************************************************
Extern definition (Function)
***********************************************************************************************************************/
extern char read_keypad(void);
extern uint8_t flag_release_key;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __KEY_SCAN_H__ */
/***********************************************************************************************************************
End of file
***********************************************************************************************************************/