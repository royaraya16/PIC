/* 
 * File:   config.c
 * Author: Roy
 *
 * Created on August 26, 2015, 7:10 PM
 */

#include <xc.h>

//======================== Configuracion Timer0 ========================//
 
/*============================================
Function : inicia el modulo timer0
Input    : no
Output   : no
=============================================*/

void timer0Config(){
    /*** Configuracion del TIMER0 (DATASHEET PAG 127) ***/
    
    //Apagando el timer para realizar los cambios en la config
    TMR0ON = 0; 
    
    //Configurando 8bits (1) o 16bits (0)
    T08BIT = 1;
    
    //Reloj interno como fuente del timer
    T0CS = 0;
    
    //Preescalador asignado
    PSA = 0;
    
    //Preescalador de 1:256
    T0PS2 = 1; 
    T0PS1 = 1;
    T0PS0 = 1;
    
    //Iniciando el timer
    TMR0ON = 1;
}

//======================== Configuracion INTERRUPTS ========================//
 
/*============================================
Function : Configura los Interrupts
Input    : no
Output   : no
=============================================*/
void intConfig(){
       
    //Configuracion de los interrupts (DATASHEET PAG 101)
    GIEH = 1; //GLOBAL INTERRUPT ENABLE
    TMR0IE = 1; //TIMER0 OVERFLOW INTERRUPT ENABLE    
    ADIE = 1; //ANALOG TO DIGITAL INTERRUPT ENABLE
    
    
}

//======================== Configuracion I/O ========================//
 
/*============================================
Function : configura las diferentes entradas y salidas
Input    : no
Output   : no
=============================================*/
void ioConfig(){
    
    //Configurando RA0 como salida
    TRISA0 = 0;
    
    //Configurando RA1 como entrada del ADC
    TRISA1 = 1;
}

//======================== Configuracion ADC ========================//
 
/*============================================
Function : inicia el modulo ADC
Input    : no
Output   : no
=============================================*/
void adcConfig(){
    //Configuracion del ADC
        
     /*ADCON0
    | 7    | 6    | 5    | 4    | 3    | 2    | 1    | 0    |
    |  -   |  -   | CHS3 | CHS2 | CHS1 | CHS0 |GODONE| ADON |
      * 
      * 7 - Unimplemented: Read as ?0'
      * 6 - Unimplemented: Read as ?0
      * CHS3:CHS0: Analog Channel Select bits
            0000 = Channel 0 (AN0)
            0001 = Channel 1 (AN1)
            0010 = Channel 2 (AN2)
            0011 = Channel 3 (AN3)
            0100 = Channel 4 (AN4)
            0101 = Channel 5 (AN5)
            0110 = Channel 6 (AN6)
            0111 = Channel 7 (AN7)
            1000 = Channel 8 (AN8)
            1001 = Channel 9 (AN9)
            1010 = Channel 10 (AN10)
            1011 = Channel 11 (AN11)
            1100 = Channel 12 (AN12)
            1101 = Unimplemented
            1110 = Unimplemented
            1111 = Unimplemented
      * GO/DONE: A/D Conversion Status bit
            When ADON = 1:
            1 = A/D conversion in progress
            0 = A/D Idle
      *  ADON: A/D On bit
            1 = A/D converter module is enabled
            0 = A/D converter module is disabled 
     */

    ADCON0 = 0b00000001; // Configuracion inicial 
    
    /*ADCON1
    | 7    | 6    | 5    | 4    | 3    | 2    | 1    | 0    |
    |  -   |  -   | VCFG1| VCFG0| PCFG3| PCFG2| PCFG1| PCFG0|
     * 
     * 7 - Unimplemented: Read as ?0'
     * 6 Unimplemented: Read as ?0?
     * VCFG1: Voltage Reference Configuration bit (VREF- source)
        1 = VREF-
        0 = VSS
     * VCFG0: Voltage Reference Configuration bit (VREF+ source)
        1 = VREF+
        0 = VDD
     * PCFG3:PCFG0: A/D Port Configuration Control bits (DATASHEET PAGINA 266)
    */
    
    //Se configura para dejar AN12 y AN10 digitales y que no interfiera con SPI
    ADCON1 = 0b00001000; 
    
     /*ADCON2
    | 7    | 6    | 5    | 4    | 3    | 2    | 1    | 0    |
    | ADFM |  -   | ACQT2| ACQT1| ACQT0| ADCS2| ADCS1| ADCS0|
      * 
      * bit 7 ADFM: A/D Result Format Select bit
            1 = Right justified
            0 = Left justified
      * bit 6 Unimplemented: Read as ?0?
      * bit 5-3 ACQT2:ACQT0: A/D Acquisition Time Select bits
            111 = 20 TAD
            110 = 16 TAD
            101 = 12 TAD
            100 = 8 TAD
            011 = 6 TAD
            010 = 4 TAD
            001 = 2 TAD
            000 = 0 TAD
      * bit 2-0 ADCS2:ADCS0: A/D Conversion Clock Select bits
            111 = FRC (clock derived from A/D RC oscillator)(1)
            110 = FOSC/64
            101 = FOSC/16
            100 = FOSC/4
            011 = FRC (clock derived from A/D RC oscillator)(1)
            010 = FOSC/32
            001 = FOSC/8
            000 = FOSC/2
     * */

    ADCON2 = 0b00110011; // Resultado del A/D es justificado a la izquierda 

}

