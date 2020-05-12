// ------------------------------------------------------------------------------
//
//  Description: This file contains the Port Initializations/Configurations
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


//Calls the rest of the initialization functions
void Init_Ports(int argument){
  Init_Port_1();
  Init_Port_2();
  Init_Port_3(argument);
  Init_Port_4();
  Init_Port_5();
  Init_Port_6();
}
//------------------------------------------------------------------------------
//Function will initialize all in pins in port 1
//E.g. set SELECT-bits (0||1), set pin direction
//Configure any pull-up resitors as needed
//Pins 1-5 Configured for ADC inputs
void Init_Port_1(void){
//------------------------------------------------------
// RED_LED              (0x01) // 0 RED LED 0 
// A1_SEEED             (0x02) // 1 A1_SEEED 
// V_DETECT_L           (0x04) // 2 A2 
// V_DETECT_R           (0x08) // 3 A3 
// V_BAT                (0x10) // 4 A4 
// V_THUMB              (0x20) // 5 A5 
// UCA0TXD              (0x40) // 6 Back Channel UCA0TXD 
// UCA0RXD              (0x80) // 7 Back Channel UCA0RXD 
//-------------------------------------------------------
  P1DIR = SET_HIGH;              //Set P1 Direction to output
  P1OUT = SET_LOW;               //P1 set Low
  
  //Pin 0
  P1SEL0 &= ~RED_LED;           //RED_LED GPIO operation
  P1SEL1 &= ~RED_LED;           //RED_LED GPIO operation
  P1DIR |= RED_LED;             //direction = output
  P1OUT &= ~RED_LED;            //set RED_LED on [Low]
  //Pin 1
  P1SEL0 |= A1_SEEED;           //ADC input for A1_SEEED
  P1SEL1 |= A1_SEEED;           //ADC input for A1_SEEED
  //Pin 2
  P1SEL0 |= V_DETECT_L;         //ADC input for V_DETECT_L
  P1SEL1 |= V_DETECT_L;         //ADC input for V_DETECT_L
  //Pin 3
  P1SEL0 |= V_DETECT_R;         //ADC input for V_DETECT_R
  P1SEL1 |= V_DETECT_R;         //ADC input for V_DETECT_R
  //Pin 4
  P1SEL0 |= A4_SEEED;           //ADC input for A4_SEEED
  P1SEL1 |= A4_SEEED;           //ADC input for A4_SEEED
  //Pin 5
  P1SEL0 |= V_THUMB;            //ADC input for V_THUMB
  P1SEL1 |= V_THUMB;            //ADC input for V_THUMB
  //Pin 6
  P1SEL0 |= UCA0RXD;            //UCSI_A0 UART operation
  P1SEL1 &= ~UCA0RXD;           //USCI_A0 UART operation
  //Pin 7
  P1SEL0 |= UCA0TXD;            //USCI_A0 UART operation
  P1SEL1 &= ~UCA0TXD;           //USC_A0 UART operation
}
//------------------------------------------------------------------------------
//Function will initialize all in pins in port 2
void Init_Port_2(void){
  P2DIR = SET_HIGH;             //Set P2 Direction to output
  P2OUT = SET_LOW;              //P2 set Low
  
  //Pin 0
  P2SEL0 &= ~P2_0;              //P2_0 GPIO operation
  P2SEL1 &= ~P2_0;              //P2_0 GPIO operation
  P2DIR &= ~P2_0;               //Direction = input
  //Pin 1
  P2SEL0 &= ~P2_1;              //P2_1 GPIO operation
  P2SEL1 &= ~P2_1;              //P2_1 GPIO operation
  P2DIR &= ~P2_1;               //Direction = input
  //Pin 2
  P2SEL0 &= ~P2_2;              //P2_2 GPIO operation
  P2SEL1 &= ~P2_2;              //P2_2 GPIO operation
  P2DIR &= ~P2_2;               //Direction = input
  //Pin 3
  P2SEL0 &= ~SW2;               //SW2 operation
  P2SEL1 &= ~SW2;               //SW2 operation
  P2DIR &= ~SW2;                //Direction = input
  P2OUT |= SW2;                 //Configure pullup resistor
  P2REN |= SW2;                 //Enable pullup resistor
  P2IES |= SW2;                 // P2.0 Hi/Lo edge interrupt
  P2IFG &= ~SW2;                //IFG SW2 cleared
  P2IE |= SW2;                  //SW2 interrupt Enabled & = ~
  //Pin 4
  P2SEL0 &= ~P2_4;              //P2_4 GPIO operation
  P2SEL1 &= ~P2_4;              //P2_4 GPIO operation
  P2DIR &= ~P2_4;               //Direction = input
  //Pin 5
  P2SEL0 &= ~P2_5;              //P2_5 GPIO operation
  P2SEL1 &= ~P2_5;              //P2_5 GPIO operation
  P2DIR &= ~P2_5;               //Direction = input
  //Pin 6
  P2SEL0 &= ~LFXOUT;            //LFXOUT Clock operation
  P2SEL1 |= LFXOUT;             //LFXOUT Clock operation
  //Pin 7
  P2SEL0 &= ~LFXIN;             //LFXIN Clock operation
  P2SEL1 |= LFXIN;              //LFXIN Clock operation
}

