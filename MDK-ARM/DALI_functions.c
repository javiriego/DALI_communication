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
 
 /****************************************************************************************************
 *					                              STANDARD COMMANDS																					 *
 *****************************************************************************************************/
void OFF_command(void){
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
}
 
void UP_command(void){
}
 
void DOWN_command(void){
}

void STEP_UP(void){
}
 
void STEP_DOWN(void){
}
 
void RECALL_MAX_LEVEL(void){	
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
}
 
void RECALL_MIN_LEVEL(void){
}
 
void STEP_DOWN_N_OFF(void){
}
 
void ON_N_STEP_UP(void){
}
 
void ENABLE_DAPC_SEQUENCE(void){
}
 
void GO_TO_LAST_ACTIVE_LEVEL(void){
}
 
void GO_TO_SCENE(void){
}
 
void RESET_command(void){
}
 
void STORE_ACTUAL_LEVEL_IN_DTR0(void){
}
 
void SAVE_PERSISTENT_VARIABLES(void){
}
 
void SET_OPERATING_MODE(void){//(DTR0)
}
 
void RESET_MEMORY_BANK(void){//(DTR0)
}
 
void IDENTIFY_DEVICE(void){
}
 
void SET_MAX_LEVEL(void){//(DTR0)
}
 
void SET_MIN_LEVEL(void){//(DTR0)
}
 
void SET_SYSTEM_FAILURE_LEVEL(void){//(DTR0)
}
 
void SET_POWER_ON_LEVEL(void){//(DTR0)
}
 
void SET_FADE_TIME(void){//(DTR0)
}
 
void SET_FADE_RATE(void){//(DTR0)
}
 
void SET_EXTENDED_FADE_RATE(void){//(DTR0)
}
 
void SET_SCENE(void){//(DTR0)
}
 
void REMOVE_FROM_SCENE(void){
}
 
void ADD_TO_GROUP(void){
}
 
void REMOVE_FROM_GROUP(void){
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
 
 
 /****************************************************************************************************
 *					                              SPECIAL COMMANDS																					 *
 *****************************************************************************************************/

 