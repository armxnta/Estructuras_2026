#include "heap.h"

NodoA* construirArbolHeap(Heap heap)
{
	if(heap.cantidad == 0)
		return NULL;

	NodoA **nodos = malloc(sizeof(NodoA*) * heap.cantidad);

	// Crear nodos
	for(int i = 0; i < heap.cantidad; i++)
	{
		nodos[i] = crearNodoA(heap.datos[i]);
	}

	// Enlazar hijos
	for(int i = 0; i < heap.cantidad; i++)
	{
		int izq = 2*i + 1;
		int dch = 2*i + 2;

		if(izq < heap.cantidad)
			nodos[i]->izq = nodos[izq];
		else
			nodos[i]->izq = NULL;

		if(dch < heap.cantidad)
			nodos[i]->dch = nodos[dch];
		else
			nodos[i]->dch = NULL;
	}

	NodoA *raiz = nodos[0];
	free(nodos);
	return raiz;
}

Heap crearHeap(unsigned char tipo,fn_comparar comparar,fn_imprimir imprimir)
{
	Heap heap = {tipo,0,NULL,NULL,comparar,imprimir};
	return heap;
}

void insertarHeap( Heap *heap,void *dato)
{
	void **aux = NULL;
	if(!heap->cantidad)
		heap->datos = calloc(1,sizeof(void*));
	else
	{
		while(!aux)
			aux = realloc(heap->datos, (heap->cantidad+1) * sizeof(void*) );
		heap->datos = aux;
	}	
	heap->datos[heap->cantidad++] = dato;
	//HEAPIFY
	heapify(heap);
}


void* eliminarHeap(Heap *heap)
{
	void *dato = NULL;
	if(!heap->cantidad)
		return dato;
	dato = heap->datos[0];
	if(heap->cantidad == 1)		
	{
		free(heap->datos);
		heap->datos = NULL;
		heap->cantidad--;
		return dato;
	}
	heap->datos[0] = heap->datos[heap->cantidad-1];
	void **aux = NULL;
	while(!aux)
		aux = realloc(heap->datos, (heap->cantidad-1) * sizeof(void*) );
	heap->datos = aux;
	heap->cantidad--;
	//HEAPIFY
	heapify(heap);
	return dato;	
}

/*void imprimirHeap( Heap heap)
{
	printf("\n HEAP: \n");
	if(heap.cantidad)
	{
		for( int i = 0; i < heap.cantidad; i++)
		{
			printf(" [%d] ",i);
			heap.imprimir( heap.datos[i] );
			printf("\n");
		}
		
	}
	else		
		printf("VACIO");		
}*/

void imprimirHeap(Heap heap)
{
	printf("\n HEAP (ARREGLO): \n");
	if(heap.cantidad)
	{
		for(int i = 0; i < heap.cantidad; i++)
		{
			printf(" [%d] ", i);
			heap.imprimir(heap.datos[i]);
			printf("\n");
		}

		printf("\n ARBOL:\n");

		NodoA *raiz = construirArbolHeap(heap);
		imprimirArbolRec(raiz, 0, ' ', heap.imprimir);
	}
	else
		printf("VACIO\n");
}




void heapify_min( Heap *heap,int padre)
{
	if( padre < 0 || padre > (heap->cantidad/2-1) )
		return;
	int min = padre;
	int izq = 2*padre+1;
	int dch = 2*padre+2;
	switch(heap->tipo)
	{
		case HEAP_MIN:			
			if( heap->comparar( heap->datos[min] , heap->datos[izq] ) > 0 )
				min = izq;
			if( dch < heap->cantidad && heap->comparar( heap->datos[min] , heap->datos[dch] ) > 0 )
				min = dch;
			break;			
		case HEAP_MAX:			
			if( heap->comparar( heap->datos[izq] , heap->datos[min] ) > 0 )
				min = izq;
			if( dch < heap->cantidad && heap->comparar( heap->datos[dch] , heap->datos[min] ) > 0 )
				min = dch;
			break;
	}

	if( min!=padre)
	{
		void *dato = heap->datos[padre];
		heap->datos[padre] = heap->datos[min];
		heap->datos[min] = dato;
		heapify_min(heap,min);
	}
	heapify_min(heap,padre-1);
	
	
}


void heapify(Heap *heap)
{
	int indice = heap->cantidad/2-1;
	heapify_min(heap,indice);
}

void imprimirArbolRec(NodoA *raiz, int nivel, char lado, fn_imprimir imprimir)
{
	if(!raiz)
		return;

	for(int i = 0; i < nivel; i++)
		printf("    ");

	if(nivel != 0)
		printf("|---%c ", lado);

	imprimir(raiz->dato);
	printf("\n");

	imprimirArbolRec(raiz->dch, nivel+1, 'R', imprimir);
	imprimirArbolRec(raiz->izq, nivel+1, 'L', imprimir);
}



void eliminarIndiceHeap(Heap *heap, int indice)
{
	if(indice < 0 || indice >= heap->cantidad)
		return;

	free(heap->datos[indice]);

	heap->datos[indice] =
		heap->datos[heap->cantidad - 1];

	heap->cantidad--;

	if(heap->cantidad > 0)
	{
		void **aux = realloc(
			heap->datos,
			sizeof(void*) * heap->cantidad
		);

		if(aux)
			heap->datos = aux;

		heapify(heap);
	}
	else
	{
		free(heap->datos);
		heap->datos = NULL;
	}
}

void vaciarHeap(Heap *heap)
{
	while(heap->cantidad)
	{
		free(eliminarHeap(heap));
	}
}