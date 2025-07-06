/**
 ******************************************************************************
 * @file    ADuC834.h
 * @author  J.Soto
 * @version V1.2.0
 * @date    Nov 11th, 2023
 * @brief   This file contains the defines for ADuC834's SFRs
 ******************************************************************************
 */

#ifndef REG_ADUC834_H
#define REG_ADUC834_H

#include <compiler.h>

SFR(P0, 0x80); // Port 0 
    SBIT(P0_0, 0x80, 0); // Port 0 Bit 0
    SBIT(P0_1, 0x80, 1); // Port 0 Bit 1
    SBIT(P0_2, 0x80, 2); // Port 0 Bit 2
    SBIT(P0_3, 0x80, 3); // Port 0 Bit 3
    SBIT(P0_4, 0x80, 4); // Port 0 Bit 4
    SBIT(P0_5, 0x80, 5); // Port 0 Bit 5
    SBIT(P0_6, 0x80, 6); // Port 0 Bit 6
    SBIT(P0_7, 0x80, 7); // Port 0 Bit 7

SFR(SP,  0x81); // Stack Pointer
SFR(DPL, 0x82); // Data Pointer LSB
SFR(DPH, 0x83); // Data Pointer MSB
SFR(DPP, 0x84); // Data Pointer Page Byte

SFR(PCON, 0x87); // Power Control Register
   #define SMOD   0x80 // Double UART Baud Rate.
   #define SERIPD 0x40 // SPI Power-Down Interrupt Enable
   #define INT0PD 0x20 // INT0 Power-Down Interrupt Enable
   #define ALEOFF 0x10 // Disable ALE Output
   #define GF1    0x08 // General-Purpose Flag Bit 1
   #define GF0    0x04 // General-Purpose Flag Bit 0
   #define PD     0x02 // Power-Down Mode Enable
   #define IDL    0x01 // Idle Mode Enable

SFR(TCON, 0x88); // Timer/Counter 0 and 1 Control Register
    SBIT(TF1, 0x88, 7); // Timer 1 Overflow Flag
    SBIT(TR1, 0x88, 6); // Timer 1 Run Control Flag
    SBIT(TF0, 0x88, 5); // Timer 0 Overflow Flag
    SBIT(TR0, 0x88, 4); // Timer 0 Run Control Flag
    SBIT(IE1, 0x88, 3); // External Interrupt 1 Flag
    SBIT(IT1, 0x88, 2); // External Interrupt 1 Trigger Type
    SBIT(IE0, 0x88, 1); // External Interrupt 0 Flag
    SBIT(IT0, 0x88, 0); // External Interrupt 0 Trigger Type

SFR(TMOD, 0x89); // Timer/Counter 0 and 1 Mode Register
   #define GATE1 0x80 // Timer 1 Gating Control
   #define C_T1  0x40 // Timer 1 Timer or Counter Select Bit
   #define M1_1  0x20 // Timer 1 Mode Select Bit 1
   #define M0_1  0x10 // Timer 1 Mode Select Bit 0
   #define GATE0 0x08 // Timer 0 Gating Control
   #define C_T0  0x04 // Timer 0 Timer or Counter Select Bit
   #define M1_0  0x02 // Timer 0 Mode Select Bit 1
   #define M0_0  0x01 // Timer 0 Mode Select Bit 0

SFR(TL0, 0x8A); // Timer 0 LSB
SFR(TL1, 0x8B); // Timer 1 LSB
SFR(TH0, 0x8C); // Timer 0 MSB
SFR(TH1, 0x8D); // Timer 1 MSB

SFR(P1, 0x90); // Port 1
    SBIT(P1_0, 0x90, 0); // Port 1 Bit 0
    SBIT(P1_1, 0x90, 1); // Port 1 Bit 1
    SBIT(P1_2, 0x90, 2); // Port 1 Bit 2
    SBIT(P1_3, 0x90, 3); // Port 1 Bit 3
    SBIT(P1_4, 0x90, 4); // Port 1 Bit 4
    SBIT(P1_5, 0x90, 5); // Port 1 Bit 5
    SBIT(P1_6, 0x90, 6); // Port 1 Bit 6
    SBIT(P1_7, 0x90, 7); // Port 1 Bit 7
    // Alternate Names
    SBIT(T2, 0x90, 0);   // Timer/Counter 2 External Input
    SBIT(PWM0, 0x90, 0); // PWM0 Output
    SBIT(T2EX, 0x90, 1); // Timer/Counter 2 Capture/Reload Trigger
    SBIT(PWM1, 0x90, 1); // PWM1 Output

