//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Author: Evan Mason
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include  <string.h>
#include  "macros.h"
#include  "ports.h" 

// Function Prototypes
void main(void);
void Init_Conditions(void);
void Init_LEDs(void);
void Init_Ports(int argument);
void Switches_Process(void);
void Init_Timers(void);
void Init_ADC(void);
void wait_screen(int switch_state);
void disp_receive(void);
void Init_Serial_UCA0(int switch_state);
void Init_Serial_UCA1(int switch_state);
void trans_disp(void);
void movements(char dir);
void Wheels_Off(void);
void Movement_8(void);
void HextoBCD(int hex_value);



  // Global Variables
volatile char slow_input_down;
extern char display_line[CHAR_WIDTH][CHAR_LEN];
extern char *display[CHAR_WIDTH];
unsigned char display_mode;
int argument = RESET_STATE;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int myTime;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int state = RESET_STATE;
extern volatile int switch_state = RESET_STATE;
//hw8
extern volatile unsigned int UCA1_index = RESET_STATE;
extern volatile unsigned int UCA0_index = RESET_STATE;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile char USB_Char_RxA0[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wrA0;
extern volatile unsigned int usb_rx_ring_rdA0;
unsigned int pb_wr = RESET_STATE;
extern volatile unsigned char switch_pressed1;
extern volatile unsigned char switch_pressed2;
extern char temp2;
extern char comm_output[SMALL_RING_SIZE] = {'\0'};
extern char command[QUEUE_SIZE][TEN];
char IOT_output[TEN] = {' '};
extern volatile int trans_command;
unsigned int init = TRUE;
extern char ip_addr1;
extern char ip_addr2;
extern unsigned int wifi_data;
unsigned int waiting_screen = FALSE;
char direction;
extern unsigned int start_up = RESET_STATE;
char stat_command[SMALL_RING_SIZE] = "AT+NSTAT=?\r";
char port_command[SMALL_RING_SIZE] = "AT+NSTCP=1998,1\r";
unsigned int command_process = RESET_STATE;
extern volatile int command_received;
char key[FOUR] = "1998";
unsigned int hundreds = RESET_STATE;
unsigned int tens = RESET_STATE;
unsigned int ones = RESET_STATE;
unsigned int duration = RESET_STATE;
unsigned int completed = RESET_STATE;
extern unsigned int queue_position;
unsigned int ptr = BEGINNING;
unsigned int unbasic = FALSE;
char arrived[TEN] = "Arrived   ";
unsigned int progress = RESET_STATE;
extern volatile unsigned int rand_time;
char adc_char[FIVE] = {' '};
unsigned int start_timer = FALSE;
unsigned int initial = RESET_STATE;


void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports(argument);                // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_ADC();                          // Initialize ADC
  Init_Serial_UCA1(switch_state);       //Initialize UCA1 UART Operation
  
  strcpy(display_line[TOP_LINE],  "          ");
  strcpy(display_line[MID_LINEA], "          ");
  strcpy(display_line[MID_LINEB], "          ");
  strcpy(display_line[BOT_LINE],  "          ");
  display_changed = TRUE;

//------------------------------------------------------------------------------
// Beginning of the "While" Operating System
//------------------------------------------------------------------------------
 state = RESET_STATE;
 unsigned int switch1 = switch_pressed1;
 unsigned int switch2 = switch_pressed2;
 unsigned int wr = usb_rx_ring_wr;
 unsigned int rd = usb_rx_ring_rd;
 myTime = RESET_STATE;
 
 while(ALWAYS) {                      // Can the Operating system run
   
//------------------------------------------------------------------------------
// IOT Boot-Up
//------------------------------------------------------------------------------
   if(init == TRUE){
     switch(start_up){
     case START_UP:
       //time delay - set IOT Reset high / initialize serial port
       if(myTime >= LIL_DELAY){
         P5OUT & ~IOT_RESET;
         Init_Serial_UCA0(switch_state);
         if(myTime >= ANOTHER_SLIGHTLY_ARBITRARY_TIME){
           start_up = IP_INFO;
         }
       }
       break;
       //send 'AT+NSTAT=?' for IP information
     case IP_INFO:
       for(int i = RESET_STATE; i<LARGE_RING_SIZE; i++){
         comm_output[i] = stat_command[i];
         if(stat_command[i] == NULL){
           myTime = RESET_STATE;
           start_up = CLR_BUFF;
         }
       }
       UCA0_index = RESET_STATE;
       UCA0IE |= UCTXIE; // Enable TX interrupt
       break;
       //clear transmit array
     case CLR_BUFF:
       if(myTime >= LIL_DELAY){
         for(int i = RESET_STATE; i<LARGE_RING_SIZE; i++){
           comm_output[i] = '\0';
         }
         start_up = CONFIG_WIFI;
       }
       break;
       //send 'AT+NSTCP=1998,1' to configure wireless comm. via TCP Client
     case CONFIG_WIFI:
       for(int i = RESET_STATE; i<LARGE_RING_SIZE; i++){
         comm_output[i] = port_command[i];
       }
       UCA0_index = RESET_STATE;
       UCA0IE |= UCTXIE; // Enable TX interrupt
       myTime = RESET_STATE;
       start_up = WAITING;
       break;
       //wait for first command
     case WAITING:
       if(myTime > LONG_DELAY){
         strcpy(display_line[TOP_LINE],  "          ");
         strcpy(display_line[MID_LINEA], " Waiting  ");
         strcpy(display_line[MID_LINEB], "          ");
         strcpy(display_line[BOT_LINE],  "          ");
         display_changed = TRUE;
         init = FALSE;
       }
       break;
     default: break;
     }
   }

//------------------------------------------------------------------------------
// Process incoming commands
//------------------------------------------------------------------------------
   if(command_received == TRUE){
     lcd_BIG_mid();
     start_timer = TRUE;
     unsigned int check = RESET_STATE;
     switch(command_process){
     //password
     case PASSWORD:
       for(int i = RESET_STATE; i<sizeof(key); i++){
         if(key[i] == command[ptr][i]){ check++;}
       }
       if(check == FOUR){ command_process = DIRECTION; }
       break;
     //direction *F - Forward* *B - REVERSE*
     case DIRECTION:
       direction = command[ptr][FOUR];
       if(direction == 'F') { command_process = REG_COMMAND; }
       else if(direction == 'B') { command_process = REG_COMMAND; }
       else if(direction == 'L') { command_process = REG_COMMAND; }
       else if(direction == 'R') { command_process = REG_COMMAND; }
       else if(direction == 'E') { command_process = REG_COMMAND; }
       //non basic commands
       else if(direction == 'N') { command_process = BL_FOLLOW; }
       else if(direction == 'A') { command_process = ARRIVED; }
       else{ 
         command_process = RESET_STATE;
       }
       break;
     //duration (0 - 999)
     case REG_COMMAND:
       if(command[ptr][DURATION] != C_R){ command_process = RESET_STATE; }
       else if(direction == 'E'){ 
         duration = A_SLIGHTLY_ARBITRARY_TIME; 
         command_process = MOVE;
       }
       else{
         hundreds = command[ptr][HUNNID];
         tens = command[ptr][TENNY];
         ones = command[ptr][ONEY];
         hundreds = (hundreds - ASCII_OFFSET) * HUNDRED;
         tens = (tens - ASCII_OFFSET) * TEN;
         ones = (ones - ASCII_OFFSET);
         duration = hundreds + tens + ones;
         command_process = MOVE;
       }
       break;
     //perform command
     case MOVE:
       movements(direction);
       command_process = FINAL;
       myTime = RESET_STATE;
       break;
     //finished?
     case FINAL:
       if(myTime >= duration || unbasic == TRUE){
         unbasic = FALSE;
         Wheels_Off();
         waiting_screen = TRUE;
         ptr++;
         command_process = RESET_STATE;
         if(ptr != queue_position){
           command_received = TRUE;
         }
         else if(direction == 'E'){
           strcpy(display_line[MID_LINEA], " FINISHED "); 
           command_received = FALSE;
           display_changed = TRUE;
           waiting_screen = FALSE;
           start_timer = RESET_STATE;
         }
         else{
           command_received = FALSE;
         }
       }
       else if(direction == 'E' && myTime == TEN){
         RIGHT_FORWARD_SPEED = LIL_SPEEDY;
         LEFT_FORWARD_SPEED = LIL_MORE_SPEEDY;
       }
     break;  
     case ARRIVED:
       movements(direction);
       unbasic = TRUE;
       myTime = RESET_STATE;
       command_process = FINAL;
       break;
       //special command - number 8
     case BL_FOLLOW:
       Movement_8();
       unbasic = TRUE;
       break;
     default: break;
     }
   }

//------------------------------------------------------------------------------
   //display IP information
   if(wifi_data == TRUE){
     strcpy(display_line[TOP_LINE],  "CenturyLin");
     strcpy(display_line[MID_LINEA], "IP ADDRESS");
     strcpy(display_line[MID_LINEB], &ip_addr1);
     strcpy(display_line[BOT_LINE],  &ip_addr2);
     display_changed = TRUE;
     wifi_data = FALSE;
     //wait for IP info
     if(start_up != LIL_DELAY){
       start_up = LIL_DELAY;
     }
   }
//------------------------------------------------------------------------------
   //revert to wait screen
   if(waiting_screen == TRUE){
     lcd_BIG_mid();
     strcpy(display_line[MID_LINEA], " WAITING  ");
     waiting_screen = FALSE;
   }
   if(start_timer == TRUE){
     if(initial == RESET_STATE){
       rand_time = RESET_STATE;
       initial++;
     }
     lcd_BIG_mid();
     HextoBCD(rand_time);
     strcpy(display_line[MID_LINEB], adc_char);
     display_changed = TRUE;
   }
   
    Switches_Process();                // Check for switch state change
    Display_Process();
 }
}
//------------------------------------------------------------------------------


