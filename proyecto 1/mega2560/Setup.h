#include "Pins.h"


void setup_arduino () {
  //Inicializacion de pines del sensor HS-20 frontal
  pinMode(echoUltraSonicFront,INPUT);
  pinMode(triggerUltraSonicFront, OUTPUT);

  //Inicializacion de pines del sensor HS-20 frontal
  pinMode(echoUltraSonicBack,INPUT);
  pinMode(triggerUltraSonicBack, OUTPUT);

  //Inicializacion de pines del seguidor de linea
  pinMode(lineFollower_S1_RO, INPUT); 
  pinMode(lineFollower_S2_RI, INPUT); 
  pinMode(lineFollower_S3_C,INPUT);
  pinMode(lineFollower_S4_LI, INPUT);
  pinMode(lineFollower_S5_LO, INPUT); 
  pinMode(lineFollower_Bump, INPUT); 
  pinMode(lineFollower_Near, INPUT);  

  //Inicializacion de pines para el led de estado
  pinMode(led_line, OUTPUT);
  
}


