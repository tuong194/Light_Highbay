/*
 * RD_Sceen.c
 *
 *  Created on: Sep 11, 2024
 *      Author: PC5
 */

#include "RD_Scene.h"
#include "RD_MessData.h"
#include "MS58.h"
#include "RD_Type_Device.h"
#include "../mesh/RD_Lib.h"

Sw_Working_Stt_Str Sw_Working_Stt_Val = { 0 };
Flash_Save_K9B dataFlashK9B = { { 0 } };


uint16_t RD_list_check_scene[50] = {0};
uint8_t numscene = 0;

//RD_EDIT: MANG CHUA THONG TIN NHOM VA GIA TRI CANH CHO TAO PHONG NHANH
#if  (NAME == SMT_121)
	uint16_t groupType 		= 0x0001;
	uint16_t temp[6] 		= {0x4e20,  0x0320, 0x4e20, 0x15c0, 0x15c0, 0x15c0};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x4ccd};
#elif(NAME == COB_122)
	uint16_t groupType 		= 0x0002;
	uint16_t temp[6] 		= {0x4e20,  0x0320, 0x4e20, 0x15c0, 0x15c0, 0x15c0};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x4ccd};
#elif(NAME == DOWNLIGHT_TT_124)
	uint16_t groupType 		= 0x0004;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == PN_T_125)
	uint16_t groupType 		= 0x0005;
	uint16_t temp[6] 		= {0x4e20,  0x0320, 0x4e20, 0x15c0, 0x15c0, 0x15c0};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x4ccd};
#elif(NAME == PN_126)
	uint16_t groupType 		= 0x0006;
	uint16_t temp[6] 		= {0x4e20,  0x15c0, 0x4e20, 0x15c0, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x0000};
#elif(NAME == OT_127)
	uint16_t groupType 		= 0x0007;
	uint16_t temp[6] 		= {0x4e20,  0x15c0, 0x4e20, 0x15c0, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x0000};
#elif(NAME == GT_128)
	uint16_t groupType 		= 0x0008;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x15c0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TL_12a)
	uint16_t groupType 		= 0x000a;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x15c0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TT_12b)
	uint16_t groupType 		= 0x000b;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == LED_WIRE_CT)
	uint16_t groupType 		= 0x000d;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x15c0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TUBE_12e)
	uint16_t groupType 		= 0x000e;
	uint16_t temp[6] 		= {0x4e20,  0x15c0, 0x4e20, 0x0320, 0x0320, 0x0320};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x7fff};
#elif(NAME == HIGHTBAY_RADA)
	uint16_t groupType 		= 0x0004;
	uint16_t temp[6] 		= {0, 0, 0, 0, 0, 0};
	uint16_t lightness[6] 	= {0x0000, 0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
//----------------------------------------------------------------------------------------

#elif(NAME == RLT03_12W_12026)
	uint16_t groupType 		= 0x001d;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TRL08_10W_12025)
	uint16_t groupType 		= 0x001c;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TRL08_20W_12024)
	uint16_t groupType 		= 0x001b;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT01_10W_12023)
	uint16_t groupType 		= 0x001a;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT02_20W_12022)
	uint16_t groupType 		= 0x0019;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT02_10W_12021)
	uint16_t groupType 		= 0x0018;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT03_06W_12020)
	uint16_t groupType 		= 0x0017;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#endif


void RD_Group_Auto(uint16_t Group_ID, mesh_cb_fun_par_t *cb_par, uint16_t Opcode_Group);
void RD_Scene_Auto(uint16_t Scene_ID, mesh_cb_fun_par_t *cb_par, uint16_t Opcode_Scene);

static void RD_Handle_ScanK9BHC(uint8_t par[8], uint16_t Gw_Add_Buff);
static void RD_Handle_Save_K9BHC(uint8_t par[8], uint16_t Gw_Add_Buff);
static void RD_Handle_K9B_SaveScene(uint8_t par[8], uint16_t Gw_Add_Buff);
static void RD_Handle_K9B_DeleteScene(uint8_t par[8], uint16_t Gw_Add_Buff);
static void RD_Handle_Delete_K9BHC(uint8_t par[8], uint16_t Gw_Add_Buff);

static void RALI_Handle_Config_Distance(uint8_t par);
static void RALI_Handle_Config_Sensitive(uint8_t *par);
static void RALI_Handle_Config_LOT(uint8_t *par);
static void RALI_Handle_Set_Mode_Rada(uint8_t mode);
static void RALI_Handle_Set_Scene_Rada(u8 *par);
static void RALI_Handle_Set_Startup_Rada(uint8_t mode_start);

void RD_rsp_hc(uint8_t *par, uint16_t GW_Addr);
extern void scene_active_set(int idx, u16 scene_id, int trans_flag);

