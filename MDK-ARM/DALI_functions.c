/****************************************************************************************************
*                           FUNCIONES DE TEMPORIZACION Y ERRORES DE TIMING                          *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		DALI_functions.c
 * @author 	Javier Riego Barcia
 * @date 		26-Marzo-2021
 *****************************************************************************************************
 *
 *
 *****************************************************************************************************
 */
 
#include "main.h"
#include "stdint.h"
#include "edge_detection.h"
#include "bus_conditions.h"
#include "timing_functions.h"
#include "frame_processing.h"
#include "global_def.h"
#include "DALI_variables.h"

uint8_t duty_cycle = 0;
 
 /****************************************************************************************************
 *					                              STANDARD COMMANDS																					 *
 *****************************************************************************************************/
void DAPC(uint16_t level){ //level (Selector_bit == 0)
}

void OFF_command(void){
	targetLevel = 0;
	TIM1->CCR1 = targetLevel;
	actualLevel = targetLevel;
}
 
void UP_command(void){/////////////////////////////////////////////////////////
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
}
 
void DOWN_command(void){///////////////////////////////////////////////////////
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
}

void STEP_UP(void){
	targetLevel += 1;
	if(targetLevel >= maxLevel) targetLevel = maxLevel;
	TIM1->CCR1 = targetLevel;
	actualLevel = targetLevel;
}
 
void STEP_DOWN(void){
	targetLevel -= 1;
	if(targetLevel <= minLevel) targetLevel = minLevel;
	TIM1->CCR1 = targetLevel;
	actualLevel = targetLevel;
}
 
void RECALL_MAX_LEVEL(void){	
	if(initialisationState == DISABLED){
		targetLevel = maxLevel;
		TIM1->CCR1 = targetLevel;
		actualLevel = maxLevel;		
	}
	else{
		// targetLevel = maxLevel;
		// actualLevel = maxLevel;
		// Luz -> 100%
	}
}
 
void RECALL_MIN_LEVEL(void){if(initialisationState == DISABLED){
		targetLevel = minLevel;
		TIM1->CCR1 = targetLevel;
		actualLevel = minLevel;		
	}
	else{
		// targetLevel = minLevel;
		// actualLevel = minLevel;
		// Luz -> PHM
	}
}
 
void STEP_DOWN_N_OFF(void){
}
 
void ON_N_STEP_UP(void){
}
 
void ENABLE_DAPC_SEQUENCE(void){
}
 
void GO_TO_LAST_ACTIVE_LEVEL(void){
}
 
void GO_TO_SCENE_0(void){
}
 
void GO_TO_SCENE_1(void){
}
 
void GO_TO_SCENE_2(void){
}
 
void GO_TO_SCENE_3(void){
}
 
void GO_TO_SCENE_4(void){
}
 
void GO_TO_SCENE_5(void){
}
 
void GO_TO_SCENE_6(void){
}
 
void GO_TO_SCENE_7(void){
}
 
void GO_TO_SCENE_8(void){
}
 
void GO_TO_SCENE_9(void){
}
 
void GO_TO_SCENE_10(void){
}
 
void GO_TO_SCENE_11(void){
}
 
void GO_TO_SCENE_12(void){
}
 
void GO_TO_SCENE_13(void){
}
 
void GO_TO_SCENE_14(void){
}
 
void GO_TO_SCENE_15(void){
}
 
void RESET_command(void){
}
 
void STORE_ACTUAL_LEVEL_IN_DTR0(void){
}
 
void SAVE_PERSISTENT_VARIABLES(void){
}
 
void SET_OPERATING_MODE(void){//(DTR0)
	operatingMode = DTR0;
}
 
void RESET_MEMORY_BANK(void){//(DTR0)
}
 
void IDENTIFY_DEVICE(void){
}
 
void SET_MAX_LEVEL(void){//(DTR0)
	maxLevel = DTR0;
}
 
void SET_MIN_LEVEL(void){//(DTR0)
	minLevel = DTR0;
}
 
void SET_SYSTEM_FAILURE_LEVEL(void){//(DTR0)
	systemFailureLevel = DTR0;
}
 
void SET_POWER_ON_LEVEL(void){//(DTR0)
	powerOnLevel = DTR0;
}
 
void SET_FADE_TIME(void){//(DTR0)
	fadeTime = DTR0;
}
 
void SET_FADE_RATE(void){//(DTR0)
	fadeRate = DTR0;
}
 
