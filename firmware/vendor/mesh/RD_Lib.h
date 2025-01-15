/*
 * RD_Lib.h
 *
 *  Created on: Sep 9, 2024
 *      Author: PC5
 */

#ifndef RD_LIB_H_
#define RD_LIB_H_



#define RD_LOG_UART         0
#define TRAINING_EN         0

#define NAME				HIGHTBAY_RADA

#if NAME != HIGHTBAY_RADA
#define MAINTYPE			0x01			//RD_EDIT: Config cac loai den
#define FEATURE				0x02
#else
#define MAINTYPE			0x01
#define FEATURE				0x06
#endif

#define RD_VID_TYPE         ((VERSION_MAIN << 8) | VERSION_SUB)
#define RD_PID_TYPE			((MAINTYPE << 12) | (FEATURE << 8) | NAME)

#define TIME_DIM9           9
#define TIME_DIM10			3
#define TIME_DIM20			5
#define TIME_LED_DAY		12

#define RD_DIM_0 		    1		//RD_EDIT: Cong suat cac loai den
#define RD_DIM_10			2
#define RD_DIM_20			3
#define RD_DIM_25			4

#define SMT_121				0x01	// AT 16-20-22-
#define COB_122				0x02	// AT14
#define DOWNLIGHT_TT_124	0x04    // DOWLIGHT TRANG TRI AT 39-40-41 -18 -19
#define PN_T_125			0x05   // panel tron P04
#define PN_126				0x06   // P07
#define OT_127				0x07   // op tran LNxx khong co OT_LN28
#define GT_128				0x08	//
#define TL_12a				0x0a	//TRACK LIGHT
#define TT_12b				0x0b	// TREO TUONG
#define LED_WIRE_CT			0x0d	//  led day ct
#define TUBE_12e			0x0e	//  M36 - M66
#define OT_LN28				0x1b    //
#define HIGHTBAY_RADA       0x03 //T_NOTE them den hightbay rada

//-----------------------------------------------------------------
#define RLT03_06W_12020			0x14 //
#define RLT02_10W_12021			0x15 //
#define RLT02_20W_12022			0x16 //
#define RLT01_10W_12023			0x17
#define TRL08_20W_12024			0x18
#define TRL08_10W_12025			0x19
#define RLT03_12W_12026			0x1a


//RD_EDIT: 0.THANH : SPM: TYPE_LIGHT
#if  (NAME == SMT_121)
	#define VERSION_MAIN        0x02		//RD_EDIT: SEC : .h VERSION_MAIN
	#define VERSION_SUB         0x02		//RD_EDIT: SEC : .h VERSION_SUB
	#define TIME_RESET			TIME_DIM10
	#define SELECT_DIM			RD_DIM_10
#elif(NAME == COB_122)
	#define VERSION_MAIN        0x02
	#define VERSION_SUB         0x02
	#define TIME_RESET			TIME_DIM10
	#define SELECT_DIM			RD_DIM_10
#elif(NAME == DOWNLIGHT_TT_124)
	#define VERSION_MAIN        0x03
	#define VERSION_SUB         0x00
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_0
#elif(NAME == PN_T_125)
	#define VERSION_MAIN        0x02
	#define VERSION_SUB         0x02
	#define TIME_RESET			TIME_DIM10
	#define SELECT_DIM			RD_DIM_10
#elif(NAME == PN_126)
	#define VERSION_MAIN        0x02
	#define VERSION_SUB         0x02
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_0
#elif(NAME == OT_127)
	#define VERSION_MAIN        0x02
	#define VERSION_SUB         0x02
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_20
#elif(NAME == GT_128)
	#define VERSION_MAIN        0x02
	#define VERSION_SUB         0x02
	#define TIME_RESET			TIME_DIM10
	#define SELECT_DIM			RD_DIM_10
#elif(NAME == TL_12a)
	#define VERSION_MAIN        0x02
	#define VERSION_SUB         0x02
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_20
#elif(NAME == TT_12b)
	#define VERSION_MAIN        0x02
	#define VERSION_SUB         0x02
	#define TIME_RESET			TIME_DIM10
	#define SELECT_DIM			RD_DIM_10
#elif(NAME == LED_WIRE_CT)
	#define VERSION_MAIN        0x02
	#define VERSION_SUB         0x02
	#define TIME_RESET			TIME_LED_DAY
	#define SELECT_DIM			RD_DIM_0
#elif(NAME == TUBE_12e)
	#define VERSION_MAIN        0x02
	#define VERSION_SUB         0x02
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_20
#elif(NAME == OT_LN28)
	#define VERSION_MAIN        0x02
	#define VERSION_SUB         0x02
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_25
#elif(NAME == HIGHTBAY_RADA) // T_NOTE: TYPE_LIGHT
	#define VERSION_MAIN        0x01		//RD_EDIT: SEC : .h VERSION_MAIN
	#define VERSION_SUB         0x00		//RD_EDIT: SEC : .h VERSION_SUB
	#define TIME_RESET			TIME_DIM9
	#define SELECT_DIM			RD_DIM_25

//-----------------------------------------------------------------------------------------

#elif(NAME == RLT03_06W_12020)
	#define VERSION_MAIN        0x03
	#define VERSION_SUB         0x00
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_0
#elif(NAME == RLT02_10W_12021)
	#define VERSION_MAIN        0x03
	#define VERSION_SUB         0x00
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_0
#elif(NAME == RLT02_20W_12022)
	#define VERSION_MAIN        0x03
	#define VERSION_SUB         0x00
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_0
#elif(NAME == RLT01_10W_12023)
	#define VERSION_MAIN        0x03
	#define VERSION_SUB         0x00
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_0
#elif(NAME == TRL08_20W_12024)
	#define VERSION_MAIN        0x03
	#define VERSION_SUB         0x00
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_0
#elif(NAME == TRL08_10W_12025)
	#define VERSION_MAIN        0x03
	#define VERSION_SUB         0x00
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_0
#elif(NAME == RLT03_12W_12026)
	#define VERSION_MAIN        0x03
	#define VERSION_SUB         0x00
	#define TIME_RESET			TIME_DIM20
	#define SELECT_DIM			RD_DIM_0
#endif



#endif /* RD_LIB_H_ */
