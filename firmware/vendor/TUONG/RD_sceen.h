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

#define RD_MAXRESPONESEND 2

#define RD_GW_ADDR    0x0001
#define RD_OPCODE_SCENE_SEND			(0xE2)
#define RD_OPCODE_SCENE_RSP				(0xE3)
#define RD_HEADER_SW_PAIR_K9BREMOTE			(0x0A0B)
#define RD_HEADER_SW_SAVESCENE_K9BREMOTE	(0x0C0B)
#define RD_HEADER_SW_K9B_PRESS				(0x0B0B)
#define RD_HEADER_SW_SAVEK9BHC				(0x0D0B)
#define RD_HEADER_SW_DELETEK9BHC			(0x0E0B)
#define RD_HEADER_SW_DELETESCENE_K9BREMOTE	(0x0F0B)

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

void RD_Check_ScanK9BHC(uint32_t k9BMac_Buff, uint8_t Num_Of_Button, s8 rssi);

#endif /* RD_SCEEN_H_ */
