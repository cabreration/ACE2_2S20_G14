

#include "Thread.h"
#include "ThreadController.h"
#include <TimerOne.h>
class ProxSensorThread: public Thread {
  byte pin; 
  
  public: 
    byte value;
    ProxSensorThread(byte _pin): pin {_pin},Thread()
    { 
      pinMode(pin, INPUT);
    }
    

    void run(){
        value = !digitalRead(pin);
        runned();
      }
  };
  
