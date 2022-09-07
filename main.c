/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
char time[30];
char date[30];
char Temp_Min;
char Temp_hour;
char Temp_second;
char targetHrs = 13;
char targetmin = 00;
char targetsec = 01;
int min_Int = 0;
int32_t target_weight = 150;

char targetHrs2 = 0;
char targetmin2 = 0;
int32_t target_weight2 = 0;

char targetHrs3 = 0;
char targetmin3 = 0;
int32_t target_weight3 = 0;

uint32_t H_S = 0;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
int32_t live_weight;
uint8_t value=0;
uint8_t i = 0;
int32_t buffer = 0 , weight = 0;
int32_t offset = 0, Read_offset = 0;
double Coef = 0.0;
int32_t Read_Coef = 1000;

int Food_Dispensed_Flag = 0;
char Key = 0;
int Weight_Ready = 0, Menu_Flag = 0;

int weight_read_flag = 0;
int time_read_flag = 0;
int Page_Counter = 0;
int Key_Scanning = 0;
int32_t Weight[3] = {0};
int32_t Time[3] = {0};
int32_t Tmin[3] = {0};

int32_t Weight2[3] = {0};
int32_t Time2[3] = {0};
int32_t Tmin2[3] = {0};

int32_t Weight3[3] = {0};
int32_t Time3[3] = {0};
int32_t Tmin3[3] = {0};

//							    0123456789012345
unsigned char Para1[2][17] = {{"1:Time:-        "},		// Multi Dimensional Array to display the string Temperature and the Temperature
							  {"1:Weight:-      "}};

volatile int Real_Min = 0;
volatile int Real_Hour = 0;

int result = 0;
int PC = 0;
int Start_interrupt_based_Delay = 0;
int start_Delay = 0;

int case5_Flag = 0;

int No = 0;

static int Switch_result = 0;

uint8_t Rx_data_Time[6];
uint8_t Rx_data_control[42];
uint8_t Rx_data_P1[42];
uint8_t Rx_data_P2[42];
uint8_t Rx_data_P3[42];
uint8_t Rx_data[50];
uint8_t data[12] = "T";
uint8_t dataP1[1] = "A";
uint8_t dataP2[1] = "B";
uint8_t dataP3[1] = "C";
uint8_t dataC[1] = "X";
uint8_t dataComplete[1] = "Y";
uint32_t send_flag = 1;
uint32_t DT_Page = 0;
int inc  = 0;


int16_t HresultP1 = 0;
int16_t MresultP1 = 0;
int16_t WresultP1 = 0;

int16_t HresultP2 = 0;
int16_t MresultP2 = 0;
int16_t WresultP2 = 0;

int16_t HresultP3 = 0;
int16_t MresultP3 = 0;
int16_t WresultP3 = 0;

int16_t Control_Counter = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_USART6_UART_Init(void);
/* USER CODE BEGIN PFP */
void Power_Up (void);
void set_time (void);
void HD44780_Init(void);
void HD44780_PutChar(unsigned char c);
void HD44780_GotoXY(unsigned char x, unsigned char y);
void HD44780_PutStr(char *str);
void HD44780_ClrScr(void);
void GET_Print (void);
void set_alarm (void);
void Main_Function (void);
int32_t Read_weight (void);
void power_down(void);
void power_up(void);
void HX711_Init(void);
int32_t HX711_Value(uint8_t gain);
int HX711_Average_Value(uint8_t gain, uint8_t times);
int32_t HX711_Tare(uint8_t gain, uint8_t times);
int32_t hx711_calibration (int32_t Odata);
void Display_Menu (int PC);

int Set_Weight1 (void);
int Set_Time1 (void);

int Set_Weight2 (void);
int Set_Time2 (void);

int Set_Weight3 (void);
int Set_Time3 (void);
int Real_Time(void);
void Disp_Para (int No);



