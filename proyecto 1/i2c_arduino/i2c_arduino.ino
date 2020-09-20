// arduino UNO
#include <Wire.h>

void setup() {
  Wire.begin(8);  //0x08 =8
  Wire.onReceive(receiveEvent);
  Wire.onRequest(sendEvent);
  Serial.begin(115200);
}
void loop() {
  delay(1000);

}

void receiveEvent(int howMany){
  String recibido;
  while (0 < Wire.available()) {
    char c = Wire.read();
    recibido += c;
  }
  Serial.println(recibido);
}

void sendEvent(int howmany){
  Wire.write("uno to mcu");
}
