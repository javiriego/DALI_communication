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
						minLevel = 170,											//Nivel minimo de luminosidad	[NVS]
						maxLevel = 254,											//Nivel maximo de luminosidad	[NVS]
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
						DTR0,													//Registro de datos 0
						DTR1,													//Registro de datos 1
						DTR2,													//Registro de datos 2
						PHM;													//Physycal Minimun

bool				statusInfo[8];								// Almacen para los indicadores de estado del sistema

uint16_t gearGroups = 0x8011;
uint16_t shortAddress = 25;


/* COMANDOS DALI ************************************************************************************/
// STANDARD COMMANDS
void (*dali_cmd_execute[])(void)={
	OFF_command,											//0x00
	UP_command,												//0x01
	DOWN_command,											//0x02
	STEP_UP,													//0x03
	STEP_DOWN,												//0x04
	RECALL_MAX_LEVEL,									//0x05
	RECALL_MIN_LEVEL,									//0x06
	STEP_DOWN_N_OFF,									//0x07
	ON_N_STEP_UP,											//0x08
	ENABLE_DAPC_SEQUENCE,							//0x09
	GO_TO_LAST_ACTIVE_LEVEL,					//0x0A
	NO_COMMAND_DEFINED,								//0x0B
	NO_COMMAND_DEFINED,								//0x0C
	NO_COMMAND_DEFINED,								//0x0D
	NO_COMMAND_DEFINED,								//0x0E
	NO_COMMAND_DEFINED,								//0x0F
	GO_TO_SCENE_0,										//0x10
	GO_TO_SCENE_1,										//0x11
	GO_TO_SCENE_2,										//0x12
	GO_TO_SCENE_3,										//0x13
	GO_TO_SCENE_4,										//0x14
	GO_TO_SCENE_5,										//0x15
	GO_TO_SCENE_6,										//0x16
	GO_TO_SCENE_7,										//0x17
	GO_TO_SCENE_8,										//0x18
	GO_TO_SCENE_9,										//0x19
	GO_TO_SCENE_10,										//0x1A
	GO_TO_SCENE_11,										//0x1B
	GO_TO_SCENE_12,										//0x1C
	GO_TO_SCENE_13,										//0x1D
	GO_TO_SCENE_14,										//0x1E
	GO_TO_SCENE_15,										//0x1F
	RESET_command,										//0x20
	STORE_ACTUAL_LEVEL_IN_DTR0, 			//0x21
  SAVE_PERSISTENT_VARIABLES,				//0x22
  SET_OPERATING_MODE, 							//0x23		//(DTR0)
	RESET_MEMORY_BANK,								//0x24		//(DTR0)
	IDENTIFY_DEVICE,									//0x25
	NO_COMMAND_DEFINED,								//0x26
	NO_COMMAND_DEFINED,								//0x27
	NO_COMMAND_DEFINED,								//0x28
	NO_COMMAND_DEFINED,								//0x29
	SET_MAX_LEVEL,										//0x2A		//(DTR0)
	SET_MIN_LEVEL,										//0x2B		//(DTR0)
	SET_SYSTEM_FAILURE_LEVEL,					//0x2C		//(DTR0)
	SET_POWER_ON_LEVEL,								//0x2D		//(DTR0)
	SET_FADE_TIME,										//0x2E		//(DTR0)
	SET_FADE_RATE,										//0x2F		//(DTR0)
	SET_EXTENDED_FADE_RATE,						//0x30		//(DTR0)
	NO_COMMAND_DEFINED,								//0x31
	NO_COMMAND_DEFINED,								//0x32
	NO_COMMAND_DEFINED,								//0x33
	NO_COMMAND_DEFINED,								//0x34
	NO_COMMAND_DEFINED,								//0x35
	NO_COMMAND_DEFINED,								//0x36
	NO_COMMAND_DEFINED,								//0x37
	NO_COMMAND_DEFINED,								//0x38
	NO_COMMAND_DEFINED,								//0x39
	NO_COMMAND_DEFINED,								//0x3A
	NO_COMMAND_DEFINED,								//0x3B
	NO_COMMAND_DEFINED,								//0x3C
	NO_COMMAND_DEFINED,								//0x3D
	NO_COMMAND_DEFINED,								//0x3E
	NO_COMMAND_DEFINED,								//0x3F
	SET_SCENE_0,											//0x40		//(DTR0)
  SET_SCENE_1,											//0x41		//(DTR0)
  SET_SCENE_2,											//0x42		//(DTR0)
  SET_SCENE_3,										  //0x43		//(DTR0)
  SET_SCENE_4,											//0x44		//(DTR0)
  SET_SCENE_5,											//0x45		//(DTR0)
  SET_SCENE_6,											//0x46		//(DTR0)
  SET_SCENE_7,											//0x47		//(DTR0)
  SET_SCENE_8,											//0x48		//(DTR0)
  SET_SCENE_9,											//0x49		//(DTR0)
  SET_SCENE_10,											//0x4A		//(DTR0)
  SET_SCENE_11,											//0x4B		//(DTR0)
  SET_SCENE_12,											//0x4C		//(DTR0)
  SET_SCENE_13,											//0x4D		//(DTR0)
  SET_SCENE_14,											//0x4E		//(DTR0)
  SET_SCENE_15,											//0x4F		//(DTR0)
  REMOVE_FROM_SCENE_0,							//0x50
  REMOVE_FROM_SCENE_1,							//0x51
  REMOVE_FROM_SCENE_2,							//0x52
  REMOVE_FROM_SCENE_3,							//0x53
  REMOVE_FROM_SCENE_4,							//0x54
  REMOVE_FROM_SCENE_5,							//0x55
  REMOVE_FROM_SCENE_6,							//0x56
  REMOVE_FROM_SCENE_7,							//0x57
  REMOVE_FROM_SCENE_8,							//0x58
  REMOVE_FROM_SCENE_9,							//0x59
  REMOVE_FROM_SCENE_10,							//0x5A
  REMOVE_FROM_SCENE_11,							//0x5B
  REMOVE_FROM_SCENE_12,							//0x5C
  REMOVE_FROM_SCENE_13,							//0x5D
  REMOVE_FROM_SCENE_14,							//0x5E
  REMOVE_FROM_SCENE_15,							//0x5F
  ADD_TO_GROUP_0,										//0x60
  ADD_TO_GROUP_1,										//0x61
  ADD_TO_GROUP_2,										//0x62
  ADD_TO_GROUP_3,										//0x63
  ADD_TO_GROUP_4,										//0x64
  ADD_TO_GROUP_5,										//0x65
  ADD_TO_GROUP_6,										//0x66
  ADD_TO_GROUP_7,										//0x67
  ADD_TO_GROUP_8,										//0x68
  ADD_TO_GROUP_9,										//0x69
  ADD_TO_GROUP_10,									//0x6A
  ADD_TO_GROUP_11,									//0x6B
  ADD_TO_GROUP_12,									//0x6C
  ADD_TO_GROUP_13,									//0x6D
  ADD_TO_GROUP_14,									//0x6E
  ADD_TO_GROUP_15,									//0x6F
  REMOVE_FROM_GROUP_0,							//0x70
  REMOVE_FROM_GROUP_1,							//0x71
  REMOVE_FROM_GROUP_2,							//0x72
  REMOVE_FROM_GROUP_3,							//0x73
  REMOVE_FROM_GROUP_4,							//0x74
  REMOVE_FROM_GROUP_5,							//0x75
  REMOVE_FROM_GROUP_6,							//0x76
  REMOVE_FROM_GROUP_7,							//0x77
  REMOVE_FROM_GROUP_8,							//0x78
  REMOVE_FROM_GROUP_9,							//0x79
  REMOVE_FROM_GROUP_10,							//0x7A
  REMOVE_FROM_GROUP_11,							//0x7B
  REMOVE_FROM_GROUP_12,							//0x7C
  REMOVE_FROM_GROUP_13,							//0x7D
  REMOVE_FROM_GROUP_14,							//0x7E
  REMOVE_FROM_GROUP_15,							//0x7F
	SET_SHORT_ADDRESS,								//0x80
	ENABLE_WRITE_MEMORY,							//0x81
	NO_COMMAND_DEFINED,								//0x82
	NO_COMMAND_DEFINED,								//0x83
	NO_COMMAND_DEFINED,								//0x84
	NO_COMMAND_DEFINED,								//0x85
	NO_COMMAND_DEFINED,								//0x86
	NO_COMMAND_DEFINED,								//0x87
	NO_COMMAND_DEFINED,								//0x88
	NO_COMMAND_DEFINED,								//0x89
	NO_COMMAND_DEFINED,								//0x8A
	NO_COMMAND_DEFINED,								//0x8B
	NO_COMMAND_DEFINED,								//0x8C
	NO_COMMAND_DEFINED,								//0x8D
	NO_COMMAND_DEFINED,								//0x8E
	NO_COMMAND_DEFINED,								//0x8F
	QUERY_STATUS,											//0x90
	QUERY_CONTROL_GEAR_PRESENT,				//0x91
	QUERY_LAMP_FAILURE,								//0x92
	QUERY_LAMP_POWER_ON,							//0x93
  QUERY_LIMIT_ERROR,								//0x94
  QUERY_RESET_STATE,								//0x95
  QUERY_MISSING_SHORT_ADDRESS,			//0x96
  QUERY_VERSION_NUMBER,							//0x97
  QUERY_CONTENT_DTR0,								//0x98
  QUERY_DEVICE_TYPE,								//0x99
  QUERY_PHYSICAL_MINIMUM,						//0x9A
  QUERY_POWER_FAILURE,							//0x9B
  QUERY_CONTENT_DRT1,								//0x9C
  QUERY_CONTENT_DRT2,								//0x9D
  QUERY_OPERATING_MODE,							//0x9E
  QUERY_LIGHT_SOUERCE_TYPE,					//0x9F
  QUERY_ACTUAL_LEVEL,								//0xA0
  QUERY_MAX_LEVEL,									//0xA1
  QUERY_MIN_LEVEL,									//0xA2
  QUERY_POWER_ON_LEVEL,							//0xA3
  QUERY_SYSTEM_FAILURA_LEVEL,				//0xA4
  QUERY_FADE_TIME_RATE,							//0xA5
  QUERY_MANUFACTURER_SPECIFIC_MODE,	//0xA6
  QUERY_NEXT_DEVICE_TYPE,						//0xA7
  QUERY_EXTENDED_FADE_TIME,					//0xA8
	NO_COMMAND_DEFINED,								//0xA9
  QUERY_CONTROL_GEAR_FAILURE,				//0xAA
	NO_COMMAND_DEFINED,								//0xAB
	NO_COMMAND_DEFINED,								//0xAC
	NO_COMMAND_DEFINED,								//0xAD
	NO_COMMAND_DEFINED,								//0xAE
	NO_COMMAND_DEFINED,								//0xAF
  QUERY_SCENE_0_LEVEL,							//0xB0
  QUERY_SCENE_1_LEVEL,							//0xB1
  QUERY_SCENE_2_LEVEL,							//0xB2
  QUERY_SCENE_3_LEVEL,							//0xB3
  QUERY_SCENE_4_LEVEL,							//0xB4
  QUERY_SCENE_5_LEVEL,							//0xB5
  QUERY_SCENE_6_LEVEL,							//0xB6
  QUERY_SCENE_7_LEVEL,							//0xB7
  QUERY_SCENE_8_LEVEL,							//0xB8
  QUERY_SCENE_9_LEVEL,							//0xB9
  QUERY_SCENE_10_LEVEL,							//0xBA
  QUERY_SCENE_11_LEVEL,							//0xBB
  QUERY_SCENE_12_LEVEL,							//0xBC
  QUERY_SCENE_13_LEVEL,							//0xBD
  QUERY_SCENE_14_LEVEL,							//0xBE
  QUERY_SCENE_15_LEVEL,							//0xBF
  QUERY_GROUPS_0_7,									//0xC0
  QUERY_GROUPS_8_15,								//0xC1
  QUERY_RANDOM_ADDR_H,							//0xC2
  QUERY_RANDOM_ADDR_M,							//0xC3
  QUERY_RANDOM_ADDR_L,							//0xC4
  QUERY_READ_MEM_LOCATION						//0xC5		//(DTR0, DTR1)
	// 0xFF -> QUERY_EXTENDED_VERSION_NUMBER
};

// SPECIAL COMMAND
void (*dali_special_cmd_execute[])(uint16_t data)={
	TERMINATE,
	DTR0_LOAD, 										//(DATA)
	INITIALISE,										//(DEVICE)
	RANDOMISE,
	COMPARE,
	WITHDRAW,
	PING,
	SEARCHADDRH, 									//(DATA)
	SEARCHADDRM, 									//(DATA)
	SEARCHADDRL, 									//(DATA)
	PROGRAM_SHORT_ADDR, 					//(DATA)
	VERIFY_SHORT_ADDR, 						//(DATA)
	QUERY_SHORT_ADDR,
	ENABLE_DEVICE_TYPE, 					//(DATA)
	DTR1_LOAD, 										//(DATA)
	DTR2_LOAD, 										//(DATA)
	WRITE_MEM_LOCATION,						//(DTR1, DTR0, DATA)
	WRITE_MEM_LOCATION_NO_REPLY 	//(DTR1, DTR0, DATA)
};