//------------------------------------------------------------------------------
//Function will initialize all in pins in port 3
void Init_Port_3(int argument){
  P3DIR = SET_HIGH;             //Set P3 direction to output
  P3OUT = SET_LOW;              //P3 set Low
  
  //Pin 0
  P3SEL0 &= ~TEST_PROBE;        //TEST_PROBE GPIO operation
  P3SEL1 &= ~TEST_PROBE;        //TEST_PROBE GPIO operation
  P3DIR &= ~TEST_PROBE;         //direction = input
  //PIN 1
  P3SEL0 |= CHECK_BAT;          //CHECK_BAT operation(??)
  P3SEL1 |= CHECK_BAT;          //CHECK_BAT operation
  P3DIR |= CHECK_BAT;           //direction = output
  //Pin 2
  P3SEL0 |= OA2N;               //OA2N operation (??)
  P3SEL1 |= OA2N;               //OA2N operation
  //Pin 3
  P3SEL0 |= OA2P;               //OA2P operation
  P3SEL1 |= OA2P;               //OA2P operation
  //Pin 4
  if(argument == USE_GPIO){
    P3SEL0 &= ~SMCLK_OUT;       //Pin3.4 GPIO operation
    P3SEL1 &= ~SMCLK_OUT;       //Pin3.4 GPIO operation
    P3DIR |= SMCLK_OUT;         //direction = output
  }
  if(argument == USE_SMCLK){
    P3SEL0 |= SMCLK_OUT;        //SMCLK clock operation
    P3SEL1 &= ~SMCLK_OUT;       //SMCLK clock operation
    P3DIR |= SMCLK_OUT;         //direction = output
    P3OUT |= SMCLK_OUT;
  }

  //Pin 5
  P3SEL0 &= ~IR_LED;            //IR_LED GPIO operation
  P3SEL1 &= ~IR_LED;            //IR_LED GPIO operation
  P3DIR |= IR_LED;              //direction = output;
  P6OUT |= IR_LED;              //set on [low]
  //Pin 6
  P3SEL0 &= ~IOT_LINK;          //IOT_LINK GPIO operation
  P3SEL1 &= ~IOT_LINK;          //IOT_LINK GPIO operation
  //Pin 7
  P3SEL0 &= ~P3_7;              //P3_7 GPIO operation
  P3SEL1 &= ~P3_7;              //P3_7 GPIO operation
}

//------------------------------------------------------------------------------
//Function will initialize all in pins in port 4
void Init_Port_4(void){
  P4DIR = SET_HIGH;             //Set P4 direction to output
  P4OUT = SET_LOW;              //P4 set Low
  
  //Pin 0
  P4SEL0 &= ~RESET_LCD;         //RESET_LCD GPIO operation
  P4SEL1 &= ~RESET_LCD;         //RESET_LCD GPIO operation
  P4DIR |= RESET_LCD;           //direction = output
  P4OUT |= RESET_LCD;           //set RESET_LCD off [high]
  //Pin 1
  P4SEL0 &= ~SW1;               //SW1 GPIO operation
  P4SEL1 &= ~SW1;               //SW1 GPIO operation
  P4DIR &= ~SW1;                //direction = input
  P4OUT |= SW1;                 //configure pullup resistor
  P4REN |= SW1;                 //enable pullup resistor
  P4IES |= SW1;                 // P4.0 Hi/Lo edge interrupt
  P4IFG &= ~SW1;                //IFG SW1 cleared
  P4IE |= SW1;                  //SW1 interrupt Enabled
  //Pin 2
  P4SEL0 |= UCA1RXD;            //USCI_A1 UART operation 
  P4SEL1 &= ~UCA1RXD;           //USCI_A1 UART operation
  //Pin 3
  P4SEL0 |= UCA1TXD;            //USCI_A1 UART operation
  P4SEL1 &= ~UCA1TXD;           //USCI_A1 UART operation
  //Pin 4
  P4SEL0 &= ~UCB1_CS_LCD;       //UCB1_CS_LCD GPIO operation
  P4SEL1 &= ~UCB1_CS_LCD;       //UCB1_CS_LCD GPIO operation
  P4DIR |= UCB1_CS_LCD;         //direction = output
  P4OUT |= UCB1_CS_LCD;         //set UCB1_CS_LCD off [high]
  //Pin 5
  P4SEL0 |= UCB1CLK;            //UCB1CLK SPI BUS operation
  P4SEL1 &= ~UCB1CLK;           //UCB1CLK SPI BUS operation
  //Pin 6
  P4SEL0 |= UCB1SIMO;           //UCB1SIMO SPI BUS operation
  P4SEL1 &= ~UCB1SIMO;          //UCB1SIMO SPI BUS operation
  //Pin 7
  P4SEL0 |= UCB1SOMI;           //UCB1SOMI SPI BUS operation
  P4SEL1 &= ~UCB1SOMI;          //UCB1SOMI SPI BUS operation
}

