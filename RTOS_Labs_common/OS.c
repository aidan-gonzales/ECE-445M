// *************os.c**************
// ECE445M Labs 1, 2, 3, 4, 5 and 6
// Starter to labs 1,2,3,4,5,6
// high level OS functions
// Students will implement these functions as part of Lab
// Runs on MSPM0
// Jonathan W. Valvano 
// January 10, 2026, valvano@mail.utexas.edu


#include <stdint.h>
#include <stdio.h>
#include <ti/devices/msp/msp.h>
#include "file.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/Timer.h"
#include "../RTOS_Labs_common/OS.h"
#include "../RTOS_Labs_common/RTOS_UART.h"
#include "../RTOS_Labs_common/SPI.h"
#include "../RTOS_Labs_common/ST7735_SDC.h"
#include "../RTOS_Labs_common/eFile.h"
#include "../RTOS_Labs_common/heap.h"

// Hardware interrupt priorities
//   Priority 0: Periodic threads 
//   Priority 1: Input/output interrupts like UART and edge triggered 
//   Priority 2: 1000 Hz periodic event to implement OS_MsTime and sleep using TimerG8
//   Priority 2: SysTick for running the scheduler
//   Priority 3: PendSV for context switch 

// *****************Timers******************
// SysTick for running the scheduler
// Use TimerG0 is used for SDC timeout
// Use TimerG7 for background periodic threads
// Use TimerG8 is interrupts at 1000Hz to implement OS_MsTime, and sleeping
// Use TimerG12 for 32-bit OS_Time, free running (no interrupts)
// Use TimerA0 for PWM outputs to motors
// Use TimerA1 for PWM outputs to motors
// Use TimerG6 for Lab 1 and then for PWM to servo steering

void OSDisableInterrupts(void);
void OSEnableInterrupts(void);
long StartCritical(void);
void EndCritical(long);
#define  OSCRITICAL_ENTER() { sr=StartCritical(); }
#define  OSCRITICAL_EXIT()  { EndCritical(sr); }

#define TogglePB22() (GPIOB->DOUTTGL31_0 = (1<<22))
#define TogglePA16() (GPIOA->DOUTTGL31_0 = (1<<16))

#define SYSTICKSET (0x1 << 26)
#define PENDSVSET (0x1 << 28)

//tcbs and stacks defined in header file

volatile uint32_t TimeMs; // in ms      just added volatile

TCB_t *RunPt = NULL;
TCB_t *NextThreadPt = NULL;
TCB_t *LastPt = NULL;       // no longer used, caused too many errors

uint8_t used_tcbs[MAX_THREADS];

TCB_t *delta_queue_head = NULL; // TIMG8 ISR time went from 6.125us to 1.167us with this

s2_thread_t s2_threads[2]; // 2 is the max amount of s2 threads
uint8_t num_s2_threads = 0; // number of active s2 threads

periodic_thread_t periodic_threads[4]; // 4 is the max amount of period threads
uint8_t num_periodic_threads = 0; // number of active periodic threads

TCB_t tcbs[MAX_THREADS];
int32_t stacks[MAX_THREADS][STACK_SIZE];


//fifo globals
#define MAX_FIFO_SIZE 256
uint8_t GetI;
uint8_t PutI;
uint16_t fifo_size;
uint32_t fifo[MAX_FIFO_SIZE];
Sema4_t DataAvailable;


// priority level TCB pointers
TCB_t *level0 = NULL;
TCB_t *level1 = NULL;
TCB_t *level2 = NULL;
TCB_t *level3 = NULL;

// periodic priority level pointers
periodic_thread_t *periodic_head = NULL;
periodic_thread_t *periodic_tail = NULL;




// ******** OS_ClearMsTime ************
// sets the system time to zero (solve for Lab 1), and start a periodic interrupt
// Inputs:  none
// Outputs: none
// You are free to change how this works
void OS_ClearMsTime(void){
  // put Lab 1 solution here
  TimeMs = 0;

  // for some reason this has to be different than TIMG7 prescale. They both have the same frequency, but diff prescale
  TimerG8_IntArm(40000, 1, 2); //gives us 1000 Hz and priority level of 2
};


// ******** OS_MsTime ************
// reads the current time in msec (solve for Lab 1)
// Inputs:  none
// Outputs: time in ms units
// You are free to select the time resolution for this function
// For Labs 2 and beyond, it is ok to make the resolution to match the first call to OS_AddPeriodicThread
uint32_t OS_MsTime(void){
  // put Lab 1 solution here
  return TimeMs;
};

void StartOS(void); // implemented in osasm.s

/*
void OS_Schedule() {
  LastPt = RunPt;
  TCB_t *tempPt = RunPt->next;
  //TogglePA16();

  uint32_t currentTime = OS_MsTime();

  //scheduler will decide which thread to go to next
  while (tempPt->sleep_state) {
    if (currentTime >= tempPt->sleep_until) {
      tempPt->sleep_state = 0;
      break;
    }
    LastPt = tempPt;
    tempPt = tempPt->next;
  }

  NextThreadPt = tempPt;

  // resets the the counter to the load value (in the case that we manually triggered SysTick)
  SysTick->VAL = 0;
}
*/

