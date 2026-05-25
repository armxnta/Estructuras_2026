#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostring.h>
#include <HashQ.h>
#include "Libro.h"
#include "BST.h"

//int folding(void *);
void imprimir(void *);

int compararISBN(void *,void *);
int compararTitulo(void *,void *);
int compararAutor(void *,void *);
int compararFecha(void *,void *);

void inicializarHash(HashQTable*, fn_folding, fn_comparar);

void buscarISBN(HashQTable*);
void buscarTitulo(HashQTable*);
void buscarAutor(HashQTable*);
void buscarFecha(HashQTable*);

void rangoTitulo(HashQTable*);
void rangoAutor(HashQTable*);
void rangoFecha(HashQTable*);

int foldingISBN(void *data);
int foldingTitulo(void *data);
int foldingAutor(void *data);
int foldingFecha(void *data);

int main(void)
{
    HashQTable hashISBN;
    HashQTable hashTitulo;
    HashQTable hashAutor;
    HashQTable hashFecha;

    inicializarHash(&hashISBN, foldingISBN, compararISBN);
    inicializarHash(&hashTitulo, foldingTitulo, compararTitulo);
    inicializarHash(&hashAutor, foldingAutor, compararAutor);
    inicializarHash(&hashFecha, foldingFecha, compararFecha);

    Acervo acervo = obtener_libros();

    for(int i=0; i<acervo.cantidad; i++)
    {
        Libro *libro = acervo.libros+i;

        fn_insertKey(&hashISBN,libro);
        fn_insertKey(&hashTitulo,libro);
        fn_insertKey(&hashAutor,libro);
        fn_insertKey(&hashFecha,libro);
    }

    int opc;

    do
    {
        printf("\n\nMENU");
        printf("\n1. Buscar ISBN");
        printf("\n2. Buscar titulo");
        printf("\n3. Buscar autor");
        printf("\n4. Buscar fecha");
        printf("\n5. Rango titulo");
        printf("\n6. Rango autor");
        printf("\n7. Rango fecha");
        printf("\n0. Salir");
        printf("\n\nOpcion: ");
        scanf("%d",&opc);
        getchar();

        switch(opc)
        {
            case 1:
                buscarISBN(&hashISBN);
                break;

            case 2:
                buscarTitulo(&hashTitulo);
                break;

            case 3:
                buscarAutor(&hashAutor);
                break;

            case 4:
                buscarFecha(&hashFecha);
                break;

            case 5:
                rangoTitulo(&hashTitulo);
                break;

            case 6:
                rangoAutor(&hashAutor);
                break;

            case 7:
                rangoFecha(&hashFecha);
                break;
        }

    }while(opc != 0);

    return 0;
}

void inicializarHash(HashQTable *tabla, fn_folding folding, fn_comparar comparar)
{
    tabla->table = calloc(100,sizeof(void*));
    tabla->len = 100;
    tabla->cant = 0;
    tabla->min = 30;
    tabla->max = 60;
    tabla->fixed = 45;
    tabla->verbose = 0;
    tabla->folding = folding;
    tabla->comparar = comparar;
    tabla->imprimir = imprimir;
}

int foldingISBN(void *data)
{
    Libro *libro = data;

    char *cadena = libro->isbn;

    int key = 0;
    int sector = 1;
    int sumatoria = 0;

    for(int i=0; cadena[i]!='\0'; i++)
    {
        sumatoria += cadena[i];

        if(i!=0 && (i+1)%3==0)
        {
            key += sector*sumatoria;
            sumatoria = 0;
            sector++;
        }
    }

    key += sector*sumatoria;
    return key;
}

int foldingTitulo(void *data)
{
    Libro *libro = data;

    char *cadena = libro->titulo;

    int key = 0;
    int sector = 1;
    int sumatoria = 0;

    for(int i=0; cadena[i]!='\0'; i++)
    {
        sumatoria += cadena[i];

        if(i!=0 && (i+1)%3==0)
        {
            key += sector*sumatoria;
            sumatoria = 0;
            sector++;
        }
    }

    key += sector*sumatoria;
    return key;
}

int foldingAutor(void *data)
{
    Libro *libro = data;

    char *cadena = libro->autor;

    int key = 0;
    int sector = 1;
    int sumatoria = 0;

    for(int i=0; cadena[i]!='\0'; i++)
    {
        sumatoria += cadena[i];

        if(i!=0 && (i+1)%3==0)
        {
            key += sector*sumatoria;
            sumatoria = 0;
            sector++;
        }
    }

    key += sector*sumatoria;

    return key;
}

int foldingFecha(void *data)
{
    Libro *libro = data;

    return libro->fecha;
}

void imprimir(void *data)
{
    imprimirLibro(data);
}

int compararISBN(void *a,void *b)
{
    Libro *A = a;
    Libro *B = b;

    return strcmp(A->isbn,B->isbn);
}

