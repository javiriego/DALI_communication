/****************************************************************************************************
*                           CONDICIONES DEL BUS Y DETECCION DE ERRORES                              *
*****************************************************************************************************/
#include "main.h"
#include "stdint.h"
#include "edge_detection.h"
#include "bus_conditions.h"
#include "timing_functions.h"
#include "global_def.h"
#include "frame_processing.h"

/* VARIABLES Y DEFINICIONES *************************************************************************/
unsigned char _powerdown;
unsigned char bus_status;

/* DECLARACION DE FUNCIONES *************************************************************************/ 
void bus_status_fall_edge(void){
	if(bus_status == WAITING_FOR_FALL_EDGE){
		stop_FrameTimer();
		bus_status = RECEIVED_FALL_EDGE;
		HalfBit_init();
	}
}

void bus_status_stop(void){
	_powerdown = 0;
	_timingerror = 0;
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
	processRxFrame();
}

void power_down_handler(void){
	_powerdown = 1;
	start_FrameTimer(500000); ///////////////////////////DIVIDIR POR TICKS/////////////////////////////////
}

void stop_condition_handler(void){
	start_FrameTimer(97600); ///////////////////////////DIVIDIR POR TICKS/////////////////////////////////
	bus_status_stop();
}