//------------------------------------------------------------------------------
//  Systick Interrupt Handler
//  SysTick interrupt happens every 2 ms
// used for preemptive foreground thread switch
// ------------------------------------------------------------------------------
void SysTick_Handler(void) { 


  // works without separate priority level linked lists

  TogglePB22();
/*
  long sr = StartCritical();

  TCB_t *candidate = RunPt;
  TCB_t *going_around = RunPt->next;

  while (going_around != RunPt) {
    if (!(going_around->sleep_state) && going_around->priority >= candidate->priority) {
      candidate = going_around;
    }
    going_around = going_around->next;
  }

  if (candidate == RunPt) {
    EndCritical(sr);
    TogglePB22();
    SysTick->VAL = 0;
    return;
  }

  NextThreadPt = candidate;
  SCB->ICSR |= PENDSVSET; // PendSV is now pending
  SysTick->VAL = 0;
  EndCritical(sr);
*/



  // should work with different priority level linked lists
  long sr = StartCritical();

  TCB_t *candidate = RunPt;
  TCB_t *going_around = RunPt->next;

  if (level0 != NULL) {
    level0 = level0->next;
    NextThreadPt = level0;
  } else if (level1 != NULL) {
    level1 = level1->next;
    NextThreadPt = level1;
  } else if (level2 != NULL) {
    level2 = level2->next;
    NextThreadPt = level2;
  } else {
    level3 = level3->next;
    NextThreadPt = level3;
  }

  if (NextThreadPt == RunPt) {
    EndCritical(sr);
    TogglePB22();
    SysTick->VAL = 0;
    return;
  }

  SCB->ICSR |= PENDSVSET; // PendSV is now pending
  SysTick->VAL = 0;
  EndCritical(sr);


/*      LAB 2 IMPLEMENTATION
  long sr = StartCritical();
  TCB_t *candidate = RunPt->next;

  while (candidate->sleep_state) {
    if (candidate == RunPt) { // everyone is sleeping, no thread switch
      EndCritical(sr);
      TogglePB22();
      SysTick->VAL = 0;
      return;
    }
    candidate = candidate->next;
  }


  if (candidate != RunPt) {
    NextThreadPt = candidate;
    //PendSV will perform the thread switch
      SCB->ICSR |= PENDSVSET; // PendSV is now pending
  }

  // resets the the counter to the load value (in the case that we manually triggered SysTick)
  SysTick->VAL = 0;

  EndCritical(sr);
*/


/*

    long sr = StartCritical();
    LastPt = RunPt;
    while (LastPt->next->sleep_state) {
      LastPt = LastPt->next;
    }

    // resets the the counter to the load value (in the case that we manually triggered SysTick)
    SysTick->VAL = 0;
    
    if (LastPt->next != RunPt) {
      NextThreadPt = LastPt->next;
      //PendSV will perform the thread switch
      SCB->ICSR |= PENDSVSET; // PendSV is now pending
    }
    EndCritical(sr);
  
  */


  TogglePB22();
  
} // end SysTick_Handler


uint32_t OS_LockScheduler(void){
 uint32_t old = SysTick->CTRL;
  SysTick->CTRL= 5;
  return old;
}
void OS_UnLockScheduler(uint32_t previous){
  SysTick->CTRL = previous;
}


//
//@details  Initialize operating system, disable interrupts until OS_Launch.
//Initialize OS controlled I/O: serial, ADC, systick, LaunchPad I/O and timers.
// Interrupts not yet enabled.
 // @param  none
 // @return none
 //@brief  Initialize OS
//
void OS_Init(void){
  // put Lab 2 (and beyond) solution here

  OSDisableInterrupts();

  //set SysTick and PendSV priorities
   NVIC_SetPriority(PendSV_IRQn, 3); // lowest priority
   NVIC_SetPriority(SysTick_IRQn, 2); // second lowest priority

   //configure SysTick scheduler
   SysTick->LOAD = 159999; // 160000 cycles * 12.5ns = 2ms
   SysTick->VAL = 0; // write to clear current value in SysTick

/*
  //ADC/DAC init
  ADC0_Init(3,ADCVREF_VDDA);  // PA24 Center ADC0_3
  LPF_Init7(2048,16);
  DAC_Init();
  DAC_Out(2048); // 1.25V
  ADC1_Init(0,ADCVREF_VDDA);  // PA15 ADC1_0, also DACout
  */

  //LDC init
  ST7735_InitR(INITR_BLACKTAB); //INITR_REDTAB for AdaFruit, INITR_BLACKTAB for SPI HiLetgo ST7735R
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_SetCursor(0, 0);

  //UART init for interpreter
  UART_Init(1); // hardware priority 1

  //Enable Interrupts occurs at OS_Launch
}

// ******** OS_InitSemaphore ************
// initialize semaphore 
// input:  pointer to a semaphore
// output: none
void OS_InitSemaphore(Sema4_t *semaPt, int32_t value){
  // put Lab 2 (and beyond) solution here
  semaPt->Value = value;

}; 


