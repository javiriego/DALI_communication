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

/* VARIABLES Y DEFINICIONES *************************************************************************/
unsigned short int rx_bits;										// Cantidad de bits recibidos
unsigned short int rx_buffer[MAX_RXBUFFER];		// Almacen debits recibidos

/* DECLARACION DE FUNCIONES *************************************************************************/ 
void valid_buffer_received(unsigned short int rx_bits, unsigned short int *rx_buffer, uint8_t buffer_size);

// Procesamiento de la cadena de flanco almacenada tras la trama de datos
void processRxFrame(void){
	for(int n=0; n<MAX_RXBUFFER; n++) rx_buffer[n]=0;
	if ((_HB_EdgeValue[0]==LOW) && (_HB_EdgeValue[1]==HIGH)){
		rx_bits = (_halfbit_count-2)/2;
		// COMPROBACION DE FRAME SIZE
		if((rx_bits==16)||(rx_bits==24)){
			// Loop para la primera parte de la trama recibida [ADDRESS]
			for(int n=0; n<HALFDATA_SIZE; n++){
				// Busqueda de flancos ascendentes [cambio de 0 a 1 logico] (se salta el bit START)
				if((_HB_EdgeValue[(2*n)+2]==LOW)&&(_HB_EdgeValue[(2*n)+3]==HIGH)) SETBIT(rx_buffer[ADDRESS], (7-n));
			}
			// Loop para la segunda parte de la trama recibida [DATA1]
			for(int n=0; n<HALFDATA_SIZE; n++){
				if((_HB_EdgeValue[(2*n)+2+16]==LOW)&&(_HB_EdgeValue[(2*n)+3+16]==HIGH)) SETBIT(rx_buffer[DATA1], (7-n));
			}
			// Loop para la tercera parte de la trama recibida [DATA2]
			for(int n=0; n<HALFDATA_SIZE; n++){
				if((_HB_EdgeValue[(2*n)+2+32]==LOW)&&(_HB_EdgeValue[(2*n)+3+32]==HIGH)) SETBIT(rx_buffer[DATA2], (7-n));
			}
			valid_buffer_received(rx_bits, rx_buffer, MAX_RXBUFFER); 
		}
		else{ // SI EL FRAME ES MAYOR DE 16 BITS ES INVALIDO
			// Backward or frame size violation	
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
}

// Procesamiento del array de bits recivido
void valid_buffer_received(unsigned short int rx_bits, unsigned short int *rx_buffer, uint8_t buffer_size){
	unsigned short int rx_buffer_watch[buffer_size];
	unsigned short int rxbits_watch;
	for(int i=0; i<buffer_size; i++){
		rx_buffer_watch[i]=rx_buffer[i];
		rxbits_watch=rx_bits;
	}
}

