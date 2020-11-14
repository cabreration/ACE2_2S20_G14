
//direcciones I2C
#define I2CAddressESP 8

#include "I2C.h"

long ellapsed = 0;
unsigned int temperaturaTotal = 0;
int randomAdded = 0;
int sign = 0;

void finalizarProceso() {
  randomAdded = random(1500);
  sign = randomAdded % 3;
  randomAdded *= sign == 0 ? 0 : sign == 1 ? 1 : -1;

  travel[0] = temperaturaTotal;
  travel[1] = floor(((millis() - ellapsed) + randomAdded) / 100);
  estado = 3;
  delay(1100);
}

#include "Temperature.h"
#include "Buzzer.h"
#include "WaterPumps.h"
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
  randomSeed(analogRead(15));

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
        //guardar para saber cuanto tiempo paso en el sistema
        ellapsed = millis();
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
