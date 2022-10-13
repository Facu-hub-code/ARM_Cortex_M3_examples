/*
    Caracteristicas del ADC [29.2]
    - f = 200khz
    - 12 bits de presicion
    - 8 pines disponibles
*/
#include <LP17xx.h>

int main(){
    configGPIO();
    configADC();
    while(1){}
    return 1;
}

void configGPIO(void){
    LPC_GPIO0->FIODIR   |=  (1<<22); //Pin 22 como salida
    return;
}

void configADC(void){
    LPC_SC->PCONP           |=  (1<<12); // bit 12 PCADC = 1 (Prendo el periferico)
    LPC_SC->PCLKSEL0        |=  (3<<24); // bit 25 y 24 PCLK_ADC = 11  (CLK / 8)
    LPC_ADC->ADCR           |=  (1<<21); // bit 21 PDN = 1 (Habilita el ADC)
    LPC_ADC->ADCR           |=  (1<<0); //  bits 0:7 Elijo el canal (hay 8)
    LPC_ADC->ADCR           &= ~(255<<8) //[15:8] CLKDIV

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

    float volt = ADC0Value*3.3/4096;

    if(ADC0Value < 2054){
        LPC_GPIO0->FIOSET = (1<<22); //Prendo el led
    }else{
        LPC_GPIO0->FIOCLR = (1 << 22); //Apago el led
    }
}