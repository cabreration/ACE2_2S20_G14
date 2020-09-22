#include <Wire.h>

#define DEBUG 0
#if DEBUG

//variables para la transmision de datos;
int travel_array[4] = { 0, 0, 0, 0 };

int delivery_array[2] = {0, 0};

char  state_from_server = 0; // 0 inactivo //1 activo

void sendEvent(int count) {
  // se envian el travel_array
  //Serial.println("Enviando datos");
  Wire.write(highByte(travel_array[0]));
  Wire.write(lowByte(travel_array[0]));
  Wire.write(highByte(travel_array[1]));
  Wire.write(lowByte(travel_array[1]));
  Wire.write(highByte(travel_array[2]));
  Wire.write(lowByte(travel_array[2]));
  Wire.write(highByte(travel_array[3]));
  Wire.write(lowByte(travel_array[3]));
  
  //se envia el delivery_array
  Wire.write(highByte(delivery_array[0]));
  Wire.write(lowByte(delivery_array[0]));
  Wire.write(highByte(delivery_array[0]));
  Wire.write(lowByte(delivery_array[1]));
}

// funcion que pide el estatus del server y el ping
// primeros 2 bytes = ping
// suguientes 2 bytes = status del server
void receiveEvent (int count) {
  Serial.println("Recibiendo");
  while (!Wire.available()) {}

  Serial.println("Recibido");
  state_from_server = Wire.read();
}
#endif
