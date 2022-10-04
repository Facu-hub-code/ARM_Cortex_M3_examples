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
    configTimer();
    while(1){}
    return 1;
}

void configGPIO(void){
    LPC_GPIO0->FIODIR   |=  (1<<22);
    return;
}

/*
La siguiente configuracion indica que el ADC va a trabajar a la maxima frecuencia 
y que la interrupcion va ser dada por un timer
*/
void configADC(void){
    LPC_SC->PCONP           |=  (1<<12);
    LPC_ADC->ADCR           |=  (1<<21); // Habilita el ADC
    LPC_SC->PCLKSEL0        |=  (3<<24); //  CLK / 8 = 12,5Mhz
    LPC_ADC->ADRC           &= ~(255<<8) //[15:8] CLKDIV
  //LPC_ADCR->ADCR          |=  (1<<0); //chanel
  //LPC_ADC->ADCR           |=  (1<<16); // burst
    LPC_ADC->ADCR           |=  (1<<25); //match
    LPC_ADC->ADCR           &=  ~(3<<24); //match
    LPC_ADC->ADCR           |=  (1<<27); //edge
    LPC_PINCON->PINMODE1    |=  (1<<15); //ni pull up ni pull down
    LPC_PINCON->PINSEL1     |=  (1<<14); //analogico
    LPC_ADC->ADINTEN        |=  1; //permito que genere interrupciones

    NVIC_EnableIRQ(ADC_IRQn);

    return;
}

void confTimer(){
	LPC_SC->PCONP		|=	(1<<1); //pag 65 por defecto timer 1
	LPC_SC->PCLKSEL0 	|=	(1<<2); //pag 59 clk del periferico 
	//LPC_PINCON->PINSEL3	|=	(3<<20); //pag 120 
	LPC_TIM0->EMR		|=	(3>>6); //pag 509 toggle
	LPC_TIM0->MR1 		= 	10000000;
	LPC_TIM0->MCR 		|= 	(1<<4);	//pag 507 reset on match
	LPC_TIM0->TCR		=	3		//pag 505 hab y reset
	LPC_TIM0->TCR		&=	~(1<<1);
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