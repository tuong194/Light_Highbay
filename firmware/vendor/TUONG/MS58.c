/*
 * MS58.c
 *
 *  Created on: Oct 22, 2024
 *      Author: PC5
 */
#include"MS58.h"
#include "../common/lighting_model.h"
#include "RD_Type_Device.h"
#include "RD_Scene.h"
#include "RD_MessData.h"

st_pub_list_t pub_list = {{0}};
mesh_cmd_lightness_set_t p_set_light;
unsigned long TimeNew, TimeOld;
int vrs_count = 0;

extern _Bool rd_check_ota;
flag_on_off_light_t flag_on_off = {0};
u32 time_start_loop = 0;
u32 TIMEOUT_MOTION_GROUP = 0;
u32 time_start_motion_by_gr = 0;
_Bool motion_detect = FALSE;

u16 flag_check_rec_uart = 0;
extern u16 uart_rx_irq;
uint8_t data_rec[15] = {0};
u8 tx_buff[10]={0};

void RD_config_pin_MS58(void){
	gpio_set_func(PIN_MS58, AS_GPIO);
	gpio_set_input_en(PIN_MS58, 1);
	gpio_setup_up_down_resistor(PIN_MS58, PM_PIN_PULLDOWN_100K);

}

void RD_save_data_MS58(void){
	uint8_t data_send[5] = {0x55, 0x02, 0x13, 0x01, 0x6B};
	uart_send_data_arr(data_send,5);
}

void RD_config_MS58(uint8_t gain, uint8_t delta[2], uint8_t lot[4]){
	uint8_t data_conf[12];
	data_conf[0] = 0x55;
	data_conf[1] = 0x09;
	data_conf[2] = 0x11;
	data_conf[3] = 0x00;
	data_conf[4] = gain;
	data_conf[5] = delta[0];
	data_conf[6] = delta[1];
	for(u8 i=0; i<4;i++){
		data_conf[7+i] = lot[i];
	}
	for (u8 i=0; i<11; i++){
		data_conf[11] += data_conf[i];
	}
	uart_send_data_arr(data_conf, sizeof(data_conf));
	sleep_ms(100);
	RD_save_data_MS58();
	sleep_ms(50);
#if LOG_MS58
	uart_recbuff_init(&data_rec[0],128, &tx_buff[0]);
	sleep_ms(5);
	RD_LOG("\n");
	if(flag_check_rec_uart != uart_rx_irq){
		RD_LOG("data rsp config: 0x%02X 0x%02X \n",data_rec[4], data_rec[5]);
		sleep_ms(5);
		flag_check_rec_uart = uart_rx_irq;
	}
#endif
}

void RD_get_data_MS58(void){
	uint8_t data_send[5] = {0x55, 0x02, 0x12, 0x00, 0x69};
	uart_send_data_arr(data_send,5);
	sleep_ms(500);
	wd_clear();

#if LOG_MS58
	uart_recbuff_init(&data_rec[0],128, &tx_buff[0]); //du lieu bat dau tu data_rec[4]
	sleep_ms(5);
	RD_LOG("\n");
	if(flag_check_rec_uart != uart_rx_irq){
		RD_LOG("data rsp get: ");
		for(uint8_t i =0; i<8; i++){
			RD_LOG("0x%02X ",data_rec[i+4]);
		}
		RD_LOG("\n");
		flag_check_rec_uart = uart_rx_irq;
	}
#endif
}

void RD_restore_MS58(void){
	uint8_t data_send[5] = {0x55, 0x02, 0x13, 0x00, 0x6A};
	uart_send_data_arr(data_send,5);
	sleep_ms(50);
	wd_clear();
#if LOG_MS58
	uart_recbuff_init(&data_rec[0],128, &tx_buff[0]);
	sleep_ms(5);
	RD_LOG("\n");
	if(flag_check_rec_uart != uart_rx_irq){
		RD_LOG("data rsp restore: 0x%02X 0x%02X \n",data_rec[4], data_rec[5]);
		sleep_ms(5);
		flag_check_rec_uart = uart_rx_irq;
	}
	sleep_ms(5);
	RD_get_data_MS58();
#endif
}

unsigned int is_motion(void){
	unsigned int out = gpio_read(PIN_MS58);
#if LOG_MS58
	RD_LOG("gia tri out: %d\n", out);
	sleep_ms(5);
#endif
	return out;
}

