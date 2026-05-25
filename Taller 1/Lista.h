//LISTA.h
#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include "Nodo.h"
#include <stdio.h>


typedef struct
{
	Nodo *inicio;
	Nodo *fin;
	int cantidad;
	void (*imprimir)(void*); //APUNTADOR A FUNCION
	int (*comparar)(void*,void*);
}Lista;

typedef struct
{
	Nodo *ante;
	Nodo *enco;
	void *dato;	
}Resultado;

Resultado buscar(Lista lista,void *dato);
void eliminarInicio(Lista *lista);
void eliminarFinal(Lista *lista);
void eliminarDato(Lista *lista,void *dato);

void insertarInicio( Lista *lista, void *dato);
int insertarEn( Lista *lista, void *dato, int index);
int eliminarEn( Lista *lista, int index);

void imprimirResultado(Lista lista,Resultado resultado);

void agregarFinal(Lista *lista,void *dato);
void agregarEnOrden(Lista *lista,void *dato);
void imprimirLista(Lista lista);

#endif