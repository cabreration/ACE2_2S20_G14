#include <Wire.h>



//variables para la transmision de datos;
int travel_array[4] = {
  0,0,0,0
};
int delivery_array[2] = {0,0};
int ping_server = 500; 
int state_from_server = 0; // 0 inactivo //1 activo

// funcion que envia la localizacion actual por i2c
void sendTravel() {
  Wire.beginTransmission(I2CAddressESP);
  Wire.write(0); //travel = 0;
  Wire.endTransmission();
  delayMicroseconds(50);
  Wire.beginTransmission(I2CAddressESP);
  for (int i = 0; i < 4; i++) {
    Wire.write(travel_array[i]);
  }

  Wire.endTransmission();
}

// funcion que envia el array con el peso y estado del auto
void sendShipping() {
  Wire.beginTransmission(I2CAddressESP);
  Wire.write(1); //shipping = 1;
  Wire.endTransmission();
  delayMicroseconds(50);
  Wire.beginTransmission(I2CAddressESP);
  for (int i = 0; i < 2; i++) {
    Wire.write(delivery_array[i]);
  }
  Wire.endTransmission();
}

// funcion que indica al servidor un estado de reinicio
void sendReset() {
  Wire.beginTransmission(I2CAddressESP); 
  Wire.write(2); 
  Wire.endTransmission();
  delayMicroseconds(50);
  Wire.beginTransmission(I2CAddressESP); 
  Wire.write(0);
  Wire.write(1);
  Wire.endTransmission();

}
// funcion que pide el estatus del server y el ping
// primeros 2 bytes = ping
// suguientes 2 bytes = status del server
void updateState () {
  Wire.requestFrom(I2CAddressESP, 4);
  delayMicroseconds(10);
  if (Wire.available())
  {
    ping_server = Wire.read();
    ping_server << 8; 
    ping_server |= Wire.read();
    state_from_server = Wire.read();
    state_from_server << 8; 
    state_from_server != Wire.read(); 
  }
}
