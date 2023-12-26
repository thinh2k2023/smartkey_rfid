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
uint8_t cnt_debounce_key[16];
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

		
	}
	else
	{
		if(cnt_debounce_key[0] > 0 && HAL_GPIO_ReadPin (C1_PORT, C1_PIN))
		{
			cnt_debounce_key[0] = 0;
			flag_release_key = 1;
			key_temp = 'D';
		}
		else
		{
			//do nothing
		}
	}
	
	
	///
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[1] ++;
		
	}
	else
	{
		if(cnt_debounce_key[1] > 0 && HAL_GPIO_ReadPin (C2_PORT, C2_PIN))
		{
			cnt_debounce_key[1] = 0;
			flag_release_key = 1;
			key_temp = '#';
		}
		else
		{
			//do nothing
		}
	}
	
		///
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[2] ++;
		
	}
	else
	{
		if(cnt_debounce_key[2] > 0 && HAL_GPIO_ReadPin (C3_PORT, C3_PIN))
		{
			cnt_debounce_key[2] = 0;
			flag_release_key = 1;
			key_temp = '0';
		}
		else
		{
			//do nothing
		}
	}
	
			///
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[3] ++;
		
	}
	else
	{
		if(cnt_debounce_key[3] > 0 && HAL_GPIO_ReadPin (C4_PORT, C4_PIN))
		{
			cnt_debounce_key[3] = 0;
			flag_release_key = 1;
			key_temp = '*';
		}
		else
		{
			//do nothing
		}
	}
	
	
	
	
	
	/* Make ROW 2 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_RESET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High

	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[4] ++;
		
	}
	else
	{
		if(cnt_debounce_key[4] > 0 && HAL_GPIO_ReadPin (C1_PORT, C1_PIN))
		{
			cnt_debounce_key[4] = 0;
			flag_release_key = 1;
			key_temp = 'C';
		}
		else
		{
			//do nothing
		}
	}
	
	
	///
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[5] ++;
		
	}
	else
	{
		if(cnt_debounce_key[5] > 0 && HAL_GPIO_ReadPin (C2_PORT, C2_PIN))
		{
			cnt_debounce_key[5] = 0;
			flag_release_key = 1;
			key_temp = '9';
		}
		else
		{
			//do nothing
		}
	}
	
		///
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[6] ++;
		
	}
	else
	{
		if(cnt_debounce_key[6] > 0 && HAL_GPIO_ReadPin (C3_PORT, C3_PIN))
		{
			cnt_debounce_key[6] = 0;
			flag_release_key = 1;
			key_temp = '8';
		}
		else
		{
			//do nothing
		}
	}
	
			///
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[7] ++;
		
	}
	else
	{
		if(cnt_debounce_key[7] > 0 && HAL_GPIO_ReadPin (C4_PORT, C4_PIN))
		{
			cnt_debounce_key[7] = 0;
			flag_release_key = 1;
			key_temp = '7';
		}
		else
		{
			//do nothing
		}
	}

	
	/* Make ROW 3 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_RESET);  // Pull the R3 High
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
	
	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[8] ++;
		
	}
	else
	{
		if(cnt_debounce_key[8] > 0 && HAL_GPIO_ReadPin (C1_PORT, C1_PIN))
		{
			cnt_debounce_key[8] = 0;
			flag_release_key = 1;
			key_temp = 'B';
		}
		else
		{
			//do nothing
		}
	}
	
	
	///
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[9] ++;
		
	}
	else
	{
		if(cnt_debounce_key[9] > 0 && HAL_GPIO_ReadPin (C2_PORT, C2_PIN))
		{
			cnt_debounce_key[9] = 0;
			flag_release_key = 1;
			key_temp = '6';
		}
		else
		{
			//do nothing
		}
	}
	
		///
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[10] ++;
		
	}
	else
	{
		if(cnt_debounce_key[10] > 0 && HAL_GPIO_ReadPin (C3_PORT, C3_PIN))
		{
			cnt_debounce_key[10] = 0;
			flag_release_key = 1;
			key_temp = '5';
		}
		else
		{
			//do nothing
		}
	}
	
			///
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[11] ++;
		
	}
	else
	{
		if(cnt_debounce_key[11] > 0 && HAL_GPIO_ReadPin (C4_PORT, C4_PIN))
		{
			cnt_debounce_key[11] = 0;
			flag_release_key = 1;
			key_temp = '4';
		}
		else
		{
			//do nothing
		}
	}
	
		
	/* Make ROW 4 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_RESET);  // Pull the R4 High

	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[12] ++;
		
	}
	else
	{
		if(cnt_debounce_key[12] > 0 && HAL_GPIO_ReadPin (C1_PORT, C1_PIN))
		{
			cnt_debounce_key[12] = 0;
			flag_release_key = 1;
			key_temp = 'A';
		}
		else
		{
			//do nothing
		}
	}
	
	
	///
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[13] ++;
		
	}
	else
	{
		if(cnt_debounce_key[13] > 0 && HAL_GPIO_ReadPin (C2_PORT, C2_PIN))
		{
			cnt_debounce_key[13] = 0;
			flag_release_key = 1;
			key_temp = '3';
		}
		else
		{
			//do nothing
		}
	}
	
		///
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[14] ++;
		
	}
	else
	{
		if(cnt_debounce_key[14] > 0 && HAL_GPIO_ReadPin (C3_PORT, C3_PIN))
		{
			cnt_debounce_key[14] = 0;
			flag_release_key = 1;
			key_temp = '2';
		}
		else
		{
			//do nothing
		}
	}
	
			///
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 1 is low
	{
		cnt_debounce_key[15] ++;
		
	}
	else
	{
		if(cnt_debounce_key[15] > 0 && HAL_GPIO_ReadPin (C4_PORT, C4_PIN))
		{
			cnt_debounce_key[15] = 0;
			flag_release_key = 1;
			key_temp = '1';
		}
		else
		{
			//do nothing
		}
	}
	
	return key_temp;

}


/***********************************************************************************************************************
End of file
***********************************************************************************************************************/
