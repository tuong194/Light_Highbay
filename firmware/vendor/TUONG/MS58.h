/*
 * MS58.h
 *
 *  Created on: Oct 22, 2024
 *      Author: PC5
 */

#ifndef MS58_H_
#define MS58_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#include "RD_Type_Device.h"
#include"../mesh/RD_Lib.h"

#define LOG_MS58 			1 //RD_LOG_UART
#define PIN_MS58            GPIO_PB4
#define LED_OUT             GPIO_PC3

#define ON_LED_RADA         gpio_write(PIN_MS58,1)
#define OFF_LED_RADA        gpio_write(PIN_MS58,0)

typedef enum{
	MANUAL 		= 0x00,
	AUTO	    = 0x01,
	KEEP_STATUS = 0x02,
}startup_status_e;


typedef struct{
	//uint8_t power;
	uint8_t gain;
	uint8_t delta[2];
	uint8_t lot[4];
}Par_MS58_t;

typedef struct{
	uint8_t user[4];
	uint8_t mode;
	uint8_t start_status;
	uint8_t sw_select;  // nhan hoac ko nhan message: 0x00 ko nhan, 0x01 co nhan
	Par_MS58_t parMS58;
}Flash_Save_MS58_t;

#define RD_FLASH_SIZE_MS58			sizeof(Flash_Save_MS58_t)
#define RD_MS58_FLASH_AREA          (0x7c000)

void RD_config_pin_MS58(void);
void RD_config_MS58(uint8_t gain, uint8_t delta[2], uint8_t lot[4]);
void RD_get_data_MS58(void);
void RD_restore_MS58(void);
unsigned int is_motion(void);
void loop_rada(void);

#endif /* MS58_H_ */
