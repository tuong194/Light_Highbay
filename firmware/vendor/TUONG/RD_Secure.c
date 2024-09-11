/*
 * RD_Secure.c
 *
 *  Created on: Sep 9, 2024
 *      Author: PC5
 */

#include "RD_Secure.h"
#include "../common/lighting_model.h"

unsigned char RD_key[16] = "Digital@28112804";
unsigned char param_RD[8] = { 0x24, 0x02, 0x28, 0x04, 0x28, 0x11, 0x20, 0x20 }; // 8 byte selfgen by RD
unsigned char aesEncrypt[16] = { 0 };

RD_Type_Device_Message *RD_Mess_Temp_Receive;
RD_Type_Device_Message RD_Mess_Recevie;
uint8_t *BuffRec;

static s8 flag_process_aes = -1;
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

int RD_Messenger_CheckSecure(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par) {
	RD_Mess_Temp_Receive = (RD_Type_Device_Message *) (&par[0]);
	RD_Mess_Recevie = *RD_Mess_Temp_Receive;
	u16 Header = RD_Mess_Recevie.Header[1] << 8 | RD_Mess_Recevie.Header[0];
	switch (Header) {
	case 0x0003:
		if (RD_AesreCheck(cb_par->adr_dst, &par[2])) {
			flag_process_aes = 1;

			RD_Mess_Recevie.Header[0] = 0x03;
			RD_Mess_Recevie.Header[1] = 0x00;
			RD_Mess_Recevie.MainType = 0x01;
			RD_Mess_Recevie.Feature = 0x02;
			RD_Mess_Recevie.Name = 0x03; // NAME
			RD_Mess_Recevie.Future[0] = 0x00;
			RD_Mess_Recevie.Future[1] = 0x03;
			RD_Mess_Recevie.Future[2] = 0x00;

			BuffRec = (uint8_t *) (&RD_Mess_Recevie.Header[0]);
			mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8,
					cb_par->adr_src, 2);

		} else {
			flag_process_aes = 0;

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
		break;

		return 0;
	}
}
void check_done_provision(void) {
	static u8 first = 0;
	if (get_provision_state() == STATE_DEV_PROVED && first == 0) {
		flag_provision = TRUE;
		uart_Csend("provision sucess");
		if (flag_process_aes == 0) { // ma hoa sai
			RD_light_ev_with_sleep(1, 500 * 1000);
			vrs_time_err_aes = clock_time_s();
		} else if (flag_process_aes == -1) { // ko co ban tin ma hoa
			RD_light_ev_with_sleep(1, 500 * 1000);
			vrs_time_bindall = clock_time_s();
		} else if (flag_process_aes == 1) { // ma hoa dung
			RD_light_ev_with_sleep(3, 500 * 1000); // T=1s, nhay 3 lan
			st_pub_list_t pub_list = { { 0 } };
			mesh_cmd_light_ctl_set_t p_set_ctl;
			mesh_cmd_lightness_set_t p_set_light;
			p_set_ctl.temp = 0x0320;
			p_set_ctl.lightness = 0xffff;
			p_set_light.lightness = 0xffff;

			light_ctl_temp_set(&p_set_ctl, 2, 0, 0, 0, &pub_list);
			lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);
		}

		first = 1;
	}
#if EN_SECURE
	Kickout_Security();
#endif
}

void Kickout_Security(void) {
	if (flag_provision == TRUE) {
		if (flag_process_aes == -1 && clock_time_s() - vrs_time_bindall > 60) { // ko co ban tin
			flag_provision = FALSE;
			flag_process_aes = -1;
			kick_out(1);
		} else if (flag_process_aes == 0 && clock_time_s() - vrs_time_err_aes
				> 10) { // ma hoa sai
			flag_provision = FALSE;
			flag_process_aes = -1;
			kick_out(1);
		}
	}
}
