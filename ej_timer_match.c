/*
Utilizando el Timer 1, escribir un código en C para que por cada presión de un pulsador,
la frecuencia de parpadeo de un led disminuya a la mitad debido a la modificación del 
reloj que llega al periférico. El pulsador debe producir una interrupción por GPIO0 con
flanco descendente. Adjuntar el código en C.
*/

#include "LPC17xx.h"

uint_32 divisor_frec;
uint_32 led22 = 0;

void confTimer(void);

int main(void){
	confGPIO(); //Recibe interumpe por flanco ascendente
	confTimer();
	while(1){}
	return 0;
}

void confGPIO(void){
	LPC_GPIO0->FIODIR	&=	~(1<<22);
    LPC_GPIOINT->IO0IntEnR |= (1<<22); //Interrumpe por GPIO
    NVIC_EnableIRQ(EINT3_IRQn); //Habilito la interrupcion
	return;
} 

/*
Configuro el timmer 1:
- PCONP Prende el periferico TMR1
- PCLKSEL0 seteo la frecuencia que le va llegar del timmer
- PINSEL3 asocia un pin de salida a la funcion de match
- EMR determina la funcionalidad del match 0: puede togglear la salida del pin correspondiente
- MCR cada vez que se genere la condicion de match, va generar una interrupcion.
- TCR 

//Configuracion en modo match
void confTimer1Match(){
	LPC_SC->PCONP		|=	(1<<2); //pag 65 prende el periferico
	LPC_SC->PCLKSEL1 	=	3; //pag 59 divide el cclk/8 
    //y despues la frec en 500.000.000
    
	LPC_PINCON->PINSEL3	|=	(3<<20); //pag 120 elige la funcion match 00
	LPC_TIM0->EMR		|=	(3>>4); //pag 509 
	LPC_TIM0->MR0 		= 	70000000; //Valor al que quiero matchear
	LPC_TIM0->MCR 		|= 	(1<<1);	//pag 507 le digo que, interrumpa y resetee
	LPC_TIM0->MCR 		|= 	(1<<0); // cuando el valor MCR = TC
	LPC_TIM0->TCR		=	3		//pag 505
	LPC_TIM0->TCR		&=	~(1<<1) //Habilito el contador
	NVIC_EnableIRQ(TIMER0_IRQn); //HJabilito la interrupcion
	return;
}


/*
Handler del timer del periferico, que salata cada cierto tiempo
Cada vez que salta prende o apaga el led 22.
*/
void TIMER1_IRQnHandler(void){  
	aux = LPC_TIM0->CR0; //Guardo lo que capturo el modulo timmer.
	if (led==0)
	{
		LPC_GPIO0->FIOSET	=	(1<<22);
		i = 1;
	}else if(i == 1){
		LPC_TIM0->IR |=	1;
		i = 0;
	}
	LPC_TIM0->IR |= 1; //Limpiamos la bandera de interrupcion.
	return;
}

void EINT3_IRQHandler(void){
    //tiene que dividir la frecuencia en 2 c/vez que entre
}