/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "tim.h"
#define SystemCoreClockInMHz 96
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId RedLedBlinkHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
osThreadId BleTransmitHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
inline void TIM11_reinit()
{
 HAL_TIM_Base_Stop(&htim11);
 __HAL_TIM_SET_PRESCALER( &htim11, (SystemCoreClockInMHz-1) );
 __HAL_TIM_SET_COUNTER( &htim11, 0 );
 HAL_TIM_Base_Start_IT(&htim11);
}

inline uint32_t get_tim11_us()
{
 __HAL_TIM_DISABLE_IT(&htim11, TIM_IT_UPDATE); //! Дуже важливо!
 //__disable_irq();
 uint32_t res = __HAL_TIM_GET_COUNTER(&htim11);
 //__enable_irq();
 __HAL_TIM_ENABLE_IT(&htim11, TIM_IT_UPDATE);
 return res;
}

uint8_t byte;
uint32_t result = 10000000;
char pow_res[100];

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//	if( GPIO_Pin == GPIO_PIN_0) {
//		BaseType_t yieldRequired;
//		yieldRequired = xTaskResumeFromISR(BleTransmitHandle);
//		portYIELD_FROM_ISR(yieldRequired);
//	}

	if( GPIO_Pin == GPIO_PIN_11) {
		 if (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET) {
			 TIM11_reinit();
		 }
		 else {
			 result = get_tim11_us()*343/2000; // the result is in millimeters
			 BaseType_t yieldRequired;
			 yieldRequired = xTaskResumeFromISR(BleTransmitHandle);
			 portYIELD_FROM_ISR(yieldRequired);
		 }
	}
}

/* USER CODE END FunctionPrototypes */

void RedLedBlinkTask(void const * argument);
void BleTransmitHandler(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of RedLedBlink */
  osThreadStaticDef(RedLedBlink, RedLedBlinkTask, osPriorityNormal, 0, 128, defaultTaskBuffer, &defaultTaskControlBlock);
  RedLedBlinkHandle = osThreadCreate(osThread(RedLedBlink), NULL);

  /* definition and creation of BleTransmit */
  osThreadDef(BleTransmit, BleTransmitHandler, osPriorityLow, 0, 128);
  BleTransmitHandle = osThreadCreate(osThread(BleTransmit), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
//  vTaskStartScheduler();
  /* add threads, ... */
//  xTaskCreate( vHandlerTask, 'Handler', 128, NULL, 3, &xTaskHandler );
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_RedLedBlinkTask */
/**
  * @brief  Function implementing the RedLedBlink thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_RedLedBlinkTask */
void RedLedBlinkTask(void const * argument)
{
  /* USER CODE BEGIN RedLedBlinkTask */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
	  osDelay(1000);
  }
  /* USER CODE END RedLedBlinkTask */
}

/* USER CODE BEGIN Header_BleTransmitHandler */
/**
* @brief Function implementing the BleTransmit thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_BleTransmitHandler */
void BleTransmitHandler(void const * argument)
{
  /* USER CODE BEGIN BleTransmitHandler */
  /* Infinite loop */
  for(;;)
  {
    vTaskSuspend(NULL);
	sprintf(pow_res, "res %lu\n", result);
	HAL_UART_Transmit(&huart2, pow_res, strlen((char*)pow_res), 100);
    osDelay(1);
  }
  /* USER CODE END BleTransmitHandler */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
