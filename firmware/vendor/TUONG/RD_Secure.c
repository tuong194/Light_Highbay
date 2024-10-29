/*
 * RD_Secure.c
 *
 *  Created on: Sep 9, 2024
 *      Author: PC5
 */

#include "RD_Secure.h"
#include "../common/lighting_model.h"
#include "../mesh/RD_Lib.h"

unsigned char RD_key[16] = "Digital@28112804";
unsigned char param_RD[8] = { 0x24, 0x02, 0x28, 0x04, 0x28, 0x11, 0x20, 0x20 }; // 8 byte selfgen by RD
unsigned char aesEncrypt[16] = { 0 };


extern u32 get_pwm_cmp(u8 val, u8 lum);
extern void light_dim_set_hw(int idx, int idx2, u16 val);

RD_Flash_Save_Secure flash_save_secure = {{0}};

uint8_t step_down;
uint8_t flag_down_step = 1;
u32 time_out_down_step;

_Bool flag_provision = FALSE;
int vrs_time_bindall = 0;
int vrs_time_err_aes = 0;

void Kickout_Security(void);

unsigned char RD_AesreCheck(uint16_t unicast_ID, uint8_t compare_key[6]) {
	unsigned char compare_buff[16] = { 0 };
	for (uint8_t i = 0; i < 8; i++) {
		compare_buff[i] = param_RD[i];
	}
	for (uint8_t i = 0; i < 6; i++) {
		compare_buff[i + 8] = tbl_mac[i];
	}
	compare_buff[14] = unicast_ID & 0xFF;
	compare_buff[15] = unicast_ID >> 8 & 0xFF;

	aes_encrypt(RD_key, compare_buff, aesEncrypt);
	for (uint8_t i = 0; i < 6; i++) {
		if (aesEncrypt[10 + i] != compare_key[i]) { // ma hoa sai
			return 0;
		}
	}
	return 1;
}


void check_done_provision(void) {
	static u8 first = 0;

	if(get_provision_state() == STATE_DEV_PROVED && flash_save_secure.flag_check_mess == 1 && first == 0){
		uart_Csend("provision sucess\n");
		RD_light_ev_with_sleep(3, 500 * 1000);
		first = 1;
	}
	if (get_provision_state() == STATE_DEV_PROVED && flash_save_secure.flag_check_mess == 1) {

		flag_provision = TRUE;

		if (flash_save_secure.flag_process_aes == ENCRYPT_ERR ) { // ma hoa sai
			//RD_light_ev_with_sleep(2, 500 * 1000);
			vrs_time_err_aes = clock_time_s();
			RD_LOG("sai ma hoa r \n");
		} else if (flash_save_secure.flag_process_aes == NO_MESS ) { // ko co ban tin ma hoa
			//RD_light_ev_with_sleep(1, 500 * 1000);
			vrs_time_bindall = clock_time_s();
			RD_LOG("ko co ban tin\n");
		} else if (flash_save_secure.flag_process_aes == ENCRYPT_OK ) { // ma hoa dung
			//RD_light_ev_with_sleep(3, 500 * 1000); // T=1s, nhay 3 lan
			RD_LOG("chuan RD nha\n");
		}

		sleep_ms(100);
		st_pub_list_t pub_list = { { 0 } };

#if	NAME != HIGHTBAY_RADA
		mesh_cmd_light_ctl_set_t p_set_ctl;
		p_set_ctl.temp = 0x0320; // yellow
		p_set_ctl.lightness = 0xffff;
		light_ctl_temp_set(&p_set_ctl, 2, 0, 0, 0, &pub_list);
#endif
		mesh_cmd_lightness_set_t p_set_light;
		p_set_light.lightness = 0xffff;
		lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);

		flash_save_secure.flag_check_mess = 0;

		flash_erase_sector(RD_PROVISION_FLASH_AREA);
		flash_write_page(RD_PROVISION_FLASH_AREA, RD_SIZE_FLASH_SECURE, (uint8_t *) (&flash_save_secure.Used[0]));
	}
#if EN_SECURE
	Kickout_Security();
#endif
}

void Kickout_Security(void) {
	if (flag_provision == TRUE) {
		if (flash_save_secure.flag_process_aes == NO_MESS && clock_time_s() - vrs_time_bindall > 120) { // ko co ban tin
			flag_provision = FALSE;
			flash_save_secure.flag_process_aes = NO_MESS;
			kick_out(1);
		} else if (flash_save_secure.flag_process_aes == ENCRYPT_ERR && clock_time_s() - vrs_time_err_aes > 60) { // ma hoa sai
			flag_provision = FALSE;
			flash_save_secure.flag_process_aes = NO_MESS;
			 kick_out(1);
		}
	}
}


void Flash_Clean_Secure(){
	flash_save_secure.Used[0] = RD_CHECK_FLASH_H;
	flash_save_secure.Used[1] = RD_CHECK_FLASH_L;
	flash_save_secure.Used[2] = RD_CHECK_FLASH_H;
	flash_save_secure.Used[3] = RD_CHECK_FLASH_L;
	flash_save_secure.flag_process_aes = NO_MESS;
	flash_save_secure.flag_check_mess = 0;
	flash_erase_sector(RD_PROVISION_FLASH_AREA);
	flash_write_page(RD_PROVISION_FLASH_AREA, RD_SIZE_FLASH_SECURE, (uint8_t *) (&flash_save_secure.Used[0]));

}

void Init_Flash_Secure(void){
	flash_read_page(RD_PROVISION_FLASH_AREA, RD_SIZE_FLASH_SECURE, (uint8_t *) (&flash_save_secure.Used[0]));

	if(flash_save_secure.Used[0] != RD_CHECK_FLASH_H && flash_save_secure.Used[1] != RD_CHECK_FLASH_L
		&& flash_save_secure.Used[2] != RD_CHECK_FLASH_H && flash_save_secure.Used[3] != RD_CHECK_FLASH_L){
		RD_LOG("init flash secure err\n");
		Flash_Clean_Secure();
	}
	RD_LOG("start flag_secure: %d\n",flash_save_secure.flag_process_aes);
	RD_LOG("start flag_check_mess: %d\n",flash_save_secure.flag_check_mess);
	//Read_val_kick_out();
#if EN_SECURE
	if(is_provision_success()){
		if(flash_save_secure.flag_process_aes != ENCRYPT_OK){
			kick_out(0);
		}
	}
#endif

}


