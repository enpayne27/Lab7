/* Lab 7
  ******************************************************************************
  * @file    main.c
  * @author  Erin Payne
  * @version V1.0
  * @date    8-May-2019
  * @brief   Default main function.
  ******************************************************************************
*/
#include "main.h"
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l475e_iot01.h"
#include "string.h"
#include "USART.h"
#include "circularBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include "SerialWifiBridge"

static uint32_t USARTCount = 0;
static commBuffer_t RX;
static commBuffer_t TX;

int main(void)
{
	HAL_Init();
	// Configure the System clock to have a frequency of 80 MHz
	SystemClock_Config();

	//Initializes Buffers
	initBuffer(&RX, 0);
	initBuffer(&TX, 1);

	// Configure UART4
	Configure_USART();

	// Startup test text
	char* text = "\nChip programmed successfully\n";
	SendCharArrayUSART4(text,strlen(text));

	while(1){
		// Check if there is a message in the receiving buffer
		if(haveMessage(&RX)){
			// Create string to hold incoming message
			char input[MAXCOMMBUFFER] = "";
			// If message available, get it from the receiving buffer
			getMessage(&RX, input);
			// Verify initial messages are responses
			char responseType[] = "Response";
			char result[300];
			GetNameValue(input, responseType, result);
			unsigned int Mask = BridgeResponseID(result);

			// Check message for corresponding response message
			switch(Mask){
				case StartUp:{
					//Response: Description and version
					break;
				}
				case WifiStatus:{
					//Response:"WifiStatus"
					//Action:
						//if null send "WifiSetup"
						//if false - setup but not connected
						//if true - setup and connected, send "SetupMQTT"
						char result1[300];
						char result2[300];
						GetNameValue(input, "Wifi", result1);
						GetNameValue(result1, "isGWPingable", result2);
					break;
				}
				case MQTTSetup:{
					//Response:"MQTTSetup" Success
					//Action:"MQTTSubs"
					break;
				}
				case MQTTPub:{ //Do we implement?
					//Response:
					//Action:
					break;
				}
				case MQTTSubs:{
					//Response:"MQTTSubs" Subscribed
					//Action:
					break;
				}
				case SubscribedMessage:{
					//Response:
					//Action:
					break;
				}
				default:{
					printf("Bad ID\n");
					break;
				}

			// and put it into the transmitting buffer
			putMessage(&TX, message, strlen(message));
			// Now that message is available, reenable interrupts for Tx buffer
			LL_USART_EnableIT_TXE(USARTx_INSTANCE);
		}
	}
/**
  * @brief  System Clock Configuration
  * The system Clock is configured as follow :
  * System Clock source            = PLL (MSI)
  * SYSCLK(Hz)                     = 80000000
  * HCLK(Hz)                       = 80000000
  * AHB Prescaler                  = 1
  * APB1 Prescaler                 = 1
  * APB2 Prescaler                 = 1
  * MSI Frequency(Hz)              = 4000000
  * PLL_M                          = 1
  * PLL_N                          = 40
  * PLL_R                          = 2
  * PLL_P                          = 7
  * PLL_Q                          = 4
  * Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  /* MSI is enabled after System reset, activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;

  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}
/*
 * This is a simple IRQ handler for USART4. A better design would
 * be to have a circular list of strings. Head index pointing to
 * where chars added. Tail index oldest string to be processed
 */
void USARTx_IRQHandler(void) {
	// Check if the USART6 receive interrupt flag was activated
	if(LL_USART_IsActiveFlag_RXNE(USARTx_INSTANCE)){
		putChar(&RX, LL_USART_ReceiveData8(USARTx_INSTANCE));
	}
	// Check if the USART6 transmit interrupt flag was activated
	// User requests information if active
	if(LL_USART_IsActiveFlag_TXE(USARTx_INSTANCE)){
		// Check if requested information is available
		if(haveMessage(&TX)){
			LL_USART_TransmitData8(USARTx_INSTANCE, getChar(&TX));
		}
		else{
			// Manually disable if no messages to transmit
			LL_USART_DisableIT_TXE(USARTx_INSTANCE);
		}
	}++USARTCount;
}
