/* DEFINICIONES GLOBALES ****************************************************************************/
#include "stdint.h"

#define POWERDOWN_TIME 40000
#define STOPCOND_TIME  1900

extern unsigned char _timingerror;

/* DEFINICION DE FUNCIONES UTILIZADAS EXTERNAMENTE **************************************************/
//Interrupciones por desbordamiento del timer 14 (BIT TIMER), start y stop:
void start_BitTimer(uint16_t countValue);
void BitTimer_overflow(void);
void stop_BitTimer(void);
//Interrupciones por desbordamiento del timer 3  (FRAME TIMER), start y stop:
void start_FrameTimer (unsigned short int countValue);
void FrameTimer_overflow(void);
void stop_FrameTimer(void);
