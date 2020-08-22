#include <Servo.h>
#include "Thread.h"
#include "ThreadController.h"
#include <TimerOne.h>


class LockThread: public Thread {
  byte OpVelocity = 0;   
  byte ClVelocity = 0;
  byte pinServo = 0; 
  byte pinState = 0; 
  
  unsigned long startTime = 0; 
  unsigned int intervalTime = 0; // variable a calibrar
  
  Servo servo; 

  public:   
  byte state = 0; // 1 para cerrado 0 para abierto
  LockThread (byte _pinServo, byte _pinState, byte _clockWise): pinServo{_pinServo}, pinState{_pinState}, Thread()
  {
    /*
    Al reiniciarse el dispositivo las puertas siempre se abrirán
    velocidad = 90 servo detenido.
    */
    servo.write(90);
    ClVelocity = (_clockWise == 0) ? 40: 140; 
    OpVelocity = (_clockWise == 0) ? 140: 40; 
    servo.attach(pinServo); 
    pinMode(pinState,INPUT);
    // Se reinicia la posición de los servos.
    while (digitalRead(pinState) == 1){
      servo.write(OpVelocity);
     }
     delay(300); // delay a calibrar
     servo.write(90);    
  }

  void run ()   
  {
    
     if (state == 1 && digitalRead(pinState) == 1){
      servo.write(90); // servo parado.
     }   
    if (state == 0 && startTime + intervalTime <= millis()) {
      startTime = 0; 
      servo.write(90);      
    }
    
    //si se deea abrir la puerta al estar cerrada
    if (state == 0 && digitalRead(pinState)== 1) {
      startTime = millis();
      servo.write(OpVelocity);      
    }
    // si se desea cerrar la puerta al estar abierta
    if (state == 1 && digitalRead(pinState)== 0) {
      servo.write(ClVelocity);
    }
   runned(); 
  }
  
}; 
