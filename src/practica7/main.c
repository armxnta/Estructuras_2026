
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <iostring.h>
#include <arbol.h>
#include "variable.h"
#include "expresion.h"


void abortar(void);
void ordenIterativo(NodoA *raiz,void (*imprimir)(void*));
void imprimirDoubleDouble(void *);
//int precedencia(char *signo);
void infixAPostfix(char *infix, char *postfix);
int verificarParentesis(char *cadena);
//int compararPrecedencia(char *a, char *b);

int main(void)
{
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.imprimir = &imprimirVariable;
	arbol.comparar = &compararVariable;
	arbol.liberar = &free;
	arbol.cantidad = 0;

	char expresion[100];
	char postfix[100];
	int opcion;

	do
	{
		printf("\n0) CAPTURAR EXPRESION");
		printf("\n1) IMPRIMIR ARBOL DE EXPRESION");
		printf("\n2) EVALUAR EXPRESION");
		printf("\n3) TERMINAR PROGRAMA");
		printf("\nIngresar una opcion: ");
		scanf("%d", &opcion);
		getchar();

		switch(opcion)
		{
			case 0:
				printf("\nIngresa expresion infix: ");
				fgets(expresion, 100, stdin);
				expresion[strcspn(expresion,"\n")] = 0;

				if(!verificarParentesis(expresion))
				{
					printf("\nExpresion invalida");
					break;
				}

				infixAPostfix(expresion, postfix);

				arbol.raiz = construirArbolPostfix(postfix);
				arbol.cantidad = contarNodos(arbol.raiz);

				printf("\nExpresion valida");
				break;

			case 1:
				if(!arbol.raiz)
				{
					printf("\nNo hay expresion cargada");
					break;
				}
				printf("\nARBOL:\n");
				imprimirArbol(arbol);
				break;

			case 2:
				if(!arbol.raiz)
				{
					printf("\nNo hay expresion cargada");
					break;
				}
				evaluar(arbol);
				break;

			case 3:
				printf("\nSaliendo...");
				break;

			default:
				printf("\nOpcion invalida");
		}

	}while(opcion != 3);

	if(arbol.raiz)
		eliminarArbol(&arbol);

	return 0;
}


void imprimirDoubleDouble(void *ptr)
{
	double **ptrdouble= ptr;	
	if(!ptrdouble)	
	{		
		printf("null ") ;
		return;
	}
	printf("%lf ",**ptrdouble); 
}

void ordenIterativo(NodoA *raiz,void (*imprimir)(void*))
{
	Pila pila = {NULL,0,-1,imprimir,NULL};
	if(!raiz)
		return;
	NodoA* aux = raiz;
	while( aux || !pilaVacia(pila))
	{			
		while(aux)
		{
			pushDato(&pila,aux);	
			aux = aux->izq;
		}		
		aux = popDato(&pila);
		imprimir(aux);		
		printf(" ");		
		aux= aux->dch;
	}	
	vaciarPila(&pila);
}

void abortar(void)
{
	char c = 'e';
	if( (c=getchar()) == 'e')
		exit(0);
}

int verificarParentesis(char *cadena)
{
	Pila pila = {NULL,0,-1,NULL,NULL};	
	int size = strlen(cadena);
	
	for(int i=0; i<size; i++)
	{
		if(cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '[')
		{
			pushDato(&pila, &cadena[i]);
			continue;
		} 
		else if(cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']')
		{
			if(pilaVacia(pila))
			{
				return 0;
			}
			
			char *letraPtr = (char*) popDato(&pila);
			char letra = *letraPtr;
				
			if(cadena[i] == ')')
			{

				if(letra == '(')
					continue;
				else
					return 0;
					
			}
				
			if(cadena[i] == '}')
			{
				
				if(letra == '{')
					continue;
				else
					return 0;
					
			}
			
			if(cadena[i] == ']')
			{
				
				if(letra == '[')
					continue;
				else
					return 0;
					
			}
		}
	}
	
	if(pilaVacia(pila))
		return 1;
	else
		return 0;

}

/*int precedencia(char *signo)
{
	
	char op = *signo;
	
    if(op == '^')
		return 3;
    if(op == '*' || op == '/')
		return 2;
    if(op == '+' || op == '-')
		return 1;
	if(op == '(' || op == ')')
		return -1;
    return 0;
	
}*/

void infixAPostfix(char *cadena, char *postfix)
{
    Pila pila = {NULL,0,-1,NULL,NULL};
    int indice = 0;
	int size = 0;
	size = strlen(cadena);

	for(int i = 0; i<size; i++)
    {
        char caracter = cadena[i];
		
		//si es caracter, se mete de una al postfix
		if((cadena[i] >= 'A'&& cadena[i] <= 'Z') || (cadena[i] >= 'a'&& cadena[i] <= 'z'))
		{
			postfix[indice++] = caracter;
			continue;
		}
		
		if(pilaVacia(pila) || compararPrecedencia(&caracter, (char*)peekPila(pila)) == 1) //si caracter es de mayor precedencia que peek pila
		{
			pushDato(&pila, &cadena[i]); //insertar dato en pila
		}
		else //si no, ver si caracter es menor que peek pila
		{
			if(caracter == '(')
				pushDato(&pila, &cadena[i]); //si es parentesis, push en la pila
			else if(caracter == ')') //si es parentesis de cierre
			{
					while(*(char*)peekPila(pila) != '(') //vaciar pila hasta que se encuentre el parentesis de apertura
					{
						postfix[indice++] = *(char*)popDato(&pila);
					}
					popDato(&pila);
			}
			else if(compararPrecedencia(&caracter, (char*)peekPila(pila)) < 1) 
			{
				while(!pilaVacia(pila))
				{
					if(compararPrecedencia(&caracter, (char*)peekPila(pila)) == 1)
					{
						break;
					}
					postfix[indice++] = *(char*)popDato(&pila);
				}
				pushDato(&pila, &cadena[i]);
			}
		}
		
	}
	
	while(!pilaVacia(pila))
	{
		postfix[indice++] = *(char*)popDato(&pila);
	}
	
	postfix[indice] = '\0';
}

/*int compararPrecedencia(char *a, char *b)
{
	
	if(precedencia(a) > precedencia(b))
		return 1;
	
	else if(precedencia(a) < precedencia(b))
		return 0;

	return -1; //si son iguales

}*/