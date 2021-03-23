/****************************************************************************************************
*																																																		*
*                            PROCESAMIENTO DE FRAMES DE ENTRADA Y SALIDA                            *
*																																																		*
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
uint8_t	send_twice_frame;

/* DECLARACION DE FUNCIONES *************************************************************************/ 
void valid_buffer_received(unsigned short int rx_bits, unsigned short int *rx_buffer, uint8_t buffer_size, uint8_t send_cuant);

// Procesamiento de la cadena de flanco almacenada tras la trama de datos
void processRxFrame(void){
	unsigned short int rx_buffer_aux[MAX_RXBUFFER];
	unsigned short int rx_bits_aux;
	for(int n=0; n<MAX_RXBUFFER; n++) rx_buffer_aux[n]=0;
	if ((_HB_EdgeValue[0]==LOW) && (_HB_EdgeValue[1]==HIGH)){
		rx_bits_aux = (_halfbit_count-2)/2;
		// Comprobacion del tamaño del frame
		if((rx_bits_aux==16)||(rx_bits_aux==24)){
			// Loop para la primera parte de la trama recibida [ADDRESS]
			for(int n=0; n<HALFDATA_SIZE; n++){
				// Busqueda de flancos ascendentes [cambio de 0 a 1 logico] (se salta el bit START)
				if((_HB_EdgeValue[(2*n)+2]==LOW)&&(_HB_EdgeValue[(2*n)+3]==HIGH)) SETBIT(rx_buffer_aux[ADDRESS], (7-n));
			}
			// Loop para la segunda parte de la trama recibida [DATA1]
			for(int n=0; n<HALFDATA_SIZE; n++){
				if((_HB_EdgeValue[(2*n)+2+16]==LOW)&&(_HB_EdgeValue[(2*n)+3+16]==HIGH)) SETBIT(rx_buffer_aux[DATA1], (7-n));
			}
			// Loop para la tercera parte de la trama recibida [DATA2]
			for(int n=0; n<HALFDATA_SIZE; n++){
				if((_HB_EdgeValue[(2*n)+2+32]==LOW)&&(_HB_EdgeValue[(2*n)+3+32]==HIGH)) SETBIT(rx_buffer_aux[DATA2], (7-n));
			}
			//Comprobacion de SEND-TWICE frames
			if(send_twice_frame == OFF){
				send_twice_frame = ON;
				rx_bits = rx_bits_aux;
				rx_buffer[ADDRESS]=rx_buffer_aux[ADDRESS];
				rx_buffer[DATA1]=rx_buffer_aux[DATA1];
				rx_buffer[DATA2]=rx_buffer_aux[DATA2];
				valid_buffer_received(rx_bits, rx_buffer, MAX_RXBUFFER, SEND_ONCE);
			}
			else{ //Si se recibe un segundo frame dentro del tiempo establecido y es igual que el anterior es un SEND-TWICE FRAME
				if((rx_buffer[ADDRESS]==rx_buffer_aux[ADDRESS]) && (rx_buffer[DATA1]==rx_buffer_aux[DATA1]) &&
					(rx_buffer[DATA2]==rx_buffer_aux[DATA2]) && (rx_bits == rx_bits_aux)){
					send_twice_frame = OFF;
					valid_buffer_received(rx_bits, rx_buffer, MAX_RXBUFFER, SEND_TWICE);
						}	//else: ambos frames (send-twice) son diferentes
			}
		}
		else{ // SI EL FRAME NO ES DE 16 O 24 BITS ES INVALIDO
			// Backward or frame size violation	
			send_twice_frame = OFF;
		}
	}
}

// Procesamiento del array de bits recivido
void valid_buffer_received(unsigned short int rx_bits, unsigned short int *rx_buffer, uint8_t buffer_size, uint8_t send_cuant){
	
}

