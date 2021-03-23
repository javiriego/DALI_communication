/****************************************************************************************************
*                            PROCESAMIENTO DE FRAMES DE ENTRADA Y SALIDA                            *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		frame_processing.h
 * @author 	Javier Riego Barcia
 * @version V1.0
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

/* EXTERNALIZACION DE VARIABLES *********************************************************************/
extern unsigned short int rxbits;
extern unsigned short int rx_buffer[MAX_RXBUFFER];
extern uint8_t	send_twice_frame;

/* DEFINICION DE FUNCIONES UTILIZADAS EXTERNAMENTE **************************************************/
void processRxFrame(void);
