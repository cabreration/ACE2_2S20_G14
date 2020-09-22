
#include "Connection.h"
#include "Sensors.h"
#include <AFMotor.h>

#define max_speed 255

//variables para el uso de motores

AF_DCMotor motor_L1(1, MOTOR12_64KHZ); //motor IZQUIERDA FRONTAL
AF_DCMotor motor_R1(4, MOTOR34_64KHZ); //motor DERECHA FRONTAL
AF_DCMotor motor_L2(2, MOTOR12_64KHZ); //motor IZQUIERDO TRASERO
AF_DCMotor motor_R2(3, MOTOR34_64KHZ); //motor DERECHA TRASERA

// #1 -> FRONTAL
// #2 -> TRASERO
//motor 4 es adelante derecha
//motor 3 es atras derecha
//motor 2 es atras izquierda
//motor 1 es adelante izquierda

#define R1F FORWARD
#define R2F FORWARD
#define L1F FORWARD
#define L2F BACKWARD

#define R1B BACKWARD
#define R2B BACKWARD
#define L1B BACKWARD
#define L2B FORWARD

void stop_motors() {
  motor_R1.run(RELEASE);
  motor_R2.run(RELEASE);
  motor_L1.run(RELEASE);
  motor_L2.run(RELEASE);
}

void forward() {
  motor_R1.setSpeed(max_speed);
  motor_R2.setSpeed(max_speed);
  motor_L1.setSpeed(max_speed);
  motor_L2.setSpeed(max_speed);

  motor_R1.run(R1F);
  motor_R2.run(R2F);
  motor_L1.run(L1F);
  motor_L2.run(L2F);
}

void go_right() {
  Serial.println("Moviendo hacia derecha");
  stop_motors();
  delay(100);

  motor_R1.run(R1B);
  motor_R2.run(R2B);
  motor_L1.run(L1F);
  motor_L2.run(L2F);
}

void go_left() {
  Serial.println("Moviendo hacia izquierda");
  stop_motors();
  delay(100);

  motor_R1.run(R1F);
  motor_R2.run(R2F);
  motor_L1.run(L1B);
  motor_L2.run(L2B);
}

void rotate_to_line() {
  Serial.println("Buscando linea negra...");
  go_right();
  while (!(digitalRead(sensorRight) && digitalRead(sensorLeft))) {
    Serial.println("L: " + String(digitalRead(sensorLeft)));
    Serial.println("R: " + String(digitalRead(sensorRight)));
    delay(2);
  }
  forward();
  stop_motors();
}

//verifica si hay algún obstaculo
is_front_free() {
  read_distance_front();
  if (distance_front < 70 ) {
    stop_motors();
    Serial.println("Hay un objeto en frente...");
#if DEBUG
    travel_array[1] = 3;
#endif

    while (distance_front < 70 ) {
      read_distance_front();

      Serial.println("D: " + String(distance_front));
      delay(10);
    }
    
    Serial.println("Objeto removido.");
    forward();
    
#if DEBUG
    travel_array[1] = 1;
#endif
  }
}

// funcion que dirige para ir al punto de entrega
void follow_line() {

  if (digitalRead(sensorLeft) || digitalRead(sensorRight)) {
    forward();

    Serial.println("Iniciando movimiento...");
  }
  else {
    Serial.println("Por favor ponga el carrito en su lugar");
    rotate_to_line();
  }

  while (digitalRead(sensorLeft) || digitalRead(sensorRight))
  {
    //si el sensor  derecho detecta linea
    //se gira para la derecha
    if (digitalRead(sensorRight) && !digitalRead(sensorLeft) ) {
      go_right();

      //Serial.println("Volteando a la derecha");
      while (!digitalRead(sensorLeft)) {
        delay(10);
        /**/
        if (!digitalRead(sensorLeft) && !digitalRead(sensorRight)){
          break;
        }
      }
      forward();
    }

    //si el sensor interno izquierdo detecta linea
    else if (digitalRead(sensorLeft) && !digitalRead(sensorRight)) {
      go_left();

      //Serial.println("Volteando a la izquierda");
      while (!digitalRead(sensorRight)) {
        delay(10);
        /**/
        
        if (!digitalRead(sensorLeft) && !digitalRead(sensorRight)){
          break;
        }
      }

      forward();
    }
    else {
      is_front_free();
    }
  }

  rotate_to_line();
  stop_motors();
}
