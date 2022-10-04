/*
    Caracteristicas del ADC [29.2]
    - f = 200khz
    - 12 bits de presicion
    - 8 pines disponibles
*/
#include "LPxx.h"

int main(){
    configGPIO();
    configADC();
    while(1){}
    return 1;
}

void configGPIO(void){
    LPC_GPIO0->FIODIR   |=  (1<<22);
    return;
}

void configADC(void){
    LPC_SC->PCONP           |=  (1<<12);
    LPC_ADC->ADCR           |=  (1<<21); // Habilita el ADC
    LPC_SC->PCLKSEL0        |=  (3<<24); //  CLK / 8
    LPC_ADC->ADRC           &= ~(255<<8) //[15:8] CLKDIV
  //LPC_ADCR->ADCR          |=  (1<<0); //chanel
    LPC_ADC->ADCR           |=  (1<<16); // burst
    LPC_PINCON->PINMODE1    |=  (1<<15); //ni pull up ni pull down
    LPC_PINCON->PINSEL1     |=  (1<<14);
    LPC_ADC->ADINTEN        |=  1;

    NVIC_EnableIRQ(ADC_IRQn);

    return;
}

/*
    Mapeo de la señal electrica en valores de codigo.
    4096(value) son 3,3v
    x(value) son x voltios
*/
void ADC_IRQHandler(void){
    ADC0Value   =   ((LPC_ADC->ADDR0)>>4) && 0xFFF; //Variable auxiliar para observar el resultado
    if(ADC0Value < 2054){
        LPC_GPIO0->FIOSET = (1<<22); //Prendo el led
    }else{
        LPC_GPIO0->FIOCLR = (1 << 22); //Apago el led
    }
}