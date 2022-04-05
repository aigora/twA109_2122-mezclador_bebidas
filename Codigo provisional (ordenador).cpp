
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//Estructuras y tipos de variables
enum estados { MENU_PPAL, MENU_2, MEZCLA, SALIR };

typedef struct {
	int A, B, C;
}proporciones;

typedef struct {
	unsigned int A, B, C;
}tiempos;

struct Bebidas {
	proporciones proporcion;
	tiempos tiempo;
	struct Bebidas* siguiente;
};
typedef struct Bebidas bebidas;

//Funciones prototipo
int menu_ppal(void);
int menu2(void);
int bebida_personalizada(char);

int main(void) {
	int opcion, confirmacion;
	enum estados estado = MENU_PPAL;
	bebidas bebida = {0,0,0,0,0,0,NULL};
	
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
	printf("5- Salir del programa\n");
	scanf_s("%d", &opcion);
	while (opcion < 1 || opcion>5) {
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