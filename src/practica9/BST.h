#ifndef BST_H
#define BST_H

#include "Libro.h"

typedef struct NodoBST
{
    Libro *libro;
    struct NodoBST *izq;
    struct NodoBST *der;
}NodoBST;

NodoBST* insertarTitulo(NodoBST *raiz,Libro *libro);
NodoBST* insertarFecha(NodoBST *raiz,Libro *libro);
NodoBST* crearNodo(Libro *libro);

void imprimirInOrder(NodoBST*);

void liberarBST(NodoBST*);

#endif