void RD_set_lightness(u16 lightness){
	TimeNew = clock_time();
	if(TimeNew > 0xfffffff0){
		TimeNew = 0;
		TimeOld = 0;
	}
	if (TimeNew - TimeOld > 160000) { // 10ms
		TimeOld = TimeNew;
		vrs_count++;
		if(vrs_count == 1 && Flash_Save_MS58. mode == AUTO){ // 10ms
			p_set_light.lightness = lightness;
			lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);
		}else if(vrs_count > 101){
			vrs_count = 0;
			motion_detect = FALSE;
			flag_on_off.flag_on_off_from_rada = NONEX;
			flag_on_off.flag_on_off_from_mesh = 0;
		}
	}
}

/*----------------------Packing lot------------------------------*/
void Rada_send_onoff_light(void){
	uint8_t buff_send[8] = {0};
	memcpy(buff_send, Flash_Save_MS58.Call_Group.ID_Group, 8);
	if(Flash_Save_MS58.mode == AUTO){
		mesh_tx_cmd2normal_primary(0xE4, buff_send, 8, 0xffff, 2);
		//mesh_tx_cmd2normal_primary(0x52, buff_send, 8, 0x0001, 2);
	}
}

void loop_mess_rada(void){
	static _Bool flag_start_on = TRUE;
	if(Flash_Save_MS58.mode == AUTO){
		if(motion_detect){
			flag_on_off.flag_on_off_from_rada = ON;
			flag_start_on = FALSE;
			motion_detect = FALSE;
		}
		if(clock_time_exceed_ms(time_start_motion_by_gr, TIMEOUT_MOTION_GROUP * 1000) && flag_start_on == FALSE){
			if(!is_motion()){
				flag_on_off.flag_on_off_from_rada = OFF;
			}
			flag_start_on = TRUE;
		}


		if(flag_on_off.flag_on_off_from_rada == ON){
			RD_set_lightness(Flash_Save_MS58.lightness_max);
		}else if(flag_on_off.flag_on_off_from_rada == OFF){
			RD_set_lightness(Flash_Save_MS58.lightness_min);
		}
	}
}
/*----------------------------------------------------------------*/
void call_scene_from_rada(uint8_t is_motion){
	u16 scene_id = 0x0000;
	u8 tid = 0;
	if(is_motion == 0){
		scene_id = Flash_Save_MS58.Call_Scene.ID_Scene[0];
		tid = (u8)(Flash_Save_MS58.Call_Scene.ID_Scene[0] + Flash_Save_MS58.Call_Scene.on_off[0]);
	}else{
		scene_id = Flash_Save_MS58.Call_Scene.ID_Scene[1];
		tid = (u8)(Flash_Save_MS58.Call_Scene.ID_Scene[1] + Flash_Save_MS58.Call_Scene.on_off[1]);
	}
	RD_Call_Scene(scene_id, tid);

}

void RD_rada_rsp_gw(uint8_t stt){
	uint16_t GW_addr = 0x0001;
	uint8_t BuffRec[6] = {0};
	BuffRec[0] = RD_HEADER_RSP_MOTION & 0xff;//ele_adr_primary & 0xff;
	BuffRec[1] = (RD_HEADER_RSP_MOTION >> 8) & 0xff;//(ele_adr_primary >> 8) & 0xff;
	BuffRec[2] = stt;
	BuffRec[3] = 0x00;
	if(stt == 0){ // scene off
		BuffRec[4] =  Flash_Save_MS58.Call_Scene.ID_Scene[0] & 0xff;
		BuffRec[5] =  (Flash_Save_MS58.Call_Scene.ID_Scene[0] >> 8 ) & 0xff;
	}else if(stt == 1){ // scene on
		BuffRec[4] =  Flash_Save_MS58.Call_Scene.ID_Scene[1] & 0xff;
		BuffRec[5] =  (Flash_Save_MS58.Call_Scene.ID_Scene[1] >> 8 ) & 0xff;
	}
	mesh_tx_cmd2normal_primary(RD_RSP_STT_RADA, BuffRec, 6, GW_addr, 1);
}

