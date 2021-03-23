/****************************************************************************************************
*                           FUNCIONES DE TEMPORIZACION Y ERRORES DE TIMING                          *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		timing_functions.h
 * @author 	Javier Riego Barcia
 * @date 		23-Marzo-2021
 * @brief		Header file for timing_functions.c
 *****************************************************************************************************
 *
 *
 *****************************************************************************************************
 */
 
/* DEFINICIONES GLOBALES ****************************************************************************/
#include "stdint.h"

#define POWERDOWN_TIME 40000
#define STOPCOND_TIME  1900

#define POWERDOWN_RESTART_TIME 500000
#define SEND_TWICE_FRAME_TIME	 99500

/* EXTERNALIZACION DE VARIABLES *********************************************************************/
extern unsigned char _timingerror;

/* DEFINICION DE FUNCIONES UTILIZADAS EXTERNAMENTE **************************************************/
//Interrupciones por desbordamiento del timer 14 (BIT TIMER), start y stop:
void start_BitTimer(uint16_t countValue);
void BitTimer_overflow(void);
void stop_BitTimer(void);
//Interrupciones por desbordamiento del timer 3  (FRAME TIMER), start y stop:
void start_FrameTimer (unsigned int countValue);
void FrameTimer_overflow(void);
void stop_FrameTimer(void);
