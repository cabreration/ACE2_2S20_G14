//libreria X711 Arduino Library
#include "Setup.h"
#include <HX711.h>
#include "LineFollower.h"


long actualMillis = 0;
long begin_millis = 0;
//int ping_serve = 0;


//variables para la comunicacion I2C-ESP8266
int actualPing = 0;

#if DEBUG
void calibrate_lineFollower() {
  // se requiere que el sensor central este sobre la linea
  while (digitalRead(lineFollower_S3_C) != line) {
    digitalWrite(led_line, lineFollower_S3_C == line);
  }

}
#endif


void setup() {
  /*
    // se esperan 2 segundo para dar tiempo a que se inicie el ESP8266
    delay(2000);
    /*
     inicialización de serials y sensores
  */
  // se inicializan los pines
  setup_arduino();
  // se aplica un tarado a la pesa
  tareW();

  //se inicializa la comunicacion I2C
  Wire.begin();

#if DEBUG
  // calibración del sensor de linea
  calibrate_lineFollower();
  //se solicita el estado y el ping del servidor
  updateState();

  while (state_from_server != 1) {
    updateState();
    if ( ping != -1) {
      //se verifica el estado del servidor a cada 1.5 segundos
      delay(1500);
    }
  }
#endif
}









void loop() {

  
#if DEBUG
  actualMillis = millis();
  /// a cada 3 veces el ping se pide un status
  if (  actualMillis - begin_millis > (ping_server * 3)) {
    begin_millis = actualMillis;
    updateState();
  }
#endif 
  read_weight();
  // si no hay conexion con el servidor no de puede hacer nada
  // o si no se ha activado el carrito desde el server
  // tampoco se hará nada

  #if DEBUG
   if (ping_server == -1  || state_from_server == 0) {
    // se paran los motores :(

  } else { 
    // si se supera el umbral de peso entonces se inicia el recorrido
#endif*/
    if (weight > weight_umbral)
    {
#if DEBUG
      travel_array[0] = 1; //ubicacion=1
      travel_array[1] = 1; //estado= 1
      travel_array[2] = 0; // aungulo = 0;
      travel_array[3] = 0; // diatancia = 0;

      updateState();

      delivery_array[0] = weight; //peso = weight
      delivery_array[1] = 0; // estado = 0 //iniciando entrega
        sendShipping();

#endif
    
      shipping();
#if DEBUG
      travel_array[0] = 2; //ubicacion = 2 punto de entrega
      travel_array[1] = 0;  // estado = 0 en reposo
      sendTravel();
      delivery_array[1] = 1; //estado 1 //entregando el objeto
      sendShipping();
#endif
      
      //el carro esperara que se quite el objeto de encima
      while (weight > weight_umbral)  {
        read_weight();
      }

      motor_R1.run(BACKWARD);
      motor_R2.run(BACKWARD);

      motor_R1.setSpeed(medium_speed);
      motor_R2.setSpeed(medium_speed);
      motor_L1.setSpeed(medium_speed);
      motor_L2.setSpeed(medium_speed);

      while (digitalRead(sensorRight) != line ) {}
      while (digitalRead(sensorRight) == line) {}

      delay(100);
      stop_motors();
      motor_R1.run(FORWARD);
      motor_R2.run(FORWARD);
#if DEBUG
      travel_array[0] = 1; //ubicacion en el putno de entrega
      travel_array[1] = 2; // estado en camino al buzon
      sendTravel();
      delivery_array[0] = 0; // peso en gramos
      delivery_array[1] = 2; // estado = 2 regresando al buzon
      sendShipping();
#endif
      comeback();
#if DEBUG
      travel_array[0] = 0;
      travel_array[1] = 0;
      travel_array[2] = 0;
      travel_array[3] = 0;
      sendTravel();
#endif
      motor_R1.run(BACKWARD);
      motor_R2.run(BACKWARD);

      motor_R1.setSpeed(medium_speed);
      motor_R2.setSpeed(medium_speed);
      motor_L1.setSpeed(medium_speed);
      motor_L2.setSpeed(medium_speed);

      while (digitalRead(sensorRight) != line ) {}
      while (digitalRead(sensorRight) == line) {}

      delay(100);
      stop_motors();
      motor_R1.run(FORWARD);
      motor_R2.run(FORWARD);

    }
#if DEBUG
/*  } */
#endif
}
