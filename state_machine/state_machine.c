/************************************************************************/
/* PROGRAM		: SIMULATION BOARD										*/
/* FILE			: adc_input_app.c										*/
/* DESCRIPTION	: 														*/
/* CPU GROUP    : STM32F407VGT6											*/
/* DATE         : 2023/07/18											*/
/* Copyright    : Diamond Electric Vietnam Co.,Ltd.						*/
/************************************************************************/

/***********************************************************************************************************************
Includes (usage file)
***********************************************************************************************************************/


/***********************************************************************************************************************
Includes (own file)
***********************************************************************************************************************/

#include "key_scan.h"


/***********************************************************************************************************************
Macro definition
***********************************************************************************************************************/

#define R1_PORT GPIOB
#define R1_PIN GPIO_PIN_15

#define R2_PORT GPIOB
#define R2_PIN GPIO_PIN_14

#define R3_PORT GPIOB
#define R3_PIN GPIO_PIN_13

#define R4_PORT GPIOB
#define R4_PIN GPIO_PIN_12

#define C1_PORT GPIOB
#define C1_PIN GPIO_PIN_11

#define C2_PORT GPIOB
#define C2_PIN GPIO_PIN_10

#define C3_PORT GPIOB
#define C3_PIN GPIO_PIN_1

#define C4_PORT GPIOB
#define C4_PIN GPIO_PIN_0

/***********************************************************************************************************************
File local variable
***********************************************************************************************************************/
uint8_t cnt_debounce_key[15];
uint8_t flag_release_key = 0;

/***********************************************************************************************************************
Function declaration (Public function)
***********************************************************************************************************************/
char read_keypad (void)
{
	
	char key_temp = 'f';
	/* Make ROW 1 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_RESET);  //Pull the R1 low
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
	
	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[0] ++;
		
		if((HAL_GPIO_ReadPin (C1_PORT, C1_PIN)) && cnt_debounce_key[0] > 0)
		{
			flag_release_key = 1;
			key_temp = 'D';
		}
		else
		{
			
		}
	}
	
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
		key_temp =  '#';
	}
	
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
		key_temp = '0';
	}
	
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
	{
		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
		key_temp = '*';
	}
	
//	/* Make ROW 2 LOW and all other ROWs HIGH */
//	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
//	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_RESET);  // Pull the R2 High
//	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
//	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
//	
//	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
//		return 'C';
//	}
//	
//	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
//		return '9';
//	}
//	
//	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
//		return '8';
//	}
//	
//	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
//		return '7';
//	}
//	
//	
//	/* Make ROW 3 LOW and all other ROWs HIGH */
//	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
//	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
//	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_RESET);  // Pull the R3 High
//	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
//	
//	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
//		return 'B';
//	}
//	
//	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
//		return '6';
//	}
//	
//	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
//		return '5';
//	}
//	
//	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
//		return '4';
//	}
//	
//		
//	/* Make ROW 4 LOW and all other ROWs HIGH */
//	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
//	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
//	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
//	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_RESET);  // Pull the R4 High
//	
//	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
//		return 'A';
//	}
//	
//	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
//		return '3';
//	}
//	
//	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
//		return '2';
//	}
//	
//	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
//	{
//		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
//		return '1';
//	}
	
	return key_temp;

}


/***********************************************************************************************************************
End of file
***********************************************************************************************************************/