// ******** OS_Wait ************
// decrement semaphore 
// Lab2 spinlock
// Lab3 block if less than zero
// input:  pointer to a counting semaphore
// output: none
//
// semaPt > 0: semaPt = number of available resources
// semaPt == 0: no resources available
// semaPt < 0: semaPt = number of threads waiting
void OS_Wait(Sema4_t *semaPt){long sr;
  // put Lab 2 (and beyond) solution here
  sr = StartCritical();

  while(semaPt->Value <= 0) { // this is always atomic. (__disable_irq() is always called before we check sema4)
  EndCritical(sr);
  OS_Suspend(); // cooperative semaphore
  sr = StartCritical();
  }
  semaPt->Value = semaPt->Value - 1;
  EndCritical(sr);

}; 

// ******** OS_Signal ************
// increment semaphore 
// Lab2 spinlock
// Lab3 wakeup blocked thread if appropriate 
// input:  pointer to a counting semaphore
// output: none
//
// signals that this thread is giving the resource back
void OS_Signal(Sema4_t *semaPt){long sr;
  // put Lab 2 (and beyond) solution here
  OSCRITICAL_ENTER();
  semaPt->Value = semaPt->Value + 1;
  OSCRITICAL_EXIT();  
}; 

// ******** OS_bWait ************
// Lab2 spinlock, set to 0
// Lab3 block if less than zero
// input:  pointer to a binary semaphore
// output: none
void OS_bWait(Sema4_t *semaPt){long sr;
  // put Lab 2 (and beyond) solution here
  sr = StartCritical();

  while(semaPt->Value == 0) {
  EndCritical(sr);
  OS_Suspend(); // cooperative semaphore
  sr = StartCritical();
  }
  semaPt->Value = 0;
  EndCritical(sr);

}; 

// ******** OS_bSignal ************
// Lab2 spinlock, set to 1
// Lab3 wakeup blocked thread if appropriate 
// input:  pointer to a binary semaphore
// output: none
void OS_bSignal(Sema4_t *semaPt){long sr;
  // put Lab 2 (and beyond) solution here
  OSCRITICAL_ENTER();
  semaPt->Value = 1;
  OSCRITICAL_EXIT();

}; 


// returns -1 if all tcbs are used. Otherwise, returns index of next free tcb
int get_next_free_tcb(void) {
  for (int i = 0; i < MAX_THREADS; i++) {
    if (used_tcbs[i] == 0) {
      used_tcbs[i] = 1;
      return i;
    }
  }

  return -1;
}

// ******** OS_AddThread *************** 
// add a foreground thread to the scheduler
// Inputs: pointer to a void/void foreground task
//         number of bytes allocated for its stack
//         priority, 0 is highest, 255 is the lowest
// Priorities are relative to other foreground threads
// Outputs: 1 if successful, 0 if this thread can not be added
// stack size must be divisable by 8 (aligned to double word boundary)
// In Lab 2, you can ignore both the stackSize and priority fields
// In Lab 3, you can ignore the stackSize fields
// In Lab 4, the stackSize can be 128, 256, or 512 bytes

int OS_AddProcessThread(void(*task)(void), 
   uint32_t stackSize, uint32_t priority, uint32_t pid){
	   return 0;
   }
int OS_AddThread(void(*task)(void), 
   uint32_t stackSize, uint32_t priority){ 

  long sr = StartCritical();
  int idnum = get_next_free_tcb();
  EndCritical(sr);

  if (idnum == -1) {
    return 0;
  }

  // put Lab 2 (and beyond) solution here

  int32_t *stackpt = &stacks[idnum][STACK_SIZE];

  //PSR
  stackpt--;
  *stackpt = 0x01000000; // 1 in bit 24 is for the T bit (thumb bit must be set)

  //PC
  stackpt--;
  *stackpt = (int32_t)task; // task is the location of the first PC

  //LR
  stackpt--;
  *stackpt = 0x0;

  //R12
  stackpt--;
  *stackpt = 0x0;

  //R3
  stackpt--;
  *stackpt = 0x0;

  //R2
  stackpt--;
  *stackpt = 0x0;

  //R1
  stackpt--;
  *stackpt = 0x0;

  //R0
  stackpt--;
  *stackpt = 0x0;

  //R7
  stackpt--;
  *stackpt = 0x0;

  //R6
  stackpt--;
  *stackpt = 0x0;

  //R5
  stackpt--;
  *stackpt = 0x0;

  //R4
  stackpt--;
  *stackpt = 0x0;

  tcbs[idnum].id = idnum;
  tcbs[idnum].sp = stackpt;
  tcbs[idnum].sleep_state = 0;
  tcbs[idnum].blocked_state = 0;
  //tcbs[idnum].sleep_until = 0;
  tcbs[idnum].priority = priority;

  tcbs[idnum].delta = 0;
  tcbs[idnum].sleep_next = NULL;


/*          // LAB 2 IMPLEMENTATION
  sr = StartCritical();

  if (idnum == 0) { // very first thread
    tcbs[idnum].next = &tcbs[idnum];
  } else if (RunPt == NULL) { // before OS started
    tcbs[idnum - 1].next = &tcbs[idnum];
    tcbs[idnum].next = &tcbs[0];
  } else { // after OS started
    tcbs[idnum].next = RunPt->next;
    RunPt->next = &tcbs[idnum];
  }

  EndCritical(sr);
*/

  sr = StartCritical();

          // LAB 3 IMPLEMENTATION
  if (priority == 0) {      // priority 0
    if (level0 == NULL) {
      level0 = &tcbs[idnum];
      tcbs[idnum].next = &tcbs[idnum];
    } else {
      tcbs[idnum].next = level0->next;
      level0->next = &tcbs[idnum];
    }
  } else if (priority == 1) {      // priority 1
    if (level1 == NULL) {
      level1 = &tcbs[idnum];
      tcbs[idnum].next = &tcbs[idnum];
    } else {
      tcbs[idnum].next = level1->next;
      level1->next = &tcbs[idnum];
    }
  } else if (priority == 2) {      // priority 2
    if (level2 == NULL) {
      level2 = &tcbs[idnum];
      tcbs[idnum].next = &tcbs[idnum];
    } else {
      tcbs[idnum].next = level2->next;
      level2->next = &tcbs[idnum];
    }
  } else {                          // priority 3
    if (level3 == NULL) {
      level3 = &tcbs[idnum];
      tcbs[idnum].next = &tcbs[idnum];
    } else {
      tcbs[idnum].next = level3->next;
      level3->next = &tcbs[idnum];
    }
  }

  EndCritical(sr);


/*
  // look into not using LastPt         FIXME

  if (LastPt == NULL) { // very first thread added
    LastPt = &tcbs[idnum];
    LastPt->next = &tcbs[idnum];
  } else if (RunPt == NULL) { // other threads added before OS_Launch
    LastPt->next = &tcbs[idnum];
    LastPt = LastPt->next;
    LastPt->next = &tcbs[0];
  } else { // threads added while OS is running
    LastPt->next = &tcbs[idnum];
    LastPt = LastPt->next;
    LastPt->next = RunPt;
  }

*/


  return 1; // thread added successfully
}

