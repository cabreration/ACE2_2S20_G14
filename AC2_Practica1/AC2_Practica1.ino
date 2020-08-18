  
#include "ProxSensorThread.h"
#include "UltraSonicThread.h"
#include "TimerOut.h"
#include "LockThread.h"
#include "WeightThread.h"
#include "ThreadController.h"
#include <TimerOne.h>
#include "Pins.h"


//hilos para sensores
ProxSensorThread proxSensorA = ProxSensorThread(proximitySensorA);
ProxSensorThread proxSensorB = ProxSensorThread(proximitySensorB);
UltraSonicThread usSensor = UltraSonicThread(echoUltraSonic, triggerUltraSonic);

//hilo para la bomba de agua
TimerOut waterPump = TimerOut(timeWPump, wPump);

//hilo para el sensor de peso
WeightThread wgtSensor = WeightThread(wgtData, wgtClock); 

//hilos para servoMotores
LockThread doorA = LockThread(servoDoorA,stDoorA,0); 
LockThread doorB = LockThread(servoDoorB,stDoorB,1); 

ThreadController controller = ThreadController();

char option;

void timerCallback () 
{
  controller.run(); 
  }

void setup() {

  /*
   * inicialización de subrutinas por medio de hilos
  */
  Serial.begin(9200);
  Serial3.begin(9200); 
  proxSensorA.setInterval(75);
  proxSensorA.setInterval(75);
  usSensor.setInterval(75);
  waterPump.setInterval(75); 
  wgtSensor.setInterval(75); 
  doorA.setInterval(75); 
  doorB.setInterval(75);
  controller.add(&proxSensorA); 
  controller.add(&proxSensorB);
  controller.add(&usSensor); 
  controller.add(&waterPump); 
  controller.add(&wgtSensor); 
  controller.add(&doorA); 
  controller.add(&doorB);
  Timer1.initialize(1000); 
  Timer1.attachInterrupt(timerCallback); 
  Timer1.start();
  

}

void loop() {
  /*
  Opciones de comunicación y operaciones I/O de serial sujetas a cambios (interfaz con el módulo wifi)
  */

    if (Serial.available()){
      option = Serial.read();

      switch (option) {
        case 'a': // abrir puerta A
          doorA.state = 0; 
          break;
        case 'b': // abrir puerta B
          doorB.state = 0; 
          break;

        case 'c': // cerrar puerta A
          doorA.state = 1; 
        break; 
        case 'd': // cerrar puerta B
          doorB.state = 1; 
        break;
        case 'e': // leer estado de la pueerta A
          Serial.print(proxSensorA.value); //1 cerrado  0 abierto
         break;

        case 'f': // leer estado de la puerta B
          Serial.print(proxSensorB.value); //1 cerrado  0 abierto
          break;
        case 'g': // leer peso
          Serial.print(wgtSensor.weigthValue,4); // float4 con el peso
          break;

        case 'h': // leer nivel del tanque (ultrasonico)
          Serial.print(usSensor.distance,4); // float4 con la distancia
          break;
        case 'i': //accionar la bomba
          waterPump.enabled = 1; 
          break;
        }      
      }
}
