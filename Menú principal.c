#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int menu_ppal(void);
//int menu2 (void);
int main (void) {
	setlocale(LC_ALL, "es-ES");
	menu_ppal();
	return 0;
}


int menu_ppal(void) {
	int opcion;	
	printf("Men� principal\n");
	printf("=================\n");
	printf("Seleccione una opci�n:\n");
	printf("1- Bebida A\n");
	printf("2- Bebida B\n");
	printf("3- Bebida C\n");
	printf("4- Bebida mezclada\n");
	printf("5- Salir del programa\n");
	scanf_s("%d", &opcion);
	while (opcion < 1 || opcion>5) {//si elige una opci�n no valida da error
		printf("La opci�n elegida no es v�lida. Seleccione una de las opciones.\n");
		scanf_s("%d", &opcion);
	}
	/*if(opcion==4)//Si se elige la opcion mezcla de bebida te manda al men� 2
	menu2();
	*/
	printf("Ha elegido la opci�n %d", opcion);
	return 0;
}
