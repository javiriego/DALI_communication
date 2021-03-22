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

extern unsigned short int rxbits;
extern unsigned short int rx_buffer[MAX_RXBUFFER];
extern uint8_t	send_twice_frame;

void processRxFrame(void);
