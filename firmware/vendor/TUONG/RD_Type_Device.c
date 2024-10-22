/*
 * RD_Type_Device.c
 *
 *  Created on: Sep 24, 2024
 *      Author: PC5
 */

#include "RD_Type_Device.h"
#include "RD_MessData.h"

Flash_Save_Type_GW Flash_Save_Type_Val;

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

//RD_EDIT LOG UART
void RD_LOG(const char *format, ...){
	char out[128];
	char *p = &out[0];
	va_list args;
	va_start( args, format );
	print(&p, format, args);
	uart_Csend(out);
}
