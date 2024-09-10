/*
 * RD_MessData.c
 *
 *  Created on: Sep 9, 2024
 *      Author: PC5
 */

#include "RD_MessData.h"

static uint8_t step_down = 6;
uint8_t flag_down_step=1;

void reset_kickout(void){
	u32 time_out_down_step = clock_time_ms();
	if(flag_down_step == 1){
		if(clock_time_exceed_ms(time_out_down_step, 3000) && clock_time_ms()-time_out_down_step <5000){
			step_down--;
			flag_down_step = 0;

		}else if(clock_time_exceed_ms(time_out_down_step, 5000)){
			step_down = 6;
			flag_down_step = 0;
		}
		flash_erase_sector(ADDR_FLASH_KICK_OUT);
		flash_write_page(ADDR_FLASH_KICK_OUT, 1, &step_down);

	}
	if(step_down == 1){
		step_down--;
		RD_light_ev_with_sleep(3, 500*1000);
		flash_erase_sector(ADDR_FLASH_KICK_OUT);
		flash_write_page(ADDR_FLASH_KICK_OUT, 1, &step_down);
	}

}

void Read_val_kick_out(void){
	flash_read_page(ADDR_FLASH_KICK_OUT,1,&step_down);
	flag_down_step = 1;
	if(step_down == 0){
		light_dim_set_hw(0, 0, get_pwm_cmp(0xff, 0));
		light_dim_set_hw(0, 1, get_pwm_cmp(0xff,0));
		kick_out(0);
		light_dim_set_hw(0, 0, get_pwm_cmp(0xff, 255));
		light_dim_set_hw(0, 1, get_pwm_cmp(0xff,255));
		step_down=6;
		flash_erase_sector(ADDR_FLASH_KICK_OUT);
		flash_write_page(ADDR_FLASH_KICK_OUT, 1, &step_down);
		flag_down_step = 0;
	}
}