SFR(SCON, 0x98); // UART Serial Port Control Register
   SBIT(SM0, 0x98, 7); // UART Serial Mode Select Bit 0
   SBIT(SM1, 0x98, 6); // UART Serial Mode Select Bit 1
   SBIT(SM2, 0x98, 5); // Multiprocessor Communication Enable Bit
   SBIT(REN, 0x98, 4); // Serial Port Receive Enable Bit
   SBIT(TB8, 0x98, 3); // Serial Port Transmit (Bit 9)
   SBIT(RB8, 0x98, 2); // Serial Port Receiver (Bit 9)
   SBIT(TI,  0x98, 1); // Serial Port Transmit Interrupt Flag
   SBIT(RI,  0x98, 0); // Serial Port Receive Interrupt Flag

SFR(SBUF, 0x99);   // UART Serial Port Data Buffer
SFR(I2CDAT, 0x9A); // I2C Data Register
SFR(I2CADD, 0x9B); // I2C Address Register
SFR(T3FD, 0x9D);   // Fractional Divider Ratio

SFR(T3CON, 0x9E); //Timer Baud Rate Control Register
   #define T3EN  0x80 // Timer 3 Baud Rate Generation Enable
   #define DIV2  0x04 // Binary Divider Factor bit 2
   #define DIV1  0x02 // Binary Divider Factor bit 1
   #define DIV0  0x01 // Binary Divider Factor bit 0

SFR(P2, 0xA0); // Port 2
   SBIT(P2_0, 0xA0, 0); // Port 2 Bit 0
   SBIT(P2_1, 0xA0, 1); // Port 2 Bit 1
   SBIT(P2_2, 0xA0, 2); // Port 2 Bit 2
   SBIT(P2_3, 0xA0, 3); // Port 2 Bit 3
   SBIT(P2_4, 0xA0, 4); // Port 2 Bit 4
   SBIT(P2_5, 0xA0, 5); // Port 2 Bit 5
   SBIT(P2_6, 0xA0, 6); // Port 2 Bit 6
   SBIT(P2_7, 0xA0, 7); // Port 2 Bit 7

SFR(TIMECON, 0xA1); // TIC Control Register Register
    #define ITS1 0x20 // Interval Timebase Selection Bit 1
    #define ITS0 0x10 // Interval Timebase Selection Bit 0
    #define STI  0x08 // Single Time Interval Bit
    #define TII  0x04 // TIC Interrupt Bit
    #define TIEN 0x02 // Time Interval Enable Bit
    #define TCEN 0x01 // Time Clock Enable Bit

SFR(HTHSEC, 0xA2); // Hundredths Seconds Time Register
SFR(SEC, 0xA3);    // Seconds Time Register
SFR(MIN, 0xA4);    // Minutes Time Register
SFR(HOUR, 0xA5);   // Hours Time Register
SFR(INTVAL, 0xA6); // User Time Interval Select Register

SFR(DPCON, 0xA7); // Data Pointer Control Register
    #define DPT   0x40 // Data Pointer Automatic Toggle Enable
    #define DP1m1 0x20 // Shadow Data Pointer Mode Bit 1
    #define DP1m0 0x10 // Shadow Data Pointer Mode Bit 0
    #define DP0m1 0x08 // Main Data Pointer Mode Bit 1
    #define DP0m0 0x04 // Main Data Pointer Mode Bit 0
    #define DPSEL 0x01 // Data Pointer Select

SFR(IE, 0xA8); // Interrupt Enable Register
   SBIT(EA, 0xA8, 7);   // Global Interrupt Enable
   SBIT(EADC, 0xA8, 6); // ADC Interrupt Enable
   SBIT(ET2, 0xA8, 5);  // Timer 2 Interrupt Enable
   SBIT(ES, 0xA8, 4);   // UART Serial Interrupt Enable
   SBIT(ET1, 0xA8, 3);  // Timer 1 Interrupt Enable
   SBIT(EX1, 0xA8, 2);  // External 1 Interrupt Enable
   SBIT(ET0, 0xA8, 1);  // Timer 0 Interrupt Enable
   SBIT(EX0, 0xA8, 0);  // External 0 Interrupt Enable