int RD_mesh_cmd_sig_cfg_model_sub_net(u8 *par, int par_len,	mesh_cb_fun_par_t *cb_par) {

	//cfg_led_event(LED_EVENT_FLASH_1HZ_1S); // nhay 1 phat

	uint16_t Header = 0;
	uint16_t GW_Addr_Buff = 0x0000;
	uint16_t ID_Group = 0;
	uint16_t ID_Group_Type = 0;
	uint16_t ID_Scene = 0;

	Header = par[1] << 8 | par[0];
	GW_Addr_Buff = cb_par->adr_src;

	//RD_LOG("header: %d\n",Header);

	switch (Header) {

	case RD_AUTO_CREATE_GROUP_SCENE:
		//uart_Csend("set group va scene\n");
		if(is_provision_success()){

			ID_Group = par[3] << 8 | par[2];
			ID_Group_Type = ID_Group + groupType;
			ID_Scene = par[5] << 8 | par[4];

			RD_Group_Auto(ID_Group, cb_par, CFG_MODEL_SUB_ADD);
			RD_Group_Auto(ID_Group_Type, cb_par, CFG_MODEL_SUB_ADD);
			RD_Scene_Auto(ID_Scene, cb_par, SCENE_STORE_NOACK);
		}
		break;
	case RD_AUTO_DELETE_GROUP_SCENE:
		if(is_provision_success()){
			RD_Group_Auto(ID_Group, cb_par, CFG_MODEL_SUB_DEL_ALL);
			RD_Scene_Auto(ID_Scene, cb_par, SCENE_DEL_NOACK);
		}
		break;
#if NAME != HIGHTBAY_RADA
	case RD_HEADER_SW_PAIR_K9BREMOTE:
		RD_Handle_ScanK9BHC(par, GW_Addr_Buff);
		break;
	case RD_HEADER_SW_SAVEK9BHC:
		RD_Handle_Save_K9BHC(par, GW_Addr_Buff);
		break;
	case RD_HEADER_SW_SAVESCENE_K9BREMOTE:
		RD_Handle_K9B_SaveScene(par, GW_Addr_Buff);
		break;
	case RD_HEADER_SW_DELETESCENE_K9BREMOTE:
		RD_Handle_K9B_DeleteScene(par, GW_Addr_Buff);
		break;
	case RD_HEADER_SW_DELETEK9BHC:
		RD_Handle_Delete_K9BHC(par, GW_Addr_Buff);
		break;
#endif
	case RALI_CONFIG_MS58_DISTANCE:
		RALI_Handle_Config_Distance(par[2]);
		RD_rsp_hc(par, GW_Addr_Buff);
		break;
	case RALI_CONFIG_MS58_SENSITIVE:
		RALI_Handle_Config_Sensitive(par);
		RD_rsp_hc(par, GW_Addr_Buff);
		break;
	case RALI_CONFIG_MS58_LOT:
		RALI_Handle_Config_LOT(par);
		RD_rsp_hc(par, GW_Addr_Buff);
		break;
	case RALI_SET_MODE_RADA:
		RALI_Handle_Set_Mode_Rada(par[2]);
		RD_rsp_hc(par, GW_Addr_Buff);
		break;
	case RALI_SET_SCENE:
		RALI_Handle_Set_Scene_Rada(par);
		break;
	case RALI_SET_STARTUP_MODE:
		RALI_Handle_Set_Startup_Rada(par[2]);
		RD_rsp_hc(par, GW_Addr_Buff);
		break;
	default:
		//uart_Csend("wrong header\n");
		break;
	}
	return 0;
}

/*----------------------------------------------------------------Handle Func-------------------------------------------------------------------------*/

