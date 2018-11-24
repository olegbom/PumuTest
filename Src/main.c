
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "fatfs.h"
#include "rng.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
#include "fsmc.h"

/* USER CODE BEGIN Includes */
#include "ili9341.h"
#include "math.h"
#include "asteroids.h"
#include "lis3.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
volatile uint16_t ADC_Data[4];
volatile float cReal = 0;
volatile float cImag = 0;
volatile float zoom = 100;
volatile float xOffset = 0;
volatile float yOffset = 0;
volatile uint16_t colorX = 0;
volatile uint16_t colorY = 0;
volatile uint16_t color = 0xFFFF;
volatile uint16_t colorLines = 0xFFFF;
volatile uint8_t  zeroBit = 0;
volatile uint8_t modeJoy2 = 0;
volatile uint8_t modeJoy1 = 0;
volatile uint8_t modeSwitchFlag = 1;
volatile uint8_t colorSwitchFlag = 1;
volatile uint8_t juliaSwitchFlag = 1;
volatile uint32_t tim3Counter = 0;

volatile uint16_t FpsCountner = 0;
volatile uint16_t FpsReal = 0;

extern USBH_HandleTypeDef hUsbHostFS;
extern ApplicationTypeDef Appli_state;
FATFS USBDISKFatFs;
FIL MyFile;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

