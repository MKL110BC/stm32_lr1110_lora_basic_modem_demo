#ifndef __DRIVER_FLASH_H
#define __DRIVER_FLASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32l1xx_hal.h"

	
#define	FLASH_BASE_ADDR				0x08000000

#define FLASH_USER_SIZE          	(256)



void EraseFlashPage(uint32_t addr, uint32_t page_num);

void WriteFlash(uint32_t startAddr,const uint8_t *pdata, uint32_t length);

void ReadFlash(uint32_t startAddr, uint8_t *pdata, uint32_t length);

void FlashDemo(void);

#endif