//======================== Configuracion SPI ========================//
 
/*============================================
Function : inicia el modulo SPI como master
Input    : no
Output   : no
=============================================*/
void spiConfig (){
    
    /*SSPSTAT
    | 7    | 6    | 5    | 4    | 3    | 2    | 1    | 0    |
    | SMP  | CKE  | D/A  | P    | S    | R/W  | UA   | BF   |
     * 
     * SMP - Sample bit
            SPI Master mode:
            1 = Input data sampled at end of data output time
            0 = Input data sampled at middle of data output time
            SPI Slave mode:
            SMP must be cleared when SPI is used in Slave mode.
     * CKE - SPI Clock Select bit
            1 = Transmit occurs on transition from active to Idle clock state
            0 = Transmit occurs on transition from Idle to active clock state
     * D/A - I2C only
     * P - - I2C only
     * S - - I2C only
     * R/W - I2C only
     * UA  - I2C only
     * BF - Buffer Full Status bit (Receive mode only)
            1 = Receive complete, SSPBUF is full
            0 = Receive not complete, SSPBUF is empty
    */
    
    SSPSTAT = 0b10000000;
    //SSPSTAT = 0x00; // SMP=0(slave mode),CKE=0(transmission on Idle to active clock state),all other bits 0      
    
    /*SSPCON1
    | 7    | 6    | 5    | 4    | 3    | 2    | 1    | 0    |
    | WCOL |SSPOV |SSPEN | CKP  |SSPM3 |SSPM2 |SSPM1 |SSPM0 |
     * 
     * WCOL - Write Collision Detect bit (Transmit mode only)
            1 = The SSPBUF register is written while it is still transmitting the previous word
            (must be cleared in software)
            0 = No collision
     * SSPOV - Receive Overflow Indicator bit(1)
            SPI Slave mode:
            1 = A new byte is received while the SSPBUF register is still holding the previous data. In case of overflow, the data in SSPSR is lost. Overflow can only occur in Slave mode. The user must read the
            SSPBUF, even if only transmitting data, to avoid setting overflow (must be cleared in software).
            0 = No overflow
     * SSPEN: Master Synchronous Serial Port Enable bit
            1 = Enables serial port and configures SCK, SDO, SDI and SS as serial port pins(2)
            0 = Disables serial port and configures these pins as I/O port pins(2)
     * CKP: Clock Polarity Select bit
            1 = Idle state for clock is a high level
            0 = Idle state for clock is a low level
     * SSPM3:SSPM0: Master Synchronous Serial Port Mode Select bits
            0101 = SPI Slave mode, clock = SCK pin, SS pin control disabled, SS can be used as I/O pin(3)
            0100 = SPI Slave mode, clock = SCK pin, SS pin control enabled(3)
            0011 = SPI Master mode, clock = TMR2 output/2
            0010 = SPI Master mode, clock = FOSC/64
            0001 = SPI Master mode, clock = FOSC/16
            0000 = SPI Master mode, clock = FOSC/4
    */
    
    SSPCON1 = 0b00100001;
    //SSPCON1 = 0x22; // SSPEN = 1 (enable serial port), SSPM[3-0] = 0b0010 (master mode,clock=FOSC/64), all other bits are zero                                        
    
    TRISC &= 0x7F;    // clear 7th bit keeping all other bits unchanged (SDO output)                         
    TRISB &= 0xFD; // clear 1th bit keeping all other bits unchanged (SCK output)
    TRISA |= 0x20; // clearing 5th bit, SS as output

    ADCON0 = 0x3C; // Disabling the ADC module which is multiplexed with SPI pins
    CMCON = 0x00; // Disabling the COMPARATOR module which is multiplexed with SPI pins
    SPPCON = 0x00; // Disabling the SERIAL PERIPHERAL CONTROL module which is multiplexed with SPI pins

    TRISD &= 0xFE; // Clearing 0th pin of PORTD as output ( SS for the slave )
    PORTD |= 0x01; // Setting 0th pin of PORTD ( Slave not selected )
}
