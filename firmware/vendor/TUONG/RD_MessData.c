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
#include "MS58.h"

RD_Type_Device_Message *RD_Mess_Temp_Receive;
RD_Type_Device_Message RD_Mess_Recevie;
RD_Save_GW_Address RD_Save_GW_Addr;
RD_Rsp_GW_Address  RD_Rsp_GW_Addr;

uint16_t packing_lot_addr = 0;
uint32_t op_rsp_packing_lot = 0;

uint8_t *BuffRec;
uint16_t RD_GATEWAY_ADDR = 0x0001;

_Bool flag_kickout_all = FALSE;


static void RD_Handle_Select_Rada(uint8_t on_off_mess);
static void RD_Handle_Config_LOT(uint8_t *par);
static void RD_Handle_Min_Max_Lightness(uint8_t *par);
static void RD_Handle_Config_Sensitive(uint8_t *par);
static void RD_Handle_Set_Mode_Rada(uint8_t mode);
static void RD_Handle_Set_Startup_Rada(uint8_t mode_start);

int RD_Messenger_Mess(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par) {
	RD_Mess_Temp_Receive = (RD_Type_Device_Message *) (&par[0]);
	RD_Mess_Recevie = *RD_Mess_Temp_Receive;
	u16 Header = RD_Mess_Recevie.Header[1] << 8 | RD_Mess_Recevie.Header[0];
	switch (Header) {

	case RD_SET_TYPE_DEVICE:
		RD_LOG("SET TYPE DEVICE Name: 0x%04X", NAME);
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
		RD_LOG("SAVE GW\n");
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
	case RD_PROVISION_AES:
		RD_LOG("KIEM TRA BAO MAT\n");
		if(is_provision_success()){
			flash_save_secure.flag_check_mess = 1;
			if (RD_AesreCheck(cb_par->adr_dst, &par[2])) {
				flash_save_secure.flag_process_aes = ENCRYPT_OK;
				RD_LOG("OK HC\n");

				RD_Mess_Recevie.Header[0] = 0x03;
				RD_Mess_Recevie.Header[1] = 0x00;
				RD_Mess_Recevie.MainType = 0x01;
				RD_Mess_Recevie.Feature = 0x02;
				RD_Mess_Recevie.Name = NAME; // NAME
				RD_Mess_Recevie.Future[0] = 0x00;
				RD_Mess_Recevie.Future[1] = 0x03;
				RD_Mess_Recevie.Future[2] = 0x00;

				BuffRec = (uint8_t *) (&RD_Mess_Recevie.Header[0]);
				mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8, cb_par->adr_src, 2);

			} else {
				flash_save_secure.flag_process_aes = ENCRYPT_ERR;
				RD_LOG("MA HOA SAI\n");

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
			RD_LOG("check_provision: %d\n", flash_save_secure.flag_process_aes);
		}

		break;
	}
	return 0;
}

int RD_mesh_cmd_sig_lightness_linear_set(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par){
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S); // nhay 1 pphat
	packing_lot_addr = cb_par->adr_src;
	op_rsp_packing_lot = cb_par->op_rsp;
	uint8_t Header = 0;
	Header = par[0];
	switch(Header){
	case RD_CONFIG_MS58_LOT:
		RD_Handle_Config_LOT(par);
		break;
	case RD_CONFIG_MS58_SENSITIVE:
		RD_Handle_Config_Sensitive(par);
		break;
	case RD_CONFIG_MIN_MAX:
		RD_Handle_Min_Max_Lightness(par);
		break;
	case RD_SET_MODE_RADA:
		RD_Handle_Set_Mode_Rada(par[3]);
		break;
	case RD_SW_SELECT_MODE_RADA:
		RD_Handle_Select_Rada(par[3]);
		break;
	case RD_SET_STARTUP_MODE:
		RD_Handle_Set_Startup_Rada(par[3]);
		break;
	default:
		uart_Csend("wrong header\n");
		break;
	}
	RD_rsp_packing_lot(par);
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


