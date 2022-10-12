#include <LPC17xx.h>
#define STCRL

int main(void){
	SystemInit(); //Inicializar la estructura de la placa
	STRELOAD = RELOAD_VALUE; //Cargar el valor de recarga
	STCRL = (1<<SBIT_ENABLE) | (1 << SBIT_TICKINT) | (1 << SBIT_CLKSOURCE);
	LPC_GPIO0 -> |= (1 << OUT_LED);
	
	while(1){}
    return 0;
}

void SysTick_Handler(void){
	LPC_GPIO0 -> FIODIR
}