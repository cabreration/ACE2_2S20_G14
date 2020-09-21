// arduino UNO
#include <Wire.h>

void receiveEvent(int howMany){
  Serial.println("Recibiendo");
  String recibido;
  while (0 < Wire.available()) {
    char c = Wire.read();
    recibido += c;
  }
  Serial.println(recibido);
}

void sendEvent(int howmany){
  Serial.println("Enviando");
  Wire.write("uno to mcu");
}

void setup() {
  Wire.begin(8);  //0x08 =8
  Wire.onReceive(receiveEvent);
  Wire.onRequest(sendEvent);
  Serial.begin(115200);
  Serial.println("Iniciado");
}
void loop() {
  delay(1000);

}