static void RD_Handle_ScanK9BHC(uint8_t par[8], uint16_t Gw_Add_Buff) {
	Sw_Working_Stt_Val.Add_K9B_HCSet = 0x0000;
	Sw_Working_Stt_Val.Pair_K9BHc_Flag = par[2];
	Sw_Working_Stt_Val.Clock_time_start_pair_onOff_ms = clock_time_ms();
}
static void RD_Handle_Save_K9BHC(uint8_t par[8], uint16_t Gw_Add_Buff) {
	uint32_t MacK9B_Buff = (uint32_t) (par[5] << 24 | par[4] << 16 | par[3] << 8 | par[2]);
	uint16_t K9BAdd = (uint16_t) (par[7] << 8 | par[6]);
	uint8_t SaveK9B_Stt = RD_Flash_Save_K9B(MacK9B_Buff, 3, K9BAdd);

	uint8_t Mess_rsp[7];
	for (int i = 0; i < 6; i++)
		Mess_rsp[i] = par[i];
	Mess_rsp[6] = SaveK9B_Stt;
	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP, &Mess_rsp[0], 7, Gw_Add_Buff, RD_MAXRESPONESEND);
}
static void RD_Handle_K9B_SaveScene(uint8_t par[8], uint16_t Gw_Add_Buff) {
	uint16_t K9BAdd = (uint16_t) (par[3] << 8 | par[2]);
	uint8_t ButtonID = par[4];
	//uint8_t ModeID = par[5];
	uint16_t SceneID = (uint16_t) (par[7] << 8 | par[6]);
	uint8_t SaveStt = RD_Flash_Save_Scene(K9BAdd, ButtonID, SceneID);

	uint8_t MessRspBuff[3] = { 0 };
	MessRspBuff[0] = RD_HEADER_SW_SAVESCENE_K9BREMOTE & 0xff;
	MessRspBuff[1] = RD_HEADER_SW_SAVESCENE_K9BREMOTE >> 8 & 0xff;
	MessRspBuff[2] = SaveStt;
	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP, &MessRspBuff[0], 3,
			Gw_Add_Buff, RD_MAXRESPONESEND);
}
static void RD_Handle_K9B_DeleteScene(uint8_t par[8], uint16_t Gw_Add_Buff){
	uint16_t K9BAdd = (uint16_t) (par[3] << 8 | par[2]);
	uint8_t ButtonID = par[4];
	//uint8_t ModeID = par[5];
	uint8_t deleteStt = 0;
	if(K9BAdd == 0xffff){
		deleteStt = RD_Flash_DeleteSceneK9BHC(K9BAdd);    // delete all scenen of all K9B_remote
	}else{
		if(ButtonID == 0xff){//xoa all scene
			deleteStt = RD_Flash_DeleteSceneK9BHC(K9BAdd); // delete all scene of 1 K9B_remote
		}else{ // xoa 1 scene
			deleteStt = RD_Flash_Save_Scene(K9BAdd, ButtonID, 0x0000); // delete 1 scene of 1 K9B_remote
		}
	}

}
static void RD_Handle_Delete_K9BHC(uint8_t par[8], uint16_t Gw_Add_Buff){
	uint16_t K9BAdd = (uint16_t) (par[3] << 8 | par[2]);
	uint8_t SaveK9B_Stt = RD_Flash_DeleteK9BHC(K9BAdd);

	uint8_t MessRSP[5] = {0};
	MessRSP[0] = RD_HEADER_SW_DELETEK9BHC & 0xff;
	MessRSP[1] = RD_HEADER_SW_DELETEK9BHC>>8 & 0xff;
	MessRSP[2] = K9BAdd & 0xff;
	MessRSP[3] = K9BAdd >> 8 & 0xff;
	MessRSP[4] = SaveK9B_Stt;
	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP, &MessRSP[0], 5, Gw_Add_Buff, RD_MAXRESPONESEND);

}
/*-----------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------Mess Func----------------------------------------------------------------*/
void RD_Mess_ScanK9BHC_Rsp(uint16_t Gw_Add_Buff, uint32_t K9Bmac, uint8_t type,	s8 TxPow) {  //rsp sau khi nhan ban tin tu K9B
	uint8_t Mess_RspBuff[8] = { 0 };
	Mess_RspBuff[0] = RD_HEADER_SW_PAIR_K9BREMOTE & 0xFF;
	Mess_RspBuff[1] = (RD_HEADER_SW_PAIR_K9BREMOTE >> 8) & 0xFF;
	Mess_RspBuff[2] = (uint8_t) (K9Bmac & 0xFF);
	Mess_RspBuff[3] = (uint8_t) ((K9Bmac >> 8) & 0xFF);
	Mess_RspBuff[4] = (uint8_t) ((K9Bmac >> 16) & 0xFF);
	Mess_RspBuff[5] = (uint8_t) ((K9Bmac >> 24) & 0xFF);
	Mess_RspBuff[6] = type;
	Mess_RspBuff[7] = TxPow;
	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP, &Mess_RspBuff[0], 8,
			Gw_Add_Buff, RD_MAXRESPONESEND);

}


void RD_MessK9BHc_Press(uint16_t K9B_Add, uint8_t ButtonID, uint8_t ModeID, uint16_t SenceID) // phan hoi lai cho HC
{
	uint8_t Mess_Buff[8] = {0};

	Mess_Buff[0] 	= RD_HEADER_SW_K9B_PRESS & 0xFF ;
	Mess_Buff[1]	= RD_HEADER_SW_K9B_PRESS >>8;
	Mess_Buff[2]  	= K9B_Add & 0xFF;
	Mess_Buff[3]  	= K9B_Add >>8;
	Mess_Buff[4]  	= ButtonID;
	Mess_Buff[5]  	= ModeID;
	Mess_Buff[6]  	= SenceID & 0xFF;
	Mess_Buff[7]  	= SenceID >>8;

	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP, Mess_Buff, 8, RD_GW_ADDR, RD_MAXRESPONESEND); //SENSOR_STATUS
	//uart_CSend("send K9B Press HC \n");
}

