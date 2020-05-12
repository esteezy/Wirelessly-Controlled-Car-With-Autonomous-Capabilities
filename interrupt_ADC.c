// ------------------------------------------------------------------------------
//
//  Description: Function definitions for ADC Channel Interrupts
//
//  Author: Evan Mason
//  Feb 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
// ------------------------------------------------------------------------------

//Macros
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include  <string.h>

//Functions
void HEXtoBCD(int hex_value);
void adc_line(int line);

//Globals
extern volatile unsigned int ADC_Channel = RESET_STATE;
extern volatile unsigned int ADC_Left_Detect = RESET_STATE;
extern volatile unsigned int ADC_Right_Detect = RESET_STATE;
extern volatile unsigned int ADC_Thumb = RESET_STATE;
extern volatile unsigned int myTime;

//configure display
#pragma vector=ADC_VECTOR 
__interrupt void ADC_ISR(void){   
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){  
  case ADCIV_NONE:       
    break;     
  case ADCIV_ADCOVIFG:    // When a conversion result is written to the ADCMEM0                             
    break;                // before its previous conversion result was read.            
  case ADCIV_ADCTOVIFG:   // ADC conversion-time overflow       
    break;     
  case ADCIV_ADCHIIFG:    // Window comparator interrupt flags       
    break;     
  case ADCIV_ADCLOIFG:    // Window comparator interrupt flag       
    break;     
  case ADCIV_ADCINIFG:    // Window comparator interrupt flag       
    break;     
  case ADCIV_ADCIFG:      // ADCMEM0 memory register with the conversion result       
    ADCCTL0 &= ~ADCENC;   // Disable ENC bit
    switch (ADC_Channel++){       
    case CHANNEL_A2:                                    // Channel A2 Interrupt         
      ADCMCTL0 &= ~ADCINCH_2;                           // Disable Last channel A2         
      ADCMCTL0 |= ADCINCH_3;                            // Enable Next channel A3         
      ADC_Left_Detect = ADCMEM0;                        // Move result into Global         
      ADC_Left_Detect = ADC_Left_Detect >> SHIFT_2;     // Divide the result by 4         
      //HEXtoBCD(ADC_Left_Detect);                        // Convert result to String         
      //adc_line(DISP_LINE1);                             // Place String in Display          
      break;       
    case CHANNEL_A3:         
      ADCMCTL0 &= ~ADCINCH_3;                           // Disable Last channel A3         
      ADCMCTL0 |= ADCINCH_5;                            // Enable Next channel A5         
      ADC_Right_Detect = ADCMEM0;                       // Move result into Global         
      ADC_Right_Detect = ADC_Right_Detect >> SHIFT_2;   // Divide the result by 4         
      //HEXtoBCD(ADC_Right_Detect);                       // Convert result to String         
      //adc_line(DISP_LINE2);                             // Place String in Display        
      break;       
    case CHANNEL_A5: 
      ADCMCTL0 &= ~ADCINCH_5;                           // Disable Last channel A5 
      ADCMCTL0 |= ADCINCH_2;                            // Enable channel A2
      ADC_Thumb = ADCMEM0;                              // Move result into Global         
      ADC_Thumb = ADC_Thumb >> SHIFT_2;                 // Divide the result by 4         
      //HEXtoBCD(ADC_Thumb);                              // Convert result to String         
      //adc_line(DISP_LINE1);                             // Place String in Display
      ADC_Channel = RESET_STATE;                        // Set state back to beginning channel   
      break;       
    default:         
      break;     
    }   
    ADCCTL0 |= ADCENC;                // Enable Conversions     
    ADCCTL0 |= ADCSC;                 // Start next sample      
    break;     
  default: 
    break;   
  } 
}

