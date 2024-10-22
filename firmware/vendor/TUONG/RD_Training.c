/*
 * RD_Training.c
 *
 *  Created on: Sep 24, 2024
 *      Author: PC5
 */

#include "RD_Training.h"

extern _Bool flag_kickout_all;
unsigned long timeNew, timeOld;
int count = 0;


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

void RD_Clean_Flash_Training(void){

}
