
// nodeMCU
#include <Wire.h>
String recibido;

void setup(){
  Wire.begin(4, 5);
  Serial.begin(115200);
}

void loop(){
  Wire.beginTransmission(8);//0x08 = 8;
  Wire.write("mcu to uno \n");
  Wire.endTransmission();

  Wire.requestFrom(8, 10);//0x08 = 8;

  String recibido;
  while (0 < Wire.available()){
    char c = Wire.read();
    recibido += c;
  }
  Serial.println(recibido);
  delay(3000);
}
