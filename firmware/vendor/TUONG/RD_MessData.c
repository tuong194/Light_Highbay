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
RD_Rsp_GW_Address RD_Rsp_GW_Addr;

uint16_t packing_lot_addr = 0;
uint32_t op_rsp_packing_lot = 0;

_Bool rd_flag_set_gr = FALSE;
u32 time_reset_flag_gr = 0;

uint8_t *BuffRec;
uint16_t RD_GATEWAY_ADDR = 0x0001;

_Bool flag_kickout_all = FALSE;
extern _Bool flag_training_2;

//static void RD_Handle_Select_Rada(uint8_t on_off_mess);
static void RD_Handle_Config_LOT(uint8_t *par);
static void RD_Handle_Min_Max_Lightness(uint8_t *par);
static void RD_Handle_Config_Sensitive(uint8_t *par);
static void RD_Handle_Set_Mode_Rada(uint8_t mode);
static void RD_Handle_Set_Startup_Rada(uint8_t mode_start);
static void RD_Handle_Get_Dim_Lightness(void);
static void RD_Handle_Set_Group(uint8_t *par, mesh_cb_fun_par_t *cb_par);


int RD_Messenger_Mess(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par) {
	RD_Mess_Temp_Receive = (RD_Type_Device_Message *) (&par[0]);
	RD_Mess_Recevie = *RD_Mess_Temp_Receive;
	u16 Header = RD_Mess_Recevie.Header[1] << 8 | RD_Mess_Recevie.Header[0];
	switch (Header) {

	case RD_SET_TYPE_DEVICE:
		//RD_LOG("SET TYPE DEVICE Name: 0x%04X", NAME);
		RD_Mess_Recevie.Header[0] = 0x01;
		RD_Mess_Recevie.Header[1] = 0x00;
		RD_Mess_Recevie.MainType = MAINTYPE;
		RD_Mess_Recevie.Feature = FEATURE;
		RD_Mess_Recevie.Name = NAME;
		RD_Mess_Recevie.Future[0] = 0x00;
		RD_Mess_Recevie.Future[1] = VERSION_MAIN;
		RD_Mess_Recevie.Future[2] = VERSION_SUB;

		RD_Flash_Save_Type(RD_Mess_Recevie.MainType, RD_Mess_Recevie.Feature,
				RD_Mess_Recevie.Name);

		BuffRec = (uint8_t *) (&RD_Mess_Recevie.Header[0]);
		mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8, cb_par->adr_src,
				2);
		break;
	case RD_SAVE_GATEWAY_ADDRESS:

		RD_GATEWAY_ADDR = saveGatewayAddr(&par[2], cb_par->adr_src);
		//RD_LOG("SAVE GW: %d\n", RD_GATEWAY_ADDR);
		RD_Save_GW_Addr.GWID[0] = (uint8_t) (RD_GATEWAY_ADDR & 0xff);
		RD_Save_GW_Addr.GWID[1] = (uint8_t) (RD_GATEWAY_ADDR >> 8 & 0xff);
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
		mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8, cb_par->adr_src, 2);
		break;
	case RD_KICKOUT_ALL:
		if (is_provision_success()) {
			flag_kickout_all = TRUE;
		}
		break;
	case RD_PROVISION_AES:
		//RD_LOG("KIEM TRA BAO MAT\n");
		if (is_provision_success()) {
			flash_save_secure.flag_check_mess = 1;
			if (RD_AesreCheck(cb_par->adr_dst, &par[2])) {
				flash_save_secure.flag_process_aes = ENCRYPT_OK;
				//RD_LOG("OK HC\n");

				RD_Mess_Recevie.Header[0] = 0x03;
				RD_Mess_Recevie.Header[1] = 0x00;
				RD_Mess_Recevie.MainType = MAINTYPE;
				RD_Mess_Recevie.Feature = FEATURE;
				RD_Mess_Recevie.Name = NAME; // NAME
				RD_Mess_Recevie.Future[0] = 0x00;
				RD_Mess_Recevie.Future[1] = VERSION_MAIN;
				RD_Mess_Recevie.Future[2] = VERSION_SUB;

				BuffRec = (uint8_t *) (&RD_Mess_Recevie.Header[0]);
				mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8,
						cb_par->adr_src, 2);

			} else {
				flash_save_secure.flag_process_aes = ENCRYPT_ERR;
				//RD_LOG("MA HOA SAI\n");

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
			//RD_LOG("check_provision: %d\n", flash_save_secure.flag_process_aes);
		}

		break;
	}
	return 0;
}

