#include "arbol.h"

Resultado buscarNodoEnArbol(Arbol arbol,void *dato)
{
	Resultado result = {NULL,NULL,NULL,DERECHA};
	NodoA *raiz = arbol.raiz;	
	while(raiz)
	{
		if(arbol.comparar(raiz->dato,dato) == 0)
		{
			result.nodo = raiz;
			result.dato = raiz->dato;	
			break;
		}
		else
		{ 
			result.padre = raiz;
			if(raiz->izq && arbol.comparar(raiz->dato,dato) > 0 )
			{
				result.rama = IZQUIERDA;
				raiz = raiz->izq;		
			}				
			else
			{
				result.rama = DERECHA;
				raiz = raiz->dch;
			}
		}
	}
	return result;
}	
	

void* buscarEnArbol(Arbol arbol,void *dato)
{
	void *result = NULL;
	NodoA *raiz = arbol.raiz;
	
	while(raiz)
	{
		if(arbol.comparar(raiz->dato,dato) == 0)
		{
			result = raiz->dato;
			break;
		}
		else if(arbol.comparar(raiz->dato,dato) > 0 )
			raiz = raiz->izq;
		else
			raiz = raiz->dch;
	}
	return result;
}	

void invertirRamas(NodoA *raiz)
{
	if(!raiz)
		return;
	NodoA *aux = raiz->izq;
	raiz->izq = raiz->dch;
	raiz->dch = aux;
	invertirRamas(raiz->izq);
	invertirRamas(raiz->dch);
}

void invertirArbol(Arbol *arbol)
{
	invertirRamas(arbol->raiz);
}


void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA
		if(!raiz->izq)			
			raiz->izq = crearNodoA(dato);
		else if(!raiz->dch && comparar(dato,raiz->dato)==0)			
			raiz->dch = crearNodoA(dato);
		else			
			insertarArbolOrdenado(raiz->izq,dato,comparar);
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}



void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else 
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
}



void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}


void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}


void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}


void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*))
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq,liberar);
	eliminar_NodosA(raiz->dch,liberar);
	//LIBERAR
	if(liberar)
		liberar(raiz->dato);
	free(raiz);
}

/*
void eliminarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}*/

int altura(NodoA *raiz)
{
    
	if(!raiz)
		return 0;

	int izq = altura(raiz->izq);
	int der = altura(raiz->dch);

	if(izq > der)
		return izq + 1;
	else
		return der + 1;
}


int compararEstructura(NodoA *a, NodoA *b)
{
	//si son null
	if(!a && !b)
		return 1;
	
	//si solo uno es null
	if(!a || !b)
		return 0;

	return compararEstructura(a->izq,b->izq) && compararEstructura(a->dch,b->dch);
}


int compararDatos(Arbol *a, Arbol *b, int (*comparar)(void*,void*))
{
	void **datos = (void**) calloc(a->cantidad, sizeof(void*));
	int i=0;
	extraerMitades(b->raiz, datos, &i);
	
	void **datos2 = (void**) calloc(b->cantidad, sizeof(void*));
	int j=0;
	extraerMitades(a->raiz, datos2, &j);
	
	for(int k = 0; k < i; k++)
	{
		if(comparar(datos[k],datos2[k])!=0)
			return 0;
	}
	
	return 1;
	
	/*if(!a && !b)
		return 1;

	if(!a || !b)
		return 0;

	if(comparar(a->dato,b->dato)!=0)
		return 0; //return solo si son distintos

	//se recorre los arboles
	return compararDatos(a->izq,b->izq,comparar) && compararDatos(a->dch,b->dch,comparar);*/
}

NodoA* eliminarNodo(NodoA* raiz, void* dato, int (*comparar)(void*,void*), void (*liberar)(void*))
{
	//arbol vacio
	if(!raiz)
		return NULL;

    
	if(comparar(dato,raiz->dato) < 0) //dato es menor
	{
		raiz->izq = eliminarNodo(raiz->izq,dato,comparar,liberar);
	}
	else if(comparar(dato,raiz->dato) > 0) //si es mayor
	{
		raiz->dch = eliminarNodo(raiz->dch,dato,comparar,liberar);
	}
	else //ya se tiene el nodo
	{
		// sin hijos
		if(!raiz->izq && !raiz->dch)
		{
			if(liberar)
				liberar(raiz->dato);
			
			free(raiz);
			return NULL; 
		}

		// hijo derecho
		if(!raiz->izq)
		{
			NodoA *temp = raiz->dch; // guardar hijo

			if(liberar)
				liberar(raiz->dato);
			free(raiz); // eliminamos nodo actual

			return temp; // reemplaza al nodo eliminado
		}

		//hijo izq
		if(!raiz->dch)
		{
			NodoA *temp = raiz->izq;

			if(liberar)
				liberar(raiz->dato);
			free(raiz);

			return temp;
		}

		//dos hijos
		NodoA *nodoPeque = raiz->dch;

		// recorrer hacia la izquierda para encontrar el mas chico
		while(nodoPeque->izq)
		{
			nodoPeque = nodoPeque->izq;
		}

		raiz->dato = nodoPeque->dato;

		raiz->dch = eliminarNodo(raiz->dch,nodoPeque->dato,comparar,NULL);
	}

	return raiz;
}

void llenarArreglo(NodoA *raiz, void **arr, int *i)
{

	if(!raiz)
		return;

	llenarArreglo(raiz->izq,arr,i); //recorre izq

	arr[*i] = raiz->dato;
	(*i)++;

	llenarArreglo(raiz->dch,arr,i); //recorre der
}

NodoA* construirBalanceado(void **arr, int inicio, int fin)
{
	if(inicio > fin)
		return NULL;

	int mid = (inicio + fin)/2;

	NodoA *n = crearNodoA(arr[mid]);

	n->izq = construirBalanceado(arr,inicio,mid-1);
	n->dch = construirBalanceado(arr,mid+1,fin);

	return n;
}

void equilibrarArbol(Arbol *arbol)
{
	if(!arbol->raiz)
		return;

	void **arr = malloc(arbol->cantidad*sizeof(void*));
	int i = 0;

	llenarArreglo(arbol->raiz,arr,&i);

	eliminar_NodosA(arbol->raiz,NULL);

	arbol->raiz = construirBalanceado(arr,0,arbol->cantidad-1);

	free(arr);
}


void equilibrar(Arbol *arbol)
{
	if(!arbol->raiz)
		return;
	
	void **datos = (void**) calloc(arbol->cantidad, sizeof(void*));
	int i=0;
	extraerMitades(arbol->raiz, datos, &i);
	vaciarArbol(arbol);
	generarArbol(arbol, datos, i);
	
	free(datos);
}

void extraerMitades(NodoA *raiz, void **datos, int *i)
{
	if(!raiz)
		return;
	extraerMitades(raiz->izq, datos, i);
	datos[*i] = raiz->dato;
	(*i)++;
	extraerMitades(raiz->dch, datos, i);
}

void eliminarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}


void vaciarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz,NULL);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}

void generarArbol(Arbol *arbol, void **datos, int longitud)
{
	if(longitud <= 0)
		return;
	int mitad = longitud/2;
	//mitad
	insertarArbol(arbol, datos[mitad]);
	
	//izq
	generarArbol(arbol, datos, mitad);
	
	//der
	generarArbol(arbol, datos+mitad+1, longitud-1-mitad);
	
}