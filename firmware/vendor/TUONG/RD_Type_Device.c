/*
 * RD_Type_Device.c
 *
 *  Created on: Sep 24, 2024
 *      Author: PC5
 */

#include "RD_Type_Device.h"
#include "RD_MessData.h"
#include "MS58.h"
#include "../mesh/RD_Lib.h"


Flash_Save_Type_GW Flash_Save_Type_Val;
Flash_Save_MS58_t  Flash_Save_MS58 = {{0}};
Flash_Save_Training flash_save_training = {{0}};

void RD_Flash_Save_GW(uint16_t GW_ADDR){
	Flash_Save_Type_Val.GWID[1] = (uint8_t) (GW_ADDR>>8 & 0xff);
	Flash_Save_Type_Val.GWID[0] = (uint8_t) (GW_ADDR & 0xff);

	flash_erase_sector(RD_GW_FLASH_AREA);
	flash_write_page(RD_GW_FLASH_AREA, sizeof(Flash_Save_Type_Val), (uint8_t *) (&Flash_Save_Type_Val.Used[0]));
}

void RD_Flash_Save_Type(uint8_t MainType, uint8_t Feature, uint8_t Name){
	Flash_Save_Type_Val.MainType = MainType;
	Flash_Save_Type_Val.Feature = Feature;
	Flash_Save_Type_Val.Name = Name;

	flash_erase_sector(RD_GW_FLASH_AREA);
	flash_write_page(RD_GW_FLASH_AREA, sizeof(Flash_Save_Type_Val), (uint8_t *) (&Flash_Save_Type_Val.Used[0]));
}

void RD_Clean_Flash_Type(void){
	Flash_Save_Type_Val.Used[0] = RD_CHECK_FLASH_H;
	Flash_Save_Type_Val.Used[1] = RD_CHECK_FLASH_L;
	Flash_Save_Type_Val.Used[2] = RD_CHECK_FLASH_H;
	Flash_Save_Type_Val.Used[3] = RD_CHECK_FLASH_L;

	Flash_Save_Type_Val.GWID[1] = (uint8_t) (RD_GATEWAY_ADDR>>8 & 0xff);
	Flash_Save_Type_Val.GWID[0] = (uint8_t) (RD_GATEWAY_ADDR & 0xff);
	Flash_Save_Type_Val.MainType = MAINTYPE;
	Flash_Save_Type_Val.Feature = FEATURE;
	Flash_Save_Type_Val.Name = NAME;

	flash_erase_sector(RD_GW_FLASH_AREA);
	flash_write_page(RD_GW_FLASH_AREA, sizeof(Flash_Save_Type_Val), (uint8_t *) (&Flash_Save_Type_Val.Used[0]));
}

void RD_Flash_Type_Init(void){
	flash_read_page(RD_GW_FLASH_AREA, sizeof(Flash_Save_Type_Val), (uint8_t *) (&Flash_Save_Type_Val.Used[0]));
	if(Flash_Save_Type_Val.Used[0] != RD_CHECK_FLASH_H && Flash_Save_Type_Val.Used[1] != RD_CHECK_FLASH_L
		&& Flash_Save_Type_Val.Used[2] != RD_CHECK_FLASH_H && Flash_Save_Type_Val.Used[3] != RD_CHECK_FLASH_L){
		RD_Clean_Flash_Type();
	}else{
		RD_GATEWAY_ADDR = Flash_Save_Type_Val.GWID[1] << 8 | Flash_Save_Type_Val.GWID[0];

	}
}

void Read_Flash_MS58(void){
	flash_read_page(RD_MS58_FLASH_AREA, RD_FLASH_SIZE_MS58, (unsigned char *)(&Flash_Save_MS58.user[0]));
}

void RD_Write_Flash_MS58(void){
	flash_erase_sector(RD_MS58_FLASH_AREA);
	flash_write_page(RD_MS58_FLASH_AREA, RD_FLASH_SIZE_MS58, (unsigned char *)(&Flash_Save_MS58.user[0]));
}

