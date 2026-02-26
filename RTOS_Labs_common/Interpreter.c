// *************Interpreter.c**************
// Students implement this as part of EE445M Lab 1,2,3,4,5,6 
// high level OS user interface
// Solution to labs 1,2,3,4,5,6
// Runs on MSPM0
// Jonathan W. Valvano 12/29/2025, valvano@mail.utexas.edu
#include <stdint.h>
#include <string.h> 
#include <stdio.h>
#include "../RTOS_Labs_common/OS.h"
#include "../RTOS_Labs_common/ST7735_SDC.h"
#include "../inc/ADC.h"
#include "../RTOS_Labs_common/RTOS_UART.h"
#include "../RTOS_Labs_common/LPF.h"
#include "../RTOS_Labs_common/eDisk.h"
#include "../RTOS_Labs_common/eFile.h"
#include "../RTOS_Labs_common/heap.h"
#include "../RTOS_Labs_common/Interpreter.h"

extern void Lab2();
extern void DFT();
extern void Jitter();


//void Lab1_Results(uint32_t d); // have to declare this in order to call in later

char c;
char str[21];
int j;
int k = 0;
void Interpreter(void) {  

  while (1) {                        // Loop forever

  for (int i = 0; i < 20; i++) {
    str[i] = '\0';
  }

  c = UART_InChar();
  /*
  if (c != '\b') {
    ST7735_OutChar(c);
  }
  */
  
  j = 0;


  while (c != '\r') {
    if (c == '\b' && j > 0) {
      j--;
      str[j] = '\0';
    } else if (c != '\b') {
      str[j] = c;
      j++;
    }
    c = UART_InChar();
    /*
    if (c != '\b') {
      ST7735_OutChar(c);
    } else {
      ST7735_SetCursor(ST7735_GetCursorX() - 1, ST7735_GetCursorY());
      ST7735_OutChar(' ');
      ST7735_SetCursor(ST7735_GetCursorX() - 1, ST7735_GetCursorY());
    }
    UART_OutChar(c);
    */
  }

  if (strcmp(str, "?") == 0) {
    //Commands:
    ST7735_DrawString(ST7735_GetCursorX(), ST7735_GetCursorY(), "Commands:", ST7735_YELLOW);
    ST7735_SetCursor(0, ST7735_GetCursorY() + 1);
    UART_OutString("Commands:\n");

    //Clear
    ST7735_DrawString(ST7735_GetCursorX(), ST7735_GetCursorY(), "clear", ST7735_YELLOW);
    ST7735_SetCursor(0, ST7735_GetCursorY() + 1);
    UART_OutString("clear:\n");

    //Lab 1 Results
    ST7735_DrawString(ST7735_GetCursorX(), ST7735_GetCursorY(), "Lab 1 Results", ST7735_YELLOW);
    ST7735_SetCursor(0, ST7735_GetCursorY() + 1);
    UART_OutString("Lab 1 Results:\n");

    //OS MsTime
    ST7735_DrawString(ST7735_GetCursorX(), ST7735_GetCursorY(), "OS MsTime", ST7735_YELLOW);
    ST7735_SetCursor(0, ST7735_GetCursorY() + 1);
    UART_OutString("OS MsTime:\n");

    //reset timer
    ST7735_DrawString(ST7735_GetCursorX(), ST7735_GetCursorY(), "reset timer", ST7735_YELLOW);
    ST7735_SetCursor(0, ST7735_GetCursorY() + 1);
    UART_OutString("reset timer:\n");
  }

  if (strcmp(str, "clear") == 0) {
    //screen width is 128, height is 160
    ST7735_FillRect(0, 80, 128, 160, ST7735_BLACK);
    ST7735_SetCursor(0, 80);
  }

/*      LAB 1
  if (strcmp(str, "Lab 1 Results") == 0) {
    Lab1_Results(1);
  }
  */
  if (strcmp(str, "OS MsTime") == 0) {
    ST7735_OutUDec(OS_MsTime());
    ST7735_SetCursor(0, ST7735_GetCursorY() + 1);
    UART_OutUDec(OS_MsTime());
    UART_OutString("\n");
  }

  if (strcmp(str, "reset timer") == 0) {
    OS_ClearMsTime();
  }
/*      LAB 2
  if (strcmp(str, "Lab 2 Results") == 0) {
    Lab2();
  }

  if (strcmp(str, "DFT") == 0) {
    DFT();
  }

  if (strcmp(str, "jitter") == 0) {
    Jitter();
  }
*/

  if (strcmp(str, "Lab 3 Results") == 0) {
    Lab3();
  }

  if (strcmp(str, "DFT") == 0) {
    DFT();
  }

   
  }
}
