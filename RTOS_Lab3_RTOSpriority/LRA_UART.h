
#ifndef __LRA_UART_H__
#define __LRA_UART_H__


void UART1_Init(void);
void UART1_OutChar(char data);

void UART2_Init(void);
char UART2_InChar(void);
void UART2_IRQHandler(void);

#endif // __LRA_UART_H__