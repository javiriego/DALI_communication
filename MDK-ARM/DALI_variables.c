/****************************************************************************************************
*                              DEFINICION DE VARIABLES Y COMANDOS DALI                              *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		DALI_variables.c
 * @author 	Javier Riego Barcia
 * @date 		25-Marzo-2021
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
uint16_t    actualLevel,									//Nivel de luminosidad actual
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
uint32_t		searchAddress,								//
						randomAddress;								//														[NVS]
uint16_t		operatingMode,								//Modo de operacion						[NVS]
						initialisationState,					//Modo de inicializacion (ENABLED, DISABLED, WITHDRAWN)
						writeEnableState;							//(ENABLED, DISABLED)
bool  			controlGearFailure,						//Indicador de fallo del dispositivo
						lampFailure,									//Indicador de fallo de la luminaria
						lampOn,												//Indicador de estado (ON/OFF) de la luminaria
						limitError,										//
						fadeRunning,									//Indicador de fade activo
						resetState,										//Indicador de estado de reset
						powerCycleSeen;								//Indicador de ciclo de potencia
uint16_t		gearGroups,										//Etiqueta de grupos 					[NVS]
						sceneX,												//Etiqueta de escenas (X=0:16)[NVS]
						DTR0,													//
						DTR1,													//
						DTR2,													//
						PHM;													//Physycal Minimun

bool				statusInfo[8];								// Almacen para los indicadores de estado del sistema

uint16_t gearGroups = 0x8011;
uint16_t shortAddress = 25;


/* COMANDOS DALI ************************************************************************************/
void (*dali_cmd_execute[])(void)={
	OFF_command,				//0x00
	UP_command,					//0x01
	DOWN_command,				//0x02
	STEP_UP,						//0x03
	STEP_DOWN,					//0x04
	RECALL_MAX_LEVEL,		//0x05
	RECALL_MIN_LEVEL,		//0x06
	STEP_DOWN_N_OFF,		//0x07
	ON_N_STEP_UP				//0x08
};
