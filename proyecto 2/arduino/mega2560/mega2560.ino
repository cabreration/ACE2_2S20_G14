
//direcciones I2C
#define I2CAddressESP 8

#include "I2C.h"
#include "Temperature.h"
#include "Buzzer.h"
#include "TScreen.h"
#include "SecuritySystem.h"
#include "Scenes.h"


//Arduino SETUP
void setup() {
  uint16_t ID;

  //se inicializa la comunicacion I2C

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(sendEvent);

  Serial.begin(9600);
  Serial.println(F(">> Iniciando arduino"));

  ID = tft.readID();

  Serial.print(F(">> Pantalla TFT ID:0x"));
  Serial.println(ID, HEX);

  tft.begin(ID);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.setRotation(Orientation);
}

//Arduino LOOP @16MHz
void loop() {
  if (hasChanged) {
    //repaint based in current scene
    switch (getCurrentScene()) {
      case START:
        estado = 1;
        printFirstScene();
        break;

      case SECURE:
        printSecureScene();
        break;

      case ENTER_OBJECTS:
        printEnterObjects();
        break;

      case TEMP:
        printTempScene();
        break;

      case SANITIZE_HANDS:
        printSanitizeHandsScene();
        break;

      case REMOVE_OBJECTS:
        printRemoveObjectsScene();
        break;

      case ENTER_DOOR:
        printPassDoorScene();
        break;

      case DESINFECTING_DOOR:
        printDesinfectingDoor();
        break;
    }
  }
}
