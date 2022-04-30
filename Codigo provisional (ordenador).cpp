
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "SerialClass/SerialClass.h"

#define MAX_BUFFER 200
#define PAUSA_MS 200

//Estructuras y tipos de variables
enum estados { MENU_PPAL, MENU_2, MEZCLA, SALIR };

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
int eliminar_bebida(lista*,int);
int menu_ppal(void);
int menu2(void);
int bebida_personalizada(char);
int Enviar_y_recibir(Serial*, char*, char*);
void encapsular_tiempos(char* mensaje_final, bebidas bebida);
void entero_a_cadena(unsigned int numero, char* cadena);
int actualizar_informacion(Serial* Arduino, char* mensaje_enviar, int recibo_primer_mensaje);
void mezclar_bebidas(Serial* Arduino, char* port, char* mensaje);

int main(void) {
	int opcion, confirmacion;
	enum estados estado = MENU_PPAL;
	lista* puntero_lista=NULL;
	bebidas bebida = {0,0,0,0,0,0,NULL};
	char mensaje_a_enviar[30]; //Cadena que contiene el mensaje a enviar a la placa de Arduino
	Serial* Arduino; //Variable que representa internamente la placa de Arduino
	char puerto[] = "COM3"; //A qué puerto se conecta Arduino
	
	setlocale(LC_ALL, "es-ES");
	Arduino = new Serial((char*)puerto);

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
			bebida.tiempo.A = bebida.proporcion.A * 1000;
			bebida.tiempo.B = bebida.proporcion.B * 1000;
			bebida.tiempo.C = bebida.proporcion.C * 1000;
			encapsular_tiempos(mensaje_a_enviar,bebida);
			mezclar_bebidas(Arduino,puerto,mensaje_a_enviar);
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
	printf("5- Bebidas guardadas\n");
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

int eliminar_bebida(lista* lista, int *plista)
{
    char nombre[TAM], respuesta[2];
    int encontrado = NO;
    int i,j;
    int lista=*plista;
    
    if(lista==0)
        printf("No hay bebidas guardadas\n");
    else
    {
        printf("Introduzca nombre de la bebida a eliminar:\n");
        gets_s(nombre, TAM);
        for(i=0;i<lista && encontrad==NO; i++)
        {
            if(strcmp(nombre, lista[i].nombre)==0)
            {
                printf("Datos de la bebida encontrados:\n");
                mostrar_lista(lista[i]);
                printf("¿Desea borrar esta bebida? (SI/NO):\n");
                gets_s(respuesta,2);
                if(strcmp(respuesta,"Si")==0||strcmp(respuesta,"si")==0||strcmp(respuesta,"SI")==0)
                {
                    encontrado=SI;
                    for(j=i;j<n-1;j++)
                        lista[j]=lista[j+1];
                    *plista=n-1;
                }
            }
        }
        if(encontrado==NO)
            printf("No se ha eliminado el usuario\n");
    }
    
    return encontrado;
}

//Almacena los tiempos en una cadena de caracteres para enviarsela a arduino
void encapsular_tiempos(char* mensaje_final, bebidas bebida) {
	char cadena[10];

	//Almacenamos el primer tiempo
	entero_a_cadena(bebida.tiempo.A, cadena);
	strcpy_s(mensaje_final,30, cadena);

	//Almacenamos el segundo
	entero_a_cadena(bebida.tiempo.B, cadena);
	strcat_s(mensaje_final,30,"B");
	strcat_s(mensaje_final,30, cadena);

	//Almacenamos el ultimo
	entero_a_cadena(bebida.tiempo.C, cadena);
	strcat_s(mensaje_final,30, "C");
	strcat_s(mensaje_final,30, cadena);

	//Añadimos un \n, la condicion de parada de Arduino
	strcat_s(mensaje_final,30, "\n");
}

//Combierte los tiempos en cadenas de caracteres
void entero_a_cadena(unsigned int numero, char* cadena) {
	int digito = 0;
	int i,j=0,k=0;
	char cadena_aux[10];

	for (i = 0; i < 10; i++) {
		cadena[i] = '0';
	}
	for (i = 1; numero != 0; i *= 10) {
		do{
			digito++;
			numero -= i;
		}while(numero % (i*10) != 0);
		if (cadena[j] + digito == '0'+10) {
			cadena[j + 1] = '1';
			cadena[j] = '0';
		}
		else {
			cadena[j] = cadena[j] + digito;
		}
		digito = 0;
		j++;
	}
	for (i = j; i >= 0; i--) {
		cadena_aux[k] = cadena[i];
		k++;
	}
	cadena_aux[k] = '\0';
	strcpy_s(cadena, 10, cadena_aux);
}

// Mandar a Arduino comenzar la mezcla
void mezclar_bebidas(Serial* Arduino, char* port, char* mensaje)
{	
	int completado;
	int recibo_primer_mensaje = 0;
	if (Arduino->IsConnected())
	{	
		completado = actualizar_informacion(Arduino,mensaje, recibo_primer_mensaje);
		mensaje = (char*)"\0";
		recibo_primer_mensaje++;
		while (completado != 1) {
			completado = actualizar_informacion(Arduino, mensaje, recibo_primer_mensaje);
		}
	}
	else
	{
		printf("No se ha podido conectar con Arduino. Verifique la conexión, \nel puerto %s y desactive el monitor seíe del IDE DE Arduino\n", port);
	}
	printf("\n");
}

int actualizar_informacion(Serial* Arduino,char* mensaje_enviar, int recibo_primer_mensaje)
{
	int completado  = 0;
	int bytesRecibidos;
	char mensaje_recibido[MAX_BUFFER];

	bytesRecibidos = Enviar_y_recibir(Arduino, mensaje_enviar, mensaje_recibido);
	if (bytesRecibidos <= 0 && recibo_primer_mensaje == 0)
	{
		printf("No se ha recibido respuesta\n");
	}
	else if(bytesRecibidos > 0)
	{	
		printf("\n%s", mensaje_recibido);
		if (strstr(mensaje_recibido, "MEZCLA FINALIZADA") != NULL) {
			completado = 1;
		}
	}
	return completado;
}

//Envia y recibe un mensaje a arduino
int Enviar_y_recibir(Serial* Arduino,const char* mensaje_enviar, char* mensaje_recibir)
{
	int bytes_recibidos = 0, total = 0;
	int intentos = 0, fin_linea = 0;

	Arduino->WriteData((char*)mensaje_enviar, strlen(mensaje_enviar));
	Sleep(PAUSA_MS);
	bytes_recibidos = Arduino->ReadData(mensaje_recibir, sizeof(char) * MAX_BUFFER - 1);

	while ((bytes_recibidos > 0 || intentos < 5) && fin_linea == 0)
	{
		if (bytes_recibidos > 0)
		{
			total += bytes_recibidos;
			if (mensaje_recibir[total - 1] == 13 || mensaje_recibir[total - 1] == 10)
				fin_linea = 1;
		}
		else
			intentos++;
		Sleep(PAUSA_MS);
		bytes_recibidos = Arduino->ReadData(mensaje_recibir + total, sizeof(char) * MAX_BUFFER - 1);
	}
	if (total > 0)
		mensaje_recibir[total - 1] = '\0';

	return total;
}