void SET_EXTENDED_FADE_RATE(void){//(DTR0)
}
 
void SET_SCENE_0(void){//(DTR0)
}
 
void SET_SCENE_1(void){//(DTR0)
}
 
void SET_SCENE_2(void){//(DTR0)
}
 
void SET_SCENE_3(void){//(DTR0)
}
 
void SET_SCENE_4(void){//(DTR0)
}
 
void SET_SCENE_5(void){//(DTR0)
}
 
void SET_SCENE_6(void){//(DTR0)
}
 
void SET_SCENE_7(void){//(DTR0)
}
 
void SET_SCENE_8(void){//(DTR0)
}
 
void SET_SCENE_9(void){//(DTR0)
}
 
void SET_SCENE_10(void){//(DTR0)
}
 
void SET_SCENE_11(void){//(DTR0)
}
 
void SET_SCENE_12(void){//(DTR0)
}
 
void SET_SCENE_13(void){//(DTR0)
}
 
void SET_SCENE_14(void){//(DTR0)
}
 
void SET_SCENE_15(void){//(DTR0)
}
 
void REMOVE_FROM_SCENE_0(void){
}
 
void REMOVE_FROM_SCENE_1(void){
}
 
void REMOVE_FROM_SCENE_2(void){
}
 
void REMOVE_FROM_SCENE_3(void){
}
 
void REMOVE_FROM_SCENE_4(void){
}
 
void REMOVE_FROM_SCENE_5(void){
}
 
void REMOVE_FROM_SCENE_6(void){
}
 
void REMOVE_FROM_SCENE_7(void){
}
 
void REMOVE_FROM_SCENE_8(void){
}
 
void REMOVE_FROM_SCENE_9(void){
}
 
void REMOVE_FROM_SCENE_10(void){
}
 
void REMOVE_FROM_SCENE_11(void){
}
 
void REMOVE_FROM_SCENE_12(void){
}
 
void REMOVE_FROM_SCENE_13(void){
}
 
void REMOVE_FROM_SCENE_14(void){
}
 
void REMOVE_FROM_SCENE_15(void){
}

void ADD_TO_GROUP_0(void){
}

void ADD_TO_GROUP_1(void){
}

void ADD_TO_GROUP_2(void){
}

void ADD_TO_GROUP_3(void){
}

void ADD_TO_GROUP_4(void){
}

void ADD_TO_GROUP_5(void){
}

void ADD_TO_GROUP_6(void){
}

void ADD_TO_GROUP_7(void){
}

void ADD_TO_GROUP_8(void){
}

void ADD_TO_GROUP_9(void){
}

void ADD_TO_GROUP_10(void){
}

void ADD_TO_GROUP_11(void){
}

void ADD_TO_GROUP_12(void){
}

void ADD_TO_GROUP_13(void){
}

void ADD_TO_GROUP_14(void){
}

void ADD_TO_GROUP_15(void){
}
 
void REMOVE_FROM_GROUP_0(void){
}
 
void REMOVE_FROM_GROUP_1(void){
}
 
void REMOVE_FROM_GROUP_2(void){
}
 
void REMOVE_FROM_GROUP_3(void){
}
 
void REMOVE_FROM_GROUP_4(void){
}
 
void REMOVE_FROM_GROUP_5(void){
}
 
void REMOVE_FROM_GROUP_6(void){
}
 
void REMOVE_FROM_GROUP_7(void){
}
 
void REMOVE_FROM_GROUP_8(void){
}
 
void REMOVE_FROM_GROUP_9(void){
}
 
void REMOVE_FROM_GROUP_10(void){
}
 
void REMOVE_FROM_GROUP_11(void){
}
 
void REMOVE_FROM_GROUP_12(void){
}
 
void REMOVE_FROM_GROUP_13(void){
}
 
void REMOVE_FROM_GROUP_14(void){
}
 
void REMOVE_FROM_GROUP_15(void){
}
 
void SET_SHORT_ADDRESS(void){//(DTR0)
}
 
void ENABLE_WRITE_MEMORY(void){
}
 
void QUERY_STATUS(void){
}
 
void QUERY_CONTROL_GEAR_PRESENT(void){
}
 
void QUERY_LAMP_FAILURE(void){
}
 
void QUERY_LAMP_POWER_ON(void){
}
 
void QUERY_LIMIT_ERROR(void){
}
 
void QUERY_RESET_STATE(void){
}
 
