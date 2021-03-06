/****************************************************************************************************
*                           CONDICIONES DEL BUS Y DETECCION DE ERRORES                              *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		bus_conditions.c
 * @author 	Javier Riego Barcia
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
#include "DALI_variables.h"

/* VARIABLES Y DEFINICIONES *************************************************************************/
unsigned char _powerdown;
unsigned char bus_status;

/****************************************************************************************************
*                              FUNCIONES DE CONTROL DEL ESTADO DEL BUS                              *
*****************************************************************************************************/
// COMPROBACION DEL PRIMER FLANCO DESCENDENTE DE UNA TRAMA
void bus_status_fall_edge(void){
	if(bus_status == WAITING_FOR_FALL_EDGE){
		stop_FrameTimer();
		bus_status = RECEIVED_FALL_EDGE;
		HalfBit_init();
	}
}

// RESETEO DEL ESTADO DEL BUS TRAS UNA STOP CONDITION
void bus_status_stop(void){
	_powerdown = OFF;
	_timingerror = OFF;
	processRxFrame();
}

// MANEJADOR DE POWER DOWN (CAIDA DEL BUS)
void power_down_handler(void){
	_powerdown = ON;
	start_FrameTimer(POWERDOWN_RESTART_TIME);
}

// MANEJADOR DE STOP CONDITION (CONDICION DE PARADA TRAS FIN DE TRAMA)
void stop_condition_handler(void){
	start_FrameTimer(SEND_TWICE_FRAME_TIME);
	bus_status_stop();
}

// MANEJADOR DE FALLOS DEL SISTEMA
void system_failure_handler(void){
 	_powerdown = OFF; 
}
