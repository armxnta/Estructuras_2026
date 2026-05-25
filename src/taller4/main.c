
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <iostring.h>
#include <heap.h>

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);


int main(void)
{
	Heap heap = crearHeap(HEAP_MIN,compararEntero,imprimirEntero);
	printf("\n INICIO");
	
	int arr[]={7,4,5,2,1,3};
	size_t cantidad = sizeof(arr) / sizeof(arr[0]);
	
	for(int i=0; i < cantidad; i++)
	{
		insertarHeap(&heap, crearEntero(arr[i]));
	}
	
	//imprimirHeap(heap);
	heapify(&heap);
	imprimirHeap(heap);
	heap.tipo = HEAP_MAX;
	heapify(&heap);
	imprimirHeap(heap);
	
	while(heap.cantidad)
	{
		//printf("\n Cantidad:  %d",heap.cantidad);
		void *dato = eliminarHeap(&heap);
		//printf("\n Dato eliminado: ");
		//imprimirEntero(dato);
		free(dato);
	}

	printf("\n\n FIN DE PROGRAMA\n");
	
	return 0;
}

/*
	arr[] //datos
	arr[] //nodos
	
	aux = Nodo[i]
	aux->izq = Nodos[2*i+1]
	aux->dch = ((2*i+2)<cant) ? nodos[2*i+2] : NULL
*/

int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}