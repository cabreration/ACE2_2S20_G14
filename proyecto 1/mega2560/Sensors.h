#include "Pins.h"

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
int distance_back = 0;

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

void read_distance_back() {
  digitalWrite(triggerUltraSonicBack, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerUltraSonicBack, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerUltraSonicBack, LOW);
  duration = pulseIn(echoUltraSonicBack, HIGH);
  distance_back = (duration * 0.034 / 2 ) * 10;


}

void tareW() {
  sWeight.begin(wgtData, wgtClock);
  sWeight.set_scale();
  sWeight.tare();
  sWeight.set_scale(calibration);
  zeroFactor = sWeight.read_average();
}