void FileReadWrite(void)
{
	FRESULT res;
	uint32_t byteswritten, bytesread;
	uint8_t r_text[100];
	if(f_mount(&USBDISKFatFs, (TCHAR const*) USBHPath, 0) != FR_OK)
    {
      LCD_DisplayStringLine(0, 30, "USB Ошибка подключения!");
	 // Error_Handler();
    }
	else
	{

		DIR dir;
		uint8_t i = 30;
		static FILINFO fno;
		res = f_opendir(&dir, (TCHAR const*) USBHPath);
		if (res == FR_OK)
		{
			while(1)
			{
				res = f_readdir(&dir, &fno);
				if (res != FR_OK || fno.fname[0] == 0) break;
				LCD_DisplayStringLine(0, i, fno.fname);
				i+=15;
			}
			f_closedir(&dir);
		}
       /*
	   res = f_open(&MyFile, "123.txt", FA_READ);
	   if(res != FR_OK)
	   {
		   LCD_DisplayStringLine(0, 50, "ERROR File Open!", 40);
		 //Error_Handler();
	   }
	   else
	   {
		 LCD_DisplayStringLine(0, 50, "File Open!", 40);
		 res = f_read(&MyFile,r_text,sizeof(r_text),(void*)&bytesread);
		 if((bytesread==0)||(res!=FR_OK))
		 {
			 LCD_DisplayStringLine(0, 70, "File Bad Data!", 40);
		 }
		 else
		 {
		   r_text[bytesread]=0;//обнулим байт, следующий за последним
		   LCD_DisplayStringLine(0, 70, (char*) r_text, 100);
		   f_close(&MyFile);
		 }

	   }
	   LCD_DisplayStringLine(0, 30, "USB подключен!", 40);*/
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint16_t Joy1_ButtonState = 0;
  static uint16_t Joy2_ButtonState = 0;
  static uint16_t secondCountner = 0;


  if(htim->Instance == htim3.Instance)
  {
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*) ADC_Data,4);
    int16_t dx;
    int16_t dy;



    Joy1_ButtonState <<=1 ;
    Joy1_ButtonState += HAL_GPIO_ReadPin(Joy1_SW_GPIO_Port, Joy1_SW_Pin);
    if((Joy1_ButtonState & 0x03FF) == 0x0200)
    {
      //Нажалась кнопка
      modeJoy2++;
      if(modeJoy2>5) modeJoy2 = 0;
      modeSwitchFlag = 1;
      juliaSwitchFlag = 1;

    }

     switch (modeJoy2) {
       case 0:
         dx = (ADC_Data[2] - 2048) /256;
         dy = (ADC_Data[3] - 2048) /256;
         cReal += dx/4096.0f/4;
         cImag += dy/4096.0f/4;
           if(dx != 0 || dy != 0)
             juliaSwitchFlag = 1;
         break;
       case 1:
         if(!(tim3Counter & 0x03))
         {
           dx = (ADC_Data[2] - 2048) /256;
           dy = (ADC_Data[3] - 2048) /256;

           colorX -= dx;
           if(colorX>LCD_TFTWIDTH + 10) colorX = 0;
           else if(colorX>LCD_TFTWIDTH-1 ) colorX = LCD_TFTWIDTH - 1;

           colorY += dy;
           if(colorY < 24) colorY = 24;
           else if(colorY>LCD_TFTHEIGHT - 1) colorY = LCD_TFTHEIGHT - 1;

           if(dx != 0 || dy != 0)
             colorSwitchFlag = 1;
       //  color = xy2rgb(((float)ADC_Data[2] - 2048)/2048, ((float)ADC_Data[3] - 2048)/2048);
         }
         break;


     }


    Joy2_ButtonState <<= 1;
    Joy2_ButtonState += HAL_GPIO_ReadPin(Joy2_SW_GPIO_Port, Joy2_SW_Pin);
    if((Joy2_ButtonState & 0x03FF) == 0x0200)
    {
      //Нажалась кнопка
      modeJoy1++;
      if(modeJoy1>1) modeJoy1 = 0;
      modeSwitchFlag = 1;
      juliaSwitchFlag = 1;

      if(modeJoy2 == 3)
      {
    	  zeroBit++;
		  if(zeroBit == 16) zeroBit = 0;
    	  colorLines = 0xFFFF & (~(1 << zeroBit));
      }
    }

    switch (modeJoy1) {

      case 0:
        dx = (ADC_Data[0] - 2048) /256;

        zoom *= 1.0f - dx/1024.0f;
          if(dx != 0 )
            juliaSwitchFlag = 1;
        break;
      case 1:
        dx = (ADC_Data[1] - 2048) /256;
        dy = (ADC_Data[0] - 2048) /256;
        xOffset -= dx/4.0f/zoom;
        yOffset += dy/4.0f/zoom;
        if(dx != 0 || dy != 0)
          juliaSwitchFlag = 1;
        break;
    }


    secondCountner++;
    if(secondCountner == 100) {
      secondCountner = 0;
      FpsReal = FpsCountner;
      FpsCountner = 0;
    }
    tim3Counter++;
  }
}
uint16_t tim4_counter = 0;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == htim12.Instance)
	{
		tim4_counter = htim12.Instance->CCR2;
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_FSMC_Init();
  MX_SPI2_Init();
  MX_TIM3_Init();
  MX_USB_HOST_Init();
  MX_FATFS_Init();
  MX_USART6_UART_Init();
  MX_TIM2_Init();
  MX_TIM12_Init();
  MX_SPI1_Init();
  MX_RNG_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  char joy_data_string[100];

  HAL_ADC_Start_DMA(&hadc1,(uint32_t*) ADC_Data,4);

  LCD_Init();

  HAL_Delay(100);

  LCD_SetTextColor(YELLOW);

  LCD_FillScreen(RED);
  HAL_TIM_Base_Start(&htim3);
  HAL_NVIC_SetPriority(TIM3_IRQn, 2, 1);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  HAL_TIM_Base_Start_IT(&htim3);

  HAL_TIM_Base_Start_IT(&htim12);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
  HAL_TIM_IC_Start_IT(&htim12, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim12, TIM_CHANNEL_2);


  char message[70] = "";
  uint16_t oldColorX = 0, oldColorY = 0;
  while (1)
  {

  /* USER CODE END WHILE */
    MX_USB_HOST_Process();

  /* USER CODE BEGIN 3 */


    FpsCountner++;






    if(modeJoy2 == 1)
    {
      if(colorSwitchFlag)
      {


     //    LCD_DrawPixel(oldColorX, oldColorY, color);
     //    color = xy2rgb(((float)colorX - LCD_TFTWIDTH/2.0f)/(LCD_TFTWIDTH)*2.0f, ((float)colorY - 24 - (LCD_TFTHEIGHT-24)/2.0f)/(LCD_TFTHEIGHT-24)*2.0f);


     //    LCD_DrawRect(300,14,10,10,color);

        // LCD_DrawPixel(colorX, colorY, BLACK);
         color = LCD_DrawColorPipet(colorX, colorY, oldColorX, oldColorY);
         oldColorX = colorX;
         oldColorY = colorY;
         uint16_t r = color >> 11;
         uint16_t g = (color >> 5) & 0x3F;
         uint16_t b = color & 0x1F;


         sprintf(joy_data_string, "(%4u;%4u) (%2u;%2u;%2u) FPS %3d;", colorX, colorY, r,g,b, FpsReal);
         LCD_DisplayStringLine(0, 0, joy_data_string);



         colorSwitchFlag = 0;

         //TEST ZONE




         //END TEST ZONE

      }
      switch (modeJoy1) {
        case 0:
          LCD_DisplayStringLine(0, 13, "Джойстик 1: Масштаб");
          break;
        case 1:
          LCD_DisplayStringLine(0, 13, "Джойстик 1: Перемещение");
          break;
      }

    }
    else if(modeJoy2 == 0)
    {
      if(juliaSwitchFlag)
      {
        LCD_GenerateJuliaFpu(xOffset, yOffset, zoom, cReal, cImag, color);
        juliaSwitchFlag = 0;
      }
      sprintf(joy_data_string, "Центр (%5.4f; %5.4f); с (%5.4f; %5.4fi); Zoom %5.2f; FPS %3d;", xOffset, yOffset, cReal, cImag, zoom, FpsReal);


      LCD_DisplayStringLine(0, 0, joy_data_string);

      HAL_UART_Transmit(&huart2, (uint8_t*)joy_data_string, 70, 100);
      HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 5, 100);


      float distance = (float)(tim4_counter)/2.0f/29.1f;
	  sprintf (message, "Дальнометр: %8d мм", (uint16_t)((tim4_counter)/2.0f/29.1f*10));


      LCD_DisplayStringLine(0, 26, message);
    }
    else if(modeJoy2 == 3)
    {

    	sprintf (message, "FPS: %d bit: %d", FpsReal, zeroBit);
    	LCD_DisplayStringLine(0, 13, message);

    	LCD_SetRecordingArea(0, 32, LCD_TFTWIDTH, LCD_TFTHEIGHT - 32);
		LCD_WriteCommand(LCD_MEMORYWRITE);
		for(uint16_t y = 32; y < LCD_TFTHEIGHT; y++)
		for(uint16_t x = 0; x < LCD_TFTWIDTH; x++)
		{
			uint16_t color = (x+tim3Counter/2) % (4+(y-20)/8) ? BLACK: colorLines;
			//LCD_DrawPixel(x,y,color);
			LCD_WriteData(color);
		}

    }
    else if(modeJoy2 == 4)
    {

        set_input(ADC_Data[1], ADC_Data[0], ADC_Data[2], ADC_Data[3]);

        asteroids_game_draw();
    }
    else if(modeJoy2 == 5)
    {

        int16_t lis3_x = LIS3_ReadX();
        int16_t lis3_y = LIS3_ReadY();
        int16_t lis3_z = LIS3_ReadZ();


        sprintf(message,"X: %6d", lis3_x);
        LCD_DisplayStringLine(0, 52, message);
        sprintf(message,"Y: %6d", lis3_y);
        LCD_DisplayStringLine(0, 65, message);
        sprintf(message,"Z: %6d", lis3_z);
        LCD_DisplayStringLine(0, 78, message);
        sprintf(message,"FPS: %3d", FpsReal);
        LCD_DisplayStringLine(0, 91, message);

        static uint16_t x_old = 0, y_old = 0;
        LCD_DrawLine(LCD_TFTWIDTH/2, LCD_TFTHEIGHT/2, x_old, y_old, BLACK);

        uint16_t lcd_x = LCD_TFTWIDTH/2 + lis3_y/170;
        uint16_t lcd_y = LCD_TFTHEIGHT/2 + lis3_x/170;
        LCD_DrawLine(LCD_TFTWIDTH/2, LCD_TFTHEIGHT/2, lcd_x, lcd_y, WHITE);
        x_old = lcd_x;
        y_old = lcd_y;
    }


    if( modeSwitchFlag == 1)
    {
      LCD_DrawRect(0,13, LCD_TFTWIDTH, 13, BLACK);
      switch (modeJoy2) {
        case 0:
          LCD_DisplayStringLine(160, 13, "Джойстик 2: Константа");
          break;
        case 1:
          LCD_DisplayStringLine(160, 13, "Джойстик 2: Цвет");

          LCD_SetRecordingArea(0, 24, LCD_TFTWIDTH, LCD_TFTHEIGHT - 24);
          LCD_WriteCommand(LCD_MEMORYWRITE);
          for(uint16_t y = 24; y < LCD_TFTHEIGHT; y++)
          for(uint16_t x = 0; x < LCD_TFTWIDTH; x++)
          {
            uint16_t color = xy2rgb(((float)x - LCD_TFTWIDTH/2.0f)/(LCD_TFTWIDTH)*2.0f, ((float)y - 24 - (LCD_TFTHEIGHT-24)/2.0f)/(LCD_TFTHEIGHT-24)*2.0f);
            LCD_WriteData(color);
          }

          break;
        case 2:
		  if(Appli_state == APPLICATION_START)
		  {
		 	FileReadWrite();
			Appli_state = APPLICATION_IDLE;
		  }
		  else if(Appli_state == APPLICATION_IDLE)
		  {

		  }
          break;
        case 4:
          LCD_FillScreen(BLACK);
          break;
        case 5:
          LCD_FillScreen(BLACK);
          LIS3_Init();

          uint8_t lis3_who_am_i = LIS3_ReadReg(LIS3_ADDR_WHO_AM_I);
          uint8_t lis3_info1 = LIS3_ReadReg(LIS3_ADDR_INFO1);
          uint8_t lis3_info2 = LIS3_ReadReg(LIS3_ADDR_INFO2);


          LCD_DisplayStringLine(0, 0, "LIS3 Registers:");
          sprintf(message,"Who am I: 0x%2.2X", lis3_who_am_i);
          LCD_DisplayStringLine(0, 13, message);
          sprintf(message,"INFO1: 0x%2.2X", lis3_info1);
          LCD_DisplayStringLine(0, 26, message);
          sprintf(message,"INFO2: 0x%2.2X", lis3_info2);
          LCD_DisplayStringLine(0, 39, message);
          break;
      }

      modeSwitchFlag = 0;
    }

    HAL_Delay(10);

    //HAL_UART_Transmit(&huart2, joy_data_string, 30, 100);


  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
