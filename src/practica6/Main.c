#include <pila.h>
#include <iostring.h>
#include <ctype.h>

#define MAX 100

int precedencia(char *signo);
void infixAPostfix(char *infix, char *postfix);
int verificarParentesis(char *cadena);
int compararPrecedencia(char *a, char *b);

int main()
{
    int opc=0;
    char *cadena = NULL;
    char postfix[MAX];

    do
    {
        printf("\n--- MENU ---\n");
        printf("1) Infix a Postfix\n");
        printf("2) Salir\n");
        printf("ingresar opcion: ");
        scanf("%d", &opc);
        getchar();

        switch(opc)
        {
            case 1:
				inputCadenaDinamica("\nCapturar infix: ",&cadena,MAX);

                // validar parentesis
                if(!verificarParentesis(cadena))
                {
                    printf("parentesis incorrectos\n");
                }
                else
                {
                    infixAPostfix(cadena, postfix);
                    printf("Postfix: %s\n", postfix);
                }
                break;

            case 2:
                printf("saliendo...\n");
                break;

            default:
                printf("Opcion invalida\n");
        }

    }while(opc!=2);

    return 0;
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

int precedencia(char *signo)
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
	
}

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

int compararPrecedencia(char *a, char *b)
{
	
	if(precedencia(a) > precedencia(b))
		return 1;
	
	else if(precedencia(a) < precedencia(b))
		return 0;

	return -1; //si son iguales

}

/*

4 reglas:

comparar precedencia
if(precedencia(*a) > precedencia (*b));
if(precedencia(*a) < precedencia (*b));
if(precedencia(*a) == precedencia (*b));

#1 ;
Si es caracter, se mete al postfix
>= 'A' && <= 'Z' 
>= 'a' && <= 'z' 

#2 ;
Comparar precedencia && verificar si es parentesis
Si es parentesis de apertura -> push a la pila
si es mayor que cima pila -> push pila
si pila esta vacia -> push pila

#3 ;

#4 ;


*/
