
#include "Connection.h"
#include "Sensors.h"
#include <AFMotor.h>

#define fwd_speed 170

#define max_speed 190

//variables para el uso de motores
AF_DCMotor motor_L1(1, MOTOR12_8KHZ); //motor IZQUIERDA FRONTAL
AF_DCMotor motor_R1(4, MOTOR34_8KHZ); //motor DERECHA FRONTAL
AF_DCMotor motor_L2(2, MOTOR12_8KHZ); //motor IZQUIERDO TRASERO
AF_DCMotor motor_R2(3, MOTOR34_8KHZ); //motor DERECHA TRASERA

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

#define MAX_ELLAPSED 200 //milliseconds
#define MAX_RIGHT 3
#define MAX_LEFT 3

void stop_motors() {
  motor_R1.run(RELEASE);
  motor_R2.run(RELEASE);
  motor_L1.run(RELEASE);
  motor_L2.run(RELEASE);
}

void forward() {
  motor_R1.setSpeed(fwd_speed);
  motor_R2.setSpeed(fwd_speed);
  motor_L1.setSpeed(fwd_speed);
  motor_L2.setSpeed(fwd_speed);

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
    delay(2);
  }
  forward();
  stop_motors();
}

//verifica si hay algún obstaculo
is_front_free() {
  read_distance_front();
  if (distance_front < 130 ) {
    stop_motors();

    Serial.println("Hay un objeto en frente");
#if DEBUG
    travel_array[1] = 3;
#endif
    while (distance_front < 130 ) {
      read_distance_front();
      delay(10);
    }

    Serial.println("Objeto removido.");
    forward();
#if DEBUG
    travel_array[1] = 1;
#endif

    delay(500);
  }
}

long ellapsedDistanceSync = 0;

boolean axis = false; // false = Y, true = X

// funcion que dirige para ir al punto de entrega
void follow_line(signed int d, signed int incVal) {

}
