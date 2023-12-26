/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1_rc522.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "i2c-lcd.h"

#include "key_scan.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


I2C_HandleTypeDef hi2c1;
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);

uint8_t str[MAX_LEN];
char RF_check[2][5];
char RF_data[5];
char RF_save[3][5];
uint8_t key;
char password[] = "1234";
char enteredPassword[5]; 

uint8_t save_card_id[3][4]; 
uint8_t state_machine = 0;


uint8_t flag_read_com_test = 0;

uint8_t num_add_card = 0;

//
char save_password[5] = {'1', '2', '3', '4', '5'};
uint8_t cnt_check_pass = 0;
char key_item[6];

int cnt_key_read = 0;
uint8_t read_5_char_key()
{
	key_item[5] = '\0';

	uint8_t flag_read_complete = 0;
	
	if(flag_release_key == 1)
	{
		flag_release_key = 0;
		if(key == 'D')
		{
			cnt_key_read --;
			key_item[cnt_key_read] = 0;
			
			lcd_goto_XY(2,cnt_key_read);
			lcd_send_string(" ");
			
			if(cnt_key_read <= 0)
			{
				cnt_key_read = 0;
			}
			
		}
		else
		{
			key_item[cnt_key_read] = key;
			cnt_key_read ++;
			
			lcd_goto_XY(2,0);
			lcd_send_string(key_item);
			
			if(cnt_key_read >= 5)
			{
				cnt_key_read = 0;
				flag_read_complete = 1;
			}
			else
			{
				flag_read_complete = 0;
			}
		}
	}
	return flag_read_complete;
}

void clear_key_5_char()
{
	cnt_key_read = 0;
	for(uint8_t i = 0; i < 5; i++)
	{
		key_item[i] = 0;
	}
}

void reset_rf_data()
{
	RF_data[0] = 0;		
	RF_data[1] = 0;		
	RF_data[2] = 0;		
	RF_data[3] = 0;		
	RF_data[4] = 0;
}


uint8_t cnt_read = 0;
void read_card()
{
	if(!MFRC522_Request(PICC_REQIDL, str))
	{
		if(!MFRC522_Anticoll(str))
		{
			RF_data[0] = str[0];		
			RF_data[1] = str[1];		
			RF_data[2] = str[2];		
			RF_data[3] = str[3];		
			RF_data[4] = str[4];
			cnt_read ++;
		}
	}
}