void RD_Call_Scene(uint16_t Scene_ID, uint8_t Mess_ID){
	Call_Scene_Str Scene_Mess_Buff;
	Scene_Mess_Buff.Scene_ID[0] = Scene_ID & 0xff;
	Scene_Mess_Buff.Scene_ID[1] = Scene_ID>>8 & 0xff;
	Scene_Mess_Buff.Null_Byte = Mess_ID;
	Scene_Mess_Buff.Tss[0] = TSS_DEFAULT & 0xff;
	Scene_Mess_Buff.Tss[1] = TSS_DEFAULT>>8 & 0xff;
	Scene_Mess_Buff.Future[0] = 0x00;
	Scene_Mess_Buff.Future[1] = 0x00;
	Scene_Mess_Buff.Future[2] = 0x00;

	uint8_t *Mess_buff;
	Mess_buff = (uint8_t *)(&Scene_Mess_Buff);

	mesh_tx_cmd2normal_primary(0x4382, Mess_buff, 8, 0xffff, 0); //SCENE_RECALL_NOACK: 0x4382
}
void RD_Check_ScanK9BHC(uint32_t k9BMac_Buff, uint8_t Num_Of_Button, s8 rssi) {//rssi cuong do tin hieu K9B
	if (Sw_Working_Stt_Val.Pair_K9BHc_Flag == 0x01) {
		RD_Mess_ScanK9BHC_Rsp(RD_GW_ADDR, k9BMac_Buff, Num_Of_Button, rssi); // phan hoi lại HC
		Sw_Working_Stt_Val.Add_K9B_HCSet = 0x0000;
		Sw_Working_Stt_Val.Pair_K9BHc_Flag = 0x00;
	}
}
uint8_t RD_K9B_ScanPress_K9BHC(u32 macDevice, u8 key, u32 par_signature) {  // khi K9B nhan nut se co ban tin gui ve
	uint8_t scanSttReturn = 0;
	uint8_t press_acess = 0;
	static u32 time_tongle_button[MAX_NUM_K9B] = { 0 };
	static u32 signatureLast = 0;
	static u32 HC_CountLast[MAX_NUM_K9B] = { 0 };
	static u8 K9B_ButtonID = 0;

	if (key > 0 && key < 0x80) {
		K9B_ButtonID = key;
		press_acess = 1;
	}
	if ((press_acess == 1) && (par_signature == 0x00 || par_signature != signatureLast)) {
		for (u8 i = 0; i < MAX_NUM_K9B; i++) {
			if (dataFlashK9B.deviceK9B[i].MacK9B == macDevice) {
				scanSttReturn = 1;
				if(clock_time_exceed_ms(time_tongle_button[i], TIMEOUT_PRESS_K9B_MS)){
					 if(HC_CountLast[i] != par_signature){
						 HC_CountLast[i] = par_signature;
						 time_tongle_button[i] = clock_time_ms();
						 u16 K9BHC_Add = dataFlashK9B.deviceK9B[i].AddrK9B;
						 u16 scene_id = 0x0000;

						 int ButtonPos_Buff = RD_CheckButton_Pos_K9BHC(dataFlashK9B.deviceK9B[i].Button_ID, key);
						 if(ButtonPos_Buff != -1) scene_id = dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[ButtonPos_Buff];

						 RD_MessK9BHc_Press(K9BHC_Add, key,1,scene_id); // send HC, log
						 if(scene_id != 0x0000) RD_Call_Scene(scene_id, (uint8_t)(key+scene_id)); // T_NOTE call scene

						 signatureLast = par_signature;

					 }
				}
			}
		}
	}
	for(u8 i=0; i< MAX_NUM_K9B; i++){
		if (dataFlashK9B.deviceK9B[i].MacK9B == macDevice){
			scanSttReturn=1;
		}
	}
	return scanSttReturn;
}

// qua 10s ko co rsp tu K9B -> HUY
void RD_K9B_TimeOutScan_OnOff(void) {
	if (Sw_Working_Stt_Val.Pair_K9BHc_Flag == 0x01 && clock_time_exceed_ms(Sw_Working_Stt_Val.Clock_time_start_pair_onOff_ms, TIME_OUT_SCAN_K9B)) {
		Sw_Working_Stt_Val.Pair_K9BHc_Flag = 0x00;
	}
}

