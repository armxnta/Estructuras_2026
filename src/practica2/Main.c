#include <stdio.h>
#include <iostring.h>
#include <listadoble.h>
#include "Alumno.h"


int main()
{
	int opc=0;
	
	//inicializar lista doble
	ListaD lista = inicializarListaD(imprimirAlumno, compararMatricula, free);
	ListaD listaComp = inicializarListaD(imprimirAlumno, compararMatricula, free);
	
	do{
        printf("\n\n----------- MENU ------------\n");
        printf("1) Agregar alumno\n2) Imprimir lista\n3) Reordenar\n");
        printf("4) Buscar alumno\n5) Borrar alumno\n6) Finalizar programa\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opc);

        switch (opc){

            case 1: {
				Alumno *nuevo = crearAlumno(); 

				NodoD *busqueda = buscarDatoEspecificoD(lista, nuevo, listaComp);

				if (busqueda != NULL)
				{
					printf("Ya existe esa matricula\n\n");
					free(nuevo);  
				}
				else
				{
					insertEnOrdenD(&lista, nuevo); 
				}
				
				free(busqueda);
				
				break;
            }

            case 2: {
                imprimirListaDIF(lista);
				printf("\n");
				imprimirListaDFI(lista);
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
                            reordenarD(&lista, compararNombre);
                            printf("Lista reordenada por nombre\n");
                            imprimirListaDIF(lista);
							printf("\n");
							imprimirListaDFI(lista);
                            break;

                        case 2:
                            reordenarD(&lista, compararPromedio);
                            printf("Lista reordenada por promedio\n");
                            imprimirListaDIF(lista);
							printf("\n");
							imprimirListaDFI(lista);
                            break;

                        case 3:
                            reordenarD(&lista, compararSemestre);
                            printf("Lista reordenada por semestre\n");
                            imprimirListaDIF(lista);
							printf("\n");
							imprimirListaDFI(lista);
                            break;

                        case 4:
                            reordenarD(&lista, compararMatricula);
                            printf("Lista reordenada por matricula\n");
                            imprimirListaDIF(lista);
							printf("\n");
							imprimirListaDFI(lista);
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
						listaComp.comparar = compararMatricula;
                        break;

                    case 2:
                        printf("Nombre: ");
                        scanf(" %[^\n]", temp.nombre);
                        listaComp.comparar = compararNombre;
                        break;

                    case 3:
                        printf("Semestre: ");
                        scanf("%d",&temp.semestre);
                        listaComp.comparar = compararSemestre;
                        break;

                    case 4:
                        printf("Promedio: ");
                        scanf("%f",&temp.promedio);
                        listaComp.comparar = compararPromedio;
                        break;

                    default:
                        printf("Opcion invalida\n");
                        break;
                }
				
				NodoD *busqueda = buscarDatoEspecificoD(lista, &temp, listaComp);
                imprimirRes(lista, busqueda);
				listaComp.comparar = compararMatricula;
                break;
            }

            case 5: {
				
				Alumno temp;

                printf("\nMatricula a eliminar: ");
                scanf("%u",&temp.matricula);
				
				listaComp.comparar = compararMatricula;
				
				NodoD *busqueda = buscarDatoEspecificoD(lista, &temp, listaComp);
				borrarElemento(&lista, &temp, listaComp, busqueda);
				
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