//libreria X711 Arduino Library
#include "Setup.h"
#include <HX711.h>
#include "LineFollower.h"

long actualMillis = 0;
long begin_millis = 0;

//int ping_serve = 0;

//variables para la comunicacion I2C-ESP8266
int actualPing = 1000;

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
  // en la posicion 8
  Wire.begin(8);
#if DEBUG

  Wire.onRecive(receiveEvent);
  Wire.onRequest(sendEvent);

  // calibración del sensor de linea
  calibrate_lineFollower();
  //se solicita el estado y el ping del servidor

#endif

  Serial.begin(115200);
  ////Serial.println("Hola...");
}


void loop() {
  read_weight();

  Serial.println(weight);

#if DEBUG
  actualMillis = millis();
  /// a cada 3 veces el ping se pide un status

#endif

  // si no hay conexion con el servidor no de puede hacer nada
  // o si no se ha activado el carrito desde el server
  // tampoco se hará nada

#if DEBUG
  if (state_from_server == 1) {
#endif
    if (weight > weight_umbral )
    {
      Serial.println("Objeto depositado, iniciando recorrido");
#if DEBUG
      travel_array[0] = 1; // ubicacion=1
      travel_array[1] = 1; // estado= 1
      travel_array[2] = 0; // aungulo = 0;
      travel_array[3] = 0; // diatancia = 0;

      // updateState();

      delivery_array[0] = weight; //peso = weight
      delivery_array[1] = 0; // estado = 0 //iniciando entrega
      /// sendShipping();
#endif

#if DEBUG
      // se indica que se encuentra en el recorido
      travel_array[0] = 1;
      // se indica el estado= en camino a enttravel1] = 1;
      travel_array[1] = 1;
      // se manda el nuevo status
      //  sendTravel();
#endif

      follow_line();

#if DEBUG
      travel_array[0] = 2; //ubicacion = 2 punto de entrega
      travel_array[1] = 0;  // estado = 0 en reposo
      //  sendTravel();
      delivery_array[1] = 1; //estado 1 //entregando el objeto
      //   sendShipping();
#endif
      Serial.println("Producto entregado, agarrarlo");
      //el carro esperara que se quite el objeto de encima
      while (weight > weight_umbral)  {
        read_weight();
        Serial.println(weight);
        delay(100);
      }
      Serial.println("Regresando a buzon...");

#if DEBUG
      // se indica que se encuentra en el recorido
      travel_array[0] = 1;
      // se indica el estado= en camino a enttravel1] = 1;
      travel_array[1] = 2;
      // se manda el nuevo status
      //  sendTravel();
#endif

      follow_line();

      /*
        #if DEBUG
            travel_array[0] = 1; //ubicacion en el putno de entrega
            travel_array[1] = 2; // estado en camino al buzon
         //   sendTravel();
            delivery_array[0] = 0; // peso en gramos
            delivery_array[1] = 2; // estado = 2 regresando al buzon
         //   sendShipping();
        #endif
            comeback();
        #if DEBUG
            travel_array[0] = 0;
            travel_array[1] = 0;
            travel_array[2] = 0;
            travel_array[3] = 0;
        ///  sendTravel();
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
      */
    }

#if DEBUG
  }
#endif

}
