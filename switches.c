// ------------------------------------------------------------------------------
//
//  Description: switches.c is an executable that contains the function defintions 
//                      to enable switches on the MSP430FR2355 microcontroller
//
//  Evan Mason
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
// ------------------------------------------------------------------------------

//Macros
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include  "macros.h"
#include  "ports.h" 

//Function Prototypes
void Switches_Process(void);
void Shape_Triangle(void);
void Shape_Figure8(void);
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);

//Global Variables
extern char display_line[CHAR_WIDTH][CHAR_LEN];
extern char *display[CHAR_WIDTH];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int myTime;
extern volatile unsigned char switch_pressed1;
extern volatile unsigned char switch_pressed2;
unsigned int count = RESET_STATE;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;

//------------------------------------------------------------------------------

//Function Definitions
void Switches_Process(void){

  if(switch_pressed1){
    //sends AT+NSTATE=? to IOT for
    switch_pressed1 = RESET_STATE;
    
  }
  

  if(switch_pressed2){
     //sets baud rate to 460,800
    switch_pressed2 = RESET_STATE;

  }
}

