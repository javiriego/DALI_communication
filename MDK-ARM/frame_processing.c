/****************************************************************************************************
*                            PROCESAMIENTO DE FRAMES DE ENTRADA Y SALIDA                            *
*****************************************************************************************************/
#include "main.h"
#include "stdint.h"
#include "edge_detection.h"
#include "bus_conditions.h"
#include "timing_functions.h"
#include "frame_processing.h"
#include "global_def.h"

unsigned short int rxbits_count;
unsigned short int rx_buffer[MAX_RXBUFFER];

void processRxFrame(void){
	if ((_HB_EdgeValue[0]==LOW) && (_HB_EdgeValue[1]==HIGH)){
		rxbits_count = (_halfbit_count-2)/2;
		// Loop para la primera mitad de la trama recibida [ADDRESS]
		for(int n=0; n<HALFDATA_SIZE; n++){
			// Busqueda de flancos ascendentes [cambio de 0 a 1 logico] (se salta el bit START)
			if((_HB_EdgeValue[(2*n)+2]==LOW)&&(_HB_EdgeValue[(2*n)+3]==HIGH)) SETBIT(rx_buffer[ADDRESS], (7-n));
		}
		// Loop para la segunda mitad de la trama recibida [DATA]
		for(int n=0; n<HALFDATA_SIZE; n++){
			if((_HB_EdgeValue[(2*n)+2+16]==LOW)&&(_HB_EdgeValue[(2*n)+3+16]==HIGH)) SETBIT(rx_buffer[DATA], (7-n));
		}	
	}
}
