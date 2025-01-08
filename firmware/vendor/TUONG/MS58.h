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

#define TIME_DELAY_ON     500  // ms
#define TIME_DELAY_OFF	  500
#define TIME_DELAY_START  10000

#define RD_RSP_STT_RADA   		0x52
#define RD_HEADER_RSP_MOTION 	0x0005
#define MY_HEADER_RSP_MODE    	0x0445

#define LOG_MS58 			RD_LOG_UART
#define PIN_MS58            GPIO_PB4
//#define LED_OUT             GPIO_PC3
//#define ON_LED_RADA         gpio_write(LED_OUT,1)
//#define OFF_LED_RADA        gpio_write(LED_OUT,0)

typedef struct{
	u8 flag_check_motion;
	u8 flag_on_off_from_rada; // ppacking lot
	u8 flag_on_off_from_mesh;
}flag_on_off_light_t;

extern flag_on_off_light_t flag_on_off;
extern u32 time_start_loop;
extern u32 TIMEOUT_MOTION_GROUP;   //second
extern u32 time_start_motion_by_gr; // ms
extern _Bool motion_detect;


enum{
	NONEX  = 0,
	ON    = 1,
	OFF   = 2,
};

typedef enum{
	NO_MOTION 	= 0,
	MOTION 		= 1,
}check_motion_e;
typedef enum{
	AUTO 		= 0x00,
	MANUAL	    = 0x01,
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
void RD_set_lightness(u16 lightness);
void RD_Rsp_Powerup(uint16 gw_addr, uint8_t mode);

#endif /* MS58_H_ */