uint8_t RD_Flash_Save_K9B(u32 macDevice, u8 NUm_Of_Button, u16 K9Badd) {
	u8 overSave_Flag = 0;
	u8 overSave_ID = 0;
	for (u8 i = 0; i < MAX_NUM_K9B; i++) { //exits
		if (dataFlashK9B.deviceK9B[i].MacK9B == macDevice) {
			overSave_Flag = 1;
			overSave_ID = i;
			break;
		}
	}
	if (overSave_Flag == 1) {
		dataFlashK9B.deviceK9B[overSave_ID].MacK9B = macDevice;
		dataFlashK9B.deviceK9B[overSave_ID].Num_Of_Button = NUm_Of_Button;
		dataFlashK9B.deviceK9B[overSave_ID].AddrK9B = K9Badd;
		flash_erase_sector(RD_K9B_FLASH_AREA);
		flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B),
				(uint8_t *) (&dataFlashK9B.Used[0]));
		return 1;
	}

	//not exits
	for (u8 i = 0; i < MAX_NUM_K9B; i++) {
		if (dataFlashK9B.deviceK9B[i].MacK9B == 0x00) {
			dataFlashK9B.deviceK9B[i].MacK9B = macDevice;
			dataFlashK9B.deviceK9B[i].Num_Of_Button = NUm_Of_Button;
			dataFlashK9B.deviceK9B[i].AddrK9B = K9Badd;
			flash_erase_sector(RD_K9B_FLASH_AREA);
			flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B),
					(uint8_t *) (&dataFlashK9B.Used[0]));
			return 1;
		}
		if (i == MAX_NUM_K9B - 1)
			return 0;
	}
	return 0;

}
int RD_CheckButton_Pos_K9BHC(uint8_t ButtonID_Aray[MAX_NUM_K9B_PRESS_STYLE], uint8_t ButtonID_Check) { // tim vi tri nut duoc nhan
	for (int i = 0; i < MAX_NUM_K9B_PRESS_STYLE; i++) {
		if (ButtonID_Aray[i] == ButtonID_Check) {
			//uart_CSend("Button Pos \n");
			return i;
		}
	}
	//uart_CSend("don't find BID \n");
	return -1;
}
uint8_t RD_Flash_Save_Scene(u16 K9BAdd, u8 ButtonID, u16 SceneID) {
	for (u8 i = 0; i < MAX_NUM_K9B; i++) {
		if (dataFlashK9B.deviceK9B[i].AddrK9B == K9BAdd) {
			int ButtonPos_buf = RD_CheckButton_Pos_K9BHC(&dataFlashK9B.deviceK9B[i].Button_ID[0], ButtonID);
			if (ButtonPos_buf == -1) { // nut moi
				int ButtonPos_new = RD_CheckButton_Pos_K9BHC(&dataFlashK9B.deviceK9B[i].Button_ID[0], 0x00);
				dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[ButtonPos_new] = SceneID;
				dataFlashK9B.deviceK9B[i].Button_ID[ButtonPos_new] = ButtonID;
			} else { // duplicate click
				if (SceneID == 0x0000) // id_scene = 0x0000 -> delete scene
					ButtonID = 0x00;
				dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[ButtonPos_buf] = SceneID;
				dataFlashK9B.deviceK9B[i].Button_ID[ButtonPos_buf] = ButtonID;
			}
			flash_erase_sector(RD_K9B_FLASH_AREA);
			flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) (&dataFlashK9B.Used[0]));
			return 1;
		}
	}
	return 0; // ko tim thay thiet bi K9B
}
static void RD_Flash_SetNullSceneK9B(uint8_t numOfArray)
{
	if( 0xFF == numOfArray)
	{
		for(int i=0; i< MAX_NUM_K9B; i++)
		{
			for(int j=0; j< MAX_NUM_K9B_PRESS_STYLE; j++)
			{
				dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[j] = 0;
				dataFlashK9B.deviceK9B[i].Button_ID[j] = 0;
			}
		}
	}
	else
	{
		for(int j=0; j < MAX_NUM_K9B_PRESS_STYLE; j++)
		{
			dataFlashK9B.deviceK9B[numOfArray].Scene_ID_OnePress[j] = 0;
			dataFlashK9B.deviceK9B[numOfArray].Button_ID[j] = 0;
		}
	}
}

void RD_Flash_SetNullK9B(uint8_t numOfArray){
	if(numOfArray == 0xff){          //delete all K9B
		for(u8 i=0;i<MAX_NUM_K9B; i++){
			dataFlashK9B.deviceK9B[i].MacK9B = 0;
			dataFlashK9B.deviceK9B[i].AddrK9B = 0;
			dataFlashK9B.deviceK9B[i].Num_Of_Button = 0;
			for(u8 j=0;j<MAX_NUM_K9B_PRESS_STYLE;j++){
				dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[j] = 0;
				dataFlashK9B.deviceK9B[i].Button_ID[j] = 0;
			}
		}
	}else{ // delete 1 K9B
		dataFlashK9B.deviceK9B[numOfArray].MacK9B = 0;
		dataFlashK9B.deviceK9B[numOfArray].AddrK9B = 0;
		dataFlashK9B.deviceK9B[numOfArray].Num_Of_Button = 0;
		for(u8 j=0;j<MAX_NUM_K9B_PRESS_STYLE;j++){
			dataFlashK9B.deviceK9B[numOfArray].Scene_ID_OnePress[j] = 0;
			dataFlashK9B.deviceK9B[numOfArray].Button_ID[j] = 0;
		}
	}
}

uint8_t RD_Flash_DeleteSceneK9BHC(uint16_t K9BAdd)
{
	if(0xFFFF != K9BAdd)
	{
		for(int i=0; i<MAX_NUM_K9B; i++)
		{
			if(dataFlashK9B.deviceK9B[i].AddrK9B == K9BAdd)
			{
				RD_Flash_SetNullSceneK9B(i);
				flash_erase_sector(RD_K9B_FLASH_AREA);
				flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0]);
				//uart_CSend("delete all scene K9B add: 0x%x\n",K9BAdd);
				//uart_Csend("delete all scene K9B add:\n");
				return 1;
			}
		}
		uart_Csend("don't have  K9B HC to delete Scene");
		return 0; // no data to delete
	}
	else
	{
		RD_Flash_SetNullSceneK9B(0xFF);
		flash_erase_sector(RD_K9B_FLASH_AREA);
		flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0] );
		uart_Csend("delete all scene of all K9B \n");
		return 1;
	}
}

