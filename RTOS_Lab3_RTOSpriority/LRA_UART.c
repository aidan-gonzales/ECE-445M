#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "LRA_UART.h"
#include "../inc/Clock.h"
#include "LRA_FIFO.h"

// power Domain PD0
// for 80MHz bus clock, UART clock is ULPCLK 40MHz
// initialize UART1 for 2000 baud rate
// blind, no synchronization on transmit
void UART1_Init(void){
    UART1->GPRCM.RSTCTL = 0xB1000003;
      UART1->GPRCM.PWREN = 0x26000001;
      Clock_Delay(24); // time for uart to power up
      IOMUX->SECCFG.PINCM[PA8INDEX]  = 0x00000082;
      UART1->CLKSEL = 0x08; // bus clock
      UART1->CLKDIV = 0x00; // no divide
      UART1->CTL0 &= ~0x01; // disable UART0
      UART1->CTL0 = 0x00020018;
     // assumes an 80 MHz bus clock
      UART1->IBRD = 1250;//   divider = 1250 + 0/64 = 1250
      UART1->FBRD = 0; // baud =2,500,000/1250 = 2000
      UART1->LCRH = 0x00000030;
      UART1->CTL0 |= 0x01; // enable UART0

}

//------------UART1_OutChar------------
// Output 8-bit to serial port
// blind synchronization
// 10 bit frame, 2000 baud, 5ms per frame
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART1_OutChar(char data){ // simply output data to transmitter without waiting or checking status
    UART1->TXDATA = data;
}



uint32_t LostData;
void Fifo1_Init(void);
// power Domain PD0
// for 80MHz bus clock, UART clock is ULPCLK 40MHz
// initialize UART2 for 2000 baud rate
// no transmit, interrupt on receive timeout, RTOUT
void UART2_Init(void){
    UART2->GPRCM.RSTCTL = 0xB1000003;
    UART2->GPRCM.PWREN = 0x26000001;
    Clock_Delay(24); // time for uart to power up
    IOMUX->SECCFG.PINCM[PA22INDEX]  = 0x00040082;
    Fifo1_Init();
    UART2->CLKSEL = 0x08; // bus clock
    UART2->CLKDIV = 0x00; // no divide
    UART2->CTL0 &= ~0x01; // disable UART2
    UART2->CTL0 = 0x00020018;
   // assumes an 80 MHz bus clock
    UART2->IBRD = 1250;//   divider = 1250 + 0/64 = 1250
    UART2->FBRD = 0; // baud =2,500,000/1250 = 2000
    UART2->LCRH = 0x00000030;
    UART2->CPU_INT.IMASK = 1;
    // bit 11 TXINT
    // bit 10 RXINT             Interrupt only on receiver timeout RTOUT (no TXINT, no RXINT)
    // bit 0  Receive timeout
    UART2->IFLS = 0x0422;
    // bits 11-8 RXTOSEL receiver timeout select 4 (0xF highest)
    // bits 6-4  RXIFLSEL 2 is greater than or equal to half
    // bits 2-0  TXIFLSEL 2 is less than or equal to half
    NVIC->ICPR[0] = 1<<14; // UART2 is IRQ 14
    NVIC->ISER[0] = 1<<14;
    NVIC->IP[3] = (NVIC->IP[3]&(~0xFF000000))|(2<<22);    // priority (bits 23,22)
    UART2->CTL0 |= 0x01; // enable UART2

}
//------------UART2_InChar------------
// Get new serial port receive data from FIFO1
// Input: none
// Output: Return 0 if the FIFO1 is empty
//         Return nonzero data from the FIFO1 if available
char UART2_InChar(void){
    return Fifo1_Get();
}

/*
void UART2_IRQHandler(void){
    uint32_t status;
    char letter;
  // acknowledge RTOUT
  //GPIOB->DOUTTGL31_0 = 
    // read all data and put in FIFO1
    status = UART2->CPU_INT.IIDX; // reading clears bit in RIS
      if((status == 0x01) || (status == 0x0B)){       // 0x01 receive timeout RTOUT
          while(((UART2->STAT&0x04) == 0)){
              letter = UART2->RXDATA;
              Fifo1_Put(letter);
          }
      }
}
*/