#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int menu_ppal(void);
int menu2 (void);

int main (void)
{
    setlocale(LC_ALL, "es_ES");
//  menu_ppal();
    menu2();
    return 0;
}

int menu2(void)
{
    int opcion2;
    float bebidaA, bebidaB, bebidaC, total;
    
    printf("Menú de mezcla\n");
    printf("==============\n");
    printf("Seleccione una opción\n");
    printf("1- Mitad de Bebida A y mitad de Bebida B\n");
    printf("2- Mitad de Bebida B y mitad de Bebida C\n");
    printf("3- Mitad de Bebida C y mitad de Bebida A\n");
    printf("4- Bebida personalizada\n");
    printf("5- Salir del programa\n");
    scanf_s("%d", &opcion2);
    
    while (opcion2 < 1 || opcion2 > 5) //Si la opción no es válida, da error.
    {  
        printf("La opción elegida no es válida. Seleccione una de las opciones\n");
        scanf_s("%d", &opcion2);
    } //Si la opcion==4 se abre un nuevo print en el que se pide proporción de cada bebida.
    if(opcion2 == 4)
    {
        printf("Introduzca la proporción de cada bebida (la suma debe ser igual a 100):\n");
        printf("Porcentaje de bebida A:\n");
        scanf_s("%f", &bebidaA);
        printf("Porcentaje de bebida B:\n");
        scanf_s("%f", &bebidaB);
        printf("Porcentaje de bebida C:\n");
        scanf_s("%f", &bebidaC);
        
        total=bebidaA+bebidaB+bebidaC;
        if(total!=100)
        printf("La proporción escogida es incorrecta. Por favor, introduzca de nuevo\n");
        //volver a mostrar print "proporción de cada bebida"
        else
        {
            printf("Ha seleccionado %f por ciento de bebida A,", bebidaA);
            printf("%f por ciento de bebida B", bebidaB);
            printf("%f por ciento de bebida C", bebidaC);
        }
    }
    printf("Ha elegido la opción %d", opcion2);
    return 0;    
}
