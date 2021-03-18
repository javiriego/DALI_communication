/* DEFINICIONES GLOBALES ****************************************************************************/
#define IDLE_STATE		1
#define ACTIVE_STATE	0

#define WAITING_FOR_FALL_EDGE	0
#define RECEIVED_FALL_EDGE		1

/* EXTERNALIZACION DE VARIABLES *********************************************************************/
extern unsigned char _powerdown, _stopcond;
extern unsigned char bus_status;

/* DEFINICION DE FUNCIONES UTILIZADAS EXTERNAMENTE **************************************************/
//Controlador de BusPower Down
void power_down_handler(void);
//Controlador de la condicion de parada
void stop_condition_handler(void);
//Detección del primer flanco de una trama
void bus_status_fall_edge(void);