// ******** OS_AddProcess *************** 
// add a process with foregound thread to the scheduler
// Inputs: pointer to process text (code) segment, entry point at top
//         pointer to process data segment
//         number of bytes allocated for its stack
//         priority (0 is highest)
// Outputs: 1 if successful, 0 if this process can not be added
// This function will be needed for Lab 5
// In Labs 2-4, this function can be ignored
int OS_AddProcess(void *text, void *data, uint32_t stackSize, uint32_t priority){ 
  
  return 0;
}


int OS_LoadProgram(char *name, uint32_t priority){
  
  return 0;
}



// ******** OS_Id *************** 
// returns the thread ID for the currently running thread
// Inputs: none
// Outputs: Thread ID, number greater than zero 
uint32_t OS_Id(void){
  // put Lab 2 (and beyond) solution here
    return RunPt->id;
}



uint32_t lcm2(uint32_t n1,uint32_t n2){
  uint32_t n;
  if(n1 > n2){
    n = n1;
  }else{
    n = n2;
  }
  while( ((n % n1) != 0) || ((n % n2) != 0) ){
    n++;
  }
  return n;
}

uint32_t lcm3(uint32_t n1,uint32_t n2,uint32_t n3){
  return lcm2(lcm2(n1,n2),n3);
}
uint32_t lcm4(uint32_t n1,uint32_t n2,uint32_t n3,uint32_t n4){
  return lcm2(lcm2(n1,n2),lcm2(n3,n4));
}
uint32_t lcm5(uint32_t n1,uint32_t n2,uint32_t n3,uint32_t n4,uint32_t n5){
  return lcm2(lcm2(n1,n2),lcm3(n3,n4,n5));
}

//******** OS_AddPeriodicThread *************** 
// Add a background periodic thread
// typically this function receives the highest priority
// Inputs: task is pointer to a void/void background function
//         period in ms
//         priority 0 is the highest, 3 is the lowest
// Priorities are relative to other background periodic threads
// Outputs: 1 if successful, 0 if this thread can not be added
// You are free to select the resolution of period
// It is assumed that the user task will run to completion and return
// This task can not spin, block, loop, sleep, or kill
// This task can call OS_Signal  OS_bSignal   OS_AddThread
// This task does not have a Thread ID
// In lab 2, this command will be called 0 or 1 times
// In lab 3, this command will be called 0 to 4 times
// In labs 3-7, there will be 0 to 4 background periodic threads, and this priority field 
//           determines the relative priority of these threads
// For Lab 3, it ok to make reasonable limits to reduce the complexity. E.g.,
//  - You can assume there are 0 to 4 background periodic threads
//  - You can assume the priorities are sequential 0,1,2,3,4
//  - You can assume a maximum thread execution time, e.g., 50us
//  - You can assume a slowest period, e.g., 50ms
//  - You can limit possible periods, e.g., 1,2,4,5,10,20,25,50ms
//  - You can assume (E0/T0)+(E1/T1)+(E2/T2)+(E3/T3) is much less than 1 

