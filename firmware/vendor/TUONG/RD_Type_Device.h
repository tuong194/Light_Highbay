/*
 * RD_Type_Device.h
 *
 *  Created on: Sep 24, 2024
 *      Author: PC5
 */

#ifndef RD_TYPE_DEVICE_H_
#define RD_TYPE_DEVICE_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#define RD_GW_FLASH_AREA   (0x78000)
#define RD_CHECK_FLASH_H   (0x55)
#define RD_CHECK_FLASH_L   (0xAA)
typedef struct{
	uint8_t Used[4];
	uint8_t GWID[2];
	uint8_t MainType;
	uint8_t Feature;
	uint8_t Name;
	uint8_t Future[7];
}Flash_Save_Type_GW;

void RD_Flash_Save_GW(uint16_t GW_ADDR);
void RD_Flash_Save_Type(uint8_t MainType, uint8_t Feature, uint8_t Name);
void RD_Flash_Type_Init(void);

void RD_LOG(const char *format, ...);
#endif /* RD_TYPE_DEVICE_H_ */
