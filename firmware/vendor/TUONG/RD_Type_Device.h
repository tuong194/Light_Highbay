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
	//uint8_t power;
	uint8_t gain;
	uint8_t delta[2];
	uint8_t lot[4];
}Par_MS58_t;

typedef struct{
	u8 on_off[2];
	u16 ID_Scene[2];
}Call_Scene_t;

typedef struct{
	uint8_t user[4];
	uint8_t mode;
	uint8_t start_status;
	uint8_t sw_select;  // nhan hoac ko nhan message: 0x00 ko nhan, 0x01 co nhan
	uint16_t lightness_max;
	uint16_t lightness_min;
	Par_MS58_t parMS58;
	Call_Scene_t Call_Scene;
}Flash_Save_MS58_t;

typedef enum{
	NONE 	   = 0,
	CALL_SCENE = 1,
}call_scene_e;

#define RD_FLASH_SIZE_MS58			sizeof(Flash_Save_MS58_t)
#define RD_MS58_FLASH_AREA          (0x7c000)

typedef struct{
	uint8_t Used[4];
	uint8_t GWID[2];
	uint8_t MainType;
	uint8_t Feature;
	uint8_t Name;
	uint8_t Future[7];
}Flash_Save_Type_GW;

extern Flash_Save_MS58_t Flash_Save_MS58;

void RD_Flash_Save_GW(uint16_t GW_ADDR);
void RD_Flash_Save_Type(uint8_t MainType, uint8_t Feature, uint8_t Name);
void RD_Flash_Type_Init(void);
void RD_Flash_MS58_Init(void);
void Init_Data_Rada(void);
void RD_Write_Flash_MS58(void);


void RD_LOG(const char *format, ...);
#endif /* RD_TYPE_DEVICE_H_ */
