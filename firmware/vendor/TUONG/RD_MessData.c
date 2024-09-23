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

RD_Type_Device_Message *RD_Mess_Temp_Receive;
RD_Type_Device_Message RD_Mess_Recevie;
uint8_t *BuffRec;


extern RD_Flash_Save_Secure flash_save_secure;

int RD_Messenger_CheckSecure(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par) {
	RD_Mess_Temp_Receive = (RD_Type_Device_Message *) (&par[0]);
	RD_Mess_Recevie = *RD_Mess_Temp_Receive;
	u16 Header = RD_Mess_Recevie.Header[1] << 8 | RD_Mess_Recevie.Header[0];
	switch (Header) {
	case 0x0003:
		if(is_provision_success()){
			if (RD_AesreCheck(cb_par->adr_dst, &par[2])) {
				flash_save_secure.flag_process_aes = 1;

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
				flash_save_secure.flag_process_aes = 0;

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
		}

		break;


	}
	return 0;
}


