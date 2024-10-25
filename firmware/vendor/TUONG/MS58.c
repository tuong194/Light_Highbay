/*
 * MS58.c
 *
 *  Created on: Oct 22, 2024
 *      Author: PC5
 */
#include"MS58.h"


u16 flag_check_rec_uart = 0;
extern u16 uart_rx_irq;
uint8_t data_rec[15] = {0};
u8 tx_buff[10]={0};

void RD_config_pin_MS58(void){
	gpio_set_func(PIN_MS58, AS_GPIO);
	gpio_set_input_en(PIN_MS58, 1);
	gpio_setup_up_down_resistor(PIN_MS58, PM_PIN_PULLDOWN_100K);

	gpio_set_func(LED_OUT, AS_GPIO);
	gpio_set_output_en(LED_OUT, 1);
	gpio_write(LED_OUT,0);
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

void loop_rada(void){
	if(is_motion()){
		ON_LED_RADA;
	}else{
		OFF_LED_RADA;
	}
}