int OS_AddPeriodicThread(void(*task)(void), 
   uint32_t period, uint32_t priority){
  // put Lab 2 (and beyond) solution here
  long sr;
  if (num_periodic_threads == 0) {
    sr = StartCritical();
    TimerG7_IntArm(40000, 1, 0); // 1000 Hz frequency with highest priority level (prescale is 1 because calc is wrong in init)
    EndCritical(sr);
  } else if (num_periodic_threads == 4) {
    return 0; // max periodic threads
  }

  uint8_t index;
  sr = StartCritical();
  for (uint8_t i = 0; i < 4; i++) {
    if (periodic_threads[i].active == 0) {
      periodic_threads[i].task = task;
      periodic_threads[i].period = period;
      periodic_threads[i].delta = period;
      periodic_threads[i].priority = priority;
      periodic_threads[i].active = 1;
      num_periodic_threads++;
      index = i;
      break;
    }
  }
  //EndCritical(sr);

  if (periodic_head == NULL) {
    periodic_head = &periodic_threads[index];
    periodic_head->next = &periodic_threads[index];
    periodic_tail = periodic_head;
  } else {
    periodic_thread_t *current_node = periodic_head;
    periodic_thread_t *previous_node = NULL;
    if (periodic_threads[index].priority < current_node->priority) {
      periodic_threads[index].next = current_node;
      periodic_head = &periodic_threads[index];
      periodic_tail->next = periodic_head;
      EndCritical(sr);
      return 1;
    }

    previous_node = current_node;
    current_node = current_node->next;

    while ((current_node != periodic_head) && (periodic_threads[index].priority >= current_node->priority)) {
      previous_node = current_node;
      current_node = current_node->next;
    }

    previous_node->next = &periodic_threads[index];
    periodic_threads[index].next = current_node;

    if (periodic_threads[index].next == periodic_head) {
      periodic_tail = &periodic_threads[index];
    }
  }
  
  EndCritical(sr);
  return 1;
}

void TIMG7_IRQHandler(void){
  if((TIMG7->CPU_INT.IIDX) == 1){ // this will acknowledge

    // change this to linked list for priority scheduler


/*      LAB 2 IMPLEMENTATION
    for (uint8_t i = 0; i < 4; i++) {
      if (periodic_threads[i].active) {
        if (periodic_threads[i].delta == 0) {
          periodic_threads[i].task();
          periodic_threads[i].delta = periodic_threads[i].period;
        } else {
          periodic_threads[i].delta--;
        }
      } 
    }
    */
    uint8_t firstLoop = 1;
    periodic_thread_t *tempPt = periodic_head;
    
    while ((tempPt != periodic_head) || firstLoop) {
      firstLoop = 0;
      if (tempPt->delta == 0) {
        tempPt->task();
        tempPt->delta = tempPt->period;
      } else {
        tempPt->delta--;
      }

      tempPt = tempPt->next;
    }
    
  }
}  

//increments TimeMs
//implement sleep checks in here
void TIMG8_IRQHandler(void){
  if((TIMG8->CPU_INT.IIDX) == 1){ // this will acknowledge
    //TogglePB22();
    TimeMs++;
    // uint32_t currentTime = OS_MsTime();
    // for (int i = 0; i < MAX_THREADS; i++) {
    //   if (used_tcbs[i] && tcbs[i].sleep_state && (currentTime >= tcbs[i].sleep_until)) { // checks if used, sleeping, and sleep timer has past
    //   tcbs[i].sleep_state = 0;
    //   }
    // }

    if (delta_queue_head != NULL) {
      delta_queue_head->delta--;
      while ((delta_queue_head != NULL) && (delta_queue_head->delta == 0)) {
        // wake up the thread
        delta_queue_head->sleep_state = 0;
        
        
        // start critical if priority is not highest here
        TCB_t *curr = delta_queue_head;
        delta_queue_head = delta_queue_head->sleep_next;
        
        // LAB 3 IMPLEMENTATION
        if (curr->priority == 0) {      // priority 0
          if (level0 == NULL) {
            level0 = curr;
            curr->next = curr;
          } else {
            curr->next = level0->next;
            level0->next = curr;
          }
        } else if (curr->priority == 1) {      // priority 1
          if (level1 == NULL) {
            level1 = curr;
            curr->next = curr;
          } else {
            curr->next = level1->next;
            level1->next = curr;
          }
        } else if (curr->priority == 2) {      // priority 2
          if (level2 == NULL) {
            level2 = curr;
            curr->next = curr;
          } else {
            curr->next = level2->next;
            level2->next = curr;
          }
        } else {                          // priority 3
          if (level3 == NULL) {
            level3 = curr;
            curr->next = curr;
          } else {
            curr->next = level3->next;
            level3->next = curr;
          }
        }

      }
    }
    //TogglePB22();
  }
}

void EdgeTriggered_Init(void){
  //PB21
  //GPIOB->POLARITY31_16 = 0x00000400;     // rising
  GPIOB->POLARITY31_16 = 0x00000800;     // falling (idle high)
  GPIOB->CPU_INT.ICLR = 0x00200000;   // clear bit 21
  GPIOB->CPU_INT.IMASK = 0x00200000;  // arm PB21
  NVIC->IP[0] = (NVIC->IP[0]&(~0x0000FF00))|1<<14;    // set priority (bits 15,14) IRQ 1
  NVIC->ISER[0] = 1 << 1; // Group1 interrupt

  //PA18
  GPIOA->POLARITY31_16 = 0x00000010;     // rising
  GPIOA->CPU_INT.ICLR = 0x00040000;   // clear bit 21
  GPIOA->CPU_INT.IMASK = 0x00040000;  // arm PA18
  //NVIC->IP[0] = (NVIC->IP[0]&(~0x0000FF00))|1<<14;    // set priority (bits 15,14) IRQ 1
  //NVIC->ISER[0] = 1 << 1; // Group1 interrupt

  GPIOA->FILTEREN31_16 |= 0x00000030; // adds glitch filter to PA18
  GPIOB->FILTEREN31_16 |= 0x00000C00; // adds glitch filter to PB21

  IOMUX->SECCFG.PINCM[PB21INDEX] |= 0x00080000; // hysteresis for PB21
  IOMUX->SECCFG.PINCM[PA18INDEX] |= 0x00080000; // hysteresis for PA18
}




