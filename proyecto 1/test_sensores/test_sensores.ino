#include "Pinns.h"
#include <HX711.h>
#define min_distance 5 //a los 5 cm se detiene el carro

//variables para la lectura de peso:
HX711 sWeight;
float calibration = 30000; //20280.0; //factor de calibración para el sensor
long zeroFactor = 0;
int weight = 0;
#define weight_umbral 150

//variables para el medidor de distancia
long duration = 0;
int distance_front = 0;

void read_weight() {
  weight = abs(sWeight.get_units()) * 1000;
}

void read_distance_front() {
  digitalWrite(triggerUltraSonicFront, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerUltraSonicFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerUltraSonicFront, LOW);
  duration = pulseIn(echoUltraSonicFront, HIGH);
  distance_front = (duration * 0.034 / 2 ) * 10;
}


void tareW() {
  sWeight.begin(wgtData, wgtClock);
  sWeight.set_scale();
  sWeight.tare();
  sWeight.set_scale(calibration);
  zeroFactor = sWeight.read_average();
}



void setup() {
  // put your setup code here, to run once:
  setup_arduino();
  Serial.begin(115200);
  tareW();
}

void loop() {
 
  read_distance_front();
  read_weight();
  Serial.println("*******************************");
  Serial.println("Peso: " + String(weight)); 
  Serial.println("Distancia: " + String(distance_front));
  Serial.println("Izquierda: " + String(digitalRead(A9)));
  Serial.println("Derecha: " + String(digitalRead(19)));

  delay(1000);
}
