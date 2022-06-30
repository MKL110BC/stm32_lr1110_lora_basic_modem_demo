/*!
 * @file      smtc_hal_gpio.c
 *
 * @brief     Implements the gpio HAL functions
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
#include "smtc_hal.h"
#include "smtc_hal_gpio.h"
#include "system_port.h"



typedef struct
{
	GPIO_TypeDef	*port;
	uint16_t		pin_num;
}gpio_t;


static gpio_t hardware[PIN_NAME_MAX] = 
{
	{
		LORA_NSS_PORT,
		LORA_NSS_PIN,
	},
	{
		LORA_SCK_PORT,
		LORA_SCK_PIN,
	},	
	{
		LORA_MISO_PORT,
		LORA_MISO_PIN,
	},	
	{
		LORA_MOSI_PORT,
		LORA_MOSI_PIN,
	},
	{
		LORA_NRST_PORT,
		LORA_NRST_PIN,	
	},
	{
		LORA_BUSY_PORT,
		LORA_BUSY_PIN,	
	},	
	{
		LORA_DIO1_PORT,
		LORA_DIO1_PIN,	
	},	
		
	{
		VDD_RF_PORT,
		VDD_RF_PIN,	
	},

	{
		LNA_CTL_PORT,
		LNA_CTL_PIN,	
	},
};




static hal_gpio_irq_t const* gpio_irq;
void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	if(gpio_irq !=NULL && gpio_irq->callback != NULL)
	{
		gpio_irq->callback( gpio_irq->context );
	}

	__HAL_GPIO_EXTI_CLEAR_IT(pin);
	
//	SYS_LOG_INFO("------HAL_GPIO_EXTI_Callback \n");
}

void EXTI9_5_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(LORA_DIO1_PIN);
}


void hal_gpio_deinit( const hal_gpio_pin_names_t pin )
{
	if(pin >= PIN_NAME_MAX)
		return;
	HAL_GPIO_DeInit(hardware[pin].port, hardware[pin].pin_num);
}

/**
 * @brief MCU input pin Handling
 */

void hal_gpio_init_in( const hal_gpio_pin_names_t pin, const hal_gpio_pull_mode_t pull_mode,
                       const hal_gpio_irq_mode_t irq_mode, hal_gpio_irq_t* irq )
{

	if(pin >= PIN_NAME_MAX)
		return;

	/* Enable the GPIO clock */
	LORA_GPIO_CLK_ENABLE();
	
	GPIO_InitTypeDef  gpioinitstruct = {0};

	if( irq_mode==HAL_GPIO_IRQ_MODE_OFF)
	{
		gpioinitstruct.Mode  = GPIO_MODE_INPUT;
		gpioinitstruct.Pull  = GPIO_PULLUP;
		gpioinitstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		gpioinitstruct.Pin = hardware[pin].pin_num;
		HAL_GPIO_Init(hardware[pin].port, &gpioinitstruct);
	}
	else
	{
		if(pin == SMTC_RADIO_DIOX)
		{
			gpioinitstruct.Mode = irq_mode;
			gpioinitstruct.Pull = GPIO_PULLDOWN;
			gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;
			gpioinitstruct.Pin = hardware[pin].pin_num;
			HAL_GPIO_Init(hardware[pin].port, &gpioinitstruct);

			HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0x0A, 0);
			HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
			SYS_LOG_INFO("lora_dio_pin init GPIO_EXTI\n");
		}
	}
}
//设置中断回调
void hal_gpio_irq_attach( const hal_gpio_irq_t* irq )
{
    if( ( irq != NULL ) && ( irq->callback != NULL ) )
    {
        gpio_irq = irq;
    }
}
//删除中断回调
void hal_gpio_irq_deatach( const hal_gpio_irq_t* irq )
{
    if( irq != NULL )
    {
        gpio_irq = NULL;
    }
}

void hal_gpio_irq_enable( void )
{
}

void hal_gpio_irq_disable( void )
{
}



void hal_gpio_init_out( const hal_gpio_pin_names_t pin, const hal_gpio_state_t value )
{
	if(pin >= PIN_NAME_MAX)
		return;

	/* Enable the GPIO clock */
	LORA_GPIO_CLK_ENABLE();
	
	GPIO_InitTypeDef  gpioinitstruct = {0};
	gpioinitstruct.Mode  = GPIO_MODE_OUTPUT_PP;
	gpioinitstruct.Pull  = GPIO_PULLUP;
	gpioinitstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	
	gpioinitstruct.Pin = hardware[pin].pin_num;
	HAL_GPIO_Init(hardware[pin].port, &gpioinitstruct);
	HAL_GPIO_WritePin(hardware[pin].port,hardware[pin].pin_num,GPIO_PIN_SET);
}


/**
 * @brief MCU pin state control
 */

void hal_gpio_set_value( const hal_gpio_pin_names_t pin, const hal_gpio_state_t value )
{
	if(pin >= PIN_NAME_MAX)
		return;
	HAL_GPIO_WritePin(hardware[pin].port, hardware[pin].pin_num,(GPIO_PinState)value);
}

void hal_gpio_toggle( const hal_gpio_pin_names_t pin )
{
	if(pin >= PIN_NAME_MAX)
		return;
	HAL_GPIO_TogglePin(hardware[pin].port, hardware[pin].pin_num);
}

uint32_t hal_gpio_get_value( const hal_gpio_pin_names_t pin )
{
    return HAL_GPIO_ReadPin(hardware[pin].port, hardware[pin].pin_num);
}

bool hal_gpio_is_pending_irq( const hal_gpio_pin_names_t pin )
{
    bool pending = false;
    return ( bool ) pending;
}