//----------------------------------------------------------------------------
//  Edge triggered Interrupt Handler
//  Rising edge of PA18 (S1) 
//  Falling edge of PB21 (S2)
//  Falling edge of PA27 (bump)
//  Falling edge of PA28 (bump)
//  Falling edge of PA31 (bump)
//----------------------------------------------------------------------------
void GROUP1_IRQHandler(void){
  // write this
/*
  uint32_t PB21Int = GPIOB->CPU_INT.RIS&(1<<21);


  static uint32_t last_press_time = 0;
  static uint8_t button_state = 0;
  uint32_t current_press_time = OS_MsTime();
*/
  
    
    if(GPIOA->CPU_INT.RIS&(1<<18)){ // PA18
      GPIOA->CPU_INT.ICLR = 1<<18;
      
      for (uint8_t i = 0; i < 2; i++) {
        if (s2_threads[i].active) {
          s2_threads[i].task();
        }
      }
    }
    if(GPIOA->CPU_INT.RIS&(1<<28)){ // PA28
      GPIOA->CPU_INT.ICLR = 1<<28;
    }
/*
    if (GPIOB->CPU_INT.RIS&(1<<21)) {
      GPIOB->CPU_INT.ICLR = 1<<21;
      if (button_state == 0) {
        if (((GPIOB->DOUT31_0 & (1<<21)) == 0)) {
          button_state = 1;
          last_press_time = current_press_time;
          for (uint8_t i = 0; i < 2; i++) {
            if (s2_threads[i].active) {
              s2_threads[i].task();
            }
          }
        }
      } else {
        if ((GPIOB->DOUT31_0 & (1<<21)) != 0) {
          //if ((current_press_time - last_press_time) > 50) {
            button_state = 0;
          //}
        }
      }

      
    }
*/

    if(GPIOB->CPU_INT.RIS&(1<<21)){ // PB21
      GPIOB->CPU_INT.ICLR = 1<<21;


      for (uint8_t i = 0; i < 2; i++) {
        if (s2_threads[i].active) {
          s2_threads[i].task();
        }
      }
      
    }
  
  // GPIOB->CPU_INT.ICLR = 1<<21;
  // GPIOA->CPU_INT.ICLR = 1<<18;
  // GPIOA->CPU_INT.ICLR = 1<<28;
  // (void)GPIOB->CPU_INT.RIS; // wait for writes to finish
  // (void)GPIOA->CPU_INT.RIS; // wait for writes to finish


  //GPIOB->CPU_INT.ICLR = 1<<21; // clear again after background thread runs
}
// ******** OS_AddS1Task *************** 
// add a background task to run whenever the S1 (PA18) button is pushed
// Inputs: pointer to a void/void background function
//         priority 0 is the highest, 1 is the lowest
// Outputs: 1 if successful, 0 if this thread can not be added
// It is assumed that the user task will run to completion and return
// This task can not spin, block, loop, sleep, or kill
// This task can call OS_Signal  OS_bSignal   OS_AddThread
// This task does not have a Thread ID
// Because of the pin conflict with TFLuna, this command will not be called 
int OS_AddS1Task(void(*task)(void), uint32_t priority){
  // put Lab 2 (and beyond) solution here
  
  return 0; // replace this line with solution
};

// ******** OS_AddS2Task *************** 
// add a background task to run whenever the S2 (PB21) button is pushed
// Inputs: pointer to a void/void background function
//         priority 0 is highest, 1 is lowest
// Outputs: 1 if successful, 0 if this thread can not be added
// It is assumed user task will run to completion and return
// This task can not spin block loop sleep or kill
// This task can call issue OS_Signal, it can call OS_AddThread
// This task does not have a Thread ID
// In lab 2, this function will be called 0 or 1 times
// In lab 3, this function will be called will be called 0 or 1 times
// In lab 3, there will be many background threads, and this priority field 
//           determines the relative priority of these four threads
int OS_AddS2Task(void(*task)(void), uint32_t priority){
  // put Lab 2 (and beyond) solution here
  long sr;
  if (num_s2_threads == 0) {
    sr = StartCritical();
    EdgeTriggered_Init(); // arm edge triggered interrupts
    EndCritical(sr);
  } else if (num_s2_threads == 2) {
    return 0; // max threads reached, can't add
  }

  sr = StartCritical();
  for (uint8_t i = 0; i < 2; i++) {
    if (s2_threads[i].active == 0) {
      s2_threads[i].task = task;
      s2_threads[i].priority = priority;
      s2_threads[i].active = 1;
      num_s2_threads++;
      break;
    }
  }
  EndCritical(sr);

  return 1; // successfully added thread
}

