/****************************************************************************************************
*                           FUNCIONES DE TEMPORIZACION Y ERRORES DE TIMING                          *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		timing_functions.c
 * @author 	Javier Riego Barcia
 * @version V1.0
 * @date 		23-Marzo-2021
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
#include "global_def.h"
#include "frame_processing.h"

/* VARIABLES Y DEFINICIONES *************************************************************************/
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart2;

unsigned char _timingerror;
uint16_t timer_overflow_count;

/****************************************************************************************************
*                        FUNCIONES DE INICIO, DESBORDE Y REARME DE LOS TIMERS                       *
*****************************************************************************************************/
// TIMER 14 [BIT TIMER]
//Inicio
void start_BitTimer(uint16_t countValue){
	__HAL_TIM_SET_COUNTER(&htim14, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim14, countValue);
	__HAL_TIM_CLEAR_IT(&htim14, TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(&htim14);
}
//Parada
void stop_BitTimer(void){
	HAL_TIM_Base_Stop_IT(&htim14);
}
//Desborde
void BitTimer_overflow(void){
	stop_BitTimer();
	bus_status = WAITING_FOR_FALL_EDGE;
	if (__HAL_TIM_GET_AUTORELOAD(&htim14) == POWERDOWN_TIME)	power_down_handler(); 		// POWER DOWN
	if (__HAL_TIM_GET_AUTORELOAD(&htim14) == STOPCOND_TIME)		stop_condition_handler(); // STOP CONDITION
}


// TIMER 3 [FRAME TIMER]
//Inicio
void start_FrameTimer (unsigned int countValue){		 
	__HAL_TIM_SET_COUNTER(&htim3, 0);	 
	__HAL_TIM_SET_AUTORELOAD(&htim3, countValue);
	__HAL_TIM_CLEAR_IT(&htim3,TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(&htim3);
}
//Parada
void stop_FrameTimer(void){
	HAL_TIM_Base_Stop_IT(&htim3);
}
//Desborde
void FrameTimer_overflow(void){
	stop_FrameTimer();
	if(_powerdown == ON) system_failure_handler();
	if(send_twice_frame == ON) send_twice_frame = OFF;
}


// MANEJADOR DE TIMING ERRORS
void TimingErrorHandler(void){
	_timingerror = ON;
}
