#include "archivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Archivo* crearArchivo(char *nombre,int paginas)
{
    Archivo *nuevo = malloc(sizeof(Archivo));

    strcpy(nuevo->nombre,nombre);
    nuevo->paginas = paginas;

    return nuevo;
}

int compararArchivo(void *a,void *b)
{
    Archivo *aa = a;
    Archivo *bb = b;

    if(aa->paginas == bb->paginas)
        return 0;
    else if(aa->paginas < bb->paginas)
        return -1;
    else
        return 1;
}

void imprimirArchivo(void *a)
{
    Archivo *aa = a;

    printf("%s (%d pags)", aa->nombre, aa->paginas);
}