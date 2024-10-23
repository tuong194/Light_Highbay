/*
 * RD_MessData.c
 *
 *  Created on: Sep 9, 2024
 *      Author: PC5
 */

#include "RD_MessData.h"
#include "RD_Secure.h"
#include "../common/light.h"
#include "../common/lighting_model.h"
#include "../mesh/RD_Lib.h"
#include "RD_Type_Device.h"

RD_Type_Device_Message *RD_Mess_Temp_Receive;
RD_Type_Device_Message RD_Mess_Recevie;
RD_Save_GW_Address RD_Save_GW_Addr;
RD_Rsp_GW_Address  RD_Rsp_GW_Addr;

uint8_t *BuffRec;
uint16_t RD_GATEWAY_ADDR = 0x0001;

_Bool flag_kickout_all = FALSE;

extern RD_Flash_Save_Secure flash_save_secure;

int RD_Messenger_Mess(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par) {
	RD_Mess_Temp_Receive = (RD_Type_Device_Message *) (&par[0]);
	RD_Mess_Recevie = *RD_Mess_Temp_Receive;
	u16 Header = RD_Mess_Recevie.Header[1] << 8 | RD_Mess_Recevie.Header[0];
	switch (Header) {
	case RD_SET_TYPE_DEVICE:
		RD_Mess_Recevie.Header[0] = 0x01;
		RD_Mess_Recevie.Header[1] = 0x00;
		RD_Mess_Recevie.MainType = 0x01;
		RD_Mess_Recevie.Feature = 0x02;
		RD_Mess_Recevie.Name = NAME;
		//RD_Mess_Recevie.Future[0] = 0x00;
		RD_Mess_Recevie.Future[1] = VERSION_MAIN;
		RD_Mess_Recevie.Future[2] = VERSION_SUB;

		RD_Flash_Save_Type(RD_Mess_Recevie.MainType, RD_Mess_Recevie.Feature, RD_Mess_Recevie.Name);

		BuffRec = (uint8_t *) (&RD_Mess_Recevie.Header[0]);
		mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8,
				cb_par->adr_src, 2);
		break;
	case RD_SAVE_GATEWAY_ADDRESS:
		RD_GATEWAY_ADDR = saveGatewayAddr(&par[2], cb_par->adr_src);
		RD_Save_GW_Addr.GWID[0] = (uint8_t) (RD_GATEWAY_ADDR & 0xff);
		RD_Save_GW_Addr.GWID[1] = (uint8_t) (RD_GATEWAY_ADDR>>8 & 0xff);
		RD_Flash_Save_GW(RD_GATEWAY_ADDR);

		RD_Rsp_GW_Addr.Header[0] = 0x02;
		RD_Rsp_GW_Addr.Header[1] = 0x00;
		RD_Rsp_GW_Addr.GWID[0] = RD_Save_GW_Addr.GWID[0];
		RD_Rsp_GW_Addr.GWID[1] = RD_Save_GW_Addr.GWID[1];
		RD_Rsp_GW_Addr.Future[0] = PROVIDER_MAIN;
		RD_Rsp_GW_Addr.Future[1] = PROVIDER_SUB;
		RD_Rsp_GW_Addr.Future[2] = 0x00;
		RD_Rsp_GW_Addr.Future[3] = 0x00;

		BuffRec = (uint8_t *) (&RD_Rsp_GW_Addr.Header[0]);
		mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8,
				cb_par->adr_src, 2);
		break;
	case RD_KICKOUT_ALL:
		if(is_provision_success()){
			flag_kickout_all = TRUE;
		}
		break;
	case RD_SWITCH_SELECT_AUTO_RADA: //T_NOTE auto rada
		/*  todo  */
		break;
	case RD_PROVISION_AES:
		if(is_provision_success()){
			if (RD_AesreCheck(cb_par->adr_dst, &par[2])) {
				flash_save_secure.flag_process_aes = 1;

				RD_Mess_Recevie.Header[0] = 0x03;
				RD_Mess_Recevie.Header[1] = 0x00;
				RD_Mess_Recevie.MainType = 0x01;
				RD_Mess_Recevie.Feature = 0x02;
				RD_Mess_Recevie.Name = NAME; // NAME
				RD_Mess_Recevie.Future[0] = 0x00;
				RD_Mess_Recevie.Future[1] = 0x03;
				RD_Mess_Recevie.Future[2] = 0x00;

				BuffRec = (uint8_t *) (&RD_Mess_Recevie.Header[0]);
				mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8,
						cb_par->adr_src, 2);

			} else {
				flash_save_secure.flag_process_aes = 0;

				RD_Mess_Recevie.Header[0] = 0x03;
				RD_Mess_Recevie.Header[1] = 0x00;
				RD_Mess_Recevie.MainType = 0xff;
				RD_Mess_Recevie.Feature = 0xfe;
				RD_Mess_Recevie.Name = 0xff; // NAME
				RD_Mess_Recevie.Future[0] = 0xfe;
				RD_Mess_Recevie.Future[1] = 0xff;
				RD_Mess_Recevie.Future[2] = 0xfe;

				BuffRec = (uint8_t *) (&RD_Mess_Recevie.Header[0]);
				mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8,
						cb_par->adr_src, 2);
			}
		}

		break;
	}
	return 0;
}

uint16_t saveGatewayAddr(uint8_t *para, uint16_t srcAddr){
	uint16_t GW_Addr = 0x0001;
	if(para[0] || para[1]){
		GW_Addr = para[1] << 8 | para[0];
	}else{
		GW_Addr = srcAddr;
	}
	return GW_Addr;
}

