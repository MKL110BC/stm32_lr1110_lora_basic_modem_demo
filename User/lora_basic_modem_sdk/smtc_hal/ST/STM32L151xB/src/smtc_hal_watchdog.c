/*!
 * \file      smtc_hal_watchdog.c
 *
 * \brief     WATCHDOG Hardware Abstraction Layer implementation
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
#include "smtc_hal_watchdog.h"
#include "stm32l1xx_hal.h"
#include "system_port.h"

IWDG_HandleTypeDef hiwdg;


/**
  * 输入参数: Tout = prv/40 * rlv (s) prv可以是[4,8,16,32,64,128,256]
  *            prv:预分频器值，取值如下：
  *            参数 IWDG_PRESCALER_4: IWDG prescaler set to 4
  *            参数 IWDG_PRESCALER_8: IWDG prescaler set to 8
  *            参数 IWDG_PRESCALER_16: IWDG prescaler set to 16
  *            参数 IWDG_PRESCALER_32: IWDG prescaler set to 32
  *            参数 IWDG_PRESCALER_64: IWDG prescaler set to 64
  *            参数 IWDG_PRESCALER_128: IWDG prescaler set to 128
  *            参数 IWDG_PRESCALER_256: IWDG prescaler set to 256
  *
  *            rlv:预分频器值，取值范围为：0-0XFFF
  * 返 回 值: 无
  * 说    明：函数调用举例：
  *           IWDG_Config(IWDG_Prescaler_64 ,625);  // IWDG 1s 超时溢出
  */
void IWDG_Init(uint16_t period)
{
	HAL_StatusTypeDef status = HAL_ERROR;
    hiwdg.Instance = IWDG;                     // 选择独立看门狗        
    hiwdg.Init.Prescaler = IWDG_PRESCALER_64; // 设置预分频
    hiwdg.Init.Reload = 40000/64*period/1000; // 设置重装载值
    status = HAL_IWDG_Init(&hiwdg);      				// 初始化独立看门狗

	SYS_LOG_INFO("IWDG_Init status:%d \n",status);
}

void hal_watchdog_init( void )
{
//	IWDG_Init(30000);
}

void hal_watchdog_reload( void ) 
{ 
	HAL_IWDG_Refresh(&hiwdg); // 将重载寄存器的值更新到计数器
	SYS_LOG_INFO("feed dog \n");
}


