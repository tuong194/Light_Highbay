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

#define TIME_DELAY_ON     10  // ms
#define TIME_DELAY_OFF	  10

#define LOG_MS58 			RD_LOG_UART
#define PIN_MS58            GPIO_PB4
//#define LED_OUT             GPIO_PC3
//
//#define ON_LED_RADA         gpio_write(LED_OUT,1)
//#define OFF_LED_RADA        gpio_write(LED_OUT,0)

typedef enum{
	NO_MOTION 	= 0,
	MOTION 		= 1,
	//NO_MOTION 	= 2,
}check_motion_e;
typedef enum{
	MANUAL 		= 0x00,
	AUTO	    = 0x01,
	KEEP_STATUS = 0x02,
}startup_status_e;

typedef enum{
	HIGH_SEN  = 0x0004,
	MIDLE_SEN = 0x0005,
	LOW_SEN   = 0x0007,
}sensitive_set_e;


void RD_config_pin_MS58(void);
void RD_config_MS58(uint8_t gain, uint8_t delta[2], uint8_t lot[4]);
void RD_get_data_MS58(void);
void RD_restore_MS58(void);
unsigned int is_motion(void);
void loop_rada(void);
void RD_Init_Config_MS58(void);
void log_par_flash_ms58(void);

#endif /* MS58_H_ */
