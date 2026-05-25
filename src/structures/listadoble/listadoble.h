#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include <stdio.h>
#include "../nodos/nododoble.h"

typedef struct 
{
	NodoD *inicio;
	NodoD *fin;
	int cant;
	void (*imprimir)(void *datoA);
	int (*comparar)(void *datoA,void *dataB);
	void (*liberar)(void *datoA);
}ListaD;

//IMPLEMENTADAS
ListaD inicializarListaD(void (*imprimir)(void*), int (*comparar)(void*,void*), void (*liberar)(void*));
void imprimirListaDIF(ListaD lista);
void imprimirListaDFI(ListaD lista);
void imprimirRes(ListaD, NodoD*);
void borrarElemento(ListaD *lista, void*, ListaD, NodoD*);
void insertarFinalD(ListaD*,void*);
void* borrarDatoD(ListaD *lista);
void borrarInicioD(ListaD *lista);
void borrarListaD(ListaD *);
void insertarInicioD(ListaD*,void*);

//IMPRIMIR

//AGREGAR

//BORRAR


//NO IMPLEMENTADAS
//BUSCAR
NodoD* buscarDatoD(ListaD lista,void *dato);
//NodoD* buscarDatoEspecificoD(ListaD lista,void *dato,int (*comparar)(void*,void*));ListaD listaComp
NodoD* buscarDatoEspecificoD(ListaD lista,void *dato,ListaD listaComp);
//INSERTAR
void insertEnOrdenD(ListaD *lista,void *dato);
int insertarEnD( ListaD * lista, void *dato,int index);
//ELIMINAR
int borrarEnD( ListaD *lista, int index);
void borrarFinD(ListaD *lista);
//void borrarDatoD(ListaD *lista,void *dato);
void reordenarD(ListaD *lista, int (*comparar)(void*,void*));


#endif