uint8_t RD_Flash_DeleteK9BHC(uint16_t K9BAdd){
	if(K9BAdd != 0xffff){
		for(int i=0; i<MAX_NUM_K9B; i++)
		{
			if(dataFlashK9B.deviceK9B[i].AddrK9B == K9BAdd)
			{
				RD_Flash_SetNullK9B(i);
				flash_erase_sector(RD_K9B_FLASH_AREA);
				flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0]);
				//uart_CSend("delete all scene K9B add: 0x%x\n",K9BAdd);
				uart_Csend("delete all scene K9B add:\n");
				return 1;
			}
		}
		return 0;
	}else{
		RD_Flash_SetNullK9B(0xFF);
		flash_erase_sector(RD_K9B_FLASH_AREA);
		flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0] );
		uart_Csend("delete all scene of all K9B \n");
		return 1;
	}
}

void RD_Group_Auto(uint16_t Group_ID, mesh_cb_fun_par_t *cb_par, uint16_t Opcode_Group){
	uint8_t parGroup[6] = {0};
	mesh_cb_fun_par_t *cb_par_g = cb_par;
	cb_par_g->op = Opcode_Group;
	cb_par_g->op_rsp = CFG_MODEL_SUB_STATUS;
	cb_par_g->model_idx = 0;
	if(cb_par_g->adr_dst == 0xFFFF){ // all node
		cb_par_g->adr_dst = ele_adr_primary;
	}

	if(Opcode_Group == CFG_MODEL_SUB_ADD){
		parGroup[0] = cb_par_g->adr_dst & 0xff;
		parGroup[1] = cb_par_g->adr_dst >>8 & 0xff;
		parGroup[2] = Group_ID & 0xff;
		parGroup[3] = Group_ID>>8 & 0xff;
		parGroup[4] = 0x00;
		parGroup[5] = 0x10;

		mesh_cmd_sig_cfg_model_sub_set(parGroup,6,cb_par_g);
	}else if(Opcode_Group == CFG_MODEL_SUB_DEL_ALL){
		parGroup[0] = cb_par_g->adr_dst & 0xff;
		parGroup[1] = cb_par_g->adr_dst >>8 & 0xff;
		parGroup[2] = 0x00;
		parGroup[3] = 0x10;

		mesh_cmd_sig_cfg_model_sub_set(parGroup,4,cb_par_g);
	}
}

u8 RD_mesh_cmd_sig_scene_set_ll(u16 scene_id, mesh_cb_fun_par_t *cb_par, u16 lightness, u16 tempLight)
{
    u8 st = SCENE_ST_SUCCESS;
    u16 op = cb_par->op;
    int save = 0;
    if((SCENE_STORE == op)||(SCENE_STORE_NOACK == op)){
		scene_data_t *p_exist = 0;
		scene_data_t *p_null = 0;

		foreach(i,SCENE_CNT_MAX){
			scene_data_t *p = &model_sig_scene.data[cb_par->model_idx][i];
			if((0 == p_null) && (0 == p->id)){
				p_null = p; 	// the first empty
			}
			if(scene_id == p->id){
				p_exist = p;
				break;	// exist
			}
		}

		scene_data_t *p_save = 0;
		if(p_exist){
			p_save = p_exist;
		}else if(p_null){
			p_save = p_null;
		}

		if(p_save){
			save = 1;
			p_save->id = scene_id;
			//p_save->lightness_s16 = light_g_level_present_get(cb_par->model_idx, lightness);
			p_save->lightness_s16 = get_level_from_lightness(lightness);
			#if LIGHT_TYPE_CT_EN
			//p_save->temp_s16 = light_g_level_present_get(cb_par->model_idx, tempLight);
			p_save->temp_s16 = get_level_from_ctl_temp(tempLight, 0x0320, 0x4e20);
			p_save->delta_uv_s16 = 0;
			p_save->ct_flag = ct_flag;
			#endif
			#if LIGHT_TYPE_HSL_EN
			p_save->hue_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_HSL_HUE);
			p_save->sat_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_HSL_SAT);
			#endif
			#if (LIGHT_TYPE_SEL == LIGHT_TYPE_XYL)
			p_save->x_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_XYL_X);
			p_save->y_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_XYL_Y);
			#endif
			#if MD_LIGHT_CONTROL_EN
			scene_get_lc_par(p_save, cb_par->model_idx);
			#endif
			CB_NL_PAR_NUM_2(p_nl_get_vendor_scene_data, scene_id, p_save->nl_data);
			scene_active_set(cb_par->model_idx, scene_id, 0);
		}else{
			st = SCENE_ST_REG_FULL;
		}
    }else{	// del
		foreach(i,SCENE_CNT_MAX){
			scene_data_t *p = &model_sig_scene.data[cb_par->model_idx][i];
			if(scene_id == p->id){
				memset(p, 0, sizeof(scene_data_t));
				scene_proc_t *p_scene = &scene_proc[cb_par->model_idx];
				if(scene_id == p_scene->current_scene){
					p_scene->current_scene = 0;
				}

				if(scene_id == p_scene->target_scene){
					p_scene->target_scene = 0;
				}
				save = 1;
				break;	// exist
			}
		}
    }

    if(save){
		mesh_model_store(1, SIG_MD_SCENE_SETUP_S);
	}

    return st;
}

