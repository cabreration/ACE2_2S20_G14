#include "Pins.h"


void setup_arduino () {
  //Inicializacion de pines del sensor HS-20 frontal
  pinMode(echoUltraSonicFront,INPUT);
  pinMode(triggerUltraSonicFront, OUTPUT);

  pinMode(sensorLeft,INPUT);
  pinMode(sensorRight, INPUT); 

  //Inicializacion de pines para el led de estado
  pinMode(led_line, OUTPUT);  
}
