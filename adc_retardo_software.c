/*
    Caracteristicas del ADC [29.2]
    - f = 200khz
    - 12 bits de presicion
    - 8 pines disponibles
*/
#include "LPxx.h"

void ADC_IRQHandler(void);
void configPin(void);
void configADC(void);

int main(){
    uint32_t tmp;
    configPin();
    configADC();

    while(1){
        //Start conversion
        ADC_StartCmd(LPC_ADC, ADC_START_NOW);
        //Activo la interrupcion 
        NVIC_EnableIRQ(ADC_IRQn);
        // retardo por software
        for (tmp = 0; tmp < 1000000; i++);
        return 0;
    }
}

void configPin(void){
    //Recordar cargar el driver !!!
    PINSEL_CFG_Type PinCfg;
    PinCfg.Funcnum = 1; //Funcion 1
    PinCfg.OpenDrain = 0; //normal
    PinCfg.Pinmode = 0; // ni pull up ni pull down
    PinCfg.Pinmnum = 25; // pin 25 - el pin cuenta con esta funcionalidad.
    PinCfg.Portnum = 0; // puerto 0
    PINSEL_ConfigPin(&PinCfg);
    return;
}

/*
La siguiente configuracion indica que el ADC va a trabajar a la maxima frecuencia 
y que la interrupcion va ser dada por un timer
*/
void configADC(void){
    ADC_Init(LPC_ADC, 200000); //frecuencia de muestreo de 200khz
    ADC_IntConfig(LPC_ADC, _ADC_INT, ENABLE); //Habilite las interuupciones por ADC
    ADC_ChannelCmd(LPC_ADC, _ADC_CHANNEL, ENABLE); //Canal 2

    NVIC_SetPriority(ADC_IRQn, (9)); //seteo prioridad
    return;
}

void ADC_IRQHandler(void){
    adc_value = 0;
    //Pregunto que canal genero la interrupcion
    if(ADC_ChannelGetStatus(LPC_ADC, _ADC_CHANNEL, ADC_DATA_DONE)){
        //Tomo el valor
        adc_value = ADC_ChannelGetData(LPC_ADC, _ADC_CHANNEL);
        //Desactivo la interrupcion
        NVIC_DisableIRQ(ADC_IRQn);
    }
}