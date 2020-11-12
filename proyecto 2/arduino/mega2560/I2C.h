#include <Wire.h>

unsigned int travel[2] = {0, 0};
boolean enabled = false; // 0 inactivo //1 activo
byte estado = 0;
byte test = 0;
// Enviar temperatura y tiempo
void sendEvent(int count) {
  Wire.write(estado);

  // temperatura
  Wire.write(highByte(travel[0]));
  Wire.write(lowByte(travel[0]));

  // tiempo
  Wire.write(highByte(travel[1]));
  Wire.write(lowByte(travel[1]));

  // si el estado es 3, asegurarse que se enviara una unica vez
  if (estado == 3) {
    estado = 2;
  }
}

// Recibir estado del sistema
void receiveEvent (int count) {
  while (!Wire.available()) { }
  enabled = Wire.read();
}
