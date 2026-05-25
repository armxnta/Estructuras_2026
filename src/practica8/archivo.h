#ifndef ARCHIVO_H
#define ARCHIVO_H

typedef struct
{
    char nombre[50];
    int paginas;

}Archivo;

Archivo* crearArchivo(char *nombre,int paginas);

int compararArchivo(void *a,void *b);

void imprimirArchivo(void *a);

#endif