//------------------------------------------------------------------------------
//Function will initialize all in pins in port 5
void Init_Port_5(void){
  P5DIR = SET_HIGH;             //Set P5 direction to output
  P5OUT = SET_LOW;              //P5 set Low
  
  //Pin 0
  P5SEL0 &= ~IOT_RESET;         //IOT_RESET GPIO operation
  P5SEL1 &= ~IOT_RESET;         //IOT_RESET GPIO operation
  P5DIR |= IOT_RESET;           //direction = output
  P5OUT |= IOT_RESET;           //set active low for IOT RESET
  //P5OUT
  //Pin 1
  P5SEL0 &= ~V_BAT;             //V_BAT GPIO operation
  P5SEL1 &= ~V_BAT;             //V_BAT GPIO operation
  P5DIR &= ~V_BAT;              //direction = input 
  //Pin 2
  P5SEL0 &= ~IOT_PROG_SEL;      //IOT_PROG_SEL GPIO operation
  P5SEL1 &= ~IOT_PROG_SEL;      //IOT_PROG_SEL GPIO operation
  P5DIR &= ~IOT_PROG_SEL;       //direction = input 
  //Pin 3
  P5SEL0 &= ~V_3_3;             //V_3_3 GPIO operation
  P5SEL1 &= ~V_3_3;             //V_3_3 GPIO operation
  P5DIR &= ~V_3_3;              //direction = input
  //Pin 4
  P5SEL0 &= ~IOT_PROG_MODE;     //IOT_PROG_MODE GPIO operation
  P5SEL1 &= ~IOT_PROG_MODE;     //IOT_PROG_MODE GPIO operation
  P5DIR &= ~IOT_PROG_MODE;      //direction = input 
}

//------------------------------------------------------------------------------
//Function will initialize all in pins in port 6
//Motors configured to utilize PWMs (implemented using TimerB3)
void Init_Port_6(void){
  P6DIR = SET_HIGH;             //P6 direction set to output
  P6OUT = SET_LOW;              //P6 set Low
  
  //Pin 0
  P6SEL0 |= R_FORWARD;          //R_FORWARD operation
  P6SEL1 &= ~R_FORWARD;         //R_FORWARD operation
  P6DIR |= R_FORWARD;           //direction = output
  //Pin 1 
  P6SEL0 |= L_FORWARD;          //L_FORWARD operation
  P6SEL1 &= ~L_FORWARD;         //L_FORWARD operation
  P6DIR |= L_FORWARD;           //direction = output
  //Pin 2
  P6SEL0 |= R_REVERSE;          //R_REVERSE operation
  P6SEL1 &= ~R_REVERSE;         //R_REVERSE operation
  P6DIR |= R_REVERSE;           //direction = output
  //Pin 3
  P6SEL0 |= L_REVERSE;          //L_REVERSE operation
  P6SEL1 &= ~L_REVERSE;         //L_REVERSE operation
  P6DIR |= L_REVERSE;           //direction = output
  //Pin 4
  P6SEL0 &= ~LCD_BACKLITE;      //LCD_BACKLITE GPIO operation
  P6SEL1 &= ~LCD_BACKLITE;      //LCD_BACKLITE GPIO operation
  P6DIR |= LCD_BACKLITE;        //direction = output
  P6OUT |= LCD_BACKLITE;        //set LCD_BACKLITE on [low]
  //Pin 5
  P6SEL0 &= ~P6_5;              //P6_5 GPIO operation
  P6SEL1 &= ~P6_5;              //P6_5 GPIO operation
  P6DIR |= P6_5;                //direction = output
  //Pin 6
  P6SEL0 &= ~GRN_LED;           //GRN_LED GPIO operation
  P6SEL1 &= ~GRN_LED;           //GRN_LED GPIO operation
  P6DIR |= GRN_LED;             //direction = output
  P6OUT &= ~GRN_LED;            //set GRN_LED on [low]
  
}