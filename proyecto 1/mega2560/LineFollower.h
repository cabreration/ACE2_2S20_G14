
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
       travel_array[1] = 3;
      sendTravel();
        while(distance_front < 5 ){
          if( millis() -  actualMillis > ping_server*5) {
            actualMillis = millis();
            sendTravel();
          }
          read_distance_front();
        }
        travel_array[1] = 1;
        sendTravel(); 
    }
}

is_back_free(){
  int actualMillis = millis();
  read_distance_back();
    if (distance_back < 5 ){     
      travel_array[1] = 3;
      sendTravel(); 
        while(distance_back < 5 ){
          if( millis() -  actualMillis > ping_server*5) {
            actualMillis = millis();
            sendTravel();
          }
          read_distance_back();
        }
        travel_array[1] = 2;
        sendTravel(); 
    }
}





void stop_motors() {
  motor_R1.run(RELEASE); 
  motor_R2.run(RELEASE);
  motor_L1.run(RELEASE);
  motor_L2.run(RELEASE); 
  }


void go_left_reverse() {
  motor_R1.setSpeed(medium_speed);
  motor_R2.setSpeed(medium_speed);
  motor_L1.setSpeed(medium_speed);
  motor_L2.setSpeed(medium_speed);

  while (digitalRead(lineFollower_S2_RI) != line) {}

  motor_R1.run(FORWARD);
  motor_R2.run(FORWARD); 
  
  while(digitalRead(lineFollower_S2_RI) == line) {}

  motor_R1.run(BACKWARD);
  motor_R2.run(BACKWARD); 

  motor_R1.setSpeed(max_speed);
  motor_R2.setSpeed(max_speed);
  motor_L1.setSpeed(max_speed);
  motor_L2.setSpeed(max_speed);

}

void go_right_reverse() {
  motor_R1.setSpeed(medium_speed);
  motor_R2.setSpeed(medium_speed);
  motor_L1.setSpeed(medium_speed);
  motor_L2.setSpeed(medium_speed);

  while(digitalRead(lineFollower_S4_LI) != line) {}

  motor_L1.run(FORWARD);
  motor_L2.run(FORWARD); 

  while(digitalRead(lineFollower_S4_LI) != line) {}

  motor_L1.run(BACKWARD);
  motor_L2.run(BACKWARD); 

  motor_R1.setSpeed(max_speed);
  motor_R2.setSpeed(max_speed);
  motor_L1.setSpeed(max_speed);
  motor_L2.setSpeed(max_speed);

}




void go_left() {
  motor_R1.setSpeed(medium_speed);
  motor_R2.setSpeed(medium_speed);
  motor_L1.setSpeed(medium_speed);
  motor_L2.setSpeed(medium_speed);

  while (digitalRead(lineFollower_S4_LI) != line) {    
  }
  motor_L1.run(BACKWARD);
  motor_L2.run(BACKWARD);
  while (digitalRead(lineFollower_S4_LI) == line)  {}
  
  motor_L1.run(FORWARD);
  motor_L2.run(FORWARD);

  motor_R1.setSpeed(max_speed);
  motor_R2.setSpeed(max_speed);
  motor_L1.setSpeed(max_speed);
  motor_L2.setSpeed(max_speed);

}

void go_right() {
    
  motor_R1.setSpeed(medium_speed);
  motor_R2.setSpeed(medium_speed);
  motor_L1.setSpeed(medium_speed);
  motor_L2.setSpeed(medium_speed);

  while (digitalRead (lineFollower_S2_RI) != line ) {    
    }
  motor_R1.run(BACKWARD); 
  motor_R2.run(BACKWARD);

  while (digitalRead(lineFollower_S2_RI) == line  ) {}
  motor_R1.run(BACKWARD); 
  motor_R2.run(BACKWARD);

}

