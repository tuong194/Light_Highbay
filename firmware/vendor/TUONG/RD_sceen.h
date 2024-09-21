/*
 * RD_sceen.h
 *
 *  Created on: Sep 11, 2024
 *      Author: PC5
 */

#ifndef RD_SCEEN_H_
#define RD_SCEEN_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#include "../common/scene.h"

#define RD_K9B_FLASH_AREA 0x7b000
#define RD_MAXRESPONESEND 2
#define MAX_NUM_K9B 5
#define MAX_NUM_K9B_PRESS_STYLE 12

#define TSS_DEFAULT          0x05

#define RD_GW_ADDR    0x0001
#define RD_OPCODE_SCENE_SEND			(0xE2)
#define RD_OPCODE_SCENE_RSP				(0xE3)

#define RD_AUTO_CREATE_GROUP_SCENE          (0x0C0A)
#define RD_AUTO_DELETE_GROUP_SCENE          (0x0D0A)
#define RD_HEADER_SW_PAIR_K9BREMOTE			(0x0A0B)
#define RD_HEADER_SW_SAVESCENE_K9BREMOTE	(0x0C0B)
#define RD_HEADER_SW_K9B_PRESS				(0x0B0B)
#define RD_HEADER_SW_SAVEK9BHC				(0x0D0B)
#define RD_HEADER_SW_DELETEK9BHC			(0x0E0B)
#define RD_HEADER_SW_DELETESCENE_K9BREMOTE	(0x0F0B)

#define TIME_OUT_SCAN_K9B       10000
#define TIMEOUT_PRESS_K9B_MS    500


typedef struct{
	uint8_t Scene_ID[2];
	uint8_t Null_Byte;
	uint8_t Tss[2];
	uint8_t Future[2];
}Call_Scene_Str;

typedef struct
{
	uint8_t Pair_K9BOnOff_Flag;
	uint8_t Button_K9BOnOff_Pair;
	uint8_t Pair_K9BHc_Flag;
	uint16_t Add_K9B_HCSet;			// HC set add for K9B remote
	uint32_t ClockTimeSetHc_ms;
	uint32_t Clock_BtK9BStartPress_ms[3];
	uint8_t  Bt_K9B_CountPress[3];
    uint32_t Clock_time_start_pair_onOff_ms;
} Sw_Working_Stt_Str;

typedef struct{
	u32 MacK9B;
	u16 AddrK9B;
	u16 Scene_ID_OnePress[MAX_NUM_K9B_PRESS_STYLE];
	u8 Button_ID[MAX_NUM_K9B_PRESS_STYLE];
	u8 Num_Of_Button;
}Flash_SaveTemp_K9B;

typedef struct{
	u8 Used[4];
	Flash_SaveTemp_K9B deviceK9B[MAX_NUM_K9B];
}Flash_Save_K9B;

int RD_mesh_cmd_sig_cfg_model_sub_net(u8 *par, int par_len,	mesh_cb_fun_par_t *cb_par);

void RD_Mess_ScanK9BHC_Rsp(uint16_t Gw_Add_Buff, uint32_t K9Bmac, uint8_t type,	s8 TxPow);
void RD_MessK9BHc_Press(uint16_t K9B_Add, uint8_t ButtonID, uint8_t ModeID, uint16_t SenceID);
void RD_Call_Scene(uint16_t Scene_ID, uint8_t Mess_ID);
void RD_Check_ScanK9BHC(uint32_t k9BMac_Buff, uint8_t Num_Of_Button, s8 rssi);
uint8_t RD_K9B_ScanPress_K9BHC(u32 macDevice, u8 key, u32 par_signature);

uint8_t RD_Flash_Save_K9B(u32 macDevice, u8 NUm_Of_Button, u16 K9Badd);
uint8_t RD_Flash_Save_Scene(u16 K9BAdd, u8 ButtonID, u16 SceneID);
uint8_t RD_Flash_DeleteSceneK9BHC(uint16_t K9BAdd);
uint8_t RD_Flash_DeleteK9BHC(uint16_t K9BAdd);

int RD_CheckButton_Pos_K9BHC(uint8_t ButtonID_Aray[MAX_NUM_K9B_PRESS_STYLE], uint8_t ButtonID_Check);
void RD_K9B_TimeOutScan_OnOff(void);


#endif /* RD_SCEEN_H_ */
