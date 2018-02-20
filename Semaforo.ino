int pulsador = 2;     // Pin conectado al Botón
const int pot = 0;    // Pin análogo conectado al Potenciómetro
unsigned long tiempoAnterior=0; // Guarda tiempo de referencia para comparar
int velocidad;        // Variable para guardar la velocidad

void setup() {
  pinMode(pulsador,INPUT);
  pinMode(3,OUTPUT);      // LED rojo peatón
  pinMode(4,OUTPUT);      // LED verde peatón
  pinMode(5,OUTPUT);      // LED rojo semáforo
  pinMode(6,OUTPUT);      // LED amarillo semáforo
  pinMode(7,OUTPUT);      // LED verde semáforo
}

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
    delay(velocidad);           // Da un tiempo de espera que es el valor de la velocidad
    tiempoAnterior=millis();    // Guarda el tiempo actual como referencia
  }
  
}
