#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../inc/Timer.h"
#include "LRA_FIFO.h"
#include "LRA_UART.h"


#define PB4 (1<<4)
#define PB1 (1<<1)

uint32_t ReceiveCount;
uint32_t TransmitCount;
/*
// simulates data being sent out
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = PB4; // toggle PB4
    TransmitCount++;
    
    GPIOB->DOUTTGL31_0 = PB4; // toggle PB4
    
    // output 4-frame message
    UART1_OutChar(0x81);
    UART1_OutChar('b');
    UART1_OutChar('c');
    UART1_OutChar('d');
    GPIOB->DOUTTGL31_0 = PB4; // toggle PB4
  }
}
*/

void IO_Init(void) {
    IOMUX->SECCFG.PINCM[PB4INDEX] = 0x81;
    IOMUX->SECCFG.PINCM[PB1INDEX] = 0x81;
    GPIOB->DOE31_0 |= (PB4 | PB1);
}


int LRA_main(void) {
    __disable_irq();
    Clock_Init80MHz(0); // no clock out to pin
    LaunchPad_Init();   // LaunchPad_Init must be called once and before other I/O initializations

    IO_Init();

    UART1_Init();
    UART2_Init();

    TimerG12_IntArm(2666667, 1); // initialize interrupts on TimerG12 at 30 Hz

    char data1,data2,data3,data4;

    ReceiveCount=0; 
    TransmitCount=0;

    __enable_irq();


    while (1) {
        data1 = UART2_InChar();
        if ((data1 & 0x80) == 0x80) { // waits for first frame
            ReceiveCount++;

            GPIOB->DOUTTGL31_0 = PB1; // toggle PB26


            // receive next three frames
            data2 = UART2_InChar();
            data3 = UART2_InChar();
            data4 = UART2_InChar();

        }

    }

}