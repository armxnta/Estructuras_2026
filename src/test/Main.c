#include <stdio.h>
#include <iostring.h>
#include <lista.h>
#include <listadoble.h>
#include <pila.h>
#include "Alumno.h"

void imprimirEntero(void *dato);


int main()
{
	Pila pila = {NULL,0,4,imprimirEntero,NULL};
	int arreglo[6] = {1,5,4,3,5,9};
	for(int i=0; i<6;i++)
		pushDato(&pila,&arreglo[i]);
	
	imprimirPila(pila);
	

	return 0;
}

void imprimirEntero(void *dato)
{
	int *datoA = dato;
	printf(" %d",*datoA);
}