// funcion que dirige para ir al punto de entrega
void shipping() {
  bool fit_left = false;
  bool fit_right = false;
  motor_R1.setSpeed(max_speed);
  motor_R2.setSpeed(max_speed);
  motor_L1.setSpeed(max_speed);
  motor_L2.setSpeed(max_speed);
  long actual_millis_SP = millis();

  // se indica que se encuentra en el recorido
  travel_array[0] = 1; 
  // se indica el estado= en camino a enttravel1] = 1;
  travel_array[1] = 1;
  // se manda el nuevo status
  sendTravel();

  //mientras que S1 y S5 no sean igual a linea entonces que se reptia el ciclo
  //se puede usar el sensor de baches tambien
  while (digitalRead(lineFollower_S1_RO) != line ||
         digitalRead(lineFollower_S5_LO) != line)
  { 
    //si el extremo izquierdo del sensor detecta linea entonces 
    if(digitalRead(lineFollower_S5_LO) == line )  {
      // se dara tiempo para comprobar si es un fin de camino
      delay(100);
      //si es fin de camino se acaba el trayecto
      if(digitalRead(lineFollower_S1_RO) == line) {
        stop_motors();
        continue;
      }
      ///sino entonces hay que girar a la izquierda
      go_left();
      fit_left = false; 
      fit_right = false;
    }

    //si el extermo derecho del sensor detecta linea entonces
    if(digitalRead(lineFollower_S1_RO) == line) {
      delay(100);  
      //si el otro extremo no deteca linea entonces es un giro
      if(digitalRead(lineFollower_S5_LO) == line) {
        stop_motors(); 
        continue;         
      } 
      go_right();
      fit_left = false; 
      fit_right = false;
    }
    
    
    //si el sensor interno derecho detecta linea 
    if (digitalRead(lineFollower_S2_RI) == line) {
      motor_R1.setSpeed(min_speed);
      motor_R2.setSpeed(min_speed);
      fit_right = true;
    }
    //si el sensor interno izquierdo detecta linea
    if (digitalRead(lineFollower_S4_LI) == line) {
      motor_L1.setSpeed(min_speed);
      motor_L2.setSpeed(min_speed);
      fit_left = true;
    }

    //si hay ajuste izquierdo en ejecución y el sensor central detecta linea y
    // el sensor izquierdo interno ya no deteca linea entonces se corrige la
    // dirección del carrito
    if ( fit_left == true && digitalRead(lineFollower_S3_C) == line && 
        digitalRead(lineFollower_S4_LI) != line )
      {
        motor_L1.setSpeed(max_speed);
        motor_L2.setSpeed(max_speed);
        fit_left = false;
      }    

    //si hay ajuste derecho en ejecución y el sensor central detecta linea y
    // el sensor izquierdo interno ya no deteca linea entonces se corrige la
    // dirección del carrito

    if ( fit_right == true && digitalRead(lineFollower_S3_C) == line   && 
        digitalRead(lineFollower_S2_RI) != line )
      {
        motor_R1.setSpeed(max_speed);
        motor_R2.setSpeed(max_speed);
        fit_right = false;
      }
    // se comprueba que no hayan obstaculos;
    is_front_free();

    // se actualiza el estatus actual de todo
    if ( millis() - actual_millis_SP > ping_server*5 ){
      actual_millis_SP = millis();
      sendTravel();
      updateState();
    }


  } 

}
// funcion para regresar al punto de origen
void comeback() {
  bool fit_left = false;
  bool fit_right = false;
  motor_R1.run(BACKWARD); 
  motor_R2.run(BACKWARD);
  motor_L1.run(BACKWARD); 
  motor_L2.run(BACKWARD);
  motor_R1.setSpeed(max_speed);
  motor_R2.setSpeed(max_speed);
  motor_L1.setSpeed(max_speed);
  motor_L2.setSpeed(max_speed);
  long actual_millis_CB  = millis();

  // se indica que se encuentra en el recorido
  travel_array[0] = 1; 
  // se indica el estado= en camino a enttravel1] = 1;
  travel_array[1] = 2;
  // se manda el nuevo status
  sendTravel();


  //mientras que S1 y S5 no sean igual a linea entonces que se reptia el ciclo
  //se puede usar el sensor de baches tambien
  while (digitalRead(lineFollower_S1_RO) != line ||
         digitalRead(lineFollower_S5_LO) != line)
  { 
    // si el sensor extremo izquierdo(derecho invertido) detecta linea entonces
    if (digitalRead(lineFollower_S1_RO) == line){
      delay(100);
    }
    // si es fin de camino se acaba el trayecto
    if(digitalRead(lineFollower_S5_LO)== line) {
      stop_motors();
      continue;
    }
    // sino entonces hay que girar a izquierda
    go_left_reverse();
    fit_left = false; 
    fit_left = false;

    // si el sensor extremo derecho (inverso) deteca linea entonces
    if (digitalRead(lineFollower_S5_LO) == line)
    {
      delay(100);
      //si el otro extremo no detecta linea entonces es un giro
      if (digitalRead(lineFollower_S1_RO) == line) {
        stop_motors();
        continue;
      }
      go_right_reverse();
      fit_left = false;
      fit_right = false; 
    }

    //si el sensor interno derecho (inverso) detecta linea
    if(digitalRead(lineFollower_S4_LI) == line)
    {
      motor_L1.setSpeed(min_speed);
      motor_L2.setSpeed(min_speed);
      fit_right = true;
    } 
    
    //si el sensor interno izquierdo (inverso) detecta linea
    if(digitalRead(lineFollower_S2_RI) == line)
    {
      motor_R1.setSpeed(min_speed);
      motor_R2.setSpeed(min_speed);
      fit_left = true;      
    }
    
    //si hay ajuste izquierdo (inverso) en ejecución y el sensor central detecta linea y
    // el sensor izquierdo (inverso) interno ya no deteca linea entonces se corrige la
    // dirección del carrito
    if (fit_left == true && digitalRead(lineFollower_S2_RI) != line &&
       digitalRead(lineFollower_S3_C) != line) 
      {
        motor_R1.setSpeed(max_speed);
        motor_R2.setSpeed(max_speed);
        fit_left = false; 
      }

    if(fit_right == true && digitalRead(lineFollower_S4_LI) != line &&
      digitalRead(lineFollower_S3_C) != line) 
    {
      motor_L1.setSpeed(max_speed);
      motor_L2.setSpeed(max_speed);
      fit_right = false; 
    }
    // se comprueba que no hayan obstaculos;
    is_back_free(); 
    
    // se actuaoliza el estatus 
     if ( millis() - actual_millis_CB > ping_server*5 ){
       actual_millis_CB = millis();
      sendTravel();
      updateState();
    }

  }

}