void RD_Scene_Auto(uint16_t Scene_ID, mesh_cb_fun_par_t *cb_par, uint16_t Opcode_Scene){
	mesh_cb_fun_par_t *cb_par_s = cb_par;
	cb_par_s->op = Opcode_Scene;
	cb_par_s->op_rsp = STATUS_NONE;
	cb_par_s->model_idx = 0;
	if(cb_par_s->adr_dst == 0xFFFF){ // all node
		cb_par_s->adr_dst = ele_adr_primary;
	}
	if(Opcode_Scene == SCENE_STORE_NOACK){
		foreach(i,6){
			//set scene
			RD_mesh_cmd_sig_scene_set_ll(Scene_ID+i, cb_par_s,lightness[i], temp[i]);
			RD_LOG("SCENE[%d] ",i);
			//RD_LOG(" id: 0x%04X, lightness: 0x%04X, temp: 0x%04X\n");
		}
	}else if(Opcode_Scene == SCENE_DEL_NOACK){
		foreach(i,SCENE_CNT_MAX){
			scene_data_t *p = &model_sig_scene.data[0][i];
			if(p->id != 0){
				RD_list_check_scene[numscene] = p->id;
				numscene++;
			}
		}
		if(numscene > 0){
			foreach(i, numscene){
				// xoa
				RD_mesh_cmd_sig_scene_set_ll(Scene_ID+i, cb_par_s, 0, 0);
				RD_list_check_scene[i] = 0;
			}
			numscene = 0;
		}
	}
}

/*-------------------------------RALI CONTROL-----------------------------------*/
static void RALI_Handle_Config_Distance(uint8_t par) {

	uint8_t gain;
	uint8_t delta[2] = { 0 };
	uint8_t lot[4] = { 0 };
	switch(par){
	// case 0x04:
	// 	gain = 0x93;
	// 	break;
	// case 0x05:
	// 	gain = 0x83;
	// 	break;
	// case 0x06:
	// 	gain = 0x73;
	// 	break;
	// case 0x07:
	// 	gain = 0x63;
	// 	break;
	case 0x08:
		gain = 0x53;
		delta[0] = 0x00;
		delta[1] = 0x17;
		break;
	case 0x09:
		gain = 0x43;
		delta[0] = 0x00;
		delta[1] = 0x16;
		break;
	case 0x0A:
		gain = 0x33;
		delta[0] = 0x00;
		delta[1] = 0x14;
		break;
	default:
		break;
	}
//	delta[0] = Flash_Save_MS58.parMS58.delta[0];
//	delta[1] = Flash_Save_MS58.parMS58.delta[1];

	lot[0] = Flash_Save_MS58.parMS58.lot[0];
	lot[1] = Flash_Save_MS58.parMS58.lot[1];
	lot[2] = Flash_Save_MS58.parMS58.lot[2];
	lot[3] = Flash_Save_MS58.parMS58.lot[3];

	RD_Mess_Config_MS58(gain, delta, lot);
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S);
}

static void RALI_Handle_Config_Sensitive(uint8_t *par) {
	//uart_Csend("hc config sensitive\n");
	uint8_t gain = Flash_Save_MS58.parMS58.gain;
	uint8_t delta[2] = { 0 };
	uint8_t lot[4] = { 0 };

	uint16_t delta_t = (par[3] << 8) | par[2];
	switch(delta_t){
	case HIGH_SEN:  // 20
		delta[0] = 0x00;
		delta[1] = 0x14;
		gain = 0x33;
		break;
	case MIDLE_SEN: // 30
		delta[0] = 0x00;
		delta[1] = 0x1e;
		break;
	case LOW_SEN: // 50
		delta[0] = 0x00;
		delta[1] = 0x32;
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
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S);
}

//static void RALI_Handle_Config_Sensitive(uint8_t *par) {
//	//uart_Csend("hc config sensitive\n");
//	uint8_t gain = Flash_Save_MS58.parMS58.gain;
//	uint8_t delta[2] = { 0 };
//	uint8_t lot[4] = { 0 };
//
//	delta[0] = par[3];
//	delta[1] = par[2];
//
//	lot[0] = Flash_Save_MS58.parMS58.lot[0];
//	lot[1] = Flash_Save_MS58.parMS58.lot[1];
//	lot[2] = Flash_Save_MS58.parMS58.lot[2];
//	lot[3] = Flash_Save_MS58.parMS58.lot[3];
//
//	RD_Mess_Config_MS58(gain, delta, lot);
//}

