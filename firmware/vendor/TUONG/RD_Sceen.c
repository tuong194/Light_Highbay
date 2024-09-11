/*
 * RD_Sceen.c
 *
 *  Created on: Sep 11, 2024
 *      Author: PC5
 */

#include "RD_sceen.h"

Sw_Working_Stt_Str   Sw_Working_Stt_Val = {0};
uint16_t GW_Addr_Buff;

int RD_mesh_cmd_sig_cfg_model_sub_net(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par){
	uint16_t Header = par[1] << 8 | par[0];
	GW_Addr_Buff = 0x00;
	switch(Header){
	case RD_HEADER_SW_PAIR_K9BREMOTE:
		RD_Handle_ScanK9BHC(par,GW_Addr_Buff);
		break;
	case RD_HEADER_SW_SAVEK9BHC:
		RD_Handle_Save_K9B(par,GW_Addr_Buff);
	}

}

static void RD_Handle_ScanK9BHC(uint8_t par[8], uint16_t Gw_Add_Buff){
	Sw_Working_Stt_Val.Add_K9B_HCSet = 0x0000;
	Sw_Working_Stt_Val.Pair_K9BHc_Flag = par[2];
}
static void RD_Handle_Save_K9B(uint8_t par[8], uint16_t Gw_Add_Buff){
	uint32_t MacK9B_Buff = (uint32_t) (par[5]<<24 | par[4]<<16 | par[3]<<8 | par[2]);
	uint16_t K9BAdd = (uint16_t) (par[7]<<8 | par[6]);
	uint8_t SaveK9B_Stt = 0; //RD_EDIT: chua xong

	uint8_t Mess_rsp[7];
	for(int i=0; i<6;i++) Mess_rsp[i]=par[i];
	Mess_rsp[7] = SaveK9B_Stt;
	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &Mess_RspBuff[0], 7, Gw_Add_Buff, RD_MAXRESPONESEND);
}

void RD_Mess_ScanK9BHC_Rsp(uint16_t Gw_Add_Buff, uint32_t K9Bmac, uint8_t type, s8 TxPow)
{
	uint8_t Mess_RspBuff[8] ={0};
	Mess_RspBuff[0]	= RD_HEADER_SW_PAIR_K9BREMOTE 	     & 0xFF;
	Mess_RspBuff[1]	= (RD_HEADER_SW_PAIR_K9BREMOTE >> 8) & 0xFF;
	Mess_RspBuff[2] = (uint8_t) (K9Bmac      & 0xFF);
	Mess_RspBuff[3] = (uint8_t) ((K9Bmac >> 8) & 0xFF);
	Mess_RspBuff[4] = (uint8_t) ((K9Bmac >> 16) & 0xFF);
	Mess_RspBuff[5] = (uint8_t) ((K9Bmac >> 24) & 0xFF);
	Mess_RspBuff[6] = type;
	Mess_RspBuff[7] = TxPow;
	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &Mess_RspBuff[0], 8, Gw_Add_Buff, RD_MAXRESPONESEND);

}

void RD_Check_ScanK9BHC(uint32_t k9BMac_Buff, uint8_t Num_Of_Button, s8 rssi){//rssi cuong do tin hieu K9B
	if(Sw_Working_Stt_Val.Pair_K9BHc_Flag == 0x01){
		RD_Mess_ScanK9BHC_Rsp(RD_GW_ADDR, k9BMac_Buff, Num_Of_Button, rssi);
		Sw_Working_Stt_Val.Add_K9B_HCSet = 0x0000;
		Sw_Working_Stt_Val.Pair_K9BHc_Flag = 0x00;
	}
}
