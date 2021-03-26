/****************************************************************************************************
*                           FUNCIONES DE TEMPORIZACION Y ERRORES DE TIMING                          *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		DALI_functions.c
 * @author 	Javier Riego Barcia
 * @date 		26-Marzo-2021
 * @brief		Headir file for DALI_functions.c
 *****************************************************************************************************
 *
 *
 *****************************************************************************************************
 */
 
 void OFF_command(void);			  		 //0x00
 void UP_command(void);				  		 //0x01
 void DOWN_command(void);			  		 //0x02
 void STEP_UP(void);							   //0x03
 void STEP_DOWN(void);					   	 //0x04
 void RECALL_MAX_LEVEL(void); 	  	 //0x05
 void RECALL_MIN_LEVEL(void); 		   //0x06
 void STEP_DOWN_N_OFF(void);  		   //0x07
 void ON_N_STEP_UP(void);					   //0x08
 void ENABLE_DAPC_SEQUENCE(void);  	 //0x09 
 void GO_TO_LAST_ACTIVE_LEVEL(void); //0x0A

