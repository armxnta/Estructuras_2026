#include "expresion.h"

NodoA* construirArbolPostfix(char *postfix)
{
	Pila pila = {NULL,0,-1,NULL,NULL};

	for(int i = 0; postfix[i] != '\0'; i++)
	{
		char c = postfix[i];

		// operando
		if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		{
			NodoA *n = crearNodoA(crearVariable(c));
			pushDato(&pila, n);
		}
		else // operador
		{
			NodoA *der = popDato(&pila);
			NodoA *izq = popDato(&pila);

			NodoA *n = crearNodoA(crearVariable(c));
			n->izq = izq;
			n->dch = der;

			pushDato(&pila, n);
		}
	}

	return popDato(&pila);
}

int contarNodos(NodoA *raiz)
{
	if(!raiz) return 0;
	return 1 + contarNodos(raiz->izq) + contarNodos(raiz->dch);
}

double evaluar(Arbol arbol)
{
	NodoA **arrOrigin = calloc(arbol.cantidad,sizeof(NodoA*));
	if(!arrOrigin)
	{
		printf("\n NO SE PUDO ASIGNAR EL ARREGLO DE NODOS");
		exit(1);
	}
	int cantidad = 0;
	extraerNodos(arbol.raiz,arrOrigin,&cantidad);	
	asignarMemoria(arrOrigin,cantidad,arbol.comparar);
	capturarValores(arrOrigin,cantidad);
	arbol.imprimir = imprimirValor;
	printf("\n ARBOL VALORES\n");
	imprimirArbol(arbol);	
	
	//AQUI LLAMAR A LA FUNCION QUE CALCULA EL RESULTADO
	double resultado = resolver(arbol.raiz);
	printf("\n\n RESULTADO = %lf\n", resultado);
		
	//LIBERAR MEMORIA RESERVADA	
	liberarMemoriaValores(arrOrigin,cantidad);	
	free(arrOrigin);
	return 0;
}

double resolver(NodoA *raiz)
{
	if(!raiz)
		return 0;

	Variable *var = (Variable*) raiz->dato;

	// Si es operando (letra)
	if(precedencia(&var->c) == 0)
	{
		return **(var->v);
	}

	// Si es operador
	double izq = resolver(raiz->izq);
	double der = resolver(raiz->dch);

	switch(var->c)
	{
		case '+': return izq + der;
		case '-': return izq - der;
		case '*': return izq * der;
		case '/': return izq / der;
		case '^': return pow(izq, der);
	}

	return 0;
}

void extraerNodos(NodoA *raiz,NodoA **nodos,int *i)
{	
	if(!raiz)
		return;
	extraerNodos(raiz->izq,nodos,i);
	nodos[ (*i) ] = raiz;
	(*i)++;
	extraerNodos(raiz->dch,nodos,i);	
}

void asignarMemoria(NodoA **original,int cantidad,int (*comparar)(void*,void*))
{
	//CREAR ARREGLO AUXILIAR
	int *indices = (int*)calloc(cantidad,sizeof(int));	
	if(!indices)
	{
		printf("\n NO SE PUDO ASIGNAR EL ARREGLO DE INDICES");
		exit(1);
	}	
	//ARREGLO AUXILIAR PARA DETECTAR DUPLICADOS
	//EN EL ARREGLO SE ASIGNAN EL INDICE DEL LA PRIMERA
	//COINCIDENCIA
	for(int i = 0; i < cantidad; i++)
		indices[i] = -1;
	for(int i = 0 ; i < cantidad; i++)
	{	
		//OMITE SI YA SE REGISTRO
		if( indices[i] != -1)
			continue;			
		//OMITE SI ES UN OPERADOR
		if(  precedencia(original[i]->dato) != OPERANDO)
			continue;	
		
		for(int j = i; j < cantidad; j++)
		{
			if( comparar(original[i]->dato,original[j]->dato)==0)				
				indices[j] = i;
		}
		double **ptr = calloc(1,sizeof(double*));		
		for(int j = 0; j < cantidad; j++)
		{
			if(indices[j] == i)
				((Variable*)(original[j]->dato))->v  = ptr;
		}		
	}
	free(indices);
}


void capturarValores(NodoA **original,int cantidad)
{
	printf("\n\n CAPTURAR VALORES \n");
	for(int i = 0;i<cantidad;i++)
	{		
		if( precedencia(original[i]->dato) != OPERANDO )
			continue;
		if(((Variable*)original[i]->dato)->v != NULL  && *((Variable*)original[i]->dato)->v == NULL )
		{
			*((Variable*)original[i]->dato)->v = calloc(1,sizeof(double));
			printf("\n Captura variable %c: ", ((Variable*)original[i]->dato)->c) ;
			inputDouble("",*((Variable*)original[i]->dato)->v);
		}			
	}	
}


void liberarMemoriaValores(NodoA **original,int cantidad)
{
	//CREAR ARREGLO AUXILIAR
	int *indices = (int*)calloc(cantidad,sizeof(int));	
	if(!indices)
	{
		printf("\n NO SE PUDO ASIGNAR EL ARREGLO DE INDICES");
		exit(1);
	}	
	//ARREGLO AUXILIAR PARA DETECTAR DUPLICADOS
	//EN EL ARREGLO SE ASIGNAN EL INDICE DEL LA PRIMERA
	//COINCIDENCIA
	for(int i = 0; i < cantidad; i++)
		indices[i] = -1;
	
	for(int i = 0;i<cantidad;i++)
	{		
		if( precedencia(original[i]->dato) != OPERANDO )
			continue;
		if( ((Variable*)original[i]->dato)->v != NULL)
		{
			//REGISTRAR DUPLICADOS
			for(int j = i; j < cantidad; j++)
			{
				if( ((Variable*)original[i]->dato)->v == ((Variable*)original[j]->dato)->v)				
					indices[j] = i;
			}	
			//LIBERAR DATO FLOTANTE double
			free( *((Variable*)original[i]->dato)->v );
			//LIBERAR APUNTADOR double*
			free( ((Variable*)original[i]->dato)->v  );
			//QUITAR DE DUPLICADOS
			for(int j = 0; j < cantidad; j++)
			{
				if( indices[j] == i )
					((Variable*)original[j]->dato)->v = NULL;
			}	
		}				
	}	
	free(indices);
}

//falta la evaluacion


