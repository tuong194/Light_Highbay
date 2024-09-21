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

#define EN_SECURE 1

typedef struct{
	uint8_t Header[2];
	uint8_t MainType;
	uint8_t Feature;
	uint8_t Name;
	uint8_t Future[8];
}RD_Type_Device_Message;

unsigned char RD_AesreCheck(uint16_t unicast_ID, uint8_t compare_key[6]);
int RD_Messenger_CheckSecure(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par);
void check_done_provision(void);

#endif /* RD_SECURE_H_ */
