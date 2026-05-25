#include <stdio.h>
#include "Alumno.h"
#include "Lista.h"

int main()
{
    int opc = 0;

    Lista lista = {NULL,NULL,0,imprimirAlumno,compararMatricula,free};
	Lista paraMat = {NULL,NULL,0,imprimirAlumno,compararMatricula,free};

    do{
        printf("\n\n----------- MENU ------------\n");
        printf("1) Agregar alumno\n2) Imprimir lista\n3) Reordenar\n");
        printf("4) Buscar alumno\n5) Borrar alumno\n6) Finalizar programa\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opc);

        switch (opc){

            case 1: {
				Alumno *nuevo = crearAlumno(); 

				Resultado res = buscarMat(lista, nuevo, paraMat);

				if (res.enco != NULL)
				{
					printf("Ya existe esa matricula\n");
					free(nuevo);  
				}
				else
				{
					agregarEnOrden(&lista, nuevo); 
				}
				break;
            }

            case 2: {
                imprimirLista(lista);
                break;
            }

            case 3: {
                int opcR = 0;

                do {
                    printf("\n--- REORDENAR ---");
                    printf("\n1) Nombre\n2) Promedio\n3) Semestres\n4) Matricula\n5) Salir\n");
                    printf("Seleccione una opcion: ");
                    scanf("%d", &opcR);

                    switch(opcR) {

                        case 1:
                            reordenar(&lista, compararNombre);
                            printf("Lista reordenada por nombre\n");
                            imprimirLista(lista);
                            break;

                        case 2:
                            reordenar(&lista, compararPromedio);
                            printf("Lista reordenada por promedio\n");
                            imprimirLista(lista);
                            break;

                        case 3:
                            reordenar(&lista, compararSemestre);
                            printf("Lista reordenada por semestre\n");
                            imprimirLista(lista);
                            break;

                        case 4:
                            reordenar(&lista, compararMatricula);
                            printf("Lista reordenada por matricula\n");
                            imprimirLista(lista);
                            break;
						case 5:
							break;
                        default:
                            printf("Opcion invalida\n");
                    }

                } while(opcR!=5);

                break;
            }

            case 4: {
                int datoBuscar;
                Alumno temp;

                printf("\nBuscar por:\n");
                printf("1) Matricula\n2) Nombre\n3) Semestre\n4) Promedio\n");
                printf("Seleccione: ");
                scanf("%d",&datoBuscar);

                switch(datoBuscar){

                    case 1:
                        printf("Matricula: ");
                        scanf("%u",&temp.matricula);
						paraMat.comparar = compararMatricula;
                        break;

                    case 2:
                        printf("Nombre: ");
                        scanf(" %[^\n]", temp.nombre);
                        paraMat.comparar = compararNombre;
                        break;

                    case 3:
                        printf("Semestre: ");
                        scanf("%d",&temp.semestre);
                        paraMat.comparar = compararSemestre;
                        break;

                    case 4:
                        printf("Promedio: ");
                        scanf("%f",&temp.promedio);
                        paraMat.comparar = compararPromedio;
                        break;

                    default:
                        printf("Opcion invalida\n");
                        break;
                }

                Resultado res = buscarPor(lista, &temp, paraMat);
                imprimirResultado(lista, res);
                break;
            }

            case 5: {
                Alumno temp;

                printf("\nMatricula a eliminar: ");
                scanf("%u",&temp.matricula);

                paraMat.comparar = compararMatricula;
                eliminarDato(&lista, &temp, &paraMat);

                printf("Alumno borrado\n");
                break;
            }

            case 6: {
                printf("\nPrograma finalizado\n");
                break;
            }

            default:
                printf("Opcion invalida\n");
        }


    }while (opc != 6);

    return 0;
}