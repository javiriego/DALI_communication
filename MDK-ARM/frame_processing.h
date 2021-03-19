
#define MAX_RXBUFFER  3
#define HALFDATA_SIZE 8

#define ADDRESS  0
#define DATA1 	 1
#define DATA2		 2

#define LOW  0
#define HIGH 1

extern unsigned short int rxbits;
extern unsigned short int rx_buffer[MAX_RXBUFFER];

void processRxFrame(void);
