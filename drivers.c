/*
Drivers:
En vez de modificar los registros a mano
Lo hacemos mediante las funciones predefinidas que tienen dichos drivers
*/
#include "LPCxx.h"
#include "lcp17xx_gpio.h"
#include "lpc17xx_pinsel.h"
//Donde el compilador encuentre PIN_22, sabe que nos referimos a 22 lugares corridos
#define PIN_22 ((uint32_t)(t<<22))

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