int compararTitulo(void *a,void *b)
{
    Libro *A = a;
    Libro *B = b;

    return strcmp(A->titulo,B->titulo);
}

int compararAutor(void *a,void *b)
{
    Libro *A = a;
    Libro *B = b;

    return strcmp(A->autor,B->autor);
}

int compararFecha(void *a,void *b)
{
    Libro *A = a;
    Libro *B = b;

    return A->fecha - B->fecha;
}

void buscarISBN(HashQTable *tabla)
{
    Libro temp;

    printf("\nISBN: ");

    fgets(temp.isbn,MAX_ISBN,stdin);

    temp.isbn[strcspn(temp.isbn,"\n")] = 0;

    Libro *res = fn_searchKey(tabla,&temp);

    if(res)
    {
        printf("\nENCONTRADO\n");

        imprimirLibro(res);
    }
    else
        printf("\nNO ENCONTRADO");
}

void buscarTitulo(HashQTable *tabla)
{
    Libro temp;

    printf("\nTITULO: ");

    fgets(temp.titulo,MAX_TITULO,stdin);

    temp.titulo[strcspn(temp.titulo,"\n")] = 0;

    Libro *res = fn_searchKey(tabla,&temp);

    if(res)
    {
        printf("\nENCONTRADO\n");

        imprimirLibro(res);
    }
    else
        printf("\nNO ENCONTRADO");
}

void buscarAutor(HashQTable *tabla)
{
    char autor[MAX_AUTOR];

    printf("\nAUTOR: ");

    fgets(autor,MAX_AUTOR,stdin);

    autor[strcspn(autor,"\n")] = 0;

    NodoBST *raiz = NULL;

    for(int i=0; i<tabla->len; i++)
    {
        Libro *libro = tabla->table[i];

        if(libro != NULL && libro != (void*)tabla)
        {
            if(strcmp(libro->autor,autor)==0)
            {
                raiz = insertarFecha(raiz,libro);
            }
        }
    }

    imprimirInOrder(raiz);

    liberarBST(raiz);
}

void buscarFecha(HashQTable *tabla)
{
    int fecha;

    printf("\nFECHA: ");

    scanf("%d",&fecha);

    getchar();

    NodoBST *raiz = NULL;

    for(int i=0; i<tabla->len; i++)
    {
        Libro *libro = tabla->table[i];

        if(libro != NULL && libro != (void*)tabla)
        {
            if(libro->fecha == fecha)
            {
                raiz = insertarTitulo(raiz,libro);
            }
        }
    }

    imprimirInOrder(raiz);

    liberarBST(raiz);
}

void rangoTitulo(HashQTable *tabla)
{
    char inicio[5];
    char fin[5];

    printf("\nInicio: ");

    fgets(inicio,5,stdin);

    inicio[strcspn(inicio,"\n")] = 0;

    printf("\nFin: ");

    fgets(fin,5,stdin);

    fin[strcspn(fin,"\n")] = 0;

    NodoBST *raiz = NULL;

    for(int i=0; i<tabla->len; i++)
    {
        Libro *libro = tabla->table[i];

        if(libro != NULL && libro != (void*)tabla)
        {
            if(strncmp(libro->titulo,inicio,1) >= 0 && strncmp(libro->titulo,fin,1) <= 0)
			{
                raiz = insertarTitulo(raiz,libro);
            }
        }
    }

    imprimirInOrder(raiz);
    liberarBST(raiz);
}

void rangoAutor(HashQTable *tabla)
{
    char inicio[5];
    char fin[5];

    printf("\nInicio: ");

    fgets(inicio,5,stdin);

    inicio[strcspn(inicio,"\n")] = 0;

    printf("\nFin: ");

    fgets(fin,5,stdin);

    fin[strcspn(fin,"\n")] = 0;

    NodoBST *raiz = NULL;

    for(int i=0; i<tabla->len; i++)
    {
        Libro *libro = tabla->table[i];

        if(libro != NULL &&
           libro != (void*)tabla)
        {
            if(strncmp(libro->autor,inicio,1) >= 0 && strncmp(libro->autor,fin,1) <= 0)
            {
                raiz = insertarTitulo(raiz,libro);
            }
        }
    }

    imprimirInOrder(raiz);
    liberarBST(raiz);
}

void rangoFecha(HashQTable *tabla)
{
    int inicio;
    int fin;

    printf("\nInicio: ");
    scanf("%d",&inicio);

    printf("\nFin: ");
    scanf("%d",&fin);

    getchar();

    NodoBST *raiz = NULL;

    for(int i=0; i<tabla->len; i++)
    {
        Libro *libro = tabla->table[i];

        if(libro != NULL &&
           libro != (void*)tabla)
        {
            if(libro->fecha >= inicio &&
               libro->fecha <= fin)
            {
                raiz = insertarFecha(raiz,libro);
            }
        }
    }

    imprimirInOrder(raiz);
    liberarBST(raiz);
}
