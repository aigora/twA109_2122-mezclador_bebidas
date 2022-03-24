//Declaramos las constantes de los pin:
const int pinFinalCarrera = 2; //Pin Digital
const int pinLED_R = 9, pinLED_G = 10, pinLED_B = 11; //Pin digital PWM
const int pinValvulaA, pinValvulaB, pinValvulaC; //Pin digitales (En realidad van a los respectivos relés)

//Declaramos las variables que usaremos en el programa:
unsigned long tiempoA, tiempoB, tiempoC; //Tiempo que debe estar abierta cada valvula (al tratarse de un tiempo nunca dara valores negativos)
int LED_R, LED_G, LED_B; //Colores que debe mostrar el LED (entre 0 y 255)

void setup() {
  //Definimos como funcionara cada pin
  //Final de Carrera
  pinMode(pinFinalCarrera,INPUT);
  
  //LED
  pinMode(pinLED_R,OUTPUT);
  pinMode(pinLED_G,OUTPUT);
  pinMode(pinLED_B,OUTPUT);

  //Relés de las valvulas
  pinMode(pinValvulaA,OUTPUT);
  pinMode(pinValvulaA,OUTPUT);
  pinMode(pinValvulaA,OUTPUT);

  //Para las primeras pruebas, daremos unos valores fijos a los tiempos
  tiempoA = tiempoB = tiempoC = 10000; //BORRAR MÁS ADELANTE
  
  Serial.begin(9600);
}

//Dado que repetiremos la misma cadena de acciones tres veces, definiremos una función para representarla

//ES NECESARIO CAMBIAR Y CORREGIR EL TEMPORIZADOR/SISTEMA PARA HACER EL TEMPORIZADOR
void mezclar_bebida(const int pinValvula, unsigned long tiempoValvula){
  //Definimos variables locales
  unsigned long temporizador; //Variable que utilizaremos como temporizador (al tratarse de un tiempo nunca dara valores negativos)
  int FinalCarrera = 0; //Valor entre 0 y 1 que da el final de carrera
  int FinalCarrera_a = 1; //Valor entre 0 y 1 que dió el final de carrera en la comprobación anterior
  
  //Comprobamos que el vaso este en posición
  do{
    FinalCarrera = digitalRead(pinFinalCarrera);
    if (FinalCarrera != 1 && FinalCarrera != FinalCarrera_a){
      Serial.println("Introduzca un Vaso");
    }
    FinalCarrera_a = FinalCarrera;
  }while(FinalCarrera != 1);

  //Abrimos la valvula e iniciamos el temporizador (suponiendo valvulas NC y relés NA)
  digitalWrite(pinValvula,HIGH);
  temporizador = millis();

  //Seguimos comprobando la presencia de vaso durante el tiempo que este abierta.
  //Emplearemos un while con nuestros tiempos como condición, así también aseguramos no cerrar 
  while(temporizador < tiempoValvula){
    FinalCarrera = digitalRead(pinFinalCarrera);
    if(FinalCarrera == 1 && FinalCarrera_a == 0){
      temporizador = temporizador + millis();//Volvemos a iniciar el temporizador
      digitalWrite(pinValvula,HIGH); //Abrimos la valvula otra vez
    }
    else if(FinalCarrera == 1){
      digitalWrite(pinValvula,HIGH); //Aseguramos que la válvula se mantenga abierta
    }
    else{
      //Paramos el temporizador y cerramos las valvulas
      temporizador = temporizador;
      digitalWrite(pinValvula,LOW);
      Serial.println("Error: Vaso no detectado, introduzca un vaso");
    }
    FinalCarrera_a = FinalCarrera;
  }
}


void loop() {
  //Empleando la función definida anteriormente, hacemos funcionar las tres valvulas:
  if(tiempoA > 0){
    Serial.println("Abriendo primera valvula:");
    mezclar_bebida(pinValvulaA,tiempoA);
    Serial.println("Fin primera valvula, pasando a la siguiente");
    tiempoA = 0;
  }
  if(tiempoB > 0){
    Serial.println("Abriendo segunda valvula:");
    mezclar_bebida(pinValvulaB,tiempoB);
    Serial.println("Fin segunda valvula, pasando a la siguiente");
    tiempoB = 0;
  }
  if(tiempoC > 0){
    Serial.println("Abriendo primera valvula:");
    mezclar_bebida(pinValvulaC,tiempoC);
    Serial.println("Fin tercera valvula, reiniciando");
    tiempoC = 0;
  }
}
