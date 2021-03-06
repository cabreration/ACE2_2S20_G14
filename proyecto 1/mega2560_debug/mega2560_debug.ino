//libreria X711 Arduino Library
#include "Setup.h"
#include "LineFollower.h"

//variables para la comunicacion I2C-ESP8266
int actualPing = 1000;

void setup() {

  // se inicializan los pines
  setup_arduino();
  // se aplica un tarado a la pesa
  tareW();

  //se inicializa la comunicacion I2C
  // en la posicion 8
  
#if DEBUG
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(sendEvent);

  //se solicita el estado y el ping del servidor
#endif

  Serial.begin(115200);
  Serial.println(">> Carrito iniciado :3");
}

void loop() {

  
  //read_distance_front();
  //Serial.println(distance_front);
  return;
  /*
  //test();
  //delay(1000);
  //return;
  
  // si no hay conexion con el servidor no de puede hacer nada
  // o si no se ha activado el carrito desde el server
  // tampoco se hará nada

#if DEBUG
  if (state_from_server == 1) {
    Serial.println("Carrito listo.");
#endif
    read_weight();
    Serial.println("W: " + String(weight));
    delay(50);

    if (weight > weight_umbral )
    {
      Serial.println("Objeto depositado");
      
#if DEBUG
      travel_array[0] = 1; // ubicacion = 1
      travel_array[1] = 1; // estado = 1
      travel_array[2] = 0; // angulo = 0;
      travel_array[3] = 0; // distancia = 0;

      delivery_array[0] = weight; //peso = weight
      delivery_array[1] = 0; // estado = 0 //iniciando entrega

      delay(1600);
#endif

      Serial.println("Iniciando recorrido");

      follow_line(0, 5);

#if DEBUG
      travel_array[0] = 2; // ubicacion = 2 punto de entrega
      travel_array[1] = 0;  // estado = 0 en reposo
      delivery_array[1] = 1; //estado 1 //entregando el objeto
      
      delay(1600);
#endif
      Serial.println("Producto entregado, agarrarlo");
      
      //el carro esperara que se quite el objeto de encima
      while (weight > weight_umbral)  {
        read_weight();
        Serial.println(weight);
        delay(5);
      }
      
      Serial.println("Regresando a buzon...");

#if DEBUG
      // se indica que se encuentra en el recorido
      travel_array[0] = 1;
      // se indica el estado= en camino a enttravel1] = 1;
      travel_array[1] = 2;
      // peso en gramos
      delivery_array[0] = 0;
      // se indica el estado= en el camino al buzon
      delivery_array[1] = 2;
      
      delay(1600);
#endif

      follow_line(150, -5);

#if DEBUG
      travel_array[0] = 0;
      travel_array[1] = 0;
      travel_array[2] = 0;
      travel_array[3] = 0;
      
      delay(2000);
#endif

    Serial.println("Listo para esperar de nuevo...");
    }
    
#if DEBUG
  }
  else {
    delay(500);
    Serial.println("Esperando Status = 1...");
  }
#endif
  */
}
