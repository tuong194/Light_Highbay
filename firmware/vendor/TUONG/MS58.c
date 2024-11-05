/*
 * MS58.c
 *
 *  Created on: Oct 22, 2024
 *      Author: PC5
 */
#include"MS58.h"
#include "../common/lighting_model.h"
#include "RD_Type_Device.h"

st_pub_list_t pub_list = {{0}};
mesh_cmd_lightness_set_t p_set_light;
unsigned long TimeNew, TimeOld;
int vrs_count = 0;

static u8 flag_check_motion = 0;

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
	sleep_ms(5);
	RD_save_data_MS58();
	sleep_ms(5);
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
	sleep_ms(500);
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
		if(vrs_count == 10){
			p_set_light.lightness = lightness;
			lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);
		}else if(vrs_count > 110) vrs_count = 0;
	}
}

void RD_on_light(void){
	static u32 time_motion_ms = 0;
	if(is_motion() && flag_check_motion == 0){
		uart_Csend("co chuyen dong\n");
		time_motion_ms = clock_time_ms();
		flag_check_motion = 1;
	}
	if(clock_time_exceed_ms(time_motion_ms, 3000) && flag_check_motion == 1){
		RD_set_lightness(Flash_Save_MS58.lightness_max);
	}
}

void RD_off_light(void){
	static u32 time_no_motion_ms = 0;
	if(is_motion() == 0 && flag_check_motion == 1){
		uart_Csend("ko co chuyen dong\n");
		time_no_motion_ms = clock_time_ms();
		flag_check_motion = 0;
	}
	if(clock_time_exceed_ms(time_no_motion_ms, 1000) && flag_check_motion == 0){
		RD_set_lightness(Flash_Save_MS58.lightness_min);
	}
}

void loop_rada(void){
	if(Flash_Save_MS58.mode == AUTO){
		RD_on_light();
		RD_off_light();
	}
}
void RD_Init_Config_MS58(void){
	uint8_t gain = 0x33;
	uint8_t delta[2] = {Flash_Save_MS58.parMS58.delta[0], Flash_Save_MS58.parMS58.delta[1]};
	uint8_t lot[4] = {0};
	for(u8 i=0; i<4;i++){
		lot[i] = Flash_Save_MS58.parMS58.lot[i];
	}
	RD_config_MS58(gain, delta, lot);
}

void log_par_flash_ms58(void){
	uart_Csend("data flash ms58: \n");
	RD_LOG("mode: %d, start_status: %d, co nhan mess: %d, light max: %d, light min: %d\n",Flash_Save_MS58.mode,
			Flash_Save_MS58.start_status, Flash_Save_MS58.sw_select, Flash_Save_MS58.lightness_max, Flash_Save_MS58.lightness_min);
	uint16_t delta = (Flash_Save_MS58.parMS58.delta[0]<<8) | Flash_Save_MS58.parMS58.delta[1];
	uint32_t lot = (Flash_Save_MS58.parMS58.lot[0] << 24) | (Flash_Save_MS58.parMS58.lot[1] << 16) |
			(Flash_Save_MS58.parMS58.lot[2] << 8) | Flash_Save_MS58.parMS58.lot[3];
	RD_LOG("gain: 0x%02X, delta: %d, lot: %d\n", Flash_Save_MS58.parMS58.gain,delta, lot);
}