SFR(IEIP2, 0xA9); // Secondary Interrupt Enable Register
    #define PTI   0x40 // TIC Interrupt Priority
    #define PPSM  0x20 // Power Supply Monitor Interrupt Priority
    #define PSI   0x10 // SPI/I2C Serial Port Interrupt Priority
    #define ETI   0x04 // TIC Interrupt Enable
    #define EPSMI 0x02 // Power Supply Monitor Interrupt Enable
    #define ESI   0x01 // SPI/I2C Serial Port Interrupt Enable

SFR(PWMCON, 0xAE); // PWM Control Register
    #define MD2_PWM 0x40 // PWM Mode Bit 2 (Repeated SFR bit name)
    #define MD1_PWM 0x20 // PWM Mode Bit 1 (Repeated SFR bit name)
    #define MD0_PWM 0x10 // PWM Mode Bit 0 (Repeated SFR bit name)
    #define CDIV1   0x08 // PWM Clock Divider bit 1
    #define CDIV0   0x04 // PWM Clock Divider bit 0
    #define CSEL1   0x02 // PWM Clock Select bit 1
    #define CSEL0   0x01 // PWM Clock Select bit 0

SFR(CFG834, 0xAF); // ADuC834 Configuration Register
    #define EXSP   0x80 // Extended SP Enable
    #define XRAMEN 0x01 // XRAM Enable Bit

SFR(P3, 0xB0); // Port 3
   SBIT(P3_0, 0xB0, 0); // Port 3 Bit 0
   SBIT(P3_1, 0xB0, 1); // Port 3 Bit 1
   SBIT(P3_2, 0xB0, 2); // Port 3 Bit 2
   SBIT(P3_3, 0xB0, 3); // Port 3 Bit 3
   SBIT(P3_4, 0xB0, 4); // Port 3 Bit 4
   SBIT(P3_5, 0xB0, 5); // Port 3 Bit 5
   SBIT(P3_6, 0xB0, 6); // Port 3 Bit 6
   SBIT(P3_7, 0xB0, 7); // Port 3 Bit 7
   // Alternate Names
   SBIT(RXD, 0xB0, 0);
   SBIT(TXD, 0xB0, 1);
   SBIT(INT0, 0xB0, 2);
   SBIT(INT1, 0xB0, 3);
   SBIT(T0, 0xB0, 4);
   SBIT(T1, 0xB0, 5);
   SBIT(WR, 0xB0, 6);
   SBIT(RD, 0xB0, 7);

SFR(PWM0L, 0xB1); // PWM 0 Duty Cycle LSB
SFR(PWM0H, 0xB2); // PWM 0 Duty Cycle MSB
SFR(PWM1L, 0xB3); // PWM 1 Duty Cycle LSB
SFR(PWM1H, 0xB4); // PWM 1 Duty Cycle MSB
SFR(SPH, 0xB7);   // Stack Pointer MSB

SFR(IP, 0xB8); // Interrupt Priority Register
   SBIT(PADC, 0xB8, 6); // ADC Interrupt Priority Bit
   SBIT(PT2, 0xB8, 5);  // Timer 2 Interrupt Priority Bit
   SBIT(PS, 0xB8, 4);   // Serial Port Interrupt Priority Bit
   SBIT(PT1, 0xB8, 3);  // Timer 1 Interrupt Priority Bit
   SBIT(PX1, 0xB8, 2);  // External Interrupt 1 Priority Bit
   SBIT(PT0, 0xB8, 1);  // Timer 0 Interrupt Priority Bit
   SBIT(PX0, 0xB8, 0);  // External Interrupt 0 Priority Bit

SFR(ECON, 0xB9);   // Flash/EE Memory Control Register
SFR(EDATA1, 0xBC); // EE Page Data Byte 1
SFR(EDATA2, 0xBD); // EE Page Data Byte 2
SFR(EDATA3, 0xBE); // EE Page Data Byte 3
SFR(EDATA4, 0xBF); // EE Page Data Byte 4

