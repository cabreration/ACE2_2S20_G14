  
#include "ProxSensorThread.h"
#include "UltraSonicThread.h"
#include "TimerOut.h"
//#include "LockThread.h"
#include "WeightThread.h"
#include "ThreadController.h"
#include "StatusThread.h"
#include <TimerOne.h>
#include "Pins.h"


//hilos para sensores
//ProxSensorThread proxSensorA = ProxSensorThread(proximitySensorA);
//ProxSensorThread proxSensorB = ProxSensorThread(proximitySensorB);
UltraSonicThread usSensor = UltraSonicThread(echoUltraSonic, triggerUltraSonic);

//hilo para la bomba de agua
TimerOut waterPump = TimerOut(timeWPump, wPump);

//hilo para el sensor de peso
WeightThread wgtSensor = WeightThread(wgtData, wgtClock); 

//hilo para enviar informacion al módulo wifi
StatusThread statusThrd = StatusThread( &(wgtSensor.weigthValue),&(usSensor.distance));

ThreadController controller = ThreadController();

int option;

void timerCallback () 
{
  controller.run(); 
  }

void setup() {

  /*
   * inicialización de subrutinas por medio de hilos
  */
  Serial.begin(9600);

  Serial.print("Inicializando....");
  //proxSensorA.setInterval(75);
  //proxSensorA.setInterval(75);
  usSensor.setInterval(500);
  waterPump.setInterval(75); 
  wgtSensor.setInterval(500); 
  statusThrd.setInterval(4900);

 // controller.add(&proxSensorA); 
 // controller.add(&proxSensorB);
  controller.add(&usSensor); 
  controller.add(&waterPump); 
  controller.add(&wgtSensor); 
  controller.add(&statusThrd);

  Timer1.initialize(1000); 
  Timer1.attachInterrupt(timerCallback); 
  Timer1.start(); 

}

void loop() {
  /*
fi)
  */

    if (Serial.available()){
      option = Serial.read(); 
      
      switch (option) {
        case 'a': // ver valores actuales de distancia y peso
        statusThrd.debug();
        break;
        case 'w':
        waterPump.enabled = true; 
        break; 
        default:
          Serial.print(option);  
          Serial.print("No supported yet q"); 
          break;
        }      
      }
}
