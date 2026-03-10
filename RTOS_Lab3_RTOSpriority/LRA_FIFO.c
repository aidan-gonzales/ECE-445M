#include "LRA_FIFO.h"

#define SIZE 31
int8_t Put;
int8_t Get;
char FIFO[SIZE];

int8_t FULL;
int8_t EMPTY;

// *********** Fifo1_Init**********
// Initializes a software FIFO1 of a
// fixed size and sets up indexes for
// put and get operations
void Fifo1_Init(void){ //Complete this
    Put = Get = 0;
    FULL = 0;
    EMPTY = 1;
}

// *********** Fifo1_Put**********
// Adds an element to the FIFO1
// Input: data is character to be inserted
// Output: 1 for success, data properly saved
//         0 for failure, FIFO1 is FULL
//int8_t COUNTER = 0;

uint32_t Fifo1_Put(char data) {
    if (FULL) return 0;
    if (EMPTY) EMPTY = 0;
    FIFO[Put] = data;
    Put = (Put + 1) % SIZE; //Increments Put circularly
    if (Put == Get) FULL = 1;
    return 1;
}

// *********** Fifo1_Get**********
// Gets an element from the FIFO1
// Input: none
// Output: If the FIFO1 is EMPTY return 0
//         If the FIFO1 has data, remove it, and return it

char Fifo1_Get(void){
    if (EMPTY) return 0;
    if (FULL) FULL = 0;
    char data = FIFO[Get];
    Get = (Get + 1) % SIZE; //Increments Get circularly
    if (Get == Put) EMPTY = 1;
    return data;
}