//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
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
  MX_USART2_UART_Init();
  MX_RTC_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
  Power_Up();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  Main_Function();
	 if ((Control_Counter == 1))
	 {
		 HAL_UART_Transmit(&huart6, dataC, sizeof(dataC), 30);
		 HAL_UART_Receive(&huart6, Rx_data_control, sizeof(Rx_data_control), 2500);
		 HAL_Delay(200);
		 if (Rx_data_control[23] == '1')
		 {
			 send_flag = 1;
			 DT_Page = 0;
			 HAL_UART_Transmit(&huart6, dataComplete, sizeof(dataComplete), 30);
			 Control_Counter = 0;
//			 Control_Counter = 0;
		 }


	 }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
//  sTime.Hours = 12;
//  sTime.Minutes = 59;
//  sTime.Seconds = 30;
//  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
//  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
//  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
//  sDate.Month = RTC_MONTH_MAY;
//  sDate.Date = 30;
//  sDate.Year = 22;
//
//  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
//  {
//    Error_Handler();
//  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |SCK_Pin|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : DT_Pin */
  GPIO_InitStruct.Pin = DT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SCK_Pin PA10 */
  GPIO_InitStruct.Pin = SCK_Pin|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void Power_Up (void)
{
	int16_t MresultI = 0;
	int16_t HresultI = 0;
	  HD44780_Init();
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
	  HD44780_ClrScr();
	  //										   0123456789012345
	  unsigned char WelcomeScreen_Data[2][17] = {{"GreenRidge  V-46"},		// Multi Dimensional Array to display the string Temperature and the Temperature
			  	  	  	  	  	  	  	  	  	 {" Initialization "}};

	  HD44780_ClrScr();
	  HD44780_GotoXY(0,0);
	  for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	  {
	  	HD44780_PutChar (WelcomeScreen_Data[0][i]);
	  }

	  HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	  for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	  {
	  	HD44780_PutChar (WelcomeScreen_Data[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	  }

	  HX711_Init();
	  HAL_Delay(500);
	  power_up();
	  Read_offset = HX711_Tare(128, 50);
	  HAL_Delay(1);
	  power_down();
	  KeyPad_Init();



	//  set_time();

		if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x32F2)
		{
		  set_time();
		}

		HD44780_ClrScr();

		Weight_Ready = 1;

	  HAL_UART_Transmit(&huart6, data, sizeof(data), 10);
	  HAL_UART_Receive(&huart6, Rx_data_Time, sizeof(Rx_data_Time), 2500);
	  for (int i=0; i <= 1; i++)
	  {
		  HresultI = (HresultI * 10) + (Rx_data_Time[i] - '0');
	  }
	  Real_Hour = HresultI;
	  for (int i=3; i <= 4; i++)
	  {
		  MresultI = (MresultI * 10) + (Rx_data_Time[i] - '0');
	  }
	  Real_Min = MresultI;
	  set_time();


}
void Main_Function (void)
{
	char ResetHrs = 23;
	char ResetMin = 59;
	char targetHrsOver = 13;
	char targetminOver = 02;
	static int MDF1 = 0;
	static int MDF2 = 0;
	static int MDF3 = 0;
	static int Stop_Weight_Flag = 0;
	static int Stop_Weight_Flag_P2 = 0;
	static int Stop_Weight_Flag_P3 = 0;


	int16_t HresultP1 = 0;
	int16_t MresultP1 = 0;
	int16_t WresultP1 = 0;

	int16_t HresultP2 = 0;
	int16_t MresultP2 = 0;
	int16_t WresultP2 = 0;

	int16_t HresultP3 = 0;
	int16_t MresultP3 = 0;
	int16_t WresultP3 = 0;


//	 if (weight_read_flag == 1)
//	 {
//		 live_weight = Read_weight();
//		 weight_read_flag = 0;
//	 }

	 if (Page_Counter == 0)
	 {
		 if (time_read_flag == 1)
		 {
			 GET_Print();
			 time_read_flag = 0;
		 }
	 }

	 if (MDF1 == 0)
	 {
		 if ((Temp_hour == targetHrs) && (Temp_Min == targetmin))
		 {
			 live_weight = Read_weight();
			 if (Stop_Weight_Flag == 0)
			 {
				 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
			 }
			 if (live_weight >= target_weight)
			 {
				 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
				 Stop_Weight_Flag = 1;
				 MDF1 = 0;
			 }
		 }
	 }

	 if (MDF2 == 0)
	 {
		 if ((Temp_hour == targetHrs2) && (Temp_Min == targetmin2))
		 {
			 live_weight = Read_weight();
			 if (Stop_Weight_Flag_P2 == 0)
			 {
				 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
			 }
			 if (live_weight >= target_weight2)
			 {
				 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
				 Stop_Weight_Flag_P2 = 1;
				 MDF2 = 0;
			 }
		 }
	 }

	 if (MDF3 == 0)
	 {
		 if ((Temp_hour == targetHrs3) && (Temp_Min == targetmin3))
		 {
			 live_weight = Read_weight();
			 if (Stop_Weight_Flag_P3 == 0)
			 {
				 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
			 }
			 if (live_weight >= target_weight3)
			 {
				 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
				 Stop_Weight_Flag_P3 = 1;
				 MDF3 = 0;
			 }
		 }
	 }
	 if ((Temp_hour == targetHrsOver) && (Temp_Min == targetminOver))
	 {
		 live_weight = Read_weight();
	 }
	 if ((Temp_hour == ResetHrs) && (Temp_Min == ResetMin))
	 {
		 MDF1 = 0;
		 Stop_Weight_Flag = 0;

		 MDF2 = 0;
		 Stop_Weight_Flag_P2 = 0;

		 MDF3 = 0;
		 Stop_Weight_Flag_P3 = 0;

		 DT_Page = 0;
	 }
	 if (Key_Scanning == 1)
	 {
		 Key = KeyPad_WaitForKeyGetChar(200);
		 switch(Key)
		 {
		 case 'A':
			 PC = 1;
			 Page_Counter = 1;
			 Display_Menu(PC);
			 break;
		 case '*':
			 PC++;
			 if (PC >= 3)
				 PC = 3;
			 Display_Menu(PC);
				 if (case5_Flag == 1)
				 {
					 No++;
					 if (No >= 3)
						 No = 3;
					 Disp_Para(No);
				 }
			 break;
		 case '#':
			 PC--;
			 if (PC <= 1)
				 PC = 1;
			 Display_Menu(PC);
				 if (case5_Flag == 1)
				 {
					 No--;
					 if (No <= 1)
						 No = 1;
					 Disp_Para(No);
				 }
			 break;
		 case 'C':
		 	 Page_Counter = 0;
		 	 case5_Flag = 0;
		 	 break;
		 case '1':
			 Switch_result = Set_Time1();
			 break;
		 case '2':
			 Switch_result = Set_Time2();
			 break;
		 case '3':
			 Switch_result = Set_Time3();
			 break;
		 case '4':
			 Switch_result = Real_Time();
			 break;
		 case '5':
			 case5_Flag = 1;
			 Disp_Para(No);
			 break;
		 }
	 }
	 if (Switch_result == 1)
	 {
		 if (Start_interrupt_based_Delay == 1)
		 {
			 Page_Counter = 0;
			 start_Delay = 0;
			 Switch_result = 0;
			 Start_interrupt_based_Delay = 0;
			 HD44780_ClrScr();
		 }
	 }


	 if (send_flag == 1)
	 {

		  if (DT_Page == 0)
		  {
			  HAL_UART_Transmit(&huart6, dataP1, sizeof(dataP1), 30);
			  HAL_UART_Receive(&huart6, Rx_data_P1, sizeof(Rx_data_P1), 2500);
			  HAL_Delay(2500);
			  if (Rx_data_P1[9] == '3')
			  {
				  int j = 21;
				  int k = 24;
				  int l = 36;
				  for (int i=0; i <= 1; i++)
				  {

					  HresultP1 = (HresultP1 * 10) + (Rx_data_P1[j] - '0');
					  j++;
				  }
				  targetHrs = HresultP1;
				  for (int i=0; i <= 1; i++)
				  {

					  MresultP1 = (MresultP1 * 10) + (Rx_data_P1[k] - '0');
					  k++;
				  }
				  targetmin = MresultP1;
				  for (int i=0; i <= 2; i++)
				  {

					  WresultP1 = (WresultP1 * 10) + (Rx_data_P1[l] - '0');
					  l++;
				  }
				  target_weight = WresultP1;
				  DT_Page = 1;
			  }
		  }
		  if (DT_Page == 1)
		  {
			  HAL_UART_Transmit(&huart6, dataP2, sizeof(dataP2), 30);
			  HAL_UART_Receive(&huart6, Rx_data_P2, sizeof(Rx_data_P2), 2500);
			  HAL_Delay(2500);
			  if (Rx_data_P2[9] == '4')
			  {
				  int j = 21;
				  int k = 24;
				  int l = 36;
				  for (int i=0; i <= 1; i++)
				  {

					  HresultP2 = (HresultP2 * 10) + (Rx_data_P2[j] - '0');
					  j++;
				  }
				  targetHrs2 = HresultP2;
				  for (int i=0; i <= 1; i++)
				  {

					  MresultP2 = (MresultP2 * 10) + (Rx_data_P2[k] - '0');
					  k++;
				  }
				  targetmin2 = MresultP2;
				  for (int i=0; i <= 2; i++)
				  {

					  WresultP2 = (WresultP2 * 10) + (Rx_data_P2[l] - '0');
					  l++;
				  }
				  target_weight2 = WresultP2;
				  DT_Page = 2;

			  }
		  }
		  if (DT_Page == 2)
		  {
			  HAL_UART_Transmit(&huart6, dataP3, sizeof(dataP3), 30);
			  HAL_UART_Receive(&huart6, Rx_data_P3, sizeof(Rx_data_P3), 2500);
			  HAL_Delay(2500);
			  if (Rx_data_P3[9] == '5')
			  {
				  int j = 21;
				  int k = 24;
				  int l = 36;
				  for (int i=0; i <= 1; i++)
				  {

					  HresultP3 = (HresultP3 * 10) + (Rx_data_P3[j] - '0');
					  j++;
				  }
				  targetHrs3 = HresultP3;
				  for (int i=0; i <= 1; i++)
				  {

					  MresultP3 = (MresultP3 * 10) + (Rx_data_P3[k] - '0');
					  k++;
				  }
				  targetmin3 = MresultP3;
				  for (int i=0; i <= 2; i++)
				  {

					  WresultP3 = (WresultP3 * 10) + (Rx_data_P3[l] - '0');
					  l++;
				  }
				  target_weight3 = WresultP3;
				  DT_Page = 3;
			  }
		  }
//		  if (DT_Page == 3)
//		  {
//			  HAL_UART_Transmit(&huart6, data, sizeof(data), 10);
//			  HAL_UART_Receive(&huart6, Rx_data_Time, sizeof(Rx_data_Time), 500);
//			  for (int i=0; i <= 1; i++)
//			  {
//				  HresultI = (HresultI * 10) + (Rx_data_Time[i] - '0');
//			  }
//			  Real_Hour = HresultI;
//			  for (int i=3; i <= 4; i++)
//			  {
//				  MresultI = (MresultI * 10) + (Rx_data_Time[i] - '0');
//			  }
//			  Real_Min = MresultI;
//			  set_time();
//			  DT_Page = 4;
//		  }
		  send_flag = 0;
	 }
}



void GET_Print (void)
{
	  //			        0123456789012345
	  char Mainline[17] = {"Press A for Menu"};
	  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	  sprintf(date,"Date: %02d.%02d.%02d",sDate.Date,sDate.Month,sDate.Year);
	  sprintf(time,"Time: %02d.%02d",sTime.Hours,sTime.Minutes);
	  Temp_Min = sTime.Minutes;
	  Temp_hour = sTime.Hours;
	  Temp_second = sTime.Seconds;
	  HD44780_GotoXY(0, 0);
	  HD44780_PutStr(time);

	  HD44780_GotoXY(0, 1);
	  HD44780_PutStr(Mainline);
}


void set_time (void)												// Function to set Date and Time parameters
{
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	sTime.Hours = Real_Hour;
	sTime.Minutes = Real_Min;
	sTime.Seconds = 0;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
	Error_Handler();
	}
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month = RTC_MONTH_MAY;
	sDate.Date = 30;
	sDate.Year = 22;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	{
	Error_Handler();
	}
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2); // backup register

	if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x32F2)
	{
		set_time();
	}

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
