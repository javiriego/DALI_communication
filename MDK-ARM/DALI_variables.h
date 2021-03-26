/****************************************************************************************************
*                              DEFINICION DE VARIABLES Y COMANDOS DALI                              *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		DALI_variables.h
 * @author 	Javier Riego Barcia
 * @date 		25-Marzo-2021
 * @brief		Header file for DALI variables declaration
 *****************************************************************************************************
 *
 *
 *****************************************************************************************************
 */
 
 #include "stdint.h"
 #include "stdbool.h"
 #include "global_def.h"
 #include "DALI_functions.h"

/* VARIABLES DALI ***********************************************************************************/
extern uint16_t   actualLevel,									//Nivel de luminosidad actual
								  targetLevel,									//Nivel de luminosidad a adquirir
								  lastActiveLevel,							//Ultimo nivel activo
								  lastLightLevel,								//Ultimo nivel de luminosidad [NVS]
									powerOnLevel,									//Nivel de encendido					[NVS]
									systemFailureLevel,						//Nivel de fallo de sistema		[NVS]
									minLevel,											//Nivel minimo de luminosidad	[NVS]
									maxLevel,											//Nivel maximo de luminosidad	[NVS]
									fadeRate,											//Ratio de fade								[NVS]
									fadeTime,											//Tiempo de fade							[NVS]
									extendedFadeTimeBase,					//														[NVS]
									extendedFadeTimeMultiplier,		//														[NVS]
									shortAddress;									//Direccion en el BUS (0:64)	[NVS]
extern uint32_t		searchAddress,								//
									randomAddress;								//														[NVS]
extern uint16_t		operatingMode,								//Modo de operacion						[NVS]
									initialisationState,					//Modo de inicializacion (ENABLED, DISABLED, WITHDRAWN)
									writeEnableState;							//(ENABLED, DISABLED)
extern bool  			controlGearFailure,						//Indicador de fallo del dispositivo
									lampFailure,									//Indicador de fallo de la luminaria
									lampOn,												//Indicador de estado (ON/OFF) de la luminaria
									limitError,										//
									fadeRunning,									//Indicador de fade activo
									resetState,										//Indicador de estado de reset
									powerCycleSeen;								//Indicador de ciclo de potencia
extern uint16_t		gearGroups,										//Etiqueta de grupos 					[NVS]
									sceneX,												//Etiqueta de escenas (X=0:16)[NVS]
									DTR0,													//
									DTR1,													//
									DTR2,													//
									PHM;													//Physycal Minimun

extern bool				statusInfo[8];								// Almacen para los indicadores de estado del sistema


/* COMANDOS DALI ************************************************************************************/
extern void (*dali_cmd_execute[])(void);
