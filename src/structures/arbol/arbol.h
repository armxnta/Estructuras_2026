#ifndef ARBOL_H
#define ARBOL_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>
#include <pila.h>

#define PREORDEN 1
#define ORDEN 2
#define POSTORDEN 3
#define INVERSO 4
#define IZQUIERDA 0
#define DERECHA 1

typedef struct
{
	NodoA *padre;
	NodoA *nodo;
	void *dato;
	int rama;
}Resultado;

typedef struct
{
	NodoA *raiz;
	int cantidad;
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
	void (*liberar)(void*);
}Arbol;


void equilibrar(Arbol *arbol);
void extraerMitades(NodoA *raiz, void **datos, int *i);

void eliminarArbol(Arbol *arbol); //ELIMINA DATOS
void vaciarArbol(Arbol *arbol);  //NO ELIMINA DATOS
void generarArbol(Arbol *arbol, void **datos, int longitud);

Resultado buscarNodoEnArbol(Arbol arbol,void *dato);
void* buscarEnArbol(Arbol arbol,void *dato);
void invertirArbol(Arbol *arbol);
void eliminarArbol(Arbol *arbol);
void insertarArbol(Arbol *arbol,void *dato);
void imprimirArbol(Arbol arbol);
void imprimirOrden(Arbol arbol,int opcion);
int altura(NodoA *raiz);
int compararEstructura(NodoA *a, NodoA *b);
int compararDatos(Arbol *a, Arbol *b, int (*comparar)(void*,void*));
NodoA* eliminarNodo(NodoA* raiz, void* dato, int (*comparar)(void*,void*), void (*liberar)(void*));
void equilibrarArbol(Arbol *arbol);

#endif