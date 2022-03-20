#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int ejecutar_menuppal(int);
int menu_ppal(void);
int menu2(void);
int bebida_personalizada(char);
int main(void) {
	int opcion;
	setlocale(LC_ALL, "es-ES");
	opcion = menu_ppal();
	ejecutar_menuppal(opcion);
	return 0;
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
	while (opcion2 < 1 || opcion2 > 5) 	{
		printf("La opción elegida no es válida. Seleccione una de las opciones\n");
		scanf_s("%d", &opcion2);
	} 
	return opcion2;
}
int ejecutar_menuppal(int opcion) {
	int bebidaA=0, bebidaB=0, bebidaC=0,opcion2=0,confirmacion;
	switch (opcion) {
	case 1:
		bebidaA = 100;
		break;
	case 2:
		bebidaB = 100;
		break;
	case 3:
		bebidaC = 100;
		break;
	case 4:
		opcion2=menu2();
		switch (opcion2) {
		case 1:
			bebidaA = bebidaB = 50;
			break;
		case 2:
			bebidaA = bebidaC = 50;
			break;
		case 3:
			bebidaC = bebidaB = 50;
			break;
		case 4:
			bebidaA = bebida_personalizada('A');
			bebidaB = bebida_personalizada('B');
			bebidaC = bebida_personalizada('C');
			while (bebidaA + bebidaB + bebidaC != 100) {
				printf("Los porcentajes introducidos no suman 100, vuelva a introducirlos.\n");
				bebidaA = bebida_personalizada('A');
				bebidaB = bebida_personalizada('B');
				bebidaC = bebida_personalizada('C');
			}
			printf("Las porcentajes de su bebida son %d de A, %d de B y %d de C\n", bebidaA, bebidaB, bebidaC);
			printf("Si desea confirmar introduzca 1. Si pulsa otro botón volverá al manu principal\n");
			scanf_s("%d", &confirmacion);
			if (confirmacion == 1) {
				//se activan las válvulas
			}
			else {
				opcion = menu_ppal;
				ejecutar_menuppal(opcion);
			}
			break;
		case 5:
			opcion = menu_ppal();
			ejecutar_menuppal(opcion);
			break;
		}
	}
	return 0;
}
int bebida_personalizada(char letra) {
	int porcentaje;
	printf("Introduzca el porcentaje deseado de la bebida %c:\n", letra);
	scanf_s("%d", &porcentaje);
	return porcentaje;
}