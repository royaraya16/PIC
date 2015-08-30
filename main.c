/* 
 * File:   main.c
 * Author: Roy
 *
 * Created on August 26, 2015, 10:34 PM
 */

#include <xc.h>

#include "fuses.h"
#include "config.h"

#define LED LATA0 //Define LEDPin

int main() {
    
    //Configuracion de interrupciones
    intConfig();
    
    //Configuracion de timer0
    timer0Config();
    
    //Configuracion de Inputs/Outputs
    ioConfig();
    
    //Configuracion de ADC
    adcConfig();
    
    //Iniciando SPI
    spiConfig();

    //OSCCON = 0x72; // set CPU Frequency as 8 MHz

    while(1);

    return 1;
}

void interrupt Timer0_ISR(void){
    
    if(TMR0IF){        
        //ADC
        LED = !LED;
        GO_DONE = 1; //Iniciar conversion
        
        //Timer Flag Reset
        TMR0IF = 0;
    }
    
    if (ADIF){
        //v = 2^8*ADRESH+ADRESL;
        //v = ((ADRESH<<8)|(ADRESL));
        //Se envia el registro del ADC que contiene la informacion importante
        //El adressL no contiene informacion relevante ya que se esta usando 
        //una configuracion de 8bits justificado a la izquierda
        SSPBUF=ADRESH;
        
        //ADC Flag Reset
        ADIF = 0;
    }
}


 

