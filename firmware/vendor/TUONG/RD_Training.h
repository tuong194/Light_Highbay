/*
 * RD_Training.h
 *
 *  Created on: Sep 24, 2024
 *      Author: PC5
 */

#ifndef RD_TRAINING_H_
#define RD_TRAINING_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#define RD_TRAINING_FLASH_AREA    (0x79000)

typedef struct{
	uint8_t User[4];
	uint8_t step;
	uint8_t cnt_cycle;
}Flash_Save_Training;

void RD_Kickout_All(void);

#endif /* RD_TRAINING_H_ */
