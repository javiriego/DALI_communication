/****************************************************************************************************
*                            PROCESAMIENTO DE FRAMES DE ENTRADA Y SALIDA                            *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		frame_processing.c
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
#include "frame_processing.h"
#include "global_def.h"
#include "DALI_variables.h"

/* VARIABLES Y DEFINICIONES *************************************************************************/
unsigned short int rx_bits;										// Cantidad de bits recibidos
unsigned short int rx_buffer[MAX_RXBUFFER];		// Almacen debits recibidos
uint8_t	 send_twice_frame;

uint8_t  S_bit; // Indicador de comando ESTANDAR o DAPC (Direct Arc Power Control)

/****************************************************************************************************
 * IMPLEMENTACION DE FUNCIONES                                                                      *
 ****************************************************************************************************/
void check_address(unsigned short int rx_bits, unsigned short int *rx_buffer, uint8_t buffer_size, uint8_t send_cuant);
void check_command(unsigned short int rx_bits, unsigned short int *rx_buffer, uint8_t send_cuant, uint8_t S_bit);

// Procesamiento de la cadena de flanco almacenada tras la trama de datos ---------------------------
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
				check_address(rx_bits, rx_buffer, MAX_RXBUFFER, SEND_ONCE);
			}
			else{ //Si se recibe un segundo frame dentro del tiempo establecido y es igual que el anterior es un SEND-TWICE FRAME
				if((rx_buffer[ADDRESS]==rx_buffer_aux[ADDRESS]) && (rx_buffer[DATA1]==rx_buffer_aux[DATA1]) &&
					(rx_buffer[DATA2]==rx_buffer_aux[DATA2]) && (rx_bits == rx_bits_aux)){
					send_twice_frame = OFF;
					check_address(rx_bits, rx_buffer, MAX_RXBUFFER, SEND_TWICE);
						}	//else: ambos frames (send-twice) son diferentes
			}
		}
		else{ // SI EL FRAME NO ES DE 16 O 24 BITS ES INVALIDO
			// Backward or frame size violation	
			send_twice_frame = OFF;
		}
	}
}

// Procesamiento del array de bits recivido (comprobacion de la direccion) --------------------------
void check_address(unsigned short int rx_bits, unsigned short int *rx_buffer, uint8_t buffer_size, uint8_t send_cuant){
	uint16_t rx_address = rx_buffer[ADDRESS];
	uint16_t indiv_addr;
	uint16_t group_addr;
	uint16_t group_mask = 0;
	S_bit = rx_address & 0x01;
	// COMANDO INDIVIDUAL *****************************************************
	if(rx_address <= MAX_INDIV_ADDR){
		indiv_addr = (rx_address >> 1) & 0x3F;
		if (indiv_addr == shortAddress) check_command(rx_bits, rx_buffer, send_cuant, S_bit);
	}
	// COMANDO A GRUPO ********************************************************
	else if(rx_address <= MAX_GROUP_ADDR){
		group_addr = (rx_address >> 1) & 0x0F;
		SETBIT(group_mask, group_addr);
		if ((gearGroups & group_mask) != 0) check_command(rx_bits, rx_buffer, send_cuant, S_bit);
	}
	// COMANDO ESPECIAL *******************************************************
	else if(rx_address <= MAX_SPECIAL_COM){
		check_command(rx_bits, rx_buffer, send_cuant, S_bit);
	}
	// COMANDO RESERVADO ******************************************************
	else if(rx_address <= MAX_RESERVED_COM){
		__NOP();
	}
	// COMANDO A BROADCAST UNNADDRESSED ***************************************
	else if(((rx_address & 0xFE)==0xFC) && (shortAddress == 255)){
		check_command(rx_bits, rx_buffer, send_cuant, S_bit);
	}
	// COMANDO A BROADCAST ****************************************************
	else if((rx_address & 0xFE)==0xFE){
		check_command(rx_bits, rx_buffer, send_cuant, S_bit);
	}
	// COMANDO NO VALIDO ******************************************************	
	else __NOP();	
}

void check_command(unsigned short int rx_bits, unsigned short int *rx_buffer, uint8_t send_cuant, uint8_t S_bit){
	uint16_t command = rx_buffer[DATA1];
	(*dali_cmd_execute[command])();
}
/* OTRA FORMA DE RESOLVER 
static unsigned char D2T_CG_FrameFilterIsForMeGet (unsigned char address)
{
	unsigned char answer=0;
	if (((address&0xfe) == 0xfe) ||	(((address&0xfe) == 0xfc) && (shortAddress==255)) || (((address&0x80) == 0x00) && ((address&0xfe) == ((shortAddress<<1) & 0xfe))) || (((address&0xe0) == 0x80) && (gearGroups&(1<<((address>>1)&0x0f)))!=0))
	{
		answer=1;
	}	
	if (((address&0xe1) == 0xa1) || ((address&0xe1) == 0xc1))
	{
		answer=1;
	}
	return answer;	
}
*/
