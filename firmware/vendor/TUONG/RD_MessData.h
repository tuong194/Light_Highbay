/*
 * RD_MessData.h
 *
 *  Created on: Sep 9, 2024
 *      Author: PC5
 */

#ifndef RD_MESSDATA_H_
#define RD_MESSDATA_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"



typedef struct{
	uint8_t Header[2];
	uint8_t MainType;
	uint8_t Feature;
	uint8_t Name;
	uint8_t Future[8];
}RD_Type_Device_Message;

int RD_Messenger_CheckSecure(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par);



#endif /* RD_MESSDATA_H_ */