static void RD_Handle_Config_LOT(uint8_t *par){
	uart_Csend("config lot\n");
	uint8_t gain = 0x33;
	uint8_t delta[2] = {0};
	uint8_t lot[4] = {0};

	uint16_t time_s = (par[4]<<8) | par[3];
	uint32_t time_ms = time_s*1000;
	delta[0] = Flash_Save_MS58.parMS58.delta[0];
	delta[1] = Flash_Save_MS58.parMS58.delta[1];
	lot[0] = (time_ms>>24)&0xff;
	lot[1] = (time_ms>>16)&0xff;
	lot[2] = (time_ms>>8)&0xff;
	lot[3] = time_ms & 0xff;

	RD_Mess_Config_MS58(gain, delta, lot);
}

static void RD_Handle_Config_Sensitive(uint8_t *par){
	uart_Csend("config sensitive\n");
	uint8_t gain = 0x33;
	uint8_t delta[2] = {0};
	uint8_t lot[4] = {0};

	delta[0] = par[4];
	delta[1] = par[3];
	lot[0] = Flash_Save_MS58.parMS58.lot[0];
	lot[1] = Flash_Save_MS58.parMS58.lot[1];
	lot[2] = Flash_Save_MS58.parMS58.lot[2];
	lot[3] = Flash_Save_MS58.parMS58.lot[3];

	RD_Mess_Config_MS58(gain, delta, lot);

}
static void RD_Handle_Min_Max_Lightness(uint8_t *par){
	Flash_Save_MS58.lightness_max = par[3]*0xffff/100;
	Flash_Save_MS58.lightness_min = par[4]*0xffff/100;
	RD_Write_Flash_MS58();
	uart_Csend("config min max\n");

}
static void RD_Handle_Select_Rada(uint8_t on_off_mess){
	Flash_Save_MS58.sw_select = on_off_mess;
	RD_Write_Flash_MS58();
	RD_LOG("set select mode: 0x%02X\n",Flash_Save_MS58.sw_select);

}
static void RD_Handle_Set_Mode_Rada(uint8_t mode){

	Flash_Save_MS58.mode = mode;
	RD_Write_Flash_MS58();
	RD_LOG("set mode rada: 0x%02X\n",Flash_Save_MS58.mode);

}
static void RD_Handle_Set_Startup_Rada(uint8_t mode_start){
	Flash_Save_MS58.start_status = mode_start;
	RD_Write_Flash_MS58();
	RD_LOG("set startup rada: 0x%02X\n",Flash_Save_MS58.start_status);

}

void RD_Mess_Config_MS58(uint8_t gain, uint8_t delta[2], uint8_t lot[4]){
	RD_config_MS58(gain, delta, lot);
	Flash_Save_MS58.parMS58.gain = gain;
	Flash_Save_MS58.parMS58.delta[0] = delta[0];
	Flash_Save_MS58.parMS58.delta[1] = delta[1];
	Flash_Save_MS58.parMS58.lot[0] = lot[0];
	Flash_Save_MS58.parMS58.lot[1] = lot[1];
	Flash_Save_MS58.parMS58.lot[2] = lot[2];
	Flash_Save_MS58.parMS58.lot[3] = lot[3];
	RD_Write_Flash_MS58();
}

void RD_rsp_packing_lot(uint8_t *par){
	uint8_t mess_buff[8] = {0};
	mess_buff[0] = MAINTYPE;
	mess_buff[1] = FEATURE;
	mess_buff[2] = NAME;
	mess_buff[3] = par[2];
	mess_buff[4] = par[1];
	mess_buff[5] = par[0];
	mess_buff[6] = par[4];
	mess_buff[7] = par[3];

	mesh_tx_cmd2normal_primary(op_rsp_packing_lot,mess_buff,8,packing_lot_addr, 0);
}
