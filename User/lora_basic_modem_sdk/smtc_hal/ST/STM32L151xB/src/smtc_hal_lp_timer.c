/*!
 * \file      smtc_hal_lp_timer.c
 *
 * \brief     Implements Low Power Timer utilities functions.
 *
 * The Clear BSD License
 * Copyright Semtech Corporation 2021. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>   // C99 types
#include <stdbool.h>  // bool type
#include "smtc_hal_lp_timer.h"
#include "smtc_hal_mcu.h"
#include "system_port.h"
#include "system_time.h"

static uint8_t timer_init_flag = 0;
static hal_lp_timer_irq_t lptim_tmr_irq = { .context = NULL, .callback = NULL };

static TIM_HandleTypeDef htim;
void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *tim_handler)
{
//	SYS_LOG_INFO("HAL_TIM_PeriodElapsedCallback:timer=%d \n",get_sys_time());

	if(tim_handler==(&htim))
	{
		if( lptim_tmr_irq.callback != NULL )
		{
			lptim_tmr_irq.callback( lptim_tmr_irq.context );
		}
	}
}


void hal_lp_timer_init( void )
{
	if(timer_init_flag==0)
	{
		timer_init_flag = 1;
		
		__HAL_RCC_TIM3_CLK_ENABLE();
		HAL_NVIC_SetPriority(TIM3_IRQn, 0x0F, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
		
		htim.Instance				= TIM3; 							// 使用定时器3
		htim.Init.Prescaler 		= (SystemCoreClock / 1000) - 1; 	// 预分频系数.定时器时钟为1MHz
		htim.Init.CounterMode		= TIM_COUNTERMODE_UP;				// 向上计数
		htim.Init.Period			= 0xFFFF;							// 自动装载器ARR的值
		htim.Init.ClockDivision 	= TIM_CLOCKDIVISION_DIV1;			// 时钟分频(与输入采样相关)
		htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;	// 不自动重新装载
		
		HAL_TIM_Base_Init(&htim);
		
		SYS_LOG_INFO("hal_lp_timer_init\n");

	}
}

void hal_lp_timer_start( const uint32_t milliseconds, const hal_lp_timer_irq_t* tmr_irq )
{
	lptim_tmr_irq = *tmr_irq;
//	HAL_TIM_Base_Stop_IT(&htim);
	__HAL_TIM_SET_AUTORELOAD(&htim, milliseconds);	// 设置定时器自动加载值
	__HAL_TIM_SET_COUNTER(&htim,0);
	__HAL_TIM_CLEAR_FLAG(&htim,TIM_FLAG_UPDATE);
	HAL_TIM_Base_Start_IT(&htim);
	
//	SYS_LOG_INFO("hal_lp_timer_start:%d,current_timer=%d\n",milliseconds,get_sys_time());

}

void hal_lp_timer_stop( void ) 
{ 
	HAL_TIM_Base_Stop_IT(&htim);	// 停止定时器
//	SYS_LOG_INFO("hal_lp_timer_stop,current_timer=%d\n",get_sys_time());

}

void hal_lp_timer_irq_enable( void ) 
{ }

void hal_lp_timer_irq_disable( void ) 
{  }

