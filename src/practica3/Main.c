#include <stdio.h>
#include <iostring.h>
#include <pila.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int palindromo(char *cadena);
int verificarParentesis(char *cadena);

int main(void)
{
	int opc=0;
	char *cadena = NULL;
	
	do{
		printf("\n\n---- MENU ----\n");
		printf("\n1) Palindromo");
		printf("\n2) Parentesis");
		printf("\n3) Salir");
		printf("\nIngresar una opcion: ");
		scanf("%d", &opc);
		getchar();
		
		switch(opc)
		{
			case 1:
				inputCadenaDinamica("\n Captura cadena: ",&cadena,MAX);
				printf(" Es palindromo: %s", palindromo(cadena) ? "SI" : "NO");
			break;
				
			case 2:
				inputCadenaDinamica("\n\n Captura expresion: ",&cadena,MAX);
				printf(" Parentesis correctos : %s", verificarParentesis(cadena) ? "SI" : "NO");
				
			break;
				
			case 3:
				printf("Saliendo del programa");
				free(cadena);
			break;
		}
		
	}while(opc!=3);
	
	return 0;
}

int palindromo(char *cadena)
{
	Pila pila = {NULL,0,-1,NULL,NULL};
	
	int size = strlen(cadena);
	
	for(int i = 0 ; i<size ; i++)
	{
		if(cadena[i] != ' ')
			pushDato(&pila, &cadena[i]);
	}
	
	for(int j = 0 ; j < size ; j++)
	{
		if(cadena[j] == ' ')
			continue;
		char *letraPtr = (char*) popDato(&pila);
		char letra = *letraPtr;
		
		if(tolower(cadena[j]) == tolower(letra))
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
	
	return 1;
	
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