#include <stdio.h>
#include <iostring.h>
#include <lista.h>
#include <listadoble.h>
#include <pila.h>
#include "Alumno.h"

int main()
{
	Pila pila = {NULL,0,-1,imprimirEntero,free};
	
	int valores[] = {8,5,6,10,2,3,9};
	
	for(int i=0; i<7; i++)
	{
		int *num = malloc(sizeof(int));
		*num = valores[i];
		
		pushDato(&pila, num);
	}
	
	printf("\nPila original:");
	imprimirPila(pila);
	
	ordenarPila(&pila, compararEnteros);
	
	printf("\n\nPila ordenada:");
	imprimirPila(pila);
	
	eliminarPila(&pila);
	
	return 0;
}