static void RALI_Handle_Config_LOT(uint8_t *par) {

	uint8_t gain = Flash_Save_MS58.parMS58.gain;
	uint8_t delta[2] = { 0 };
	uint8_t lot[4] = { 0 };

	uint16_t time_s = (par[3] << 8) | par[2];
	uint32_t time_ms = 0;
	time_ms = (uint32_t)time_s * 1000;
	delta[0] = Flash_Save_MS58.parMS58.delta[0];
	delta[1] = Flash_Save_MS58.parMS58.delta[1];
	lot[0] = (time_ms >> 24) & 0xff;
	lot[1] = (time_ms >> 16) & 0xff;
	lot[2] = (time_ms >> 8) & 0xff;
	lot[3] = time_ms & 0xff;

#if RD_LOG_UART
	uart_Csend("hc config lot\n");
	RD_LOG("time: %d\n", time_ms);
	RD_LOG("lot: 0x%02X 0x%02X 0x%02X 0x%02X\n",lot[0], lot[1], lot[2], lot[3]);
#endif
	RD_Mess_Config_MS58(gain, delta, lot);
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S);
}

static void RALI_Handle_Set_Mode_Rada(uint8_t mode) {

	Flash_Save_MS58.mode = mode;
	RD_Write_Flash_MS58();
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S);

#if RD_LOG_UART
	RD_LOG("hc set mode rada: 0x%02X\n", Flash_Save_MS58.mode);
#endif

}

static void RALI_Handle_Set_Scene_Rada(u8 *par){
	if(par[4] == 0xA0){ // co chuyen dong : call scene ID_Scene[1]
		Flash_Save_MS58.Call_Scene.on_off[1] = 1;
		Flash_Save_MS58.Call_Scene.ID_Scene[1] = (par[3] << 8) | par[2];
	}else if(par[4] == 0x20){ // ko co chuyen dong : call scene ID_Scene[0]
		Flash_Save_MS58.Call_Scene.on_off[0] = 1;
		Flash_Save_MS58.Call_Scene.ID_Scene[0] = (par[3] << 8) | par[2];
	}
	flash_erase_sector(RD_MS58_FLASH_AREA);
	flash_write_page(RD_MS58_FLASH_AREA, RD_FLASH_SIZE_MS58, (unsigned char *)(&Flash_Save_MS58.user[0]));
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S);
}

static void RALI_Handle_Set_Startup_Rada(uint8_t mode_start) {
	Flash_Save_MS58.start_status = mode_start;
	RD_Write_Flash_MS58();
	cfg_led_event(LED_EVENT_FLASH_1HZ_1S);

#if RD_LOG_UART
	RD_LOG("set startup rada: 0x%02X\n", Flash_Save_MS58.start_status);
#endif
}

void RD_rsp_hc(uint8_t *par, uint16_t GW_Addr){
	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP, par, sizeof(par)/sizeof(par[0]), GW_Addr, RD_MAXRESPONESEND);
}


/*--------------------------FLASH-----------------------------------*/
void Flash_Clean_K9B(void){
	dataFlashK9B.Used[0] = RD_CHECK_FLASH_K9B_H;
	dataFlashK9B.Used[1] = RD_CHECK_FLASH_K9B_L;
	dataFlashK9B.Used[2] = RD_CHECK_FLASH_K9B_H;
	dataFlashK9B.Used[3] = RD_CHECK_FLASH_K9B_L;
	for(u8 i=0; i< MAX_NUM_K9B; i++){
		dataFlashK9B.deviceK9B[i].AddrK9B = 0;
		dataFlashK9B.deviceK9B[i].MacK9B = 0;
		dataFlashK9B.deviceK9B[i].Num_Of_Button = 0;
		for(u8 j=0;j<MAX_NUM_K9B_PRESS_STYLE;j++){
			dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[j] = 0;
			dataFlashK9B.deviceK9B[i].Button_ID[j] = 0;
		}
	}
	flash_erase_sector(RD_K9B_FLASH_AREA);
	flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (unsigned char *) (&dataFlashK9B.Used[0]));
}

void Read_Flash_K9B(void){
	flash_read_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (unsigned char *) (&dataFlashK9B.Used[0]));
}

void Init_Flash_K9B(void){
	//flash_read_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (unsigned char *) (&dataFlashK9B.Used[0]));
	Read_Flash_K9B();

	if(dataFlashK9B.Used[0] != RD_CHECK_FLASH_K9B_H && dataFlashK9B.Used[1] != RD_CHECK_FLASH_K9B_L
       && dataFlashK9B.Used[2] != RD_CHECK_FLASH_K9B_H && dataFlashK9B.Used[3] != RD_CHECK_FLASH_K9B_L){
		Flash_Clean_K9B();
	}
}




















