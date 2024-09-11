/*
 * RD_MessData.c
 *
 *  Created on: Sep 9, 2024
 *      Author: PC5
 */

#include "RD_MessData.h"

uint8_t step_down;
uint8_t flag_down_step = 1;
u32 time_out_down_step;

void reset_kickout(void) {

	if (flag_down_step == 1) {
		if (clock_time_exceed_ms(time_out_down_step, 1000) && (clock_time_ms()
				- time_out_down_step) < 3000) {
			step_down--;

			uint8_t buff[2];
			buff[0] = step_down;
			flag_down_step = 0;
			flash_erase_sector(ADDR_FLASH_KICK_OUT);
			flash_write_page(ADDR_FLASH_KICK_OUT, 1, buff);

		}
	}
	if (clock_time_exceed_ms(time_out_down_step, 3000)) {
		step_down = 6;
		uint8_t buff[2];
		buff[0] = step_down;
		flag_down_step = 0;
		flash_erase_sector(ADDR_FLASH_KICK_OUT);
		flash_write_page(ADDR_FLASH_KICK_OUT, 1, buff);
	}
	if (step_down == 1) {
		step_down--;
		RD_light_ev_with_sleep(3, 500 * 1000);
		flash_erase_sector(ADDR_FLASH_KICK_OUT);
		flash_write_page(ADDR_FLASH_KICK_OUT, 1, &step_down);
	}

}

void Read_val_kick_out(void) {
	flash_read_page(ADDR_FLASH_KICK_OUT, 1, &step_down);
	if (step_down > 6)
		step_down = 6;
	flag_down_step = 1;
	if (step_down == 0) {
		RD_light_ev_with_sleep(1, 500 * 1000);
		step_down = 6;
		flash_erase_sector(ADDR_FLASH_KICK_OUT);
		flash_write_page(ADDR_FLASH_KICK_OUT, 1, &step_down);
		flag_down_step = 0;
		kick_out(0);
	}
	time_out_down_step = clock_time_ms();
}

