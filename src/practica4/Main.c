#include <stdio.h>
#include <stdlib.h>
#include <pila.h>
#include "Laberinto.h"

int main(void)
{
    Laberinto lab = crear_laberinto();
	Coordenada *punto;
	//Movimientos mov;
	Coordenada origen = {3,13};
	Coordenada destino = {1,1};
	setOrigen(lab,origen);
	setDestino(lab,destino);
	imprimirLab(lab);
	Pila pila = {NULL,0,-1,imprimirCoordenada,free};
	//PUSH INICIAL DEL ORIGEN
	punto = crearCoordenada(origen.x,origen.y);
	pushDato(&pila,punto);
	Movimientos mov;
	
	//CICLO
	while( !pilaVacia(pila) && (punto->x != destino.x || punto->y != destino.y))
	{

		punto = peekPila(pila);
		mov = movimientosPosibles(lab,*punto);	
		
		//REGRESAR
		if(bloqueado(mov))
		{
			lab[punto->x][punto->y] = 'O';
			free( popDato(&pila) );
		}
		
		
		//verificar si hay movimientos disponibles
		if(mov.down)
		{//64
			punto = crearCoordenada(punto->x+1, punto->y);
			pushDato(&pila, punto);
			printf("\n");
			imprimirCoordenada(punto);
			
			if(lab[punto->x][punto->y] == 'B')
				break;
			else
				lab[punto->x][punto->y] = '.';
			
		}
		else if(mov.right)
		{
			punto = crearCoordenada(punto->x, punto->y+1);
			pushDato(&pila, punto);
			printf("\n");
			imprimirCoordenada(punto);
			
			if(lab[punto->x][punto->y] == 'B')
				break;
			else
				lab[punto->x][punto->y] = '.';
			
		}
		else if(mov.up)
		{
			punto = crearCoordenada(punto->x-1, punto->y);
			pushDato(&pila, punto);
			printf("\n");
			imprimirCoordenada(punto);
			
			if(lab[punto->x][punto->y] == 'B')
				break;
			else
				lab[punto->x][punto->y] = '.';
			
		}
		else if(mov.left)
		{
			punto = crearCoordenada(punto->x, punto->y-1);
			pushDato(&pila, punto);
			printf("\n");
			imprimirCoordenada(punto);
			
			if(lab[punto->x][punto->y] == 'B')
				break;
			else
				lab[punto->x][punto->y] = '.';
			
		}
		
	}

	imprimirLab(lab);
	liberarLaberinto(lab);
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}


