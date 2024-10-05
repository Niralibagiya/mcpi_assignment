/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define BV(n)     (1 << (n))

#define LCD_SLAVE_ADDR_W	0x4E
#define LCD_SLAVE_ADDR_R	0x4F
//#define LCD_SLAVE_ADDR_W	0x7E
//#define LCD_SLAVE_ADDR_R	0x7F

#define LCD_CLEAR				0x01
#define LCD_FN_SET_8BIT			0x30
#define LCD_FN_SET_4BIT_1LINE	0x20
#define LCD_FN_SET_4BIT_2LINES	0x28
#define LCD_DISP_CTRL			0x08
#define LCD_DISP_ON				0x0C
#define LCD_ENTRY_MODE			0x06
#define LCD_LINE1				0x80
#define LCD_LINE2				0xC0
#define LCD_DISP_SHIFT_LEFT		0x18
#define LCD_DISP_SHIFT_RIGHT	0x1C

#define LCD_RS	0
#define LCD_RW	1
#define LCD_EN	2
#define LCD_BL	3

#define LCD_CMD		0x80
#define LCD_DATA	1
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void Lcd_Write4BitAndCtrl(uint8_t val);
void Lcd_WriteByte(uint8_t rs, uint8_t val);
void Lcd_Puts(uint8_t line, char str[]);
int Lcd_Init();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  Lcd_Init();
  /* USER CODE END 2 */
  Lcd_Puts(LCD_LINE1, "Hello");
  //Lcd_Puts(LCD_LINE2, "I am Prasad!");
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void Lcd_Write4BitAndCtrl(uint8_t val) {
	//I2C_Start();
	//I2C_SendSlaveAddr(LCD_SLAVE_ADDR_W);
	//I2C_SendData(val);
	//I2C_Stop();
	HAL_I2C_Master_Transmit(&hi2c1, LCD_SLAVE_ADDR_W, &val, sizeof(val), 50);
}
void Lcd_WriteByte(uint8_t rs, uint8_t val) {
	uint8_t high = val & 0xF0, low = (val << 4) & 0xF0;
	uint8_t bvrs = (rs == LCD_CMD) ? 0 : BV(LCD_RS);
	Lcd_Write4BitAndCtrl(high | bvrs | BV(LCD_EN) | BV(LCD_BL));
	HAL_Delay(1);//DelayMs(1);
	Lcd_Write4BitAndCtrl(high | bvrs | BV(LCD_BL));
	Lcd_Write4BitAndCtrl(low | bvrs | BV(LCD_EN) | BV(LCD_BL));
	HAL_Delay(1);//DelayMs(1);
	Lcd_Write4BitAndCtrl(low | bvrs | BV(LCD_BL));
}
int Lcd_Init()
{
	// wait for 15ms
	HAL_Delay(20);//DelayMs(20);
	// check if lcd is ready
	if(HAL_I2C_IsDeviceReady(&hi2c1, LCD_SLAVE_ADDR_W, 5, 50) != HAL_OK)
		return 1;

	// attention sequence
	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT);
	HAL_Delay(5);//DelayMs(5);

	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT);
	HAL_Delay(1);//DelayMs(1);

	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT);
	HAL_Delay(3);//DelayMs(3);

	Lcd_Write4BitAndCtrl(LCD_FN_SET_4BIT_1LINE | BV(LCD_EN));
	__NOP();
	Lcd_Write4BitAndCtrl(LCD_FN_SET_4BIT_1LINE);
	HAL_Delay(3);//DelayMs(3);

	// lcd initialization
	//Lcd_WriteByte(LCD_CMD, LCD_FN_SET_4BIT_2LINES);
	Lcd_WriteByte(LCD_CMD, LCD_FN_SET_4BIT_1LINE);
	HAL_Delay(1);//DelayMs(1);
	Lcd_WriteByte(LCD_CMD, LCD_DISP_CTRL); // no shift, decrementing cursor move
	HAL_Delay(1);//DelayMs(1);
	Lcd_WriteByte(LCD_CMD, LCD_CLEAR); // clear lcd
	HAL_Delay(1);//DelayMs(1);
	Lcd_WriteByte(LCD_CMD, LCD_ENTRY_MODE); // incrementing cursor move, no shift
	HAL_Delay(1);//DelayMs(1);
	Lcd_WriteByte(LCD_CMD, LCD_DISP_ON); // display on
	HAL_Delay(1);//DelayMs(1);

	return 0;
}
void Lcd_Puts(uint8_t line, char str[]) {
	int i;
	Lcd_WriteByte(LCD_CMD, line); // line address
	HAL_Delay(1);//DelayMs(1);
	for(i=0; str[i]!='\0'; i++)
		Lcd_WriteByte(LCD_DATA, str[i]);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
