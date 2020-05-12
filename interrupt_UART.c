// ------------------------------------------------------------------------------
//
//  Description: Initialization/configuration for UART interrupts
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


// global variables
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int UCA1_index;
extern volatile char USB_Char_RxA0[LARGE_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wrA0;
extern volatile unsigned int UCA0_index;
extern char disp_string[TEN];
extern volatile unsigned int state;
extern volatile int command_received = RESET_STATE;
extern volatile int trans_command = RESET_STATE;
extern volatile char wait_4_transmit;
extern char temp2 = RESET_STATE;
unsigned int index = RESET_STATE;
extern char comm_output[SMALL_RING_SIZE];
extern char command[QUEUE_SIZE][TEN] = {' '};
unsigned int ip = RESET_STATE;
unsigned int ip_index = ONE;
extern char ip_addr1[TEN] = {' '};
extern char ip_addr2[TEN] = {' '};
extern unsigned int wifi_data = RESET_STATE;
unsigned int data = RESET_STATE;
unsigned int data_index = RESET_STATE;
unsigned int command_decision = RESET_STATE;
extern unsigned int queue_position = RESET_STATE;
extern unsigned int q = RESET_STATE;




//------------------------------------------------------------------------------
#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  
  //unsigned int temp;
  switch(__even_in_range(UCA1IV,ALL_CASES)){
  case VECTOR0: // Vector 0 - no interrupt
    break;
  case VECTOR2: // Vector 2 - RXIFG
    //temp = usb_rx_ring_wr++;
    //USB_Char_Rx[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
    temp2 = UCA1RXBUF;
    UCA0TXBUF = temp2;

    if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
      usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    break;
  case VECTOR4: // Vector 4 – TXIFG
    UCA1TXBUF = comm_output[UCA1_index++];
    if (comm_output[UCA1_index] == NULL){
      UCA1IE &= ~UCTXIE;
    } 
    break;
    
  default: break; 
  }
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  char temp3;
  switch(__even_in_range(UCA0IV,ALL_CASES)){
  case VECTOR0: // Vector 0 - no interrupt
    break;
  case VECTOR2: // Vector 2 - RXIFG
    temp3 = UCA0RXBUF;
    UCA1TXBUF = temp3;
    
    //isolating commands
    switch(command_decision){
    case FIRST_CHAR:
      //TCP client formatting - confirming correct transmission
      if(temp3 == 'S'){ command_decision = VALID_CONN; }
      break;
    case VALID_CONN:
      if(temp3 == '0' || temp3 == '1'){ command_decision = VALID_COMM; }
      else{ command_decision = FIRST_CHAR; }
      break; 
    //process command
    case VALID_COMM:
      if(temp3 == ':'){ command_decision = FILL_BUFF; }
      else{ command_decision = FIRST_CHAR; }
      break;
    case FILL_BUFF:
      if(temp3 != ESC){ command[queue_position][index++] = temp3; }
      else{
        index = RESET_STATE;
        queue_position++;
        if(queue_position >= QUEUE_SIZE){
          queue_position = RESET_STATE;
        }
        command_received = TRUE;
        command_decision = FIRST_CHAR;
      }
      break;

    default: break;
    }

    //isolating ip addr
    switch(ip){
    case FIRST_CHAR:
      if(temp3 == 'r'){ ip = IP_VAL; }
      break;
    case IP_VAL:
      if(temp3 == '='){ ip = IP_FILL; }
      else{ ip = RESET_STATE;}
      break;
    case IP_FILL:
      if(ip_index < IP_LEN){
        ip_addr1[ip_index] = temp3;
      }
      if(ip_index >= IP_LEN && ip_index < IP_END){
          ip_addr2[ip_index - SEVEN] = temp3;
      }
      if(ip_index == IP_END){
        wifi_data = TRUE;
        ip_index = ONE;
        ip = RESET_STATE;
      }
      ip_index++;
      break;
    default: break;
    }

    if (usb_rx_ring_wrA0 >= (sizeof(USB_Char_RxA0))){
      usb_rx_ring_wrA0 = BEGINNING; // Circular buffer back to beginning
    }
    break;
  case VECTOR4: // Vector 4 – TXIFG
    UCA0TXBUF = comm_output[UCA0_index++];
    if (comm_output[UCA0_index] == NULL){
      for(int i = RESET_STATE; i<SMALL_RING_SIZE; i++){
        comm_output[i] = '\0';
      }
      UCA0_index = RESET_STATE;
      UCA0IE &= ~UCTXIE;
    } 
    break;
  default: break;
  }
}
