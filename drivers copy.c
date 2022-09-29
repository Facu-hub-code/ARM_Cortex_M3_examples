/*
Drivers:
En vez de modificar los registros a mano
Lo hacemos mediante las funciones predefinidas que tienen dichos drivers
*/
#include "LPCxx.h"
#include "lcp17xx_gpio.h"
#include "lpc17xx_pinsel.h"

#define OUTPUT		(uint8_t) 	1
#define INPUT		(uint8_t) 	0
//Donde el compilador encuentre PIN_22, sabe que nos referimos a 22 lugares corridos
#define PIN_22 		((uint32_t)(t<<22))
#define PORT_ZERO	(uint8_t)	0
#define PORT_ONE	(uint8_t)	1
#define PORT_TWO	(uint8_t)	2
#define PORT_THREE	(uint8_t)	3

void configGPIO(void);
voif config_timer(void);

int main(void){
	/*
	Variable que toma al forma de estructura para modificar los perifericos
	"Lista del super" diciendo que va a hacer, no necesariamente tenemos que usar todos los puertos
	*/
	PINSEL_CF0_Type pin_conf; 
	pin_conf.Portnum = PINSEL_PORT_0;
	pin_conf.Pinnum  = PINSEL_PIN_22;
	pin_conf.Funcnum = PINSEL_FUNC_0;

	/*
	Funcion del fabricante del driver, que recibe como argumento
	una estructura predefinida para modificar los registros.
	*/
	PINSEL_ConfPin(&pin_conf);

	/*
	Funcion que modifica el FIODIR 
	*/
	GPIO_SetDir(0, 22, 1);

	return 0;
}

void configGPIO(void){
	//Esta estructura esta definida por el fabricante del driver.
	PINSEL_CFG_Type pin_configuration;

	//Hago la listita
	pin_configuration.Portnum	=	PINSEL_PORT_0;
	pin_configuration.Pinnum	=	PINSEL_PIN_22;
	pin_configuration.Pinmode	= 	PINSEL_PINMODE_PULLUP;
	pin_configuration.Funcmode	=	PINSEL_FUNC_0;
	pin_configuration.OpenDrain	=	PINSEL_PINMODE_PINNORMAL;

	//Escribo los registros
	PINSEL_ConfigPin(&pin_configuration);

	GPIO_SetDir(PORT_ZERO, PIN_22, OUTPUT);
	return;
}

void TIMER0_IRQHandler(void){
	TIM_ClearIntPendig(LPC_TIM0, TIM0MR0_INT);

	if (GPIO_ReadValue(PORT_ZERO)&PIN_22)
	{
		GPIO_ClearValue(PORT_ZERO, PIN_22);
	}else{
		GPIO_SetValue(PORT_ZERO, PIN_22);
	}
	return;
}