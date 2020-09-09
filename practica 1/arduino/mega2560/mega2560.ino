#include "HX711.h" //libreria X711 Arduino Library
#include "Pins.h"


long actualMillis = 0;
int weigtht = 0;
int distance = 0;



//variables para la lectura de peso:
HX711 sWeight;
float calibration = 20280.0; //factor de calibración para el sensor
long zeroFactor = 0;
int weight = 0;


//variables para el medidor de distancia
long duration = 0;

//variables para la conexion
String string_to_send;
long begin_millisC = 0; 


//variables para sensores 
long begin_millisS = 0;
byte doorA = 0; 
byte doorB = 0; 

//variable para la bomba
long begin_water_pump = 0;
byte status_water_pump = 0;

void setup() {

  /*
     inicialización de serials y sensores
  */
  pinMode(echoUltraSonic, INPUT);
  pinMode(triggerUltraSonic, OUTPUT);
  pinMode(proximitySensorA, INPUT);
  pinMode(proximitySensorB, INPUT);
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);   
  pinMode(ledC, OUTPUT);
  pinMode(wPump, OUTPUT);
  tareW();
  Serial .begin(115200);
  Serial3.begin(115200);
  Serial.println(F(">> ** INICIANDO ARDUINO **"));

}



void read_prox_sensors(){
  //sensor de proximidad
  doorA = !digitalRead(proximitySensorA);
  //sensor de luz
  doorB = digitalRead(proximitySensorB); 
  
  if (doorA>0){
    digitalWrite(ledA, HIGH);
  }else {
    digitalWrite(ledA, LOW);
    
    }
  if (doorB>0){
    digitalWrite(ledB, HIGH);
  }else {
    digitalWrite(ledB, LOW);
    }
}


void read_weight() {
  weight = abs(sWeight.get_units()) * 1000;
  if (weight<360 && status_water_pump == 1){
    status_water_pump = 0;
    }

}

void read_spray_level() {
  digitalWrite(triggerUltraSonic, LOW);
  delayMicroseconds(2); 
  digitalWrite(triggerUltraSonic, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerUltraSonic, LOW);
  duration = pulseIn(echoUltraSonic, HIGH);
  distance = (duration * 0.034 / 2 ) * 10;

}


void tareW(){
  sWeight.begin(wgtData, wgtClock);
  sWeight.set_scale();
  sWeight.tare();
  sWeight.set_scale(calibration);
  zeroFactor = sWeight.read_average();
  
  }

// Obtener los valores a enviar a la API
String get_string_to_send() {
  return "peso=" + String(weight) + "&spray=" + String(distance);
}

// Esperar a que el modulo esp8266 realice todas sus operaciones
void wait_module() {
  // Esperar a que el modulo devuelva un mensaje de "continuar"
  char test;
  Serial.println(F(">> Esperando modulo esp8266..."));
  while (1) {
    delay(100);
    if (Serial3.available() > 0) {
      test = Serial3.read();
      Serial.print(test);
      if (test == '#') {
        break;
      }
    }
  }
  
  Serial.println(F("\n>> Espera finalizada"));
}

void send_serial(){
   Serial.println(F("\n******"));
  Serial.println(F(">> Enviando informacion de los sensores a la API"));

  // Obtener el string que se enviara a la API
  string_to_send = get_string_to_send();

  Serial.print(F(">> Valor a enviar: "));
  Serial.println(string_to_send);

  // Enviar inicio de API
  Serial.println(F(">> Enviando 'arduino'..."));
  Serial3.println(F("arduino"));
  
  wait_module();

  // Enviar valor a escribir en la API
  Serial.println(F(">> Enviando valor a la API..."));
  Serial3.println(string_to_send);
  Serial.println(string_to_send);
  
  Serial.println(F(">> Envio finalizado."));
  }

void loop() {
  actualMillis = millis();

  //se actualizan los valores de los sensores a cada 150 ms
  if(  actualMillis - begin_millisS > interval_sensors){    
    read_spray_level();
    read_weight();
    read_prox_sensors();
    begin_millisS = millis();
    Serial.println(weight);
  }

  // si el las puertas estan cerradas y hay un peso mayor a 360g se activa el spray
  if (weight> 360 && doorA == true && doorB == true && status_water_pump  == 0){
     begin_water_pump = millis()+ interval_wPump;
   }
   
   /// ejecuta el inicio de la bomba si esta activa

   if ( begin_water_pump >= actualMillis ) {
      if(digitalRead(wPump) == LOW){
        digitalWrite(wPump,HIGH);
        digitalWrite(ledC, HIGH);
         status_water_pump = 1; 
      }
    }else {
      //apaga la bomba al finalizar el intervalo de tiempo
      if(digitalRead(wPump) == HIGH){
        digitalWrite(wPump,LOW);
        digitalWrite(ledC, LOW);
        begin_water_pump = 0;
       
      }
    }  

      
  //se llama la conexión al módulo cada 15 segundos
  if (actualMillis - begin_millisC > 15000 ){
    send_serial();    
    begin_millisC = millis();
  }

}
