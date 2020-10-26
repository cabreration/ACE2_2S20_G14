#include <Wire.h>

#define DEBUG 0
#if DEBUG

//variables para la transmision de datos;
int travel_array[4] = { 0, 0, 0, 0 };

int delivery_array[2] = {0, 0};

char  state_from_server = 0; // 0 inactivo //1 activo

void sendEvent(int count) { return; }

// funcion que pide el estatus del server y el ping
// primeros 2 bytes = ping
// suguientes 2 bytes = status del server
void receiveEvent (int count) {
  while (!Wire.available()) {}

  state_from_server = Wire.read();
}

#endif
