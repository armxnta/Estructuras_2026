
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <iostring.h>
#include <heap.h>
#include "archivo.h"

void generarNombre(char *nombre);

int main(void)
{
    srand(time(NULL));

    Heap heap = crearHeap(HEAP_MIN, compararArchivo, imprimirArchivo);

    int opcion;

    do
    {
        printf("\n====================================");
        printf("\n     COLA DE IMPRESION");
        printf("\n====================================\n");

        if(heap.tipo == HEAP_MIN)
            printf("\nPRIORIDAD ACTUAL: Menos paginas\n");
        else
            printf("\nPRIORIDAD ACTUAL: Mas paginas\n");

        imprimirHeap(heap);

        printf("\n[0] Cambiar prioridad");
        printf("\n[1] Mostrar cola");
        printf("\n[2] Agregar archivo");
        printf("\n[3] Procesar archivo");
        printf("\n[4] Eliminar archivo");
        printf("\n[5] Eliminar todo");
        printf("\n[6] Fin programa");

        printf("\n\nopcion: ");
        scanf("%d",&opcion);

        switch(opcion)
        {
            case 0:
            {
                if(heap.tipo == HEAP_MIN)
                    heap.tipo = HEAP_MAX;
                else
                    heap.tipo = HEAP_MIN;

                heapify(&heap);

                printf("\nprioridad cambiada\n");
            }
            break;

            case 1:
            {
                imprimirHeap(heap);
            }
            break;

            case 2:
            {
                char nombre[50];

                generarNombre(nombre);

                int paginas = rand()%35 + 1;

                printf("\nArchivo creado:\n");
                printf("\nNombre: %s",nombre);
                printf("\n# de paginas: %d\n",paginas);

                insertarHeap(&heap, crearArchivo(nombre,paginas));
                printf("\nArchivo agregadop\n");
            }
            break;

            case 3:
            {
                Archivo *archivo = eliminarHeap(&heap);

                if(archivo)
                {
                    printf("\nIMPRIMIENDO:\n");
                    imprimirArchivo(archivo);
                    printf("\n");
                    free(archivo);
                }
                else
                {
                    printf("\nNo hay archivos\n");
                }
            }
            break;

            case 4:
            {
                if(!heap.cantidad)
                {
                    printf("\n- heap vacio -\n");
                    break;
                }

                imprimirHeap(heap);

                int indice;

                printf("\nIngresar indice: ");
                scanf("%d",&indice);

                eliminarIndiceHeap(&heap,indice);

                printf("\nArchivo eliminado\n");
            }
            break;

            case 5:
            {
                vaciarHeap(&heap);

                printf("\nVaciado\n");
            }
            break;

            case 6:
            {
                printf("\nFIN\n");
            }
            break;

            default:
            {
                printf("\nOpcion invalida\n");
            }
        }

    }while(opcion != 6);

    vaciarHeap(&heap);

    return 0;
}

void generarNombre(char *nombre)
{
    char letras[] =
    {
        'A','B','C','D','E','F','G','H','I','J',
        'K','L','M','N','O','P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };

    int longitud = rand()%7 + 3;

    for(int i=0;i<longitud;i++)
    {
        int indice = rand()%26;
        nombre[i] = letras[indice];
    }
    nombre[longitud] = '\0';
}