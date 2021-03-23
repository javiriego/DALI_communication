/****************************************************************************************************
*																																																		*
*                    DETECCION Y TRATAMIENTO DE FLANCOS EN LA SEÑAL DE ENTRADA                      *
*																																																		*
*****************************************************************************************************/
#include "main.h"
#include "stdint.h"
#include "edge_detection.h"
#include "bus_conditions.h"
#include "timing_functions.h"
#include "global_def.h"
#include "frame_processing.h"

/* VARIABLES Y DEFINICIONES *************************************************************************/
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart2;
unsigned char _edgeType;				// Tipo de flanco (RISING/FALLING)
unsigned char _postedgeValue;		// Valor de la señal tras un nuevo flanco
unsigned char _preedgeValue;		// Valor de la señal previa la entrada de un nuevo flanco
unsigned char _edgePosition;		// Posicion del flanco en el tiempo de bit (START/MIDDLE)
unsigned char _lineStatus;			// Estado de la recepcion de tramas (0->INACTIVO / 1->ACTIVO)
unsigned int  _timervalue;			// Valor de cuenta del timer de bit

uint16_t _halfbit_count = 0;								// Contador de medios bits
unsigned int _HB_EdgeValue[MAX_HB_STORAGE];	// Almacenamiento para cada medio bit analizado
unsigned int _HB_TimeValue[MAX_HB_STORAGE];	// Almacenamiento para cada medio bit analizado


/* DECLARACION DE FUNCIONES *************************************************************************/ 
void edgeHandler(unsigned char edgePosition, unsigned char edgeType, unsigned char postedgeValue, unsigned int timervalue);
void HalfBitHandler(unsigned char edgePosition, unsigned char edgeType,  unsigned int timervalue);
void TimingErrorHandler(void);


/****************************************************************************************************
*                       DETECCION Y TRATAMIENTO DE FLANCOS POR INTERRUPCION                         *
*****************************************************************************************************/
void receive_edge(void){
	//Recogida cuenta del timer
	_timervalue = __HAL_TIM_GET_COUNTER(&htim14);
	//Comprobacion de la dirección del flanco
	if(HAL_GPIO_ReadPin(DALI_RX_GPIO_Port, DALI_RX_Pin) == GPIO_PIN_SET){
		#ifdef TRANSCEIVER_INVERTED_LOGIC
				_edgeType = FALLING;
		#endif
		#ifdef TRANSCEIVER_DIRECT_LOGIC
				_edgeType = RISING;
		#endif
	}
	else{
		#ifdef TRANSCEIVER_INVERTED_LOGIC
				_edgeType = RISING;
		#endif
		#ifdef TRANSCEIVER_DIRECT_LOGIC
				_edgeType = FALLING;
		#endif
	}
	//Parada la cuenta del TIMER14
	stop_BitTimer();
	//Reseteo del contador tel timer
	__HAL_TIM_SET_COUNTER(&htim14, 0);
	//Ajuste del timer14 para la comprobacion de "BIT TIMING VIOLATION"
	if (_edgeType==FALLING)	__HAL_TIM_SET_AUTORELOAD(&htim14, POWERDOWN_TIME); 	// Desbordamiento en BUS POWER DOWN TIME
	if (_edgeType==RISING)  __HAL_TIM_SET_AUTORELOAD(&htim14, STOPCOND_TIME);		// Desbordamiento en STOP CONDITION TIME
	__HAL_TIM_CLEAR_IT(&htim14, TIM_IT_UPDATE);
	//Reeinicio del timer14 en modo interrupción
	HAL_TIM_Base_Start_IT(&htim14);
	//Almacenaimento de valor de la linea
	_postedgeValue = HAL_GPIO_ReadPin(DALI_RX_GPIO_Port, DALI_RX_Pin);
	//Almacenamiento del estado previo tras el flanco
	_preedgeValue = _postedgeValue;
	//Procesamiento del flanco
	if (_edgeType==FALLING) bus_status_fall_edge();
	edgeHandler(_edgePosition, _edgeType, _postedgeValue, _timervalue);
}

/****************************************************************************************************
*       PROCESAMIENTO DE LOS FLANCOS RECIBIDOS Y ALMACENAMIENTO DE LA INFO DE CADA HALFBIT          *
*****************************************************************************************************/
// MANEJADOR DE FLANCOS:
void edgeHandler(unsigned char edgePosition, unsigned char edgeType, unsigned char postedgeValue, unsigned int timervalue){
	// Espera el primer bit del frame (WAITING_FOR_SIGNAL)
	if(_lineStatus == WAITING_FOR_SIGNAL){
		HalfBitHandler(AT_BIT_START, edgeType, timervalue);
		_lineStatus = RECEIVING_SIGNAL;
	}
	else{ // Si no es el primer flanco (RECEIVING_SIGNAL)
		switch (edgePosition){
			case AT_BIT_MIDDLE:
				if(timervalue > 317){	// < 317 us -> TimingError
					if(timervalue < 517) 				HalfBitHandler(AT_BIT_START, edgeType, timervalue);				// 1 HALF BIT
					else if(timervalue < 633) 	TimingErrorHandler();																			// GREY AREA
					// Si se recibe un flanco entre 633 y 1033 us, será en mitad del bit, y habrá ocurrido un cambio de
					//valor en la trama recibida, por lo que no se habrá detectado flanco al inicion del tiempo de bit
					else if(timervalue < 1033) {HalfBitHandler(AT_BIT_START, _preedgeValue, timervalue); 	// 2 HALF BIT
																			HalfBitHandler(AT_BIT_MIDDLE, edgeType, timervalue);}
					else { // timervalue > 1033
						switch (edgeType){
							case RISING:
								if(timervalue < STOPCOND_TIME) 	TimingErrorHandler();	// Before STOP CONDITION
								break;
							case FALLING:
								if(timervalue < POWERDOWN_TIME) TimingErrorHandler(); // Before POWER DOWN 
								break;
						}
					}
				}
				break;
			case AT_BIT_START:
				if(timervalue > 317){
					if(timervalue < 517) HalfBitHandler(AT_BIT_MIDDLE, edgeType, timervalue);
					else {
						switch (edgeType){
							case RISING:
								if(timervalue < STOPCOND_TIME) 	TimingErrorHandler();	// Before STOP CONDITION
								break;
							case FALLING:
								if(timervalue < POWERDOWN_TIME) TimingErrorHandler(); // Before POWER DOWN 
								break;
						}
					}
				}
				break;
		}
	}
}

// PREPARACIÓN DEL SISTEMA PARA LA RECEPCIÓN DE UNA NUEVA TRAMA
void HalfBit_init(void){
	_halfbit_count = 0;
	_edgePosition = AT_BIT_START;
	_lineStatus = WAITING_FOR_SIGNAL;
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
}

// ALMACENAMIENTO DE CADA MEDIO BIT
void HalfBitStorage(unsigned char edgeType, unsigned int timervalue){
	if (_halfbit_count < MAX_HB_STORAGE){
		_HB_EdgeValue[_halfbit_count] = edgeType;
		_HB_TimeValue[_halfbit_count] = timervalue;
		_halfbit_count ++;
	}
}

// MANEJADOR DE MEDIOS BITS
void HalfBitHandler(unsigned char edgePosition, unsigned char edgeType, unsigned int timervalue){
	_edgePosition = edgePosition;
	_edgeType = edgeType;
	HalfBitStorage(edgeType, timervalue);	
}