SFR(WDCON, 0xC0); //Watchdog Timer Control Register
    SBIT(PRE3, 0xC0, 7); // Watchdog Timer Prescale Bit 3
    SBIT(PRE2, 0xC0, 6); // Watchdog Timer Prescale Bit 2
    SBIT(PRE1, 0xC0, 5); // Watchdog Timer Prescale Bit 1
    SBIT(PRE0, 0xC0, 4); // Watchdog Timer Prescale Bit 0
    SBIT(WDIR, 0xC0, 3); // Watchdog Interrupt Response Enable Bit
    SBIT(WDS, 0xC0, 2);  // Watchdog Status Bit
    SBIT(WDE, 0xC0, 1);  // Watchdog Enable Bit
    SBIT(WDWR, 0xC0, 0); // Watchdog Write Enable Bit

SFR(CHIPID, 0xC2); // ADuC834 System Self-Identification Register
SFR(EADRL, 0xC6);  // Flash/EE Address LSB
SFR(EADRH, 0xC7);  // Flash/EE Address MSB

SFR(T2CON, 0xC8); // Timer/Counter 2 Control Register
   SBIT(TF2, 0xC8, 7);   // Timer 2 Overflow Flag
   SBIT(EXF2, 0xC8, 6);  // Timer 2 External Flag
   SBIT(RCLK, 0xC8, 5);  // Receive Clock Enable Bit
   SBIT(TCLK, 0xC8, 4);  // Transmit Clock Enable Bit
   SBIT(EXEN2, 0xC8, 3); // Timer 2 External Enable Flag
   SBIT(TR2, 0xC8, 2);   // Timer 2 Start/Stop Control Bit
   SBIT(CNT2, 0xC8, 1);  // Timer 2 Timer or Counter Function Select Bit
   SBIT(CAP2, 0xC8, 0);  // Timer 2 Capture/Reload Select Bit

SFR(RCAP2L, 0xCA); // Timer 2 Capture LSB
SFR(RCAP2H, 0xCB); // Timer 2 Capture MSB
SFR(TL2, 0xCC);    // Timer 2 LSB
SFR(TH2, 0xCD);    // Timer 2 MSB

SFR(PSW, 0xD0); // Program Status Word
   SBIT(CY, 0xD0, 7);  // Carry Flag
   SBIT(AC, 0xD0, 6);  // Auxiliary Carry Flag
   SBIT(F0, 0xD0, 5);  // User-Defined Flag 0
   SBIT(RS1, 0xD0, 4); // Register Bank Select 1
   SBIT(RS0, 0xD0, 3); // Register Bank Select 0
   SBIT(OV, 0xD0, 2);  // Overflow Flag
   SBIT(F1, 0xD0, 1);  // User-Defined Flag 1
   SBIT(P, 0xD0, 0);   // Parity Flag

SFR(ADCMODE, 0xD1); // ADC Mode Register
    #define ADC0EN 0x20 // Primary ADC Enable
    #define ADC1EN 0x10 // Auxiliary ADC Enable
    #define MD2    0x04 // Primary and Auxiliary ADC Mode bit 2
    #define MD1    0x02 // Primary and Auxiliary ADC Mode bit 1
    #define MD0    0x01 // Primary and Auxiliary ADC Mode bit 0

SFR(ADC0CON, 0xD2); // Primary ADC Control Register
    #define XREF0 0x40 // Primary ADC External Reference Select Bit
    #define CH1   0x20 // Primary ADC Channel Selection Bit 1
    #define CH0   0x10 // Primary ADC Channel Selection Bit 0
    #define UNI0  0x08 // Primary ADC Unipolar Bit
    #define RN2   0x04 // Primary ADC Range Bit 2
    #define RN1   0x02 // Primary ADC Range Bit 1
    #define RN0   0x01 // Primary ADC Range Bit 0

SFR(ADC1CON, 0xD3); // Auxiliary ADC Control Register
    #define XREF1 0x40 // Auxiliary ADC External Reference Bit
    #define ACH1  0x20 // Auxiliary ADC Channel Selection Bit 1
    #define ACH0  0x10 // Auxiliary ADC Channel Selection Bit 0
    #define UNI1  0x08 // Auxiliary ADC Unipolar Bit