int RD_Messenger_Training_2(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par){
	if(get_provision_state() == STATE_DEV_UNPROV){
		flag_training_2 = TRUE;
		flash_save_training.rd_flag_test_mode = 1;
	}else{
		flag_training_2 = FALSE;
	}
	return 0;
}

int RD_mesh_cmd_sig_lightness_linear_set(u8 *par, int par_len,
		mesh_cb_fun_par_t * cb_par) {

	packing_lot_addr = cb_par->adr_src;
	op_rsp_packing_lot = cb_par->op_rsp;
	uint8_t Header = 0;
	Header = par[0];
	switch (Header) {
	case RD_CONFIG_MS58_LOT:
		RD_Handle_Config_LOT(par);
		RD_rsp_packing_lot(&par[0]);
		break;
	case RD_SET_GROUP:
		RD_Handle_Set_Group(par, cb_par);
		RD_rsp_packing_lot(&par[0]);
		break;
	case RD_CONFIG_MS58_SENSITIVE:
		RD_Handle_Config_Sensitive(par);
		RD_rsp_packing_lot(&par[0]);
		break;
	case RD_CONFIG_MIN_MAX:
		RD_Handle_Min_Max_Lightness(par);

		break;
	case RD_SET_MODE_RADA:
		RD_Handle_Set_Mode_Rada(par[3]);
		RD_rsp_packing_lot(&par[0]);
		break;
	case RD_GET_DIM_LIGHTNESS:
		RD_Handle_Get_Dim_Lightness();
		break;
	case RD_SET_STARTUP_MODE:
		RD_Handle_Set_Startup_Rada(par[3]);
		RD_rsp_packing_lot(&par[0]);
		break;
	default:
		//uart_Csend("0x0582 wrong header\n");
		break;
	}

	return 0;
}
uint16_t saveGatewayAddr(uint8_t *para, uint16_t srcAddr) {
	uint16_t GW_Addr = 0x0001;
	if (para[0] || para[1]) {
		GW_Addr = para[1] << 8 | para[0];
	} else {
		GW_Addr = srcAddr;
	}
	return GW_Addr;
}

static void RD_Handle_Config_LOT(uint8_t *par) {

	uint8_t gain = 0x33;
	uint8_t delta[2] = { 0 };
	uint8_t lot[4] = { 0 };

	uint16_t time_s = (par[4] << 8) | par[3];
	TIMEOUT_MOTION_GROUP = time_s;
	//RD_LOG("time out gr: %d\n", TIMEOUT_MOTION_GROUP);
	uint32_t time_ms = 0;
	time_ms = (uint32_t)time_s * 1000;
	delta[0] = Flash_Save_MS58.parMS58.delta[0];
	delta[1] = Flash_Save_MS58.parMS58.delta[1];
	lot[0] = (time_ms >> 24) & 0xff;
	lot[1] = (time_ms >> 16) & 0xff;
	lot[2] = (time_ms >> 8) & 0xff;
	lot[3] = time_ms & 0xff;

#if RD_LOG_UART
	uart_Csend("config lot\n");
	RD_LOG("time: %d\n", time_ms);
	RD_LOG("lot: 0x%02X 0x%02X 0x%02X 0x%02X\n",lot[0], lot[1], lot[2], lot[3]);
#endif
	RD_Mess_Config_MS58(gain, delta, lot);
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S); // nhay 1 phat
}

