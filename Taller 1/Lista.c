//LISTA.c
#include "Lista.h"

void agregarFinal(Lista *lista,void *dato)
{
	Nodo *nuevo = crearNodo(dato);
	//LISTA VACIA
	if( lista->inicio==NULL && lista->inicio==lista->fin)
	{
		//AGREGAR UNICO NODO
		lista->inicio = lista->fin = nuevo;		
	}
	//LISTA TIENE MINIMO UN NODO
	else
	{
		//ENLAZAR NODO AL FINAL
		lista->fin->sig = nuevo;
		//ACTUALIZAR FINAL
		lista->fin = nuevo;
	}
	lista->cantidad++;
}


Resultado buscar(Lista lista,void *dato)
{	
	Resultado resultado = {NULL,NULL,NULL};
	for (Nodo *q = NULL,*p = lista.inicio; p!= NULL ;q=p, p = p->sig)
	{
		if( lista.comparar(dato, p->dato) == 0)
		{
			//LO ENCONTRAMOS
			resultado.ante = q;
			resultado.enco = p;
			resultado.dato = p->dato;
			break;
		}
	}
	return resultado;
}



void imprimirResultado(Lista lista,Resultado res)
{
	
	if( res.enco )
	{
		//ENCONTRADO
		if(res.ante)
		{
			printf("\n Anterior:" );
			lista.imprimir(res.ante->dato);
		}
		printf("\n Encontrado:" );
		lista.imprimir(res.enco->dato);
	}
	else
	{
		//NO ENCONTRADO
		printf("\n No encontrado");
	}
}

void agregarEnOrden(Lista *lista,void *dato)
{
	Nodo *nuevo = crearNodo(dato);
	//LISTA VACIA?
	if ( !lista->inicio)
	{	
		lista->inicio = lista->fin = nuevo;
	}	
	//LISTA YA TIENE ALGO
	else
	{
		for (Nodo *q = NULL,*aux = lista->inicio; aux!= NULL ;q=aux, aux = aux->sig)
		{
			
			if( lista->comparar( nuevo->dato , aux->dato  ) < 0 || aux == lista->fin)
			{
				//REEMPLAZAR INICIO
				if(aux == lista->inicio)
				{
					nuevo->sig = aux;
					lista->inicio = nuevo;
				}
				else if ( aux == lista->fin)
				{
					aux->sig = nuevo;
					lista->fin = nuevo;
				}
				//INSERTAR EN MEDIO DE NODOS
				else
				{
					q->sig = nuevo;
					nuevo->sig = aux;
				}
				break;
			}						
		}			
	}	
	lista->cantidad++;
}

void imprimirLista(Lista lista)
{
	//SALIR DE LA FUNCION SI LA LISTA ESTA VACIA
	printf("\n [%d] LISTA :",lista.cantidad); 
	if(!lista.inicio)
	{
		printf(" VACIA");
		return;
	}
	//RECORRER NODOS HASTA QUE LLEGUE EL
	//ENLACE SIGUENTE DEL ULTIMO NODO, QUE ES NULO
	for ( Nodo *aux = lista.inicio; aux!= NULL ; aux = aux->sig)
	{
		//UTILIZAR LA FUNCION DE IMPRIMIR ESPECIFICADA
		//EN LA LISTA
		lista.imprimir( aux->dato );
		//LA FUNCION SE ENCARGA DE DESREFERENCIAR
		//LA DIRECCION DE TIPO VOID AL TIPO ESPECIFICO
	}	
}


void eliminarInicio(Lista *lista)
{
	Nodo *aux;
	if(lista->inicio)
	{
		aux = lista->inicio;
		lista->inicio = aux->sig;
		//ELIMINASTE EL UNICO NODO
		if( !lista->inicio) //lista->inicio == NULL
			lista->fin = NULL;
		lista->cantidad--;
		free(aux);
	}
}

void eliminarFinal(Lista *lista)
{
	
	Nodo *aux;
	if(lista->inicio)
	{	
		Resultado res = buscar(*lista,lista->fin->dato);
		lista->fin = res.ante; //PENULTIMO
		if(lista->fin)
			lista->fin->sig = NULL;
		else 
			lista->inicio = NULL;
		free(res.enco); //FIN
		lista->cantidad--;
	}	
}


void eliminarDato(Lista *lista,void *dato)
{
	Resultado res = buscar(*lista,dato);
	if( res.enco)
	{
		if( res.enco == lista->inicio)
			eliminarInicio(lista);
		else if (res.enco == lista->fin)
			eliminarFinal(lista);
		else
		{
			res.ante->sig = res.enco->sig;
			free(res.enco);
			lista->cantidad--;
		}
	}
}


void insertarInicio(Lista *lista, void *dato)
{
	Nodo *nuevo = crearNodo(dato);
	
	if(lista->inicio==NULL)
		lista->fin=nuevo;
	
	nuevo->sig = lista->inicio;
	lista->inicio = nuevo;
	lista->cantidad++;
}

int insertarEn(Lista *lista, void *dato, int index)
{

	Nodo *nuevo = crearNodo(dato);
	int contador=0;
	
	//anadir al final
	if (index == lista->cantidad)
	{
		Nodo *aux = lista->inicio;

		while (aux->sig != NULL)
		{
			aux = aux->sig;
		}

		aux->sig = nuevo;
		nuevo->sig = NULL;
		lista->cantidad++;
		return 1;
	}
	
	//anadir al inicio y en medio
	for (Nodo *q = NULL,*aux = lista->inicio; aux!= NULL ;q=aux, aux = aux->sig)
	{
		if(index==0){
			nuevo->sig = lista->inicio;
			lista->inicio = nuevo;
			lista->cantidad++;
			break;
		} else if(contador == index)
		{
			q->sig = nuevo;
			nuevo->sig = aux;
			lista->cantidad++;
			break;
		}  else {
			contador++;
		}
	}
	return 0;
}

int eliminarEn(Lista *lista, int index)
{
	if (!lista->inicio || index < 0 || index >= lista->cantidad)
	{
		printf("\n Valor fuera de rango.\n");
		return 0;
	}

	// ELIMINAR POSICION 0
	if (index == 0)
	{
		eliminarInicio(lista);
		return 1;
	}

	int contador = 0;
	Nodo *q = NULL;
	Nodo *aux = lista->inicio;

	while (aux)
	{
		if (contador == index)
		{
			// ELIMINAR FINAL
			if (aux == lista->fin)
			{
				eliminarFinal(lista);
			}
			// ELIMINAR EN MEDIO
			else
			{
				q->sig = aux->sig;
				free(aux);
				lista->cantidad--;
			}
			return 1;
		}
		q = aux;
		aux = aux->sig;
		contador++;
	}
}