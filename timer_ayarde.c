/*
En la primera comparacion del timmer con el match es cierta:
Y la salida esetaba en cero que la lleve a uno, a su vez que resetee el timer pa
*/

#include "LPC17xx.h"

void confTimer(void);

unit32_t aux = 0;

int main(void){
	confGPIO();
	confTimer();
	while(1){}
	return 0;
}

void confGPIO(void){
	LPC_GPIO0->FIODIR	|=	(1<<22);
	return;
}

/*
Configuro el timmer 0:
- PCONP Prende el periferico TMR0
- PCLKSEL0 seteo la frecuencia que le va llegar del timmer
- PINSEL3 asocia un pin de salida a la funcion de match
- EMR determina la funcionalidad del match 0: puede togglear la salida del pin correspondiente
- MCR cada vez que se genere la condicion de match, va generar una interrupcion.
- TCR 

//Configuracion en modo match
void confTimer(){
	LPC_SC->PCONP		|=	(1<<1); //pag 65 
	LPC_SC->PCLKSEL0 	|=	(1<<2); //pag 59
	LPC_PINCON->PINSEL3	|=	(3<<20); //pag 120
	LPC_TIM0->EMR		|=	(3>>4); //pag 509
	LPC_TIM0->MR0 		= 	70000000;
	LPC_TIM0->MCR 		|= 	(1<<1);	//pag 507
	LPC_TIM0->MCR 		|= 	(1<<0);	  
	LPC_TIM0->TCR		=	3		//pag 505
	LPC_TIM0->TCR		&=	~(1<<1)
	NVIC_EnableIRQ(TIMER0_IRQn);
	return;
}
*/

/*Configuracion en modo captura
	- Vamos a esperar una entrada en el pin 20
	- El evento que vaya a disparar sera con un flanco de bajada
	- Y genera una interrupcion
*/
void confTimer(){
	LPC_SC->PCONP		|=	(1<<1); //pag 65 
	LPC_SC->PCLKSEL0 	|=	(1<<2); //pag 59
	LPC_PINCON->PINSEL3	|=	(3<<20); //pag 120
	LPC_TIM0->CCR		|=	(1<<1)|(1<<2);//pag 508
	LPC_TIM0->TCR   	|=	3; //pag 505
	LPC_TIM0->TCR 		&=	~(1<<1);
	NVIC_EnableIRQ(TIMER0_IRQn);
	return;
}

//Si se genero esa interrupcion de flanco de bajada
//usamos la misma interrupcion
void TIMER0_IRQnHandler(void){
	static	unit8_t i = 0;   
	aux = LPC_TIM0->CR0; //Guardo lo que capturo el modulo timmer.
	if (i==0)
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
//Video 2 minuto 35: Explica la configuracion del timmer de forma resumida
//Video 3 minuto 50: Muestra como mostrar una variable global
//Video 3 minuto   : 