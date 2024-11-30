/*
 * RD_Training.c
 *
 *  Created on: Sep 24, 2024
 *      Author: PC5
 */

#include "RD_Training.h"
#include "../common/lighting_model.h"

extern _Bool flag_kickout_all;
unsigned long timeNew, timeOld;
int count = 0;
_Bool flag_start_training = TRUE;


u16 time_s = 0;
u16 time_s_old = 0;
u16 time_m;

void RD_set_lightness_training(u8 lightness_100){
	st_pub_list_t pub_list1 = {{0}};
	mesh_cmd_lightness_set_t p_set_light;
	p_set_light.lightness = 0xffff * lightness_100/100;
	lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list1);
}

void Start_Training(void){
	if(flag_start_training == TRUE){
		if(flash_save_training.step == 1){
			if(time_s <= 4){
				if(time_s != time_s_old){
					RD_set_lightness_training(100);
					time_s_old = time_s;
				}
			}else {
				flag_start_training = FALSE;
				time_s = 0;
			}
		}else{
			if(time_s != time_s_old){
				count++;
				if(count == 1){
					RD_set_lightness_training(100);
				}else if(count == 2){
					RD_set_lightness_training(0);
				}else if(count == 3){
					RD_set_lightness_training(100);
				}else if(count == 4){
					RD_set_lightness_training(0);
				}else if(count == 5){
					time_s = 0;
					flag_start_training = FALSE;
					time_m = 0;
				}
				time_s_old = time_s;
			}
		}
	}
}

void RD_Training(void){
	if(time_m != flash_save_training.minute && flag_start_training == FALSE){
		if(flash_save_training.minute < 1){
			flash_save_training.step = 1;
		}else if(flash_save_training.minute >= 1 && flash_save_training.minute < 2){
			flash_save_training.step = 2;
			RD_set_lightness_training(100);
		}else if(flash_save_training.minute >= 2 && flash_save_training.minute < 3){
			flash_save_training.step = 3;
			RD_set_lightness_training(50);
		}else{
			flash_save_training.step = 4;  // luyen xong
			flash_save_training.rd_flag_test_mode = 0;
			RD_set_lightness_training(15);
		}
		time_m = flash_save_training.minute;
		RD_LOG("time minute: %d, step: %d\n", time_m, flash_save_training.step);
		RD_Write_Flash_Training();
	}
	if(flash_save_training.step == 1 && flag_start_training == FALSE){
		if(time_s_old != time_s){
			time_s_old = time_s;
			count++;
			//RD_LOG("time second: %d, count %d\n", time_s, count);
			if(count == 1){
				RD_set_lightness_training(20);
			}else if(count == 2){
				count = 0;
				RD_set_lightness_training(100);
			}
		}
	}
	if(flash_save_training.rd_flag_test_mode == 0){
		mesh_adv_prov_link_close();
	}
}

void Time_Kick_Out_All(void){
	timeNew = clock_time();
	if(timeNew > 0xfffffff0){
		timeNew =0;
		timeOld =0;
	}
	if(timeNew - timeOld > 1600000){ // 100ms
		timeOld = timeNew;
		count++;
		if(count > 600){
			count =0;
			flag_kickout_all = FALSE;
			kick_out(1);
		}
	}
}

void RD_Kickout_All(void){
	if(flag_kickout_all == TRUE){
		Time_Kick_Out_All();
	}
}


