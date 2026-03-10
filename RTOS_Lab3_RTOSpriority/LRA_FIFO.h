
#ifndef __LRA_FIFO_H__
#define __LRA_FIFO_H__

#include <ti/devices/msp/msp.h>

void Fifo1_Init(void);
uint32_t Fifo1_Put(char data);
char Fifo1_Get(void);

#endif // __LRA_FIFO_H__