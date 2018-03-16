/*
----------------------------------------------------------------------
Semáforo con LEDs
-----------------------------------------------------------------------
Programa que simula el funcionamiento de dos semáforos, uno de 
peatones y otro de automivilistas, sincronizados para que los 
automivilistas puedan circular mientas el semáforo de peatón se 
encuentra en alto y cuando el peatón presione el botón
ambos semáforos cambien permitiendo que el peatón pase. También
utiliza un buzzer para que produzca un sonido mientras el peatón
pasa.

Sistemas Programables
Karla Paola Gaona Delgado
19 de febrero del 2018
*/

//--------------------------------------------------
//Declara puertos de entradas y salidas y variables
//--------------------------------------------------
int pulsador = 2;                   // Pin conectado al Botón
const int pot = 0;                  // Pin análogo conectado al Potenciómetro
unsigned long tiempoAnterior=0;     // Guarda tiempo de referencia para comparar
int velocidad;                      // Variable para guardar la velocidad
int buzzer = 8;                     // Pin asignado al Buzzer
int duracion=250;                   // Duración del sonido
int fMin=2000;                      // Frecuencia más baja que queremos emitir
int fMax=4000;                      // Frecuencia más alta que queremos emitir
int i=0;

// ---------------------------------------------------------------------
// Método para reproducir el sonido para indicar al peatón que puede pasar mediante 
// las variables de frecuencia más baja y más alta, reproduciendose durante un tiempo determinado
// ----------------------------------------------------------------------
void sonido(){
    //sonido más agudo
    for (i=fMin;i<=fMax; i++)
      tone(buzzer, i, duracion);
    //sonido más grave
    for (i=fMax;i>=fMin; i--)
      tone(buzzer, i, duracion);
}

//------------------------------------
//Funcion principal
//------------------------------------
void setup() {
  pinMode(pulsador,INPUT);
  pinMode(3,OUTPUT);      // LED rojo peatón
  pinMode(4,OUTPUT);      // LED verde peatón
  pinMode(5,OUTPUT);      // LED rojo semáforo
  pinMode(6,OUTPUT);      // LED amarillo semáforo
  pinMode(7,OUTPUT);      // LED verde semáforo
}

//------------------------------------
//Funcion ciclicla
//------------------------------------
void loop() {
  /*leemos el valor del potenciometro divididos entre 4 ya que
   solo se pueden usar valores entre 0 y 255 en analog Write  */
  velocidad = analogRead ((pot)/4) + 5000;      // Le sumo 5000 para que el tiempo no sea muy corto
  /*analogWrite recibe dos valores, el pin a usar y la intensidad del voltaje
   los valores de voltaje van de 0 a 255*/
  
  digitalWrite(3,HIGH);         // Enciende Rojo peatón
  digitalWrite(7,HIGH);         // Enciende verde semáforo

  //Condicional para saber estado del pulsador
  if (digitalRead(pulsador)==HIGH){
    //Pulsador oprimido
    digitalWrite(4,LOW);        // Apaga Verde peatón
    digitalWrite(5,LOW);        // Apaga Rojo semáforo
  } else if(millis()>tiempoAnterior+velocidad){     // Debe cumplir con el tiempo especificado para continuar
    //Pulsador NO oprimido
    digitalWrite(7,LOW);        // Apaga verde semáforo
    delay(500);             
    digitalWrite(6,HIGH);       // Enciende amarillo semáforo
    delay(500);
    digitalWrite(6,LOW);        // Apaga amarillo semáforo
    delay(500);
    digitalWrite(5,HIGH);       // Enciende rojo semáforo
    digitalWrite(4,HIGH);       // Enciende Verde peatón
    digitalWrite(3,LOW);        // Apaga Rojo peatón
    sonido();
    delay(velocidad);           // Da un tiempo de espera que es el valor de la velocidad
    tiempoAnterior=millis();    // Guarda el tiempo actual como referencia
  }
  
}
