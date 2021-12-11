/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f4xx_it.h"
#include <stopwatch/stopwatch.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif
}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&tim_handle_struct);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &tim_handle_struct)
	  {

		stopwatch_micro_s += 1;
		if( stopwatch_micro_s == 100) {
			stopwatch_milli_s += 1;
			stopwatch_micro_s = 0;
		}
		if( stopwatch_milli_s == 100) {
				stopwatch_s += 1;
				stopwatch_milli_s = 0;
		}
		if(stopwatch_s == 60){
			stopwatch_m += 1;
			stopwatch_s = 0;
		}
		if(stopwatch_m == 60) {
			stopwatch_h += 1;
			stopwatch_m = 0;
		}
	  }
}

void EXTI0_IRQHandler(void)
{
	EXTI_HandleTypeDef hexti;
	HAL_EXTI_GetHandle(&hexti, EXTI_LINE_0);
	if(HAL_EXTI_GetPending(&hexti, EXTI_TRIGGER_RISING))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	switch(GPIO_Pin){
	case GPIO_PIN_0:  counter += 1;
		if(counter == 1){
			stopwatch_start();
		}
		else{
			stopwatch_save_time();
		}
		break;
	default:
		break;
	}

}

