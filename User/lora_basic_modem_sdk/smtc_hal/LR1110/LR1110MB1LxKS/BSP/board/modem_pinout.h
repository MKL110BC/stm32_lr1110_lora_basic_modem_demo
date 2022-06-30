/*!
 * \file      modem_pinout.h
 *
 * \brief     modem specific pinout
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
#ifndef  SMTC_PINOUT_H
#define  SMTC_PINOUT_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include "board_options.h"

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/********************************************************************************/
/*                         Application     dependant                            */
/********************************************************************************/

// Radio specific pinout and peripherals


#if 0
//52840 ×Ô¼ºÄ£¿é
#define SMTC_RADIO_SPI_MOSI 	P1_14
#define SMTC_RADIO_SPI_MISO 	P0_3
#define SMTC_RADIO_SPI_SCLK 	P1_15
#define SMTC_RADIO_NSS 		P1_13
#define SMTC_RADIO_NRST 		P0_2
#define SMTC_RADIO_DIOX 		P0_29
#define SMTC_RADIO_BUSY 		P1_12

#define RADIO_LNA_CTRL 		P1_10
#endif



enum
{
	SMTC_RADIO_NSS = 0,
	SMTC_RADIO_SPI_SCLK,//
	SMTC_RADIO_SPI_MISO,//
	SMTC_RADIO_SPI_MOSI,//
	SMTC_RADIO_NRST,
	SMTC_RADIO_BUSY,
	SMTC_RADIO_DIOX,
	SMTC_RADIO_RF,
	RADIO_LNA_CTRL,
	PIN_NAME_MAX,
};



//stm32
#define LORA_NSS_PORT		GPIOA
#define LORA_NSS_PIN		GPIO_PIN_4

#define LORA_SCK_PORT		GPIOA
#define LORA_SCK_PIN		GPIO_PIN_5

#define LORA_MISO_PORT		GPIOA
#define LORA_MISO_PIN		GPIO_PIN_6

#define LORA_MOSI_PORT		GPIOA
#define LORA_MOSI_PIN		GPIO_PIN_7

#define LORA_NRST_PORT		GPIOB
#define LORA_NRST_PIN		GPIO_PIN_15


#define LORA_BUSY_PORT		GPIOB
#define LORA_BUSY_PIN		GPIO_PIN_0

#define LORA_DIO1_PORT		GPIOA
#define LORA_DIO1_PIN		GPIO_PIN_8

#define VDD_RF_PORT			GPIOB
#define VDD_RF_PIN			GPIO_PIN_2

#define LNA_CTL_PORT		GPIOB
#define LNA_CTL_PIN			GPIO_PIN_1


#define	LORA_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE();__HAL_RCC_GPIOB_CLK_ENABLE();

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

#ifdef __cplusplus
}
#endif

#endif  // SMTC_PINOUT_H
