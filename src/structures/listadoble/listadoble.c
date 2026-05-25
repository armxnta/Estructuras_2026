#include "listadoble.h"

ListaD inicializarListaD(void (*imprimir)(void*), int (*comparar)(void*,void*), void (*liberar)(void*))
{
	ListaD lista;

    lista.inicio = NULL;
    lista.fin = NULL;
    lista.cant = 0;

    lista.imprimir = imprimir;
    lista.comparar = comparar;
    lista.liberar = liberar;

    return lista;
}

void insertarInicioD(ListaD *lista,void *dato)
{
	NodoD *nuevo = crearNodoD(dato);
	
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = nuevo;
	}
	else
	{
		lista->inicio->ant = nuevo;
		nuevo->sig = lista->inicio;
		lista->inicio = nuevo;
	}
	lista->cant++;
}

void insertarFinalD(ListaD *lista,void *dato)
{
	NodoD *nuevo = crearNodoD(dato);
	//LISTA VACIA
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = nuevo;
	}
	//LISTA NO VACIA
	else
	{
		lista->fin->sig = nuevo;
		nuevo->ant = lista->fin;
		lista->fin = nuevo;
	}
	lista->cant++;
}

void imprimirListaDIF(ListaD lista)
{
	printf("\n [%d] LISTA:",lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
		return;
	}
	for(NodoD *aux = lista.inicio; aux!=NULL;  aux=aux->sig )
	{
		printf("\n");
		lista.imprimir( aux->dato);
	}	
}

void imprimirListaDFI(ListaD lista)
{
	printf("\n [%d] LISTA:",lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
		return;
	}
	for(NodoD *aux = lista.fin; aux!=NULL;  aux=aux->ant )
	{
		printf("\n");
		lista.imprimir( aux->dato);
	}
	
}

void borrarInicioD(ListaD *lista)
{
	NodoD *aux;
	if(!lista->inicio)
		return;	
	aux = lista->inicio;
	//UNICO NODO
	if( lista->inicio == lista->fin)
	{
		lista->inicio = lista->fin = NULL;
	}	
	//MINIMO 2
	else
	{
		lista->inicio = aux->sig;
		lista->inicio->ant = NULL;
		
	}
	if(lista->liberar)
		lista->liberar( aux->dato);
	free(aux);	
	lista->cant--;	
}

void borrarListaD(ListaD *lista)
{
	while(lista->inicio)
	{
		borrarInicioD(lista);
	}	
}

//BUSCAR
//NodoD* buscarDatoD(ListaD lista,void *dato)


NodoD *buscarDatoEspecificoD(ListaD lista, void *dato, ListaD listaComp)
{
    NodoD *aux;

    for(aux = lista.inicio; aux != NULL; aux = aux->sig)
    {
        if(listaComp.comparar(dato, aux->dato) == 0)
        {
            return aux;
        }
    }

    return NULL;
}

//INSERTAR
void insertEnOrdenD(ListaD *lista,void *dato)
{
	NodoD *aux;
	NodoD *nuevo = crearNodoD(dato);
	
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = nuevo;
	}
	else
	{
		for(aux = lista->inicio; aux != NULL; aux = aux->sig)
		{
			if(lista->comparar(nuevo->dato, aux->dato) < 0)
			{
				if(aux == lista->inicio) //inicio
				{
					nuevo->sig = aux;
					aux->ant = nuevo;
					lista->inicio = nuevo;
				}
				else //en medio
				{
					nuevo->ant = aux->ant;
					aux->ant->sig = nuevo;
					nuevo->sig = aux;
					aux->ant = nuevo;
				}
				break;
			}
			else if (aux == lista->fin) //final
			{
				aux->sig = nuevo;
				nuevo->ant = aux;
				lista->fin = nuevo;
				break;
			}
		}
	}
	lista->cant++;
    
}

void reordenarD(ListaD *lista, int (*comparar)(void*,void*))
{
	ListaD aux = {NULL,NULL,0,lista->imprimir,comparar,lista->liberar};
	void *dato;
	
	while( lista->cant  )
	{
		dato = borrarDatoD(lista);
		insertEnOrdenD(&aux,dato);		
	}
	*lista = aux;
	lista->comparar= aux.comparar;
}

void* borrarDatoD(ListaD *lista)
{
	if(!lista->inicio)
		return NULL;
	void *dato = lista->inicio->dato;
	lista->inicio->dato = NULL;
	borrarInicioD(lista);
	return dato;
}

void imprimirRes(ListaD lista, NodoD* busqueda)
{
	if(busqueda)
	{
		printf("\n Anterior: ");
		lista.imprimir(busqueda->ant->dato);
		printf("\n Encontrado: ");
		lista.imprimir(busqueda->dato);
	}
	else
	{
		printf("\n No encontrado");
	}
}

void borrarFinD(ListaD *lista)
{
	NodoD *aux;
	
	if(!lista->fin)
		return;
	
	aux = lista->fin;
	
	if(lista->inicio == lista->fin)
	{
		lista->inicio = lista->fin = NULL;
	}
	else
	{
		lista->fin = aux->ant;
		lista->fin->sig = NULL;
	}
	if(lista->liberar)
		lista->liberar(aux->dato);
	free(aux);
	lista->cant--;
}

void borrarElemento(ListaD *lista, void *dato, ListaD listaComp, NodoD* busqueda)
{
	if(busqueda)
	{
		if(busqueda == lista->inicio)
			borrarInicioD(lista);
		else if (busqueda == lista->fin)
			borrarFinD(lista);
		else
		{
			busqueda->ant->sig = busqueda->sig;
			busqueda->sig->ant = busqueda->ant;
			free(busqueda);
			lista->cant--;
		}
	}
}

/*
int insertarEnD( ListaD * lista, void *dato,int index)
{
	
}

//ELIMINAR
int borrarEnD( ListaD *lista, int index)
{

}


*/