// ******** OS_AddPA28Task *************** 
// add a background task to run whenever the bump (PA28) button is pushed
// Inputs: pointer to a void/void background function
//         priority 0 is the highest, 1 is the lowest
// Outputs: 1 if successful, 0 if this thread can not be added
// It is assumed that the user task will run to completion and return
// This task can not spin, block, loop, sleep, or kill
// This task can call OS_Signal  OS_bSignal   OS_AddThread
// This task does not have a Thread ID
// In lab 3, this command will be called 0 or 1 times
// In lab 2, not implemented
// In lab 3, there will be many background threads, and this priority field 
//           determines the relative priority of these four threads
int OS_AddPA28Task(void(*task)(void), uint32_t priority){
  // put Lab 3 (and beyond) solution here

  // same as S2Task
 
  return 0; // replace this line with solution
};



// ******** OS_Sleep ************
// place this thread into a dormant state
// input:  number of msec to sleep
// output: none
// You are free to select the time resolution for this function
// OS_Sleep(0) implements cooperative multitasking
void OS_Sleep(uint32_t sleepTime){
  // put Lab 2 (and beyond) solution here
  __disable_irq();

  RunPt->sleep_state = 1;

//  LAB 3 START

  TCB_t *candidate = RunPt->next;
  if (candidate == RunPt) {
    switch (candidate->priority) {
      case 0:
        level0 = NULL;
        break;
      case 1:
        level1 = NULL;
        break;
      case 2:
        level2 = NULL;
        break;
      case 3:
        level3 = NULL;
        break;
    }
  } else {
    while (candidate->next != RunPt) {
      candidate = candidate->next;
    }

    candidate->next = RunPt->next;
    RunPt->next = NULL;
  }
//  LAB 3 END
  //DeltaQueue implementation
  TCB_t *currTemp = delta_queue_head;
  TCB_t *prevTemp = NULL;

  //finds the correct spot in the sorted linked list
  while (currTemp != NULL && (sleepTime >= currTemp->delta)) {
    sleepTime -= currTemp->delta;
    prevTemp = currTemp;
    currTemp = currTemp->sleep_next;
  }

  // update current thread's values
  RunPt->delta = sleepTime;
  if (prevTemp == NULL) {
    RunPt->sleep_next = delta_queue_head;
    delta_queue_head = RunPt;
  } else {
    RunPt->sleep_next = currTemp;
    prevTemp->sleep_next = RunPt;
  }

  // update next thread's delta
  if (RunPt->sleep_next != NULL) {
    RunPt->sleep_next->delta -= RunPt->delta;
  }

  __enable_irq();

  OS_Suspend(); // trigger SysTick

} 



// ******** OS_Kill ************
// kill the currently running thread, release its TCB and stack
// input:  none
// output: none

void OS_Kill(void){
  // put Lab 2 (and beyond) solution here

  long sr = StartCritical();
/*
  TCB_t *candidate = RunPt;
  if (candidate->next == RunPt) {
    return; // only one thread left, can't kill
  }

  while (candidate->next != RunPt) {
    candidate = candidate->next;
  }

  candidate->next = RunPt->next;
  used_tcbs[RunPt->id] = 0;
*/
  //  LAB 3 START

  TCB_t *candidate = RunPt->next;
  if (candidate == RunPt) {
    switch (candidate->priority) {
      case 0:
        level0 = NULL;
        break;
      case 1:
        level1 = NULL;
        break;
      case 2:
        level2 = NULL;
        break;
      case 3:
        level3 = NULL;
        break;
    }
  } else {
    while (candidate->next != RunPt) {
      candidate = candidate->next;
    }

    candidate->next = RunPt->next;
  }

  used_tcbs[RunPt->id] = 0;
  RunPt->next = NULL;
  //  LAB 3 END
  
  EndCritical(sr);
  OS_Suspend();

/*
  if (RunPt->next != LastPt) {
    __disable_irq();
    LastPt->next = RunPt->next;
    used_tcbs[RunPt->id] = 0;
    __enable_irq();
  }


  OS_Suspend();
*/
  for(;;){};        // can not return (must return in Lab 5 since called from SVC_hander)
   
}; 

// ******** OS_Suspend ************
// suspend execution of currently running thread
// scheduler will choose another thread to execute
// Can be used to implement cooperative multitasking 
// Same function as OS_Sleep(0)
// input:  none
// output: none
void OS_Suspend(void){
  // put Lab 2 (and beyond) solution here

  __disable_irq();
/*
  // this skips SysTick overhead (pushing and restoring registers entering and exiting the interrupt)
  OS_Schedule();
  if (NextThreadPt != RunPt) {
    //PendSV will perform the thread switch
    SCB->ICSR |= PENDSVSET; // PendSV is now pending
  }
*/
  SCB->ICSR |= SYSTICKSET; // SysTick is now pending

  __enable_irq();

};
  


// ******** OS_Fifo_Init ************
// Initialize the Fifo to be empty
// Inputs: size
// Outputs: none 
// In Lab 2, you can ignore the size field
// In Lab 3, you should implement the user-defined fifo size
// In Lab 3, you can put whatever restrictions you want on size
//    e.g., 4 to 64 elements
//    e.g., must be a power of 2,4,8,16,32,64,128,256
void OS_Fifo_Init(uint32_t size){
  // put Lab 2 (and beyond) solution here
  
  if (size > 256) {
    fifo_size = 256;
  } else {
    fifo_size = size;
  }
  PutI = 0;
  GetI = 0;
  OS_InitSemaphore(&DataAvailable, 0);  


 
}

