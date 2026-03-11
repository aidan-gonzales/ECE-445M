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
#include "eFile.h"

extern void Lab2();
extern void DFT();
extern void Jitter();

extern void Lab4();

extern Sema4_t LCDFree;

#define SUCCESS 0
#define FAIL 1


//void Lab1_Results(uint32_t d); // have to declare this in order to call in later

char c;
char str[21];
int j;
int k = 0;
int validCommand = 0;

void Interpreter(void) {  

  while (1) {                        // Loop forever


    validCommand = 0;
    UART_OutString("\n\n>");

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

      validCommand = 1;

      // Commands:
      UART_OutString("Commands:\n");

      // clear
      UART_OutString("clear\n");

      //os mstime
      UART_OutString("time\n");

      // reset timer
      UART_OutString("reset time");

      /*
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
      */
    }

    if (strcmp(str, "clear") == 0) {
      validCommand = 1;
      OS_bWait(&LCDFree);
      //screen width is 128, height is 160
      ST7735_FillRect(0, 0, 128, 160, ST7735_BLACK);
      ST7735_SetCursor(0, 0);
      OS_bSignal(&LCDFree);
    }

  /*      LAB 1
    if (strcmp(str, "Lab 1 Results") == 0) {
      Lab1_Results(1);
    }
    */
    if (strcmp(str, "time") == 0) {
      validCommand = 1;
      // ST7735_OutUDec(OS_MsTime());
      // ST7735_SetCursor(0, ST7735_GetCursorY() + 1);
      UART_OutUDec(OS_MsTime());
    }

    if (strcmp(str, "reset time") == 0) {
      validCommand = 1;
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

  /*      LAB 3
    if (strcmp(str, "Lab 3 Results") == 0) {
      Lab3();
    }
    

    if (strcmp(str, "dft") == 0) {
      validCommand = 1;
      DFT();
    }
    */

    if (strcmp(str, "lab4") == 0) {
      validCommand = 1;
      Lab4();
    }

    if (strcmp(str, "dft") == 0) {
      validCommand = 1;
      DFT();
    }

    // File system:
    if (str[0] == '\'') {
      char temp[21];
      char name[21];

      int i = 1;
      while (str[i] != ' ' && str[i] != '\0' && i < 21) {
        temp[i - 1] = str[i];
        i++;
      }
      temp[i - 1] = 0;

      i++;
      int nameI = 0;
      while (str[i] != 0) {
        name[nameI] = str[i];
        i++;
        nameI++;
      }
      name[nameI] = 0;

      if (strcmp(temp, "delete") == 0) {
        validCommand = 1;
        OS_bWait(&LCDFree);
        if (eFile_Delete(name)) {
          UART_OutString("failed to delete ");
          UART_OutString(name);
        } else {
          UART_OutString("successfully deleted ");
          UART_OutString(name);
        }

        
        OS_bSignal(&LCDFree);
      }

      if (strcmp(temp, "create") == 0) {
        validCommand = 1;
        OS_bWait(&LCDFree);
        if (eFile_Create(name)) {
          UART_OutString("failed to create ");
          UART_OutString(name);
        } else {
          UART_OutString("successfully created ");
          UART_OutString(name);
        }

        eFile_WOpen(name);
        for (int i = 0; i < 1536; i++) {
          eFile_Write(42);
        }
        eFile_WClose();


        OS_bSignal(&LCDFree);
      }

      if (strcmp(temp, "format") == 0) {
        if (strcmp(name, "disk") == 0) {
          validCommand = 1;
          OS_bWait(&LCDFree);

          if (eFile_Format()) {
            UART_OutString("failed to format disk");
          } else {
            UART_OutString("successfully formatted disk");
          }

          if (eFile_Mount()) {
            UART_OutString("failed to mount disk");
          }

          OS_bSignal(&LCDFree);
        }
      }

      if (strcmp(temp, "mount") == 0) {
        if (strcmp(name, "disk") == 0) {
          validCommand = 1;
          OS_bWait(&LCDFree);
          if (eFile_Mount()) {
            UART_OutString("failed to mount disk");
          } else {
            UART_OutString("successfully mounted disk");
          }
          OS_bSignal(&LCDFree);
        }
      }

      if (strcmp(temp, "unmount") == 0) {
        if (strcmp(name, "disk") == 0) {
          validCommand = 1;
          OS_bWait(&LCDFree);
          if (eFile_Unmount()) {
            UART_OutString("failed to unmount disk");
          } else {
            UART_OutString("successfully unmounted disk");
          }
          OS_bSignal(&LCDFree);
        }
      }

      if (strcmp(temp, "init") == 0) {
        if (strcmp(name, "disk") == 0) {
          validCommand = 1;
          OS_bWait(&LCDFree);
          if (eFile_Init()) {
            UART_OutString("failed to initialize disk");
          } else {
            UART_OutString("successfully initialized disk");
          }
          OS_bSignal(&LCDFree);
        }
      }

      if (strcmp(temp, "ls") == 0) {
        validCommand = 1;

        char *name;
        unsigned long size;
        int totalFiles = 0;

        OS_bWait(&LCDFree);

        if (eFile_DOpen("") == FAIL) {
          UART_OutString("failed to open directory\n");
        } else {
          UART_OutString("Successfully scanned directory.\n");
          UART_OutString("------------------------------------------------\n");

          while (eFile_DirNext(&name, &size) == SUCCESS) {
            UART_OutString(name);
            UART_OutString(" | ");
            UART_OutUDec(size);
            UART_OutString("\n");
            totalFiles++;
          }

          eFile_DClose();

          UART_OutString("------------------------------------------------\n");
          UART_OutString("Files found: ");
          UART_OutUDec(totalFiles);
          UART_OutString(" / 32");
        }

        OS_bSignal(&LCDFree);

        /*
        validCommand = 1;

        char *namesArr[32];
        unsigned long sizeArr[32];

        int totalFiles = 0;

        OS_bWait(&LCDFree);

        if (eFile_ListFiles(namesArr, sizeArr, &totalFiles)) {
          UART_OutString("failed to scan directory");
        } else {
          UART_OutString("Successfully scanned directory. Files found: ");
          UART_OutUDec(totalFiles);
          UART_OutString(" / 32\n");
          UART_OutString("------------------------------------------------\n");
          for (int i = 0; i < totalFiles; i++) {
            UART_OutString(namesArr[i]);
            UART_OutString(" | ");
            UART_OutUDec(sizeArr[i]);
            UART_OutString("\n");
          }
          UART_OutString("------------------------------------------------\n");
        }
        OS_bSignal(&LCDFree);
        */
      }

      if (strcmp(temp, "print") == 0) {
        validCommand = 1;
        OS_bWait(&LCDFree);

        if (eFile_ROpen(name)) {
          UART_OutString("unable to open file");
        } else {
          char data;
          UART_OutString("reading file contents:\n");
          UART_OutString("------------------------------------------------\n");
          while (eFile_ReadNext(&data) == SUCCESS) {
            UART_OutChar(data);
            //UART_OutString("\n");
          }
          UART_OutString("------------------------------------------------\n");
          UART_OutString("end of file");
        }

        if (eFile_RClose()) {
          UART_OutString("\nunable to close file");
        }
        OS_bSignal(&LCDFree);
      }
      
    }

    if (!validCommand) {
      UART_OutString("Invalid Command");
    }
    
  }
}