void RD_on_light(void){
	static u32 time_motion_ms = 0;
	if(is_motion() && flag_on_off.flag_check_motion == NO_MOTION){
		//uart_Csend("co chuyen dong\n");
		time_motion_ms = clock_time_ms();
		if(time_motion_ms >= 0xfffffff0) time_motion_ms = 0;
		flag_on_off.flag_check_motion = MOTION;
		flag_on_off.flag_on_off_from_mesh = 1;
		RD_rada_rsp_gw(1);

		Rada_send_onoff_light(); // packinglot call group

		if(Flash_Save_MS58.Call_Scene.on_off[1] == 1){
			call_scene_from_rada(1); // Ralli
		}
	}
	if(clock_time_exceed_ms(time_motion_ms, TIME_DELAY_ON) && flag_on_off.flag_check_motion == MOTION && flag_on_off.flag_on_off_from_mesh == 1){
		if(is_motion()){
			RD_set_lightness(Flash_Save_MS58.lightness_max);
		}else{
			flag_on_off.flag_on_off_from_mesh = 0;
			flag_on_off.flag_check_motion = NO_MOTION;
		}

	}
}

void RD_off_light(void){
	static u32 time_no_motion_ms = 0;
	if(is_motion() == 0 && flag_on_off.flag_check_motion == MOTION){
		//uart_Csend("ko co chuyen dong\n");
		time_no_motion_ms = clock_time_ms();
		if(time_no_motion_ms >= 0xfffffff0) time_no_motion_ms = 0;
		flag_on_off.flag_check_motion = NO_MOTION;
		flag_on_off.flag_on_off_from_mesh = 1;
		RD_rada_rsp_gw(0);

		if(Flash_Save_MS58.Call_Scene.on_off[0] == 1){
			call_scene_from_rada(0);
		}
	}
	if(clock_time_exceed_ms(time_no_motion_ms, TIME_DELAY_OFF) && flag_on_off.flag_check_motion == NO_MOTION && flag_on_off.flag_on_off_from_mesh == 1){
		if(!is_motion()){
			RD_set_lightness(Flash_Save_MS58.lightness_min);
		}else{
			flag_on_off.flag_on_off_from_mesh = 0;
			flag_on_off.flag_check_motion = MOTION;
		}
	}
}

void loop_rada(void){
	static _Bool flag_loop_rada = FALSE;
	static _Bool first_check_loop = FALSE;
	if(clock_time_exceed_ms(time_start_loop, TIME_DELAY_START) && first_check_loop == FALSE){
		flag_loop_rada = TRUE;
		first_check_loop = TRUE;
	}
	if(flag_loop_rada == TRUE && rd_check_ota == FALSE){
		RD_on_light();
		RD_off_light();
		loop_mess_rada();
	}
}

void RD_Init_Config_MS58(void){
	uint8_t gain = Flash_Save_MS58.parMS58.gain;
	uint8_t delta[2] = {Flash_Save_MS58.parMS58.delta[0], Flash_Save_MS58.parMS58.delta[1]};
	uint8_t lot[4] = {0};
	for(u8 i=0; i<4;i++){
		lot[i] = Flash_Save_MS58.parMS58.lot[i];
	}
	RD_config_MS58(gain, delta, lot);
}

void RD_Rsp_Powerup(uint16 gw_addr, uint8_t mode){
	uint8_t BuffSend[3] = {0};
	BuffSend[0] = MY_HEADER_RSP_MODE & 0xff;
	BuffSend[1] = (MY_HEADER_RSP_MODE>>8) & 0xff;
	BuffSend[2] = mode;
	mesh_tx_cmd2normal_primary(0xE1, BuffSend, 3, gw_addr, 1);
}

void log_par_flash_ms58(void){
	//uart_Csend("data flash ms58: \n");
	RD_LOG("mode: %d, start_status: %d, light max: %d, light min: %d\n",Flash_Save_MS58.mode,
			Flash_Save_MS58.start_status, Flash_Save_MS58.lightness_max, Flash_Save_MS58.lightness_min);
	uint16_t delta = (Flash_Save_MS58.parMS58.delta[0]<<8) | Flash_Save_MS58.parMS58.delta[1];
	uint32_t lot = (Flash_Save_MS58.parMS58.lot[0] << 24) | (Flash_Save_MS58.parMS58.lot[1] << 16) |
			(Flash_Save_MS58.parMS58.lot[2] << 8) | Flash_Save_MS58.parMS58.lot[3];
	RD_LOG("gain: 0x%02X, delta: %d, lot: %d\n", Flash_Save_MS58.parMS58.gain,delta, lot);

	RD_LOG("group id: %d\n", Flash_Save_MS58.Call_Group.ID_Group);
}