void RD_Flash_Reset_Config_MS58(void){
	Flash_Save_MS58.mode = AUTO;
	Flash_Save_MS58.start_status = KEEP_STATUS;
	Flash_Save_MS58.lightness_max = 0xffff;
	Flash_Save_MS58.lightness_min = 0x4cc2;
	Flash_Save_MS58.parMS58.gain = 0x33;
	Flash_Save_MS58.parMS58.delta[0] = 0x00;
	Flash_Save_MS58.parMS58.delta[1] = 0x14;
	Flash_Save_MS58.parMS58.lot[0] = 0x00;
	Flash_Save_MS58.parMS58.lot[1] = 0x00;
	Flash_Save_MS58.parMS58.lot[2] = 0xEA;  //
	Flash_Save_MS58.parMS58.lot[3] = 0x60;
	for(u8 i=0; i< RD_MAX_NUM_GROUP; i++){
		Flash_Save_MS58.Call_Group.ID_Group[i] = 0xff;
	}
	Flash_Save_MS58.Call_Scene.on_off[0] = 0;
	Flash_Save_MS58.Call_Scene.on_off[1] = 0;
}
void RD_Flash_Clean_MS58(void){
	Flash_Save_MS58.user[0] = RD_CHECK_FLASH_H;
	Flash_Save_MS58.user[1] = RD_CHECK_FLASH_L;
	Flash_Save_MS58.user[2] = RD_CHECK_FLASH_H;
	Flash_Save_MS58.user[3] = RD_CHECK_FLASH_L;

	Flash_Save_MS58.mode = AUTO;
	Flash_Save_MS58.start_status = KEEP_STATUS;
	Flash_Save_MS58.lightness_max = 0xffff;
	Flash_Save_MS58.lightness_min = 0x4cc2;
	Flash_Save_MS58.parMS58.gain = 0x33;
	Flash_Save_MS58.parMS58.delta[0] = 0x00;
	Flash_Save_MS58.parMS58.delta[1] = 0x14;
	Flash_Save_MS58.parMS58.lot[0] = 0x00;
	Flash_Save_MS58.parMS58.lot[1] = 0x00;
	Flash_Save_MS58.parMS58.lot[2] = 0xEA;  // 60s
	Flash_Save_MS58.parMS58.lot[3] = 0x60;
	Flash_Save_MS58.Call_Scene.on_off[0] = 0;
	Flash_Save_MS58.Call_Scene.on_off[1] = 0;
	Flash_Save_MS58.Call_Scene.ID_Scene[0] = 0x0000;
	Flash_Save_MS58.Call_Scene.ID_Scene[1] = 0x0000;
	for(u8 i=0; i< RD_MAX_NUM_GROUP; i++){
		Flash_Save_MS58.Call_Group.ID_Group[i] = 0xff;
	}


	flash_erase_sector(RD_MS58_FLASH_AREA);
	flash_write_page(RD_MS58_FLASH_AREA, RD_FLASH_SIZE_MS58, (unsigned char *)(&Flash_Save_MS58.user[0]));
}

void RD_Flash_MS58_Init(void){
	Read_Flash_MS58();
	if(Flash_Save_MS58.user[0] != RD_CHECK_FLASH_H && Flash_Save_MS58.user[1] != RD_CHECK_FLASH_L &&
	   Flash_Save_MS58.user[2] != RD_CHECK_FLASH_H && Flash_Save_MS58.user[3] != RD_CHECK_FLASH_L){
		RD_Flash_Clean_MS58();
	}
	RD_Init_Config_MS58();
#if RD_LOG_UART
	log_par_flash_ms58();
#endif
}

void RD_Check_Startup_Rada(void){
	switch(Flash_Save_MS58.start_status){
	case MANUAL:
		Flash_Save_MS58.mode = MANUAL;
		break;
	case AUTO:
		Flash_Save_MS58.mode = AUTO;
		break;
	default:
		break;
	}
}
void Init_Data_Rada(void){
	RD_Flash_MS58_Init();
	RD_Check_Startup_Rada();
	RD_Rsp_Powerup(RD_GATEWAY_ADDR, Flash_Save_MS58.mode); // T_NOTE: rsp mode rada
	uint32_t lot = (Flash_Save_MS58.parMS58.lot[0] << 24) | (Flash_Save_MS58.parMS58.lot[1] << 16) |
			(Flash_Save_MS58.parMS58.lot[2] << 8) | Flash_Save_MS58.parMS58.lot[3];
	TIMEOUT_MOTION_GROUP = lot/1000;
	time_start_loop = clock_time_ms();
}

void RD_Flash_Clean_Training(void){
	flash_save_training.User[0] = RD_CHECK_FLASH_H;
	flash_save_training.User[1] = RD_CHECK_FLASH_L;
	flash_save_training.User[2] = RD_CHECK_FLASH_H;
	flash_save_training.User[3] = RD_CHECK_FLASH_L;

	flash_save_training.minute = 0;
	flash_save_training.step = 1;
	flash_save_training.rd_flag_test_mode = 1;

	flash_erase_sector(RD_TRAINING_FLASH_AREA);
	flash_write_page(RD_TRAINING_FLASH_AREA, RD_TRAINING_FLASH_SIZE, (unsigned char *)(&flash_save_training.User[0]));
}

void Init_Flash_Training(void){
#if TRAINING_EN
	flash_read_page(RD_TRAINING_FLASH_AREA, RD_TRAINING_FLASH_SIZE, (unsigned char *)(&flash_save_training.User[0]));
	if(flash_save_training.step == 4){
		flash_save_training.rd_flag_test_mode = 0;
	}
	if(flash_save_training.User[0] != RD_CHECK_FLASH_H && flash_save_training.User[1] != RD_CHECK_FLASH_L &&
		flash_save_training.User[2] != RD_CHECK_FLASH_H && flash_save_training.User[3] != RD_CHECK_FLASH_L){
		RD_Flash_Clean_Training();
	}

	//RD_LOG("time minute start: %d\n",flash_save_training.minute);
#else
	flash_save_training.rd_flag_test_mode = 0;
#endif

}

void RD_Write_Flash_Training(void){
	flash_erase_sector(RD_TRAINING_FLASH_AREA);
	flash_write_page(RD_TRAINING_FLASH_AREA, RD_TRAINING_FLASH_SIZE, (unsigned char *)(&flash_save_training.User[0]));
}

//RD_EDIT LOG UART
void RD_LOG(const char *format, ...){
#if RD_LOG_UART
	char out[256];
	char *p = &out[0];
	va_list args;
	va_start( args, format );
	print(&p, format, args);
	uart_Csend(out);
#endif
}
