#include "Thread.h"
#include "ThreadController.h"
#include <TimerOne.h>

class TimerOut: public Thread {
  unsigned long interval; 
  byte pinOut; 
  
  unsigned long beginMillis = 0; 

  public: 
  byte enabled = 0; 
  TimerOut(unsigned long _interval, byte _pinOut): interval{_interval}, pinOut{_pinOut}, Thread()
  {
    pinMode(pinOut,OUTPUT);
    
  }

  void run ()
  {
    if (enabled == 1){
      enabled = 0; 
      beginMillis = millis();
      digitalWrite(pinOut,HIGH);      
     } else if ( (millis() - beginMillis) >= interval)  {
      digitalWrite(pinOut,LOW);
      beginMillis = 0; 
     }
     runned();
  }

};
