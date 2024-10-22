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

#define LOG_MS58 				RD_LOG_UART
#define PIN_MS58                GPIO_PC4

void RD_config_pin_MS58(void);
void RD_config_MS58(uint8_t gain, uint8_t delta[2], uint8_t lot[4]);
void RD_get_data_MS58(void);
void RD_restore_MS58(void);

#endif /* MS58_H_ */
