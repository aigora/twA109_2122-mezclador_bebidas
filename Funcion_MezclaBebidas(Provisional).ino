//Declaramos las constantes de los pin:
const int pinFinalCarrera = 2; //Pin Digital
const int pinLED_R = 9, pinLED_G = 10, pinLED_B = 11; //Pin digital PWM
const int pinValvulaA = 3, pinValvulaB = 4, pinValvulaC = 5; //Pin digitales (En realidad van a los respectivos relés)

//Emplearemos una máquina de estados que mida si el vaso está presente o no:
enum estados {sin_vaso, con_vaso};

//Declaramos las variables que usaremos en el programa:
//Variables que utilizaremos como temporizador (al tratarse de un tiempo nunca dara valores negativos)
unsigned long temporizador;
unsigned long tiempoA, tiempoB, tiempoC; //Tiempo que debe estar abierta cada valvula (al tratarse de un tiempo nunca dara valores negativos)
int LED_R, LED_G, LED_B; //Colores que debe mostrar el LED (entre 0 y 255)

void setup() {
  //Definimos como funcionara cada pin
  //Final de Carrera
  pinMode(pinFinalCarrera, INPUT);

  //LED
  pinMode(pinLED_R, OUTPUT);
  pinMode(pinLED_G, OUTPUT);
  pinMode(pinLED_B, OUTPUT);

  //Relés de las valvulas
  pinMode(pinValvulaA, OUTPUT);
  pinMode(pinValvulaB, OUTPUT);
  pinMode(pinValvulaC, OUTPUT);

  //Para las primeras pruebas, daremos unos valores fijos a los tiempos
  tiempoA = tiempoB = tiempoC = 0;

  //Emplearemos el monitor en serie para realizar pruebas durante el desarrollo del programa (mostrar errores, estado, o valores de variables)
  Serial.begin(9600);
}

//Dado que repetiremos la misma cadena de acciones tres veces, definiremos una función para representarla

void mezclar_bebida(const int pinValvula, unsigned long tiempoValvula) {
  
  //Definimos variables locales
  //Empezamos por dos variables que midan el tiempo que lleva abierta la valvula, y el tiempo total registrado en la última actualización de tiempos:
  unsigned long tiempo_f = 0, tiempo_a = millis();
  
  //Continuamos con la variable para comprobar el estado del botón y la máquina de estados
  int FinalCarrera = 0; //Valor entre 0 y 1 que da el final de carrera
  estados estado = con_vaso; //Estado para la máquina de estados

  //Emplearemos un while con nuestros tiempos como condición, así también aseguramos no cerrar
  while (tiempo_f < tiempoValvula) {
    FinalCarrera = digitalRead(pinFinalCarrera);
    temporizador = millis(); //Actualizamos el tiempo del temporizador
    
    //Maquina de estados para decidir si va abierto o cerrado.
    switch (estado) {
      case sin_vaso:
        if (FinalCarrera == 1) {
          estado = con_vaso;
          Serial.println("Continuando proceso de mezclado");
          digitalWrite(pinValvula, HIGH);
          //Actualizamos el tiempo en funcionamiento, igual a el tiempo que ya ha estado funcionado, más el tiempo que ha pasado desde la última vez que se actualizó (milisegundos).
          tiempo_f = tiempo_f + (temporizador - tiempo_a);
          tiempo_a = temporizador;
        }
        else{
          tiempo_a = temporizador;
        }
        break;
      case con_vaso:
        if (FinalCarrera == 0) {
          estado = sin_vaso;
          digitalWrite(pinValvula, LOW);
          Serial.println("Error: No se detecta vaso.");
          Serial.println("Por favor, vuelva a introducir el vaso para continuar.");
          tiempo_a = temporizador;
        }
        else {
          digitalWrite(pinValvula, HIGH);
          //Actualizamos el tiempo en funcionamiento, igual a el tiempo que ya ha estado funcionado, más el tiempo que ha pasado desde la última vez que se actualizó (milisegundos).
          tiempo_f = tiempo_f + (temporizador - tiempo_a);
          tiempo_a = temporizador;
        }
    }
  }
  digitalWrite(pinValvula,LOW);
}

//Necesitamos tambien una funcion que permita obtener los tiempos de la cadena que los contiene
void extraer_tiempo(String mensaje, unsigned long* tiempo){
  int i;
  for(i=0;mensaje[i]!='\0';i++){
    if(mensaje[i]>='0' && mensaje[i]<='9'){
      *tiempo = ((*tiempo)*10)+(mensaje[i]-'0');
    }
  }
}


void loop() {
  //Empleando la función definida anteriormente, hacemos funcionar las tres valvulas:
  if (Serial.available ()>0){
    //Leemos los tiempos
    String mensaje_ordenador = Serial.readStringUntil('B');
    extraer_tiempo(mensaje_ordenador, &(tiempoA));
    mensaje_ordenador = Serial.readStringUntil('C');
    extraer_tiempo(mensaje_ordenador, &(tiempoB));
    mensaje_ordenador = Serial.readStringUntil('\n');
    extraer_tiempo(mensaje_ordenador, &(tiempoC));
    //Abrimos Valvulas
    if (tiempoA > 0) {
      Serial.println("Abriendo primera valvula:");
      mezclar_bebida(pinValvulaA, tiempoA);
      Serial.println("Fin primera valvula, pasando a la siguiente");
      tiempoA = 0;
    }
    if (tiempoB > 0) {
      Serial.println("Abriendo segunda valvula:");
      mezclar_bebida(pinValvulaB, tiempoB);
      Serial.println("Fin segunda valvula, pasando a la siguiente");
      tiempoB = 0;
    }
    if (tiempoC > 0) {
      Serial.println("Abriendo tercera valvula:");
      mezclar_bebida(pinValvulaC, tiempoC);
      Serial.println("Fin tercera valvula");
      tiempoC = 0;
    }
    Serial.println("MEZCLA FINALIZADA");
  }
}
