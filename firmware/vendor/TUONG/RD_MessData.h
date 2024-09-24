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

#define RD_SET_TYPE_DEVICE  	 (0x0001)
#define RD_SAVE_GATEWAY_ADDRESS  (0x0002)
#define RD_PROVISION_AES         (0x0003)
#define RD_KICKOUT_ALL           (0xffff)

#define PROVIDER_MAIN    0x00
#define PROVIDER_SUB     0x01

extern uint16_t RD_GATEWAY_ADDR;

typedef struct{
	uint8_t Header[2];
	uint8_t MainType;
	uint8_t Feature;
	uint8_t Name;
	uint8_t Future[8];
}RD_Type_Device_Message;

typedef struct {
	uint8_t GWID[2];
}RD_Save_GW_Address;

typedef struct{
	uint8_t Header[2];
	uint8_t GWID[2];
	uint8_t Future[4];
}RD_Rsp_GW_Address;

int RD_Messenger_CheckSecure(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par);
uint16_t saveGatewayAddr(uint8_t *para, uint16_t srcAddr);


#endif /* RD_MESSDATA_H_ */
