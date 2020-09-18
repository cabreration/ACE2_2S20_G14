#include "Pinns.h"
#include <HX711.h>
#define min_distance 5 //a los 5 cm se detiene el carro

//variables para la lectura de peso:
HX711 sWeight;
float calibration = 20280.0; //factor de calibración para el sensor
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
  // put your main code here, to run repeatedly:
  read_weight();
  Serial.println("peso leido" + String(weight));
  read_distance_front();
  Serial.println("distancia leida: " + String(distance_front));
  Serial.println("S1: "+ String(digitalRead(lineFollower_S1_RO)));
  Serial.println("S2: "+ String(digitalRead(lineFollower_S2_RI))); 
  Serial.println("S3: "+ String(digitalRead(lineFollower_S3_C))) ;
  Serial.println("S4: "+ String(digitalRead(lineFollower_S4_LI)));
  Serial.println("S5: "+ String(digitalRead(lineFollower_S5_LO)));
  
}
