// ------------------------------------------------------------------------------
//
//  Description: Initialization/configuration for USCI_A module
//
//  Author: Evan Mason
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
// ------------------------------------------------------------------------------

//Macros
#include  "functions.h"
#include  "msp430.h"
#include  <string.h>
#include  "macros.h"
#include  "ports.h" 

//Globals
extern volatile char USB_Char_Rx[SMALL_RING_SIZE] = {' '};
extern volatile unsigned int usb_rx_ring_wr = RESET_STATE;
extern volatile unsigned int usb_rx_ring_rd = RESET_STATE;
extern volatile char USB_Char_RxA0[LARGE_RING_SIZE] = {' '};
extern volatile unsigned int usb_rx_ring_wrA0 = RESET_STATE;
extern volatile unsigned int usb_rx_ring_rdA0 = RESET_STATE;
extern volatile int switch_state;
extern volatile char wait_4_transmit = RESET_STATE;

//------------------------------------------------------------------------------
void Init_Serial_UCA1(int switch_state){
  int i;
  for(i=RESET_STATE; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = CLEAR;              // USB Rx Buffer
  }
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;

  
  // Configure UART 1
  //Baud Rate 115200 -- switch_state == 0
  if(switch_state == BAUD_115){
    //BRCLK    Baudrate UCOS16 UCBRx UCFx UCSx
    //8000000  115200     1      4    5   0x55
    UCA1CTLW0 = RESET_STATE;                        // Use word register
    UCA1CTLW0 |= UCSWRST;                 // Set Software reset enable
    UCA1CTLW0 |= UCSSEL__SMCLK;           // Set SMCLK as fBRCLK
    UCA1BRW = BRW4;     //4
    UCA1MCTLW = TLW55; //0x5551
    UCA1CTLW0 &= ~ UCSWRST;               // Set Software reset enable
    UCA1IE |= UCRXIE;                     // Enable RX interrupt
  }
  //Baud Rate 9600 -- switch_state == 1
  if(switch_state == ONE){
    //BRCLK    Baudrate UCOS16 UCBRx UCFx UCSx
    //8000000    9600     1      52    1   0x49
    UCA1CTLW0 = RESET_STATE;                        // Use word register
    UCA1CTLW0 |= UCSWRST;                 // Set Software reset enable
    UCA1CTLW0 |= UCSSEL__SMCLK;           // Set SMCLK as fBRCLK
    UCA1BRW = BRW52; //52
    UCA1MCTLW = TLW49; //0x4911
    UCA1CTLW0 &= ~ UCSWRST;               // Set Software reset enable
    UCA1IE |= UCRXIE;                     // Enable RX interrupt
  }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Init_Serial_UCA0(int switch_state){
  int i;
  for(i=RESET_STATE; i<SMALL_RING_SIZE; i++){
    USB_Char_RxA0[i] = CLEAR;              // USB Rx Buffer
  }
  usb_rx_ring_wrA0 = BEGINNING;
  usb_rx_ring_rdA0 = BEGINNING;
  
  // Configure UART 1
  //Baud Rate 115200 -- switch_state == 0
  //BRCLK    Baudrate UCOS16 UCBRx UCFx UCSx
  //8000000  115200     1      4    5   0x55
  UCA0CTLW0 = RESET_STATE;                        // Use word register
  UCA0CTLW0 |= UCSWRST;                 // Set Software reset enable
  UCA0CTLW0 |= UCSSEL__SMCLK;           // Set SMCLK as fBRCLK
  UCA0BRW = BRW4;
  UCA0MCTLW = TLW55;
  UCA0CTLW0 &= ~ UCSWRST;               // Set Software reset enable
  UCA0IE |= UCRXIE;                     // Enable RX interrupt
}
//------------------------------------------------------------------------------
