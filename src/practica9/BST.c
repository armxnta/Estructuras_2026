#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BST.h"

NodoBST* crearNodo(Libro *libro)
{
    NodoBST *nuevo = malloc(sizeof(NodoBST));
    nuevo->libro = libro;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

NodoBST* insertarTitulo(NodoBST *raiz,Libro *libro)
{
    if(raiz == NULL)
        return crearNodo(libro);
    if(strcmp(libro->titulo,raiz->libro->titulo) < 0)
        raiz->izq = insertarTitulo(raiz->izq,libro);
    else
        raiz->der = insertarTitulo(raiz->der,libro);
    return raiz;
}

NodoBST* insertarFecha(NodoBST *raiz,Libro *libro)
{
    if(raiz == NULL)
        return crearNodo(libro);
    if(libro->fecha < raiz->libro->fecha)
        raiz->izq = insertarFecha(raiz->izq,libro);
    else if(libro->fecha > raiz->libro->fecha)
        raiz->der = insertarFecha(raiz->der,libro);
    else
    {
        if(strcmp(libro->titulo,raiz->libro->titulo) < 0)

            raiz->izq = insertarFecha(raiz->izq,libro);

        else

            raiz->der = insertarFecha(raiz->der,libro);
    }

    return raiz;
}

void imprimirInOrder(NodoBST *raiz)
{
    if(raiz == NULL)
        return;

    imprimirInOrder(raiz->izq);

    imprimirLibro(raiz->libro);

    printf("\n");

    imprimirInOrder(raiz->der);
}

void liberarBST(NodoBST *raiz)
{
    if(raiz == NULL)
        return;

    liberarBST(raiz->izq);
    liberarBST(raiz->der);
    free(raiz);
}