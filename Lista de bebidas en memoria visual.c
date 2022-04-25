#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TAM 50
//Estructuras y tipos de variables
enum estados { MENU_PPAL, MENU_2,MENU_LISTA, MEZCLA, SALIR };

typedef struct {
	int A, B, C;
}proporciones;

typedef struct {
	unsigned int A, B, C;
}tiempos;

typedef struct{
	proporciones proporcion;
	tiempos tiempo;
}bebidas;

struct Lista_de_bebidas{
	char nombre[TAM];
	bebidas bebida_lista;
	struct Lista_de_bebidas* siguiente;
};
typedef struct Lista_de_bebidas lista;
//Funciones prototipo
int menu_lista(void);
int ampliar_lista(lista**);
void mostrar_bebidas(lista); 
lista* posicion_bebida(lista*, char*);
void consultar_bebida(lista*);
void mostrar_lista(lista*);
void modificar_bebida(lista*);
int menu_ppal(void);
int menu2(void);
int bebida_personalizada(char);

int main(void) {
	int opcion, confirmacion,resultado;
	enum estados estado = MENU_PPAL;
	lista* puntero_lista=NULL;
	bebidas bebida = {0,0,0,0,0,0};

	setlocale(LC_ALL, "es-ES");

	while (estado != SALIR) {
		switch (estado) {
		case MENU_PPAL:
			opcion = menu_ppal();
			switch (opcion) {
			case 1:
				bebida.proporcion.A = 100;
				estado = MEZCLA;
				break;
			case 2:
				bebida.proporcion.B = 100;
				estado = MEZCLA;
				break;
			case 3:
				bebida.proporcion.C = 100;
				estado = MEZCLA;
				break;
			case 4:
				estado = MENU_2;
				break;
			case 5:
				estado = MENU_LISTA;
				break;
			case 6:
				estado = SALIR;
				break;
			}
			break;
		case MENU_2:
			opcion = menu2();
			switch (opcion) {
			case 1:
				bebida.proporcion.A = bebida.proporcion.B = 50;
				estado = MEZCLA;
				break;
			case 2:
				bebida.proporcion.A = bebida.proporcion.C = 50;
				estado = MEZCLA;
				break;
			case 3:
				bebida.proporcion.C = bebida.proporcion.B = 50;
				estado = MEZCLA;
				break;
			case 4:
				bebida.proporcion.A = bebida_personalizada('A');
				bebida.proporcion.B = bebida_personalizada('B');
				bebida.proporcion.C = bebida_personalizada('C');
				while (bebida.proporcion.A + bebida.proporcion.B + bebida.proporcion.C != 100) {
					printf("Los porcentajes introducidos no suman 100, vuelva a introducirlos.\n");
					bebida.proporcion.A = bebida_personalizada('A');
					bebida.proporcion.B = bebida_personalizada('B');
					bebida.proporcion.C = bebida_personalizada('C');
				}
				printf("Las porcentajes de su bebida son %d de A, %d de B y %d de C\n", bebida.proporcion.A, bebida.proporcion.B, bebida.proporcion.C);
				printf("Si desea confirmar introduzca 1. Si pulsa otro botón volverá al manu principal\n");
				scanf_s("%d", &confirmacion);
				if (confirmacion == 1) {
					estado = MEZCLA;
				}
				else {
					estado = MENU_PPAL;
				}
				break;
			case 5:
				estado = MENU_PPAL;
				break;
			}
		case MEZCLA:
			printf("PENDIENTE DE DESARROLLO\n");
			bebida.tiempo.A = bebida.proporcion.A * 1000;
			bebida.tiempo.B = bebida.proporcion.B * 1000;
			bebida.tiempo.C = bebida.proporcion.C * 1000;
			estado = MENU_PPAL;
			break;
		case MENU_LISTA:
			opcion = menu_lista();
			switch (opcion) {
			case 1:
				resultado = ampliar_lista(&puntero_lista);
				if (resultado == 0) {
					printf("Se ha añadido correctamente la bebida");
				}
				else {
					printf("No se ha añadido correctamnete la bebida");
				}
				break;
			case 2:
				mostrar_lista(puntero_lista);
				break;
			case 3:
				consultar_bebida(puntero_lista);
				break;
			case 4:
				modificar_bebida(puntero_lista);
				break;
			
			case 6:
				estado = MENU_PPAL;
				break;
			}

		}
	}
}

int menu_ppal(void) {
	int opcion;
	printf("Menú principal\n");
	printf("=================\n");
	printf("Seleccione una opción:\n");
	printf("1- Bebida A\n");
	printf("2- Bebida B\n");
	printf("3- Bebida C\n");
	printf("4- Bebida mezclada\n");
	printf("5- Menú de lista\n");
	printf("6- Salir del programa\n");
	scanf_s("%d", &opcion);
	while (opcion < 1 || opcion>6) {
		printf("La opción elegida no es válida. Seleccione una de las opciones.\n");
		scanf_s("%d", &opcion);
	}
	printf("Ha elegido la opción %d\n", opcion);
	return opcion;
}

