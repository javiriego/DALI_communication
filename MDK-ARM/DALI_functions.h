/****************************************************************************************************
*                           FUNCIONES DE TEMPORIZACION Y ERRORES DE TIMING                          *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		DALI_functions.c
 * @author 	Javier Riego Barcia
 * @date 		26-Marzo-2021
 * @brief		Headir file for DALI_functions.c
 *****************************************************************************************************
 *
 *
 *****************************************************************************************************
 */
 
 #include "stdint.h"
 
 /****************************************************************************************************
 *					                              STANDARD COMMANDS																					 *
 *****************************************************************************************************/
 void DAPC(uint16_t level);										//level (Selector_bit == 0)
 void OFF_command(void);			  		 					//0x00
 void UP_command(void);				  		 					//0x01
 void DOWN_command(void);			  		 					//0x02
 void STEP_UP(void);							   					//0x03
 void STEP_DOWN(void);					   	 					//0x04
 void RECALL_MAX_LEVEL(void); 	  	 					//0x05
 void RECALL_MIN_LEVEL(void); 		   					//0x06
 void STEP_DOWN_N_OFF(void);  		   					//0x07
 void ON_N_STEP_UP(void);					   					//0x08
 void ENABLE_DAPC_SEQUENCE(void);  	 					//0x09 
 void GO_TO_LAST_ACTIVE_LEVEL(void); 					//0x0A
 void GO_TO_SCENE_0(void);										//0x10
 void GO_TO_SCENE_1(void);										//0x11
 void GO_TO_SCENE_2(void);										//0x12
 void GO_TO_SCENE_3(void);										//0x13
 void GO_TO_SCENE_4(void);										//0x14
 void GO_TO_SCENE_5(void);										//0x15
 void GO_TO_SCENE_6(void);										//0x16
 void GO_TO_SCENE_7(void);										//0x17
 void GO_TO_SCENE_8(void);										//0x18
 void GO_TO_SCENE_9(void);										//0x19
 void GO_TO_SCENE_10(void);										//0x1A
 void GO_TO_SCENE_11(void);										//0x1B
 void GO_TO_SCENE_12(void);										//0x1C
 void GO_TO_SCENE_13(void);										//0x1D
 void GO_TO_SCENE_14(void);										//0x1E
 void GO_TO_SCENE_15(void);										//0x1F
 void RESET_command(void);										//0x20
 void STORE_ACTUAL_LEVEL_IN_DTR0(void); 			//0x21
 void SAVE_PERSISTENT_VARIABLES(void);				//0x22
 void SET_OPERATING_MODE(void); 							//0x23		//(DTR0)
 void RESET_MEMORY_BANK(void);								//0x24		//(DTR0)
 void IDENTIFY_DEVICE(void);									//0x25
 void SET_MAX_LEVEL(void);										//0x2A		//(DTR0)
 void SET_MIN_LEVEL(void);										//0x2B		//(DTR0)
 void SET_SYSTEM_FAILURE_LEVEL(void);					//0x2C		//(DTR0)
 void SET_POWER_ON_LEVEL(void);								//0x2D		//(DTR0)
 void SET_FADE_TIME(void);										//0x2E		//(DTR0)
 void SET_FADE_RATE(void);										//0x2F		//(DTR0)
 void SET_EXTENDED_FADE_RATE(void);						//0x30		//(DTR0)
 void SET_SCENE_0(void);											//0x40		//(DTR0)
 void SET_SCENE_1(void);											//0x41		//(DTR0)
 void SET_SCENE_2(void);											//0x42		//(DTR0)
 void SET_SCENE_3(void);											//0x43		//(DTR0)
 void SET_SCENE_4(void);											//0x44		//(DTR0)
 void SET_SCENE_5(void);											//0x45		//(DTR0)
 void SET_SCENE_6(void);											//0x46		//(DTR0)
 void SET_SCENE_7(void);											//0x47		//(DTR0)
 void SET_SCENE_8(void);											//0x48		//(DTR0)
 void SET_SCENE_9(void);											//0x49		//(DTR0)
 void SET_SCENE_10(void);											//0x4A		//(DTR0)
 void SET_SCENE_11(void);											//0x4B		//(DTR0)
 void SET_SCENE_12(void);											//0x4C		//(DTR0)
 void SET_SCENE_13(void);											//0x4D		//(DTR0)
 void SET_SCENE_14(void);											//0x4E		//(DTR0)
 void SET_SCENE_15(void);											//0x4F		//(DTR0)
 void REMOVE_FROM_SCENE_0(void);							//0x50
 void REMOVE_FROM_SCENE_1(void);							//0x51
 void REMOVE_FROM_SCENE_2(void);							//0x52
 void REMOVE_FROM_SCENE_3(void);							//0x53
 void REMOVE_FROM_SCENE_4(void);							//0x54
 void REMOVE_FROM_SCENE_5(void);							//0x55
 void REMOVE_FROM_SCENE_6(void);							//0x56
 void REMOVE_FROM_SCENE_7(void);							//0x57
 void REMOVE_FROM_SCENE_8(void);							//0x58
 void REMOVE_FROM_SCENE_9(void);							//0x59
 void REMOVE_FROM_SCENE_10(void);							//0x5A
 void REMOVE_FROM_SCENE_11(void);							//0x5B
 void REMOVE_FROM_SCENE_12(void);							//0x5C
 void REMOVE_FROM_SCENE_13(void);							//0x5D
 void REMOVE_FROM_SCENE_14(void);							//0x5E
 void REMOVE_FROM_SCENE_15(void);							//0x5F
 void ADD_TO_GROUP_0(void);										//0x60
 void ADD_TO_GROUP_1(void);										//0x61
 void ADD_TO_GROUP_2(void);										//0x62
 void ADD_TO_GROUP_3(void);										//0x63
 void ADD_TO_GROUP_4(void);										//0x64
 void ADD_TO_GROUP_5(void);										//0x65
 void ADD_TO_GROUP_6(void);										//0x66
 void ADD_TO_GROUP_7(void);										//0x67
 void ADD_TO_GROUP_8(void);										//0x68
 void ADD_TO_GROUP_9(void);										//0x69
 void ADD_TO_GROUP_10(void);									//0x6A
 void ADD_TO_GROUP_11(void);									//0x6B
 void ADD_TO_GROUP_12(void);									//0x6C
 void ADD_TO_GROUP_13(void);									//0x6D
 void ADD_TO_GROUP_14(void);									//0x6E
 void ADD_TO_GROUP_15(void);									//0x6F
 void REMOVE_FROM_GROUP_0(void);							//0x70
 void REMOVE_FROM_GROUP_1(void);							//0x71
 void REMOVE_FROM_GROUP_2(void);							//0x72
 void REMOVE_FROM_GROUP_3(void);							//0x73
 void REMOVE_FROM_GROUP_4(void);							//0x74
 void REMOVE_FROM_GROUP_5(void);							//0x75
 void REMOVE_FROM_GROUP_6(void);							//0x76
 void REMOVE_FROM_GROUP_7(void);							//0x77
 void REMOVE_FROM_GROUP_8(void);							//0x78
 void REMOVE_FROM_GROUP_9(void);							//0x79
 void REMOVE_FROM_GROUP_10(void);							//0x7A
 void REMOVE_FROM_GROUP_11(void);							//0x7B
 void REMOVE_FROM_GROUP_12(void);							//0x7C
 void REMOVE_FROM_GROUP_13(void);							//0x7D
 void REMOVE_FROM_GROUP_14(void);							//0x7E
 void REMOVE_FROM_GROUP_15(void);							//0x7F
 void SET_SHORT_ADDRESS(void);								//0x80		//(DTR0)
 void ENABLE_WRITE_MEMORY(void);							//0x81
 void QUERY_STATUS(void);											//0x90
 void QUERY_CONTROL_GEAR_PRESENT(void);				//0x91
 void QUERY_LAMP_FAILURE(void);								//0x92
 void QUERY_LAMP_POWER_ON(void);							//0x93
 void QUERY_LIMIT_ERROR(void);								//0x94
 void QUERY_RESET_STATE(void);								//0x95
 void QUERY_MISSING_SHORT_ADDRESS(void);			//0x96
 void QUERY_VERSION_NUMBER(void);							//0x97
 void QUERY_CONTENT_DTR0(void);								//0x98		//40
 void QUERY_DEVICE_TYPE(void);								//0x99
 void QUERY_PHYSICAL_MINIMUM(void);						//0x9A
 void QUERY_POWER_FAILURE(void);							//0x9B
 void QUERY_CONTENT_DRT1(void);								//0x9C
 void QUERY_CONTENT_DRT2(void);								//0x9D
 void QUERY_OPERATING_MODE(void);							//0x9E
 void QUERY_LIGHT_SOUERCE_TYPE(void);					//0x9F
 void QUERY_ACTUAL_LEVEL(void);								//0xA0
 void QUERY_MAX_LEVEL(void);									//0xA1
 void QUERY_MIN_LEVEL(void);									//0xA2
 void QUERY_POWER_ON_LEVEL(void);							//0xA3
 void QUERY_SYSTEM_FAILURA_LEVEL(void);				//0xA4
 void QUERY_FADE_TIME_RATE(void);							//0xA5
 void QUERY_MANUFACTURER_SPECIFIC_MODE(void);	//0xA6
 void QUERY_NEXT_DEVICE_TYPE(void);						//0xA7
 void QUERY_EXTENDED_FADE_TIME(void);					//0xA8
 void QUERY_CONTROL_GEAR_FAILURE(void);				//0xAA
 void QUERY_SCENE_0_LEVEL(void);							//0xB0
 void QUERY_SCENE_1_LEVEL(void);							//0xB1
 void QUERY_SCENE_2_LEVEL(void);							//0xB2
 void QUERY_SCENE_3_LEVEL(void);							//0xB3
 void QUERY_SCENE_4_LEVEL(void);							//0xB4
 void QUERY_SCENE_5_LEVEL(void);							//0xB5
 void QUERY_SCENE_6_LEVEL(void);							//0xB6
 void QUERY_SCENE_7_LEVEL(void);							//0xB7
 void QUERY_SCENE_8_LEVEL(void);							//0xB8
 void QUERY_SCENE_9_LEVEL(void);							//0xB9
 void QUERY_SCENE_10_LEVEL(void);							//0xBA
 void QUERY_SCENE_11_LEVEL(void);							//0xBB
 void QUERY_SCENE_12_LEVEL(void);							//0xBC
 void QUERY_SCENE_13_LEVEL(void);							//0xBD
 void QUERY_SCENE_14_LEVEL(void);							//0xBE
 void QUERY_SCENE_15_LEVEL(void);							//0xBF
 void QUERY_GROUPS_0_7(void);									//0xC0
 void QUERY_GROUPS_8_15(void);								//0xC1		//60
 void QUERY_RANDOM_ADDR_H(void);							//0xC2
 void QUERY_RANDOM_ADDR_M(void);							//0xC3
 void QUERY_RANDOM_ADDR_L(void);							//0xC4
 void QUERY_READ_MEM_LOCATION(void);					//0xC5		//(DTR0, DTR1)
 // 0xFF -> QUERY_EXTENDED_VERSION_NUMBER
 void NO_COMMAND_DEFINED(void);
 
 
 /****************************************************************************************************
 *					                              SPECIAL COMMANDS																					 *
 *****************************************************************************************************/
 void TERMINATE(uint16_t data);
 void DTR0_LOAD(uint16_t data); 									//(DATA)
 void INITIALISE(uint16_t data);									//(DEVICE)
 void RANDOMISE(uint16_t data);
 void COMPARE(uint16_t data);
 void WITHDRAW(uint16_t data);
 void PING(uint16_t data);
 void SEARCHADDRH(uint16_t data); 								//(DATA)
 void SEARCHADDRM(uint16_t data); 								//(DATA)
 void SEARCHADDRL(uint16_t data); 								//(DATA)
 void PROGRAM_SHORT_ADDR(uint16_t data); 					//(DATA)
 void VERIFY_SHORT_ADDR(uint16_t data); 					//(DATA)
 void QUERY_SHORT_ADDR(uint16_t data);
 void ENABLE_DEVICE_TYPE(uint16_t data); 					//(DATA)
 void DTR1_LOAD(uint16_t data); 									//(DATA)
 void DTR2_LOAD(uint16_t data); 									//(DATA)
 void WRITE_MEM_LOCATION(uint16_t data);					//(DTR1, DTR0, DATA)
 void WRITE_MEM_LOCATION_NO_REPLY(uint16_t data); //(DTR1, DTR0, DATA)
 