static void RD_Handle_Config_Sensitive(uint8_t *par) {
	//uart_Csend("config sensitive\n");
	uint8_t gain = Flash_Save_MS58.parMS58.gain;
	uint8_t delta[2] = { 0 };
	uint8_t lot[4] = { 0 };

	uint16_t delta_t = (par[4] << 8) | par[3];
	switch(delta_t){
	case HIGH_SEN:  // 20
		delta[0] = 0x00;
		delta[1] = 0x14;
		break;
	case MIDLE_SEN: // 50
		delta[0] = 0x00;
		delta[1] = 0x32;
		break;
	case LOW_SEN: // 100
		delta[0] = 0x00;
		delta[1] = 0x64;
		break;
	default:
		//uart_Csend("delta wrong\n");
		break;
	}
	lot[0] = Flash_Save_MS58.parMS58.lot[0];
	lot[1] = Flash_Save_MS58.parMS58.lot[1];
	lot[2] = Flash_Save_MS58.parMS58.lot[2];
	lot[3] = Flash_Save_MS58.parMS58.lot[3];

	RD_Mess_Config_MS58(gain, delta, lot);
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S); // nhay 1 phat
}
static void RD_Handle_Min_Max_Lightness(uint8_t *par) {
	Flash_Save_MS58.lightness_max = par[3] * 0xffff / 100;
	Flash_Save_MS58.lightness_min = par[4] * 0xffff / 100;
	RD_Write_Flash_MS58();

	RD_rsp_packing_lot(&par[0]);
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S); // nhay 1 phat
	mesh_tx_cmd2normal_primary(op_rsp_packing_lot, par, 5,
			packing_lot_addr, 2);

#if RD_LOG_UART
	uart_Csend("config min max\n");
	RD_LOG("light max: %d, light min: %d\n",Flash_Save_MS58.lightness_max,Flash_Save_MS58.lightness_min);
#endif
}

static void RD_Handle_Set_Mode_Rada(uint8_t mode) {

	if(mode == 0x00){
		Flash_Save_MS58.mode = MANUAL;
	}else{
		Flash_Save_MS58.mode = AUTO;
	}

	RD_Write_Flash_MS58();
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S); // nhay 1 phat

#if RD_LOG_UART
	RD_LOG("set mode rada: 0x%02X\n", Flash_Save_MS58.mode);
#endif

}
static void RD_Handle_Set_Startup_Rada(uint8_t mode_start) {
	if(mode_start == 0x00){
		Flash_Save_MS58.start_status = MANUAL;
	}else if(mode_start == 0x01){
		Flash_Save_MS58.start_status = AUTO;
	}else{
		Flash_Save_MS58.start_status = KEEP_STATUS;
	}
	RD_Write_Flash_MS58();
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S); // nhay 1 phat

#if RD_LOG_UART
	RD_LOG("set startup rada: 0x%02X\n", Flash_Save_MS58.start_status);
#endif
}

static void RD_Handle_Set_Group(uint8_t *par, mesh_cb_fun_par_t *cb_par){ // chi call 1 group cuoi cung
	uint16_t Group_ID = (par[4]<<8) | par[3];
	uint16_t Opcode_Group = (par[6]<<8) | par[5];

	uint8_t parGroup[6] = {0};
	mesh_cb_fun_par_t *cb_par_g = cb_par;
	cb_par_g->op = Opcode_Group;
	cb_par_g->op_rsp = CFG_MODEL_SUB_STATUS;
	cb_par_g->model_idx = 0;
	if(cb_par_g->adr_dst == 0xFFFF){ // all node
		cb_par_g->adr_dst = ele_adr_primary;
	}

	if(Opcode_Group == CFG_MODEL_SUB_ADD){
		for(u8 i = 0; i< RD_MAX_NUM_GROUP; i++){
			if(Flash_Save_MS58.Call_Group.ID_Group[i] == (Group_ID & 0xff)) break;
			Flash_Save_MS58.Call_Group.ID_Group[i] = Group_ID & 0xff;
		}
		RD_Write_Flash_MS58();
		//RD_LOG("parkinglot set group id: 0x%02X\n", Group_ID & 0xff);

		parGroup[0] = cb_par_g->adr_dst & 0xff;
		parGroup[1] = cb_par_g->adr_dst >>8 & 0xff;
		parGroup[2] = Group_ID & 0xff;
		parGroup[3] = Group_ID>>8 & 0xff;
		parGroup[4] = 0x00;
		parGroup[5] = 0x10;

		mesh_cmd_sig_cfg_model_sub_set(parGroup,6,cb_par_g);
	}else if(Opcode_Group == CFG_MODEL_SUB_DEL_ALL){
		//RD_EDIT:delete ID group
		for(u8 i = 0; i< RD_MAX_NUM_GROUP; i++){
			if(Flash_Save_MS58.Call_Group.ID_Group[i] == (Group_ID & 0xff)){
				Flash_Save_MS58.Call_Group.ID_Group[i] = 0xff;
			}
		}
		RD_Write_Flash_MS58();
		//RD_LOG("parkinglot del group id: 0x%02X\n", Group_ID & 0xff);

		parGroup[0] = cb_par_g->adr_dst & 0xff;
		parGroup[1] = cb_par_g->adr_dst >>8 & 0xff;
		parGroup[2] = 0x00;
		parGroup[3] = 0x10;

		mesh_cmd_sig_cfg_model_sub_set(parGroup,4,cb_par_g);
	}

}

