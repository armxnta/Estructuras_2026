
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include <iostring.h>
#include <arbol.h>

int* crearEntero(int);
void imprimirEntero(void *dato);
int compararEntero(void *a, void *b);
void liberarEntero(void *dato);

void myprintf(char *msg,char *formato,...);

int main()
{
    Arbol A = {NULL,0,imprimirEntero,compararEntero,liberarEntero};
    Arbol B = {NULL,0,imprimirEntero,compararEntero,liberarEntero};

	insertarArbol(&A, crearEntero(7));
	insertarArbol(&A, crearEntero(3));
	insertarArbol(&A, crearEntero(1));
	insertarArbol(&A, crearEntero(0));
	insertarArbol(&A, crearEntero(5));
	insertarArbol(&A, crearEntero(2));
	insertarArbol(&A, crearEntero(4));
	insertarArbol(&A, crearEntero(6));
	insertarArbol(&A, crearEntero(11));
	insertarArbol(&A, crearEntero(13));
	insertarArbol(&A, crearEntero(12));
	insertarArbol(&A, crearEntero(14));
	insertarArbol(&A, crearEntero(9));
	
	insertarArbol(&B, crearEntero(7));
	insertarArbol(&B, crearEntero(3));
	insertarArbol(&B, crearEntero(1));
	insertarArbol(&B, crearEntero(0));
	insertarArbol(&B, crearEntero(5));
	insertarArbol(&B, crearEntero(2));
	insertarArbol(&B, crearEntero(4));
	insertarArbol(&B, crearEntero(6));
	insertarArbol(&B, crearEntero(11));
	insertarArbol(&B, crearEntero(13));
	insertarArbol(&B, crearEntero(12));
	insertarArbol(&B, crearEntero(14));
	insertarArbol(&B, crearEntero(9));
	
    int opc = 0, valor = 0;

    do{
        printf("\n1)Insertar en A");
		printf("\n2) Insertar en B");
		printf("\n3) Comparar arboles");
		printf("\n4) eliminar en A");
		printf("\n5) eliminar en B");
		printf("\n6) Altura");
		printf("\n7) Equilibrar arboles");
		printf("\n8) Mostrar arboles");
		printf("\n9) Salir\n");
		printf("ingresar opcion: ");
        scanf("%d",&opc);

        switch(opc)
        {
            case 1:
                printf("valor: ");
                scanf("%d",&valor);
                int *x = malloc(sizeof(int));
                *x = valor;
                insertarArbol(&A,x);
                break;

            case 2:
                printf("valor: ");
                scanf("%d",&valor);
                int *y = malloc(sizeof(int));
                *y = valor;
                insertarArbol(&B,y);
                break;

            case 3:
                if(compararDatos(&A,&B,A.comparar))
                    printf("datos iguales\n");
                else
                    printf("datos distintos\n");

                if(compararEstructura(A.raiz,B.raiz))
                    printf("Misma estructura\n");
                else
                    printf("diferente estructura\n");
                break;

            case 4:
                printf("valor: ");
                scanf("%d",&valor);
                A.raiz = eliminarNodo(A.raiz,&valor,A.comparar,A.liberar);
                break;

            case 5:
                printf("valor: ");
                scanf("%d",&valor);
                B.raiz = eliminarNodo(B.raiz,&valor,B.comparar,B.liberar);
                break;

            case 6:
                printf("altura A: %d\n", altura(A.raiz));
                printf("altura B: %d\n", altura(B.raiz));
                break;

            case 7:
                equilibrar(&A);
                equilibrar(&B);
                printf("arboles balanceados\n");
                break;

            case 8:
                printf("\nArbol A:\n");
                imprimirArbol(A);
                printf("\n\nArbol B:\n");
                imprimirArbol(B);
                break;
			
			case 9:
				printf("saliendo del programa...");
				eliminarArbol(&A);
				eliminarArbol(&B);
				break;
        }

    }while(opc!=9);

    return 0;
}

void imprimirEntero(void *dato)
{
    printf("%d", *(int*)dato);
}

int compararEntero(void *a, void *b)
{
    return (*(int*)a - *(int*)b);
}

void liberarEntero(void *dato)
{
    free(dato);
}

int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

void myprintf(char* msg,char *formato,...)
{
	va_list args;
    va_start(args, formato);
	printf("\n %s ",msg);
	char *ptr = formato;
	while(*ptr!='\0')
	{
		switch(*ptr)
		{
			case 'd':
				printf("%d ",va_arg(args, int));
				break;
			case 'c':
				printf("%c ",va_arg(args, int));				
				break;
			case 'f':
				printf("%f ",va_arg(args, double));				
				break;
			case 'x':
				printf("%x ",va_arg(args, Arbol*));				
				break;
		}
		ptr++;
	}
	va_end(args);
}

