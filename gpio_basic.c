#include <LPC17xx.H>
int main()
{
	int i;
	PINSEL = 0; //Seleccionó la función 0 : la default.
	FIODIR = 0XFFFFFFFF; //Lo pongo como salida

	while(1)
	{
		FIOSET = 0XFFFFFFFF; 
		//Fioset pone en 1, pero le paso un 1 osea un apagado, creo.
		for(i=0; i<100000; i++);
		FIO0CLR = 0XFFFFFFFF; 
	for(i=0; i<100000; i++);
	}
}
