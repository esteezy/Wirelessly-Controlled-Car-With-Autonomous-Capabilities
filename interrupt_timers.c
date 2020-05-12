// ------------------------------------------------------------------------------
//
//  Description: Function definitions for timer interrupts
//
//  Author: Evan Mason
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
// ------------------------------------------------------------------------------

//Macros
#include  "functions.h"
#include  "msp430.h"
#include  "ports.h"
#include  "macros.h"
#include <string.h>



extern char display_line[CHAR_WIDTH][CHAR_LEN];
extern char *display[CHAR_WIDTH];

extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int interrupt_num = RESET_STATE;
extern volatile unsigned int myTime = RESET_STATE;
extern volatile unsigned int rand_time = RESET_STATE;
int disp_bool = TRUE;

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){

  //----------------------------------------------------------------------------
  // TimerB0 0 Interrupt handler
  //----------------------------------------------------------------------------
  update_display = TRUE;
  rand_time++;
  myTime++;
  TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
  //----------------------------------------------------------------------------
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
  switch(__even_in_range(TB0IV,MAX_CASES)){
  case RESET_STATE: break; // No interrupt
  case CCR_ONE: // CCR1 not used
    
    TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
    break;
  case CCR_TWO: // CCR2 not used

    break;
  case OVERFLOW: // overflow

    break;
  default: break;
  }
//
}