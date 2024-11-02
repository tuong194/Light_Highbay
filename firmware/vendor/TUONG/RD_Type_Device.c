/*
 * RD_Type_Device.c
 *
 *  Created on: Sep 24, 2024
 *      Author: PC5
 */

#include "RD_Type_Device.h"
#include "RD_MessData.h"
#include "MS58.h"

Flash_Save_Type_GW Flash_Save_Type_Val;
Flash_Save_MS58_t  Flash_Save_MS58 = {{0}};

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
	Flash_Save_Type_Val.MainType = 0x01;
	Flash_Save_Type_Val.Feature = 0x02;
	Flash_Save_Type_Val.Name = 0x01;

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


void RD_Flash_Clean_MS58(void){
	Flash_Save_MS58.user[0] = RD_CHECK_FLASH_H;
	Flash_Save_MS58.user[1] = RD_CHECK_FLASH_L;
	Flash_Save_MS58.user[2] = RD_CHECK_FLASH_H;
	Flash_Save_MS58.user[3] = RD_CHECK_FLASH_L;

	Flash_Save_MS58.mode = AUTO;
	Flash_Save_MS58.start_status = KEEP_STATUS;
	Flash_Save_MS58.sw_select = 0x01;
	Flash_Save_MS58.lightness_max = 0xffff;
	Flash_Save_MS58.lightness_min = 0x0000;
	Flash_Save_MS58.parMS58.gain = 0x33;
	Flash_Save_MS58.parMS58.delta[0] = 0x00;
	Flash_Save_MS58.parMS58.delta[1] = 0x64;
	Flash_Save_MS58.parMS58.lot[0] = 0x00;
	Flash_Save_MS58.parMS58.lot[1] = 0x00;
	Flash_Save_MS58.parMS58.lot[2] = 0x07;  //7D0: 2000 ms
	Flash_Save_MS58.parMS58.lot[3] = 0xD0;

	flash_erase_sector(RD_MS58_FLASH_AREA);
	flash_write_page(RD_MS58_FLASH_AREA, RD_FLASH_SIZE_MS58, (unsigned char *)(&Flash_Save_MS58.user[0]));
}

void RD_Flash_MS58_Init(void){
	Read_Flash_MS58();
	if(Flash_Save_MS58.user[0] != RD_CHECK_FLASH_H && Flash_Save_MS58.user[1] != RD_CHECK_FLASH_L &&
	   Flash_Save_MS58.user[2] != RD_CHECK_FLASH_H && Flash_Save_MS58.user[3] != RD_CHECK_FLASH_L){
		RD_Flash_Clean_MS58();
		RD_Init_Config_MS58();
	}
	log_par_flash_ms58();
}
void RD_Check_Startup_Rada(void){
	switch(Flash_Save_MS58.start_status){
	case MANUAL:
		Flash_Save_MS58.mode = MANUAL;
		break;
	case AUTO:
		Flash_Save_MS58.mode = AUTO;
		break;
	}
}
void Init_Data_Rada(void){
	RD_Flash_MS58_Init();
	RD_Check_Startup_Rada();
}



//RD_EDIT LOG UART
void RD_LOG(const char *format, ...){
	char out[256];
	char *p = &out[0];
	va_list args;
	va_start( args, format );
	print(&p, format, args);
	uart_Csend(out);
}
