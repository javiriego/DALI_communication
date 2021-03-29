/****************************************************************************************************
*                            PROCESAMIENTO DE FRAMES DE ENTRADA Y SALIDA                            *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		frame_processing.h
 * @author 	Javier Riego Barcia
 * @date 		23-Marzo-2021
 * @brief		Header file for frame_processing.c
 *****************************************************************************************************
 *
 *
 *****************************************************************************************************
 */
 
/* DEFINICIONES GLOBALES ****************************************************************************/
#include "stdint.h"

#define MAX_RXBUFFER  3
#define HALFDATA_SIZE 8

#define ADDRESS  0
#define DATA1 	 1
#define DATA2		 2

#define LOW  0
#define HIGH 1

#define SEND_ONCE  1
#define SEND_TWICE 2

#define MAX_INDIV_ADDR   		0x7F //127 (0111 1111)
#define MAX_GROUP_ADDR   		0x9F //159 (1001 1111)
#define MAX_SPECIAL_COM  		0xCB //203 (1100 1011)
#define MAX_RESERVED_COM 		0xFB //251 (1111 1011)
#define MAX_UNAD_BROADC_COM 0xFD //253 (1111 1101)
#define MAX_BROADC_COM			0xFF //255 (1111 1111)

/* EXTERNALIZACION DE VARIABLES *********************************************************************/
extern unsigned short int rxbits;
extern unsigned short int rx_buffer[MAX_RXBUFFER];
extern uint8_t	send_twice_frame;

/* DEFINICION DE FUNCIONES UTILIZADAS EXTERNAMENTE **************************************************/
void processRxFrame(void);