static void RD_Handle_Get_Dim_Lightness(void){
	u16 lightness = s16_to_u16(light_g_level_present_get(0,ST_TRANS_LIGHTNESS));//
	u8 on_off = light_res_sw_save[0].level[ST_TRANS_LIGHTNESS].onoff;
	uint8_t mess_buff[4] = { 0 };
	mess_buff[0] = 0x02;
	mess_buff[1] = (on_off<<4)|0x01;
	// if(on_off == 0){
	// 	mess_buff[1] = 0x11;
	// }else{
	// 	mess_buff[1] = 0x01;
	// }
	mess_buff[2] = lightness & 0xff;
	mess_buff[3] = (lightness >> 8) & 0xff;

	mesh_tx_cmd2normal_primary(op_rsp_packing_lot, mess_buff, 4, packing_lot_addr, 2);
}


void RD_Mess_Config_MS58(uint8_t gain, uint8_t delta[2], uint8_t lot[4]) {
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

void RD_rsp_packing_lot(u8 *par) {
	uint8_t mess_buff[8] = { 0 };
	mess_buff[0] = MAINTYPE;
	mess_buff[1] = FEATURE;
	mess_buff[2] = NAME;
	mess_buff[3] = par[2];
	mess_buff[4] = par[1];
	mess_buff[5] = par[0];
	mess_buff[6] = par[4];
	mess_buff[7] = par[3];

	mesh_tx_cmd2normal_primary(op_rsp_packing_lot, mess_buff, 8,
			packing_lot_addr, 2);
}

int RD_Control_Group_By_SENSOR(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par){

	for(u8 i =0; i< RD_MAX_NUM_GROUP; i++){
		if(par[i] != 0xff){
			for(u8 j =0; j < RD_MAX_NUM_GROUP; j++){
				if(Flash_Save_MS58.Call_Group.ID_Group[j] == par[i]){
					// ton tai group
					time_start_motion_by_gr = clock_time_ms();
					if(time_start_motion_by_gr >= 0xfffffff0) time_start_motion_by_gr = 0;
					motion_detect = TRUE;
					return 1;
				}
			}
		}
	}
	return 0;
}

void RD_Sub_Del_ID_Group(uint16_t op, uint8_t ID_group){
	// ADD GROUP
	if(op == 0x1B80){
		//Flash_Save_MS58.Call_Group.flag_on_off_group = 1;
		for(u8 i = 0; i< RD_MAX_NUM_GROUP; i++){
			if(Flash_Save_MS58.Call_Group.ID_Group[i] == ID_group)
				return;
			else if(Flash_Save_MS58.Call_Group.ID_Group[i] == 0xff){
				Flash_Save_MS58.Call_Group.ID_Group[i] = ID_group;
				RD_Write_Flash_MS58();
				//RD_LOG("set group id: 0x%02X\n", ID_group);
				break;
			}
		}
	}
	// DEL GROUP
	else if(op == 0x1C80){
		for(u8 i = 0; i< RD_MAX_NUM_GROUP; i++){
			if(Flash_Save_MS58.Call_Group.ID_Group[i] == ID_group){
				Flash_Save_MS58.Call_Group.ID_Group[i] = 0xff;
				RD_Write_Flash_MS58();
				//RD_LOG("delete group id: 0x%02X\n", ID_group);
			}
		}
	}
}

void RD_Clear_Flag_Group(void){
	if(clock_time_exceed_ms(time_reset_flag_gr, 800)){
		rd_flag_set_gr = FALSE;
	}
}
