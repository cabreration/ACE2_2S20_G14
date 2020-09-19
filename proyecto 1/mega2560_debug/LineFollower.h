
#include "Connection.h"
#include "Sensors.h"
#include <AFMotor.h>



#define max_speed 150
#define medium_speed 75
#define min_speed 50

//variables para el seguidor de linea:
#define line false // linea blanca = true linea negra = false

//variables para el uso de motores
AF_DCMotor motor_R1(1, MOTOR12_1KHZ); //motor derecho frontal
AF_DCMotor motor_R2(4, MOTOR12_1KHZ); //motor derecho trasero
AF_DCMotor motor_L1(2, MOTOR12_1KHZ); //motor izquierdo frontal
AF_DCMotor motor_L2(3, MOTOR12_1KHZ); //motor izquierdo trasero


//verifica si hay algún obstaculo
is_front_free(){
  int actualMillis = millis();
  read_distance_front();
    if (distance_front < 5 ){
      #if DEBUG
       travel_array[1] = 3;
  //    sendTravel();
      #endif
        while(distance_front < 50 ){
          #if DEBUG
        
           #endif
          read_distance_front();
        }
        #if DEBUG
        travel_array[1] = 1;
 //       sendTravel();
        #endif 
    }
}






void stop_motors() {
  motor_R1.run(RELEASE); 
  motor_R2.run(RELEASE);
  motor_L1.run(RELEASE);
  motor_L2.run(RELEASE); 
  }


// funcion que dirige para ir al punto de entrega
void shipping() {

  motor_R1.setSpeed(max_speed);
  motor_R2.setSpeed(max_speed);
  motor_L1.setSpeed(max_speed);
  motor_L2.setSpeed(max_speed);

#if DEBUG 
  // se indica que se encuentra en el recorido
  travel_array[0] = 1; 
  // se indica el estado= en camino a enttravel1] = 1;
  travel_array[1] = 1;
  // se manda el nuevo status
//  sendTravel();
#endif
  //mientras que S1 y S5 no sean igual a linea entonces que se reptia el ciclo
  //se puede usar el sensor de baches tambien
  while (digitalRead(sensorLeft) != line ||
         digitalRead(sensorRight) != line)
  {     
    //si el sensor  derecho detecta linea 
    //se gira para la derecha
    if (digitalRead(sensorRight) == line ) {
      motor_R1.run(BACKWARD); 
      motor_R2.run(BACKWARD);
      motor_R1.setSpeed(min_speed);
      motor_R2.setSpeed(min_speed);
      while(sensorRight == line) {}
      motor_R1.run(FORWARD); 
      motor_R2.run(FORWARD);
      motor_R2.setSpeed(max_speed);
      motor_R2.setSpeed(max_speed);
    }

    //si el sensor interno izquierdo detecta linea
    if (digitalRead(sensorRight) == line  ) {
      motor_L1.run(BACKWARD); 
      motor_L2.run(BACKWARD);
      motor_L1.setSpeed(min_speed);
      motor_L2.setSpeed(min_speed);
      while(sensorRight == line) {}
      motor_L1.run(FORWARD); 
      motor_L2.run(FORWARD);
      motor_L2.setSpeed(max_speed);
      motor_L2.setSpeed(max_speed);
    }

   
    // se comprueba que no hayan obstaculos;
    is_front_free();
    #if DEBUG
    // se actualiza el estatus actual de todo
    if ( millis() - actual_millis_SP > ping_server*3 ){
      actual_millis_SP = millis();
    //  sendTravel();
    //  updateState();
    }
  #endif
  } 
}
// funcion para regresar al punto de origen
void comeback() {
  motor_R1.run(FORWARD); 
  motor_R2.run(FORWARD);
  motor_L1.run(FORWARD); 
  motor_L2.run(FORWARD);
  motor_R1.setSpeed(max_speed);
  motor_R2.setSpeed(max_speed);
  motor_L1.setSpeed(max_speed);
  motor_L2.setSpeed(max_speed);

  #if DEBUG
  // se indica que se encuentra en el recorido
  travel_array[0] = 1; 
  // se indica el estado= en camino a enttravel1] = 1;
  travel_array[1] = 2;
  // se manda el nuevo status
//  sendTravel();
  #endif

  //mientras que S1 y S5 no sean igual a linea entonces que se reptia el ciclo
  //se puede usar el sensor de baches tambien
  while (digitalRead(sensorLeft) != line ||
         digitalRead(sensorRight) != line)
  { 
    //si el sensor  derecho detecta linea 
    //se gira para la derecha
    if (digitalRead(sensorRight) == line ) {
      motor_R1.run(BACKWARD); 
      motor_R2.run(BACKWARD);
      motor_R1.setSpeed(min_speed);
      motor_R2.setSpeed(min_speed);
      while(sensorRight == line) {}
      motor_R1.run(FORWARD); 
      motor_R2.run(FORWARD);
      motor_R2.setSpeed(max_speed);
      motor_R2.setSpeed(max_speed);
    }

    //si el sensor interno izquierdo detecta linea
    if (digitalRead(sensorLeft) == line  ) {
      motor_L1.run(BACKWARD); 
      motor_L2.run(BACKWARD);
      motor_L1.setSpeed(min_speed);
      motor_L2.setSpeed(min_speed);
      while(sensorRight == line) {}
      motor_L1.run(FORWARD); 
      motor_L2.run(FORWARD);
      motor_L2.setSpeed(max_speed);
      motor_L2.setSpeed(max_speed);
    }

    
    // se comprueba que no hayan obstaculos;
    is_front_free();
    #if DEBUG


    #endif
  }

}
