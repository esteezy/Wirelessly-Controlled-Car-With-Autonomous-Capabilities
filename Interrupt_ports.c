// ------------------------------------------------------------------------------
//
//  Description: Function definitions for port interrupts
//
//  Author: Evan Mason
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
// ------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include  "ports.h"
#include  "macros.h"
#include <string.h>

//Globals
//------------------------------------------------------------------------------
extern volatile unsigned char switch_pressed1 = RESET_STATE;
extern volatile unsigned char switch_pressed2 = RESET_STATE;
extern volatile unsigned char start_trans = RESET_STATE;
unsigned char switch_debounce = RESET_STATE;
extern  char display_line[CHAR_WIDTH][CHAR_LEN];
extern volatile unsigned char update_display;
extern volatile unsigned int state;
extern volatile unsigned int myTime;
unsigned int deb_count = RESET_STATE;
extern volatile int switch_state;


//------------------------------------------------------------------------------
// Port 4 interrupt. For switches, they are disabled for the duration
// of the debounce timer. Flag is set that user space can check.
// Turn on IR_LED

#pragma vector = PORT4_VECTOR
__interrupt void switch1_interrupt(void) {
if (P4IFG & SW1) {              // Switch 1
  //Baud 115
  switch_state = RESET_STATE;
  // Set a variable to identify the switch has been pressed.
  switch_pressed1 = SW1;
  // Set a variable to identify the switch is being debounced.
  switch_debounce = TRUE;
  // Reset the count required of the debounce.
  deb_count = RESET_STATE;
  // Disable the Switch Interrupt.
  P4IFG &= ~SW1;              // IFG SW1 cleared
  // Clear any current timer interrupt.
  myTime = RESET_STATE;
  }
  // Use a Timer Value to control the debounce

}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Port 4 interrupt. For switches, they are disabled for the duration
// of the debounce timer. Flag is set that user space can check.

#pragma vector = PORT2_VECTOR
__interrupt void switch2_interrupt(void) {
if (P2IFG & SW2) {              // Switch 1
  //460 Baud
  switch_state = 1;
  // Set a variable to identify the switch has been pressed.
  switch_pressed2 = SW2;
  // Set a variable to identify the switch is being debounced.
  switch_debounce = TRUE;
  // Reset the count required of the debounce.
  deb_count = RESET_STATE;
  // Disable the Switch Interrupt.
  P2IFG &= ~SW2;
  // Clear any current timer interrupt.
  myTime = RESET_STATE;
  }
// Use a Timer Value to control the debounce
}
//------------------------------------------------------------------------------