SFR(SF, 0xD4); // Sinc Filter Register

SFR(ICON, 0xD5); // Current Sources Control Register
    #define BO     0x40 // Burnout Current Enable Bit
    #define ADC1IC 0x20 // Auxiliary ADC Current Correction Bit
    #define ADC0IC 0x10 // Primary ADC Current Correction Bit
    #define I2PIN  0x08 // Current Source-2 Pin Select Bit
    #define I1PIN  0x04 // Current Source-1 Pin Select Bit
    #define I2EN   0x02 // Current Source-2 Enable Bit
    #define I1EN   0x01 // Current Source-1 Enable Bit

SFR(PLLCON, 0xD7); // PLL Control Register
    #define OSC_PD 0x80 // Oscillator Power-Down Bit
    #define LOCK   0x40 // PLL Lock Bit
    #define LTEA   0x10 // EA State At Reset/Power-On
    #define FINT   0x08 // Fast Interrupt Response Bit
    #define CD2    0x04 // CPU (Core Clock) Divider Bit 2
    #define CD1    0x02 // CPU (Core Clock) Divider Bit 1
    #define CD0    0x01 // CPU (Core Clock) Divider Bit 0

SFR(ADCSTAT, 0xD8); // ADC Status Register
    SBIT(RDY0, 0xD8, 7);   // Ready Bit For Primary ADC
    SBIT(RDY1, 0xD8, 6);   // Ready Bit For Auxiliary ADC
    SBIT(CAL, 0xD8, 5);    // Calibration Status Bit
    SBIT(NOXREF, 0xD8, 4); // No External Reference Bit
    SBIT(ERR0, 0xD8, 3);   // Primary ADC Error Bit
    SBIT(ERR1, 0xD8, 2);   // Auxiliary ADC Error Bit

SFR(ADC0L, 0xD9); // Primary ADC Conversion Result Low Byte
SFR(ADC0M, 0xDA); // Primary ADC Conversion Result Middle Byte 
SFR(ADC0H, 0xDB); // Primary ADC Conversion Result High Byte
SFR(ADC1L, 0xDC); // Auxiliary ADC Conversion Result Low Byte
SFR(ADC1H, 0xDD); // Auxiliary ADC Conversion Result High Byte

SFR(PSMCON, 0xDF); // Power Supply Monitor Control Register
    #define CMPD  0x80 // DVDD Comparator Bit
    #define CMPA  0x40 // AVDD Comparator Bit    
    #define PSMI  0x20 // Power Supply Monitor Interrupt Bit
    #define TPD1  0x10 // DVDD Trip Point Selection Bit 1
    #define TPD0  0x08 // DVDD Trip Point Selection Bit 0
    #define TPA1  0x04 // AVDD Trip Point Selection Bit 1
    #define TPA0  0x02 // AVDD Trip Point Selection Bit 0
    #define PSMEN 0x01 // Power Supply Monitor Enable Bit

SFR(ACC, 0xE0); // Accumulator
   SBIT(ACC_0, 0xE0, 0); // Accumulator Bit 0
   SBIT(ACC_1, 0xE0, 1); // Accumulator Bit 1
   SBIT(ACC_2, 0xE0, 2); // Accumulator Bit 2
   SBIT(ACC_3, 0xE0, 3); // Accumulator Bit 3
   SBIT(ACC_4, 0xE0, 4); // Accumulator Bit 4
   SBIT(ACC_5, 0xE0, 5); // Accumulator Bit 5
   SBIT(ACC_6, 0xE0, 6); // Accumulator Bit 6
   SBIT(ACC_7, 0xE0, 7); // Accumulator Bit 7

SFR(OF0L, 0xE1); // Primary ADC Offset Calibration Low Byte
SFR(OF0M, 0xE2); // Primary ADC Offset Calibration Middle Byte 
SFR(OF0H, 0xE3); // Primary ADC Offset Calibration High Byte
SFR(OF1L, 0xE4); // Auxiliary ADC Offset Calibration Low Byte
SFR(OF1H, 0xE5); // Auxiliary ADC Offset Calibration High Byte

