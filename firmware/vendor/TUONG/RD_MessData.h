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

#define RD_SET_TYPE_DEVICE  	 	(0x0001)
#define RD_SAVE_GATEWAY_ADDRESS  	(0x0002)
#define RD_PROVISION_AES         	(0x0003)

#define RD_SET_STARTUP_MODE                 (0x0C)
#define RD_SW_SELECT_MODE_RADA              (0x0B)  // nhan ban tin hoac ko nhan ban tin (not use)

#define RD_CONFIG_MS58_SENSITIVE            (0x0A) //do nhay
#define RD_SET_GROUP	                    (0x06)
#define RD_CONFIG_MS58_LOT					(0x07) // thoi gian giu chuyen dong
#define RD_CONFIG_MIN_MAX					(0x08)
#define RD_SET_MODE_RADA                 	(0x09) //auto / manual
#define RD_GET_DIM_LIGHTNESS                (0x02)
#define RD_SET_LIGHT_FROM_RADA              (0x05)



#define RD_KICKOUT_ALL              (0xffff)

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

extern _Bool rd_flag_set_gr;
extern u32 time_reset_flag_gr;

int RD_Messenger_Mess(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par);
int RD_mesh_cmd_sig_lightness_linear_set(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par);
int RD_Messenger_Training_2(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par);
int RD_Control_Group_By_SENSOR(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par);
uint16_t saveGatewayAddr(uint8_t *para, uint16_t srcAddr);
void RD_Mess_Config_MS58(uint8_t gain, uint8_t delta[2], uint8_t lot[4]);
void RD_rsp_packing_lot(u8 *par);
void RD_Sub_Del_ID_Group(uint16_t op, uint8_t ID_group);
void RD_Clear_Flag_Group(void);


#endif /* RD_MESSDATA_H_ */