// ******** OS_Fifo_Put ************
// Enter one data sample into the Fifo
// Called from the background, so no waiting 
// Inputs:  data
// Outputs: true if data is properly saved,
//          false if data not saved, because it was full
// Since this is called by interrupt handlers 
//  this function can not disable or enable interrupts
int OS_Fifo_Put(uint32_t data){
  // put Lab 2 (and beyond) solution here
  
  if (DataAvailable.Value >= fifo_size) {
    return 0; // fifo full, return false
  }

  fifo[PutI] = data;
  PutI = (PutI + 1) & (fifo_size - 1);
  OS_Signal(&DataAvailable);
  
  return 1; // data added to fifo, return true
}

// ******** OS_Fifo_Get ************
// Remove one data sample from the Fifo
// Called in foreground, will spin/block if empty
// Inputs:  none
// Outputs: data 
uint32_t OS_Fifo_Get(void){
  // put Lab 2 (and beyond) solution here
  
  OS_Wait(&DataAvailable);

  uint32_t retval = fifo[GetI];
  GetI = (GetI + 1) & (fifo_size - 1);
  
  return retval; // return the data retrieved
}

// ******** OS_Fifo_Size ************
// Check the status of the Fifo
// Inputs: none
// Outputs: returns the number of elements in the Fifo
//          greater than zero if a call to OS_Fifo_Get will return right away
//          zero or less than zero if the Fifo is empty 
//          zero or less than zero if a call to OS_Fifo_Get will spin or block
int32_t OS_Fifo_Size(void){
  // put Lab 2 (and beyond) solution here
  return DataAvailable.Value;
}

uint32_t MailBoxData;
Sema4_t MailBoxFree;
Sema4_t MailBoxDataAvailable;

// ******** OS_MailBox_Init ************
// Initialize communication channel
// Inputs:  none
// Outputs: none
void OS_MailBox_Init(void){
  // put Lab 2 (and beyond) solution here
  MailBoxData = 0;
  OS_InitSemaphore(&MailBoxFree, 1);
  OS_InitSemaphore(&MailBoxDataAvailable, 0);
  
}

// ******** OS_MailBox_Send ************
// enter mail into the MailBox
// Inputs:  data to be sent
// Outputs: none
// This function will be called from a foreground thread
// It will spin/block if the MailBox contains data not yet received 
void OS_MailBox_Send(uint32_t data){
  // put Lab 2 (and beyond) solution here
  OS_bWait(&MailBoxFree);
  MailBoxData = data;
  OS_bSignal(&MailBoxDataAvailable);
};

// ******** OS_MailBox_Recv ************
// remove mail from the MailBox
// Inputs:  none
// Outputs: data received
// This function will be called from a foreground thread
// It will spin/block if the MailBox is empty 
uint32_t OS_MailBox_Recv(void){
  // put Lab 2 (and beyond) solution here
  OS_bWait(&MailBoxDataAvailable);
  uint32_t retval = MailBoxData;
  OS_bSignal(&MailBoxFree);
  return retval;
};

// ******** OS_Time ************
// return the system time, counting up 
// Inputs:  none
// Outputs: time in 12.5ns units, 0 to 4294967295
// The time resolution should be less than or equal to 1us, and the precision 32 bits
// It is ok to change the resolution and precision of this function as long as 
//   this function and OS_TimeDifference have the same resolution and precision 
uint32_t OS_Time(void){
  // put Lab 2 (and beyond) solution here
  return TIMG12->COUNTERREGS.CTR;
};

// ******** OS_TimeDifference ************
// Calculates difference between two times
// Inputs:  two times measured with OS_Time
// Outputs: time difference in 12.5ns units 
// The time resolution should be less than or equal to 1us, and the precision at least 12 bits
// It is ok to change the resolution and precision of this function as long as 
//   this function and OS_Time have the same resolution and precision 
uint32_t OS_TimeDifference(uint32_t start, uint32_t stop){
  // put Lab 2 (and beyond) solution here
    return (start - stop);
};




// ******** OS_Launch *************** 
// start the scheduler, enable interrupts
// Inputs: number of 12.5ns clock cycles for each time slice
//         you may select the units of this parameter
// Outputs: none (does not return)
// In Lab 2, you can ignore the theTimeSlice field
// In Lab 3, you should implement the user-defined TimeSlice field
// It is ok to limit the range of theTimeSlice to match the 24-bit SysTick
// make PendSV priority 3, and SysTick priority 2
void OS_Launch(uint32_t theTimeSlice){
  // put Lab 2 (and beyond) solution here
   
   SysTick->CTRL = 0x7; // enable SysTick

   // LAB 2 IMPLEMENTATION
   //RunPt = &tcbs[0];

  if (level0 != NULL) {
    RunPt = level0;
  } else if (level1 != NULL) {
    RunPt = level1;
  } else if (level2 != NULL) {
    RunPt = level2;
  } else {
    RunPt = level3;
  }

   OS_ClearMsTime(); // starts TimeMs counter
   TimerG12_Init(); // starts global OS clock

   StartOS(); // interrupts enabled in here

   while (1){};

}
