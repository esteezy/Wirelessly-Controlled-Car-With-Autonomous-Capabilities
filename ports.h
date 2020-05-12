// ------------------------------------------------------------------------------
//
//  Description: Macro definitions for ports.c (pin declarations)
//
//  Author: Evan Mason
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
// ------------------------------------------------------------------------------

//Port 1 Pins
#define RED_LED         (0x01) // 0 RED LED 0
#define A1_SEEED        (0x02) // 1 A1_SEEED
#define V_DETECT_L      (0x04) // 2 V_DETECT_L
#define V_DETECT_R      (0x08) // 3 V_DETECT_R
#define A4_SEEED        (0x10) // 4 A4_SEEED
#define V_THUMB         (0x20) // 5 V_THUMB
#define UCA0RXD         (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD         (0x80) // 7 Back Channel UCA0TXD

//Port 2 Pins
#define P2_0            (0x01) // 0
#define P2_1            (0x02) // 1
#define P2_2            (0x04) // 2
#define SW2             (0x08) // 3 SW2
#define P2_4            (0x10) // 4 
#define P2_5            (0x20) // 5 
#define LFXOUT          (0x40) // 6 XOUTR
#define LFXIN           (0x80) // 7 XINR

//Port 3 Pins
#define TEST_PROBE      (0x01) // 0 TEST PROBE
#define CHECK_BAT       (0x02) // 1 CHECK_BAT
#define OA2N            (0x04) // 2 Photodiode Circuit
#define OA2P            (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT       (0x10) // 4 SMCLK
#define IR_LED          (0x20) // 5 IR_LED
#define IOT_LINK        (0x40) // 6 IOT_LINK
#define P3_7            (0x80) // 7 P3_7

//Port 4 Pins
#define RESET_LCD       (0x01) // 0 RESET_LCD
#define SW1             (0x02) // 1 SW1
#define UCA1RXD         (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD         (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD     (0x10) // 4 Chip Select
#define UCB1CLK         (0x20) // 5 SPI mode - clock output - UCB1CLK
#define UCB1SIMO        (0x40) // 6 UCB1SIMO
#define UCB1SOMI        (0x80) // 7 UCB1SOMI

//Port 5 Pins 
#define IOT_RESET       (0x01) // 0 IOT_RESET
#define V_BAT           (0x02) // 1 V_BAT
#define IOT_PROG_SEL    (0x04) // 2 IOT_PROGRAM_SELECT
#define V_3_3           (0x08) // 3 V_3.3
#define IOT_PROG_MODE   (0x10) // 4 IOT_PROGRAM_MODE

//Port 6 Pins
#define R_FORWARD       (0x01) // 0 R_FORWARD
#define L_FORWARD       (0x02) // 1 L_FORWARD
#define R_REVERSE       (0x04) // 2 R_REVERSE
#define L_REVERSE       (0x08) // 3 L_REVERSE
#define LCD_BACKLITE    (0x10) // 4 LCD_BACKLITE
#define P6_5            (0x20) // 5 
#define GRN_LED         (0x40) // 6 GRN_LED