/*
 * RD_Secure.h
 *
 *  Created on: Sep 9, 2024
 *      Author: PC5
 */

#ifndef RD_SECURE_H_
#define RD_SECURE_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#define RD_PROVISION_FLASH_AREA (0x7a000)
#define RD_SIZE_FLASH_SECURE    5
#define RD_CHECK_FLASH_H   (0x55)
#define RD_CHECK_FLASH_L   (0xAA)

#define EN_SECURE           0

typedef struct{
	uint8_t Used[4];
	s8 flag_process_aes;
	//uint8_t step_down;
}RD_Flash_Save_Secure;

unsigned char RD_AesreCheck(uint16_t unicast_ID, uint8_t compare_key[6]);
void check_done_provision(void);
void reset_kickout(void);
void Init_Flash_Secure(void);


#endif /* RD_SECURE_H_ */