void QUERY_MISSING_SHORT_ADDRESS(void){
}
 
void QUERY_VERSION_NUMBER(void){
}
 
void QUERY_CONTENT_DTR0(void){
}
 
void QUERY_DEVICE_TYPE(void){
}
 
void QUERY_PHYSICAL_MINIMUM(void){
}
 
void QUERY_POWER_FAILURE(void){
}
 
void QUERY_CONTENT_DRT1(void){
}
 
void QUERY_CONTENT_DRT2(void){
}
 
void QUERY_OPERATING_MODE(void){
}
 
void QUERY_LIGHT_SOUERCE_TYPE(void){
}
 
void QUERY_ACTUAL_LEVEL(void){
}
 
void QUERY_MAX_LEVEL(void){
}
 
void QUERY_MIN_LEVEL(void){
}
 
void QUERY_POWER_ON_LEVEL(void){
}
 
void QUERY_SYSTEM_FAILURA_LEVEL(void){
}
 
void QUERY_FADE_TIME_RATE(void){
}
 
void QUERY_MANUFACTURER_SPECIFIC_MODE(void){
}
 
void QUERY_NEXT_DEVICE_TYPE(void){
}
 
void QUERY_EXTENDED_FADE_TIME(void){
}
 
void QUERY_CONTROL_GEAR_FAILURE(void){
}
 
void QUERY_SCENE_0_LEVEL(void){
}
 
void QUERY_SCENE_1_LEVEL(void){
}
 
void QUERY_SCENE_2_LEVEL(void){
}
 
void QUERY_SCENE_3_LEVEL(void){
}
 
void QUERY_SCENE_4_LEVEL(void){
}
 
void QUERY_SCENE_5_LEVEL(void){
}
 
void QUERY_SCENE_6_LEVEL(void){
}
 
void QUERY_SCENE_7_LEVEL(void){
}
 
void QUERY_SCENE_8_LEVEL(void){
}
 
void QUERY_SCENE_9_LEVEL(void){
}
 
void QUERY_SCENE_10_LEVEL(void){
}
 
void QUERY_SCENE_11_LEVEL(void){
}
 
void QUERY_SCENE_12_LEVEL(void){
}
 
void QUERY_SCENE_13_LEVEL(void){
}
 
void QUERY_SCENE_14_LEVEL(void){
}
 
void QUERY_SCENE_15_LEVEL(void){
}
 
void QUERY_GROUPS_0_7(void){
}
 
void QUERY_GROUPS_8_15(void){
}
 
void QUERY_RANDOM_ADDR_H(void){
}
 
void QUERY_RANDOM_ADDR_M(void){
}
 
void QUERY_RANDOM_ADDR_L(void){
}
 
void QUERY_READ_MEM_LOCATION(void){
}

void NO_COMMAND_DEFINED(void){
	__NOP();
}
 
// 0xFF -> QUERY_EXTENDED_VERSION_NUMBER
 
 
 /****************************************************************************************************
 *					                              SPECIAL COMMANDS																					 *
 *****************************************************************************************************/
void TERMINATE(uint16_t data){
}
 
void DTR0_LOAD(uint16_t data){
	DTR0 = data;
}
 
void INITIALISE(uint16_t data){ //(DEVICE)
}
 
void RANDOMISE(uint16_t data){
}
 
void COMPARE(uint16_t data){
}
 
void WITHDRAW(uint16_t data){
}
 
void PING(uint16_t data){
}
 
void SEARCHADDRH(uint16_t data){ //(DATA)
}
 
void SEARCHADDRM(uint16_t data){ //(DATA)
}
 
void SEARCHADDRL(uint16_t data){ //(DATA)
}
 
void PROGRAM_SHORT_ADDR(uint16_t data){ //(DATA)
}
 
void VERIFY_SHORT_ADDR(uint16_t data){ //(DATA)
}

void QUERY_SHORT_ADDR(uint16_t data){
}
 
void ENABLE_DEVICE_TYPE(uint16_t data){ //(DATA)
}
 
void DTR1_LOAD(uint16_t data){
	DTR1 = data;
}
 
void DTR2_LOAD(uint16_t data){
	DTR2 = data;
}
 
void WRITE_MEM_LOCATION(uint16_t data){ //(DTR1, DTR0, DATA)
}
 
void WRITE_MEM_LOCATION_NO_REPLY(uint16_t data){ //(DTR1, DTR0, DATA)
}