uint8_t cnt_check_card = 0;
uint8_t flag_check_card = 0;
uint8_t check_card()
{
	for(uint8_t i = 0; i < 3; i++)
	{
		for(uint8_t j = 0; j < 5; j++)
		{
			if((RF_save[i][j] == RF_data[j]) && (cnt_read > 2))
			{
				cnt_read = 0;
				cnt_check_card ++;
			}
		}
	}
	if(cnt_check_card >= 5)
	{
		cnt_check_card = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}



int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
	
	HAL_Delay(1000);
	MFRC522_Init();
	lcd_init ();
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	

	
	
  while (1)
  {
		key = read_keypad ();
		
		
		if(flag_release_key == 1)
		{
			
			
			if(key == 'A')
			{
				state_machine = 1;
				flag_release_key = 0;
			}
			else if(key == 'B')
			{
				state_machine = 2;
				flag_release_key = 0;
				cnt_read = 0;
			}
			else if(key == 'C')
			{
				state_machine = 0;		//back to main screen
				flag_release_key = 0;
				HAL_Delay(50);
				lcd_clear_display();
				clear_key_5_char();
				reset_rf_data();
			}
			else
			{
				//state_machine = 0;
			}
		}
			
		if(state_machine == 0)
		{
				read_card();
				flag_check_card = check_card();
				if(flag_check_card ==1)
				{
					flag_check_card = 0;
					cnt_check_pass = 0;
					lcd_goto_XY(1,0);
					clear_key_5_char();
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8, GPIO_PIN_SET);
					htim1.Instance->CCR1 = 25;
					HAL_Delay(4000);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8, GPIO_PIN_RESET);
					htim1.Instance->CCR1 = 45;
					lcd_goto_XY(2,0);
					lcd_send_string("                 ");					
				}

			
				lcd_goto_XY(1,0);
				lcd_send_string("Enter password:");
				uint8_t read_complete_flag = read_5_char_key();
				HAL_Delay(100);
				if( read_complete_flag == 1)
				{
					for(uint8_t i = 0; i < 5; i ++)
					{
						if(key_item[i] == save_password[i])
						{
							cnt_check_pass ++;
						}
					}
					if(cnt_check_pass >= 5 || (flag_check_card == 1))
					{
						cnt_check_pass = 0;
						lcd_goto_XY(1,0);
						clear_key_5_char();
						lcd_send_string("Open door!         ");
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8, GPIO_PIN_SET);
						htim1.Instance->CCR1 = 25;
						HAL_Delay(4000);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8, GPIO_PIN_RESET);
						htim1.Instance->CCR1 = 45;
						lcd_goto_XY(2,0);
						lcd_send_string("                 ");
						
						//open door
					}
					else
					{
						cnt_check_pass = 0;
						lcd_goto_XY(1,0);
						clear_key_5_char();
						lcd_send_string("NG password:      ");
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9, GPIO_PIN_SET);
						HAL_Delay(1000);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9, GPIO_PIN_RESET);
						HAL_Delay(1000);
						lcd_goto_XY(2,0);
						lcd_send_string("                 ");
					}
				}
		}
		
		if(state_machine == 1)
		{
				lcd_goto_XY(1,0);
				lcd_send_string("Old password:    ");
				uint8_t read_complete_flag = read_5_char_key();
				HAL_Delay(100);
				if( read_complete_flag == 1)
				{
					for(uint8_t i = 0; i < 5; i ++)
					{
						if(key_item[i] == save_password[i])
						{
							cnt_check_pass ++;
						}
					}
					if(cnt_check_pass >= 5)
					{
						cnt_check_pass = 0;
						clear_key_5_char();
						lcd_goto_XY(1,0);
						lcd_send_string("OK!            ");
						HAL_Delay(1000);
						lcd_goto_XY(2,0);
						lcd_send_string("                 ");
						state_machine = 3;
						//open door
					}
					else
					{
						clear_key_5_char();
						cnt_check_pass = 0;
						lcd_goto_XY(1,0);
						lcd_send_string("NG password:     ");
						lcd_goto_XY(2,0);
						lcd_send_string("                 ");
						HAL_Delay(500);
						lcd_goto_XY(2,0);
						lcd_send_string("                 ");
						lcd_goto_XY(1,0);
						lcd_send_string("Old password:     ");
						lcd_goto_XY(2,0);
						lcd_send_string("                 ");
					}
				}
		}
		
		if(state_machine == 3)
		{
			lcd_goto_XY(1,0);
			lcd_send_string("New password:      ");
			uint8_t read_complete_flag = read_5_char_key();
			HAL_Delay(100);
			if( read_complete_flag == 1)
			{
				for(uint8_t i = 0; i < 5; i ++)
				{
					save_password[i] = key_item[i];
				}
				clear_key_5_char();
				HAL_Delay(500);
				lcd_goto_XY(2,0);
				lcd_send_string("OK!                ");
				HAL_Delay(500);
				lcd_goto_XY(2,0);
				lcd_send_string("                 ");
				state_machine = 0;
			}			
		}
		
		if(state_machine == 2)
		{
			HAL_Delay(50);
			lcd_goto_XY(1,0);
			lcd_send_string("Add card:         ");
			
			if(flag_release_key == 1)
			{
				if(key == '1')
				{
					flag_release_key = 0;
					lcd_goto_XY(2,0);
					HAL_Delay(50);
					lcd_send_string("Add card 1!");
					num_add_card = 1;
				}
				else if(key == '2')
				{
					flag_release_key = 0;
					lcd_goto_XY(2,0);
					HAL_Delay(50);
					lcd_send_string("Add card 2!");
					num_add_card = 2;
				}
				else if(key == '3')
				{
					flag_release_key = 0;
					lcd_goto_XY(2,0);
					HAL_Delay(50);
					lcd_send_string("Add card 3!");
					num_add_card = 3;
				}
			}
			
			if(num_add_card == 1)
			{
				
				read_card();
				if(cnt_read > 3)
				{
					
					//reset flag
					cnt_read = 0;
					
					//save data card
					for(uint8_t i = 0; i < 5; i++)
					{
						RF_save[0][i] = RF_data[i];
					}
					
					//reset RF
					reset_rf_data();
					
					//reset num add card
					num_add_card = 0;
					
					//lcd print
					lcd_goto_XY(2,0);
					lcd_send_string("OK!               ");
				}
			}
			
			if(num_add_card == 2)
			{
				
				read_card();
				if(cnt_read > 3)
				{
					
					//reset flag
					cnt_read = 0;
					
					//save data card
					for(uint8_t i = 0; i < 5; i++)
					{
						RF_save[1][i] = RF_data[i];
					}
					
					//reset RF
					reset_rf_data();
					
					//reset num add card
					num_add_card = 0;
					lcd_goto_XY(2,0);
					HAL_Delay(50);
					lcd_send_string("OK!               ");
				}
			}
			
			if(num_add_card == 3)
			{
				
				read_card();
				if(cnt_read > 3)
				{
					
					//reset flag
					cnt_read = 0;
					
					//save data card
					for(uint8_t i = 0; i < 5; i++)
					{
						RF_save[2][i] = RF_data[i];
					}
					
					//reset RF
					reset_rf_data();
					
					//reset num add card
					num_add_card = 0;
					lcd_goto_XY(2,0);
					lcd_send_string("OK!               ");
				}
			}
		}
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 450;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 450;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15
                           PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