int menu2(void) {
	int opcion2;
	printf("Menú de mezcla\n");
	printf("==============\n");
	printf("Seleccione una opción\n");
	printf("1- Mitad de Bebida A y mitad de Bebida B\n");
	printf("2- Mitad de Bebida B y mitad de Bebida C\n");
	printf("3- Mitad de Bebida C y mitad de Bebida A\n");
	printf("4- Bebida personalizada\n");
	printf("5- Volver al menú principal\n");
	scanf_s("%d", &opcion2);
	while (opcion2 < 1 || opcion2 > 5) {
		printf("La opción elegida no es válida. Seleccione una de las opciones\n");
		scanf_s("%d", &opcion2);
	}
	return opcion2;
}

int bebida_personalizada(char letra) {
	int porcentaje;
	printf("Introduzca el porcentaje deseado de la bebida %c:\n", letra);
	scanf_s("%d", &porcentaje);
	return porcentaje;
}
int menu_lista() {
	int opcion_lista;
	printf("Menú de lista\n");
	printf("==============\n");
	printf("Seleccione una opción\n");
	printf("1- Ampliar lista\n");
	printf("2- Visualizar lista\n");
	printf("3- Consultar bebida\n");
	printf("4- Modificar bebida guardada\n");
	printf("5- Eliminar bebida de lista\n");
	printf("6- Volver al menú principal\n");
	scanf_s("%d", &opcion_lista);
	while (opcion_lista < 1 || opcion_lista > 6) {
		printf("La opción elegida no es válida. Seleccione una de las opciones\n");
		scanf_s("%d", &opcion_lista);
	}
	return opcion_lista;
}
int ampliar_lista(lista** bebida_lista) {
	int error=0;
	lista* cab=*bebida_lista;
	lista* bebida;
	char c;
	bebida = (lista*)malloc(sizeof(lista));
	if (bebida == NULL) {
		printf("No hay memoria disponible\n");
		error = -1;
	}
	else {
		scanf_s("%c", &c);
		printf("Introduzca el nombre de la bebida: ");
		gets_s(bebida->nombre, TAM);
		do {
			bebida->bebida_lista.proporcion.A = bebida_personalizada('A');
			bebida->bebida_lista.proporcion.B = bebida_personalizada('B');
			bebida->bebida_lista.proporcion.C = bebida_personalizada('C');
			scanf_s("%c", &c);
			if (bebida->bebida_lista.proporcion.A + bebida->bebida_lista.proporcion.B + bebida->bebida_lista.proporcion.C != 100) {
				printf("Los porcentajes introducidos no suman 100, vuelva a introducirlos\n");
			}
		} while (bebida->bebida_lista.proporcion.A + bebida->bebida_lista.proporcion.B + bebida->bebida_lista.proporcion.C != 100);
		bebida->siguiente = cab;
		cab = bebida;
	}
	*bebida_lista = cab;
	return error;
 
}
void mostrar_bebidas(lista* bebida) {
	printf("Nombre: %s\n", bebida->nombre);
	printf("Porcentaje bebida A: %d. ", bebida->bebida_lista.proporcion.A);
	printf("Porcentaje bebida B: %d. ", bebida->bebida_lista.proporcion.B);
	printf("Porcentaje bebida C: %d.\n", bebida->bebida_lista.proporcion.C);
	return;
}
void mostrar_lista(lista** elementos_lista) {
	lista* bebidas;
	if (elementos_lista == NULL) {
		printf("No hay bebidas guardadas\n");
	}
	else {
		printf("Bebidas en la lista y sus porcentajes\n");
		for (bebidas = elementos_lista; bebidas != NULL; bebidas = (lista*)bebidas->siguiente) {
			mostrar_bebidas(bebidas);
		}
	}
}
lista* posicion_bebida(lista* bebida, char nombre[TAM]) {
	lista* p = bebida;
	for (p = bebida; p != NULL; p = p->siguiente) {
		if (strcmp(nombre, p->nombre) == 0) {
			return p;
		}
	}
	p = NULL;
	return p;
}
void consultar_bebida(lista* bebida) {
	char c;
	char nombre[TAM];
	lista* lista;
	scanf_s("%c", &c);
	printf("Introduzca el nombre de la bebida que quiere buscar:\n");
	gets_s(nombre, TAM);
	lista = posicion_bebida(bebida, nombre);
	if (lista == NULL) {
		printf("No hay ninguna bebida guaradada con ese nombre");
	}
	else {
		mostrar_bebidas(lista);
	}
	return;
}
void modificar_bebida(lista* bebida) {
	char nombre[TAM];
	char c;
	lista* p;
	scanf_s("%c", &c);
	printf("Introduzca el nombre de la bebida a modificar\n");
	gets_s(nombre, TAM);
	p = posicion_bebida(bebida, nombre);
	if (p == NULL) {
		printf("No hay ninguna bebida guaradada con ese nombre");
	}
	else{
		printf("Vuelva a introducir los procentajes de la bebida %s", bebida->nombre);
		do {
			bebida->bebida_lista.proporcion.A = bebida_personalizada('A');
			bebida->bebida_lista.proporcion.B = bebida_personalizada('B');
			bebida->bebida_lista.proporcion.C = bebida_personalizada('C');
			scanf_s("%c", &c);
			if (bebida->bebida_lista.proporcion.A + bebida->bebida_lista.proporcion.B + bebida->bebida_lista.proporcion.C != 100) {
				printf("Los porcentajes introducidos no suman 100, vuelva a introducirlos\n");
			}
		} while (bebida->bebida_lista.proporcion.A + bebida->bebida_lista.proporcion.B + bebida->bebida_lista.proporcion.C != 100);
	}
	return;
}