SFR(I2CCON, 0xE8); // I2C Control Register
    SBIT(MDO, 0xE8, 7);   // I2C Software Master Data Output Bit
    SBIT(MDE, 0xE8, 6);   // I2C Software Master Data Output Enable Bit
    SBIT(MCO, 0xE8, 5);   // I2C Software Master Clock Output Bit
    SBIT(MDI, 0xE8, 4);   // I2C Software Master Data Input Bit
    SBIT(I2CM, 0xE8, 3);  // I2C Master/Slave Mode Bit
    SBIT(I2CRS, 0xE8, 2); // I2C Reset Bit (Slave Mode Only)
    SBIT(I2CTX, 0xE8, 1); // I2C Direction Transfer Bit (Slave Mode Only)
    SBIT(I2CI, 0xE8, 0);  // I2C Interrupt Bit (Slave Mode Only)

SFR(GN0L, 0xE9); // Primary ADC Gain Coefficient Low Byte
SFR(GN0M, 0xEA); // Primary ADC Gain Coefficient Middle Byte 
SFR(GN0H, 0xEB); // Primary ADC Gain Coefficient High Byte
SFR(GN1L, 0xEC); // Auxiliary ADC Gain Coefficient Low Byte
SFR(GN1H, 0xED); // Auxiliary ADC Gain Coefficient High Byte

SFR(B, 0xF0); // B Register
   SBIT(B_0, 0xF0, 0); // Register B Bit 0
   SBIT(B_1, 0xF0, 1); // Register B Bit 1
   SBIT(B_2, 0xF0, 2); // Register B Bit 2
   SBIT(B_3, 0xF0, 3); // Register B Bit 3
   SBIT(B_4, 0xF0, 4); // Register B Bit 4
   SBIT(B_5, 0xF0, 5); // Register B Bit 5
   SBIT(B_6, 0xF0, 6); // Register B Bit 6
   SBIT(B_7, 0xF0, 7); // Register B Bit 7

SFR(SPIDAT, 0xF7); // SPI Data Register

SFR(SPICON, 0xF8); // SPI Control Register
    SBIT(ISPI, 0xF8, 7); // SPI Interrupt Bit
    SBIT(WCOL, 0xF8, 6); // Write Collision Error Bit
    SBIT(SPE,  0xF8, 5); // SPI Interface Enable Bit
    SBIT(SPIM, 0xF8, 4); // SPI Master/Slave Mode Select Bit
    SBIT(CPOL, 0xF8, 3); // Clock Polarity Select Bit
    SBIT(CPHA, 0xF8, 2); // Clock Phase Select Bit
    SBIT(SPR1, 0xF8, 1); // SPI Bit Rate Select Bit 2
    SBIT(SPR0, 0xF8, 0); // SPI Bit Rate Select Bit 1

SFR(DACL, 0xFB); // DAC Data LSB
SFR(DACH, 0xFC); // DAC Data MSB

SFR(DACCON, 0xFD); // DAC Control Register
    #define DACPIN 0x10 // DAC Output Pin Select
    #define DAC8   0x08 // DAC 8-bit Mode Bit
    #define DACRN  0x04 // DAC Output Range Bit
    #define DACCLR 0x02 // DAC Clear Bit
    #define DACEN  0x01 // DAC Enable Bit

// Interrupt Vector Address = (number * 8) + 3
#define IE0_VECTOR  0  // External Interrupt 0
#define TF0_VECTOR  1  // Timer/Counter 0 Interrupt
#define IE1_VECTOR  2  // External Interrupt 1
#define TF1_VECTOR  3  // Timer/Counter 1 Interrupt
#define SI0_VECTOR  4  // RI/TI Serial Interrupt
#define TF2_VECTOR  5  // Timer/Counter 2 Interrupt 
#define EX2_VECTOR  5  // External Interrupt 2
#define RDY0_VECTOR 6  // Primary ADC Interrupt
#define RDY1_VECTOR 6  // Auxiliary ADC Interrupt
#define ISPI_VECTOR 7  // SPI Interrupt
#define I2CI_VECTOR 7  // I2C Interrupt
#define PSMI_VECTOR 8  // Power Supply Monitor Interrupt 
#define TII_VECTOR  9  // Time Interval Counter Interrupt
#define WDS_VECTOR  10 // Watchdog Interrupt

#endif //REG_ADUC834_H
