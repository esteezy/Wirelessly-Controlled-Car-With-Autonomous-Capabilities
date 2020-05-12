// ------------------------------------------------------------------------------
//
//  Description: This file contains the Initializations following 
//                      
//
//  Author: Evan Mason
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
// ------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include  <string.h>

//Globals
extern char display_line[CHAR_WIDTH][CHAR_LEN];
extern char *display[CHAR_WIDTH];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=RESET_STATE;i<ELEVEN;i++){
    display_line[INDEX0][i] = RESET_STATE;
    display_line[INDEX1][i] = RESET_STATE;
    display_line[INDEX2][i] = RESET_STATE;
    display_line[INDEX3][i] = RESET_STATE;
  }
  display_line[INDEX0][TEN] = RESET_STATE;
  display_line[INDEX1][TEN] = RESET_STATE;
  display_line[INDEX2][TEN] = RESET_STATE;
  display_line[INDEX3][TEN] = RESET_STATE;

  display[INDEX0] = &display_line[INDEX0][RESET_STATE];
  display[INDEX1] = &display_line[INDEX0][RESET_STATE];
  display[INDEX2] = &display_line[INDEX0][RESET_STATE];
  display[INDEX3] = &display_line[INDEX0][RESET_STATE];
  update_display = RESET_STATE;
  update_display_count = RESET_STATE;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}