void movements(char dir){
  lcd_BIG_mid();
  if(dir == 'F'){
    strcpy(display_line[MID_LINEA], " FORWARD  "); 
    display_changed = TRUE;
    LEFT_FORWARD_SPEED = LIL_MORE_SPEEDY;
    RIGHT_FORWARD_SPEED = ALMOST_SPEEDY;
  }
  if(dir == 'B'){
    strcpy(display_line[MID_LINEA], " REVERSE  ");
    display_changed = TRUE;
    LEFT_REVERSE_SPEED = LIL_MORE_SPEEDY;
    RIGHT_REVERSE_SPEED = ALMOST_SPEEDY;
  }
  if(dir == 'L'){
    strcpy(display_line[MID_LINEA], "  LEFT    "); 
    display_changed = TRUE;
    LEFT_REVERSE_SPEED = LIL_MORE_SPEEDY;
    RIGHT_FORWARD_SPEED = LIL_LESS_SPEEDY;
  }
  if(dir == 'R'){
    strcpy(display_line[MID_LINEA], "  RIGHT   "); 
    display_changed = TRUE;
    LEFT_FORWARD_SPEED = LIL_MORE_SPEEDY;
    RIGHT_REVERSE_SPEED = KINDA_SPEEDY;
  }
  if(dir == 'A'){
    arrived[INDEX9] = command[ptr][INDEX7];
    strcpy(display_line[TOP_LINE], arrived);
  }
  if(dir == 'N'){
    
  }
  if(dir == 'E'){
    strcpy(display_line[MID_LINEA], "   EXIT   "); 
    display_changed = TRUE;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = KINDA_SPEEDY;
  }
}

void Wheels_Off(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void Movement_8(void){
  switch(progress){
  case BL_START:
    strcpy(display_line[MID_LINEA], "  START   ");
    display_changed = TRUE;
    LEFT_FORWARD_SPEED = ALMOST_SPEEDY;
    RIGHT_FORWARD_SPEED = ADEQUATE_SPEED;
    myTime = RESET_STATE;
    progress = BL_INTERCEPT;
    break;
  case BL_INTERCEPT:
    if(myTime >= FIVE_SEC){
      P3OUT |= IR_LED;
      strcpy(display_line[MID_LINEA], "INTERCEPT ");
      display_changed = TRUE;
      progress = BL_INTERCEPTED;
    }
    break;
  case BL_INTERCEPTED:
    strcpy(display_line[MID_LINEA], "INTERCEPT ");
    display_changed = TRUE;
    if((ADC_Left_Detect > BIG_THRESHOLD)||(ADC_Right_Detect > BIG_THRESHOLD)){
      Wheels_Off();
      progress = BL_TURN;
      myTime = RESET_STATE;
    }
    break;
  case BL_TURN:
    strcpy(display_line[MID_LINEA], "INTERCEPT ");
    display_changed = TRUE;
    if(myTime >= TWO_SEC){
      LEFT_REVERSE_SPEED = JUST_ANOTHER_SPEED;
      RIGHT_FORWARD_SPEED = LIKE_NOT_SLOW;
      progress = BL_FOLLOW;
    }
    break;
  case BL_FOLLOW2:
    if((ADC_Right_Detect > SMALL_THRESHOLD)){
      Wheels_Off();
      myTime = RESET_STATE;
      strcpy(display_line[MID_LINEA], "BL TRAVEL ");
      display_changed;
      progress = BL_TRAVEL;
    }
    break;
  case BL_TRAVEL:
    if(myTime >= FIFTEEN_SEC){
      Wheels_Off();
      //P3OUT &= ~IR_LED;
      progress = BL_START;
      command_process = FINAL;
      myTime = RESET_STATE;
    }
    if(myTime == TWO_SEC){
      strcpy(display_line[MID_LINEA], "BL CIRCLE ");
      display_changed;
    }
    //on line
    if((ADC_Left_Detect > SMALL_THRESHOLD) && (ADC_Right_Detect > SMALL_THRESHOLD)){
      LEFT_FORWARD_SPEED = MARGINALLY_SPEEDY;
      RIGHT_FORWARD_SPEED = LIKE_NOT_SLOW;
    }
    //left off line
    if((ADC_Left_Detect < SMALL_THRESHOLD) && (ADC_Right_Detect > SMALL_THRESHOLD)){
      LEFT_FORWARD_SPEED = FINALLY_THE_END;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
    }
    //right off line
    if((ADC_Left_Detect > SMALL_THRESHOLD) && (ADC_Right_Detect < SMALL_THRESHOLD)){
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = FINALLY_THE_END;
    }
    break;
  default: break;
  }
  lcd_BIG_mid();
}

//-----------------------------------------------------------------------------
// Hex to BCD Conversion 
// Convert a Hex number to a BCD for display on an LCD or monitor 
// 
//-----------------------------------------------------------------------------
void HextoBCD(int hex_value){ 
  int value = RESET_STATE; 
  while (hex_value > TH_LIMIT){ 
    hex_value = hex_value - THOUS; 
    value = value + ALWAYS; 
    adc_char[INDEX0] = ASCII_OFFSET + value;
    if(value == RESET_STATE){
      adc_char[INDEX0] = '0';
    }
  } 
  value = RESET_STATE; 
  while (hex_value > H_LIMIT){ 
    hex_value = hex_value - HUNDRED; 
    value = value + ALWAYS; 
    adc_char[INDEX1] = ASCII_OFFSET + value; 
    if(value == RESET_STATE){
      adc_char[INDEX1] = '0';
    }
  } 
  if(value == RESET_STATE){
      adc_char[INDEX1] = '0';
    }
  value = RESET_STATE; 
  while (hex_value > TEN_LIMIT){ 
    hex_value = hex_value - TEN; 
    value = value + ALWAYS; 
    adc_char[INDEX2] = ASCII_OFFSET + value;
    if(value == RESET_STATE){
      adc_char[INDEX2] = '0';
    }
  } 
  if(value == RESET_STATE){
      adc_char[INDEX2] = '0';
    }

  if(adc_char[INDEX1] == '\0'){
    adc_char[INDEX1] = ' ';
    }
  adc_char[INDEX3] = '.';
  adc_char[INDEX4] = ASCII_OFFSET + hex_value; 
  
} 
//-----------------------------------------------------------------------------