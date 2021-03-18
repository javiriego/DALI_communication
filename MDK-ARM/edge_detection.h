/* DEFINICIONES GLOBALES ****************************************************************************/
#include "stdint.h"

// MODO DE MUESTREO DEL TRANSCEPTOR *****************************************************************
#define TRANSCEIVER_INVERTED_LOGIC
//***************************************************************************************************
#define RISING  1
#define FALLING 0

#define AT_BIT_START  0
#define AT_BIT_MIDDLE 1

#define RECEIVING_SIGNAL 		1
#define WAITING_FOR_SIGNAL	0

#define MAX_HB_STORAGE 64


/* EXTERNALIZACION DE VARIABLES *********************************************************************/
extern unsigned char _edgeType;				// Tipo de flanco (RISING/FALLING)
extern unsigned char _postedgeValue;	// Valor de la señal tras un nuevo flanco
extern unsigned char _preedgeValue;		// Valor de la señal previa la entrada de un nuevo flanco
extern unsigned char _edgePosition;		// Posicion del flanco en el tiempo de bit (START/MIDDLE)
extern unsigned int _timervalue;			// Valor de cuenta del timer de bit


/* DEFINICION DE FUNCIONES UTILIZADAS EXTERNAMENTE **************************************************/
//Reinicio de mitad de bit
void HalfBit_init(void);
//Controlador de mitad de bit
void HalfBitHandler(unsigned char edgePosition, unsigned char edgeType,  unsigned int timervalue);
//Controlador de errores de timing
void TimingErrorHandler(void);
//Interrupcion por flancos (RISING/FALLING):
void receive_edge(void);

