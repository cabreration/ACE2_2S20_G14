#include "Thread.h"
#include "ThreadController.h"
#include <TimerOne.h>
class StatusThread: public Thread {
  private:
    int* distanceValue;
    int* weightValue;
    String strSend;
    long actualMilis; 

  public:

    StatusThread(int* _distance, int* _weight ): distanceValue {_distance}, weightValue(_weight), Thread() {
      // duni n00b
    }
    
    void run() {
      Serial3.print("arduino\n");
      Serial.print("arduino\n");
      actualMilis = millis(); 
      
      Serial.readString();
      //se envia la cadena con los valores requeridos por el módulo wifi
      //weightValue en gramos y distanceValue en milimietros
      strSend = "peso=" + String(*weightValue);
      strSend += "&spray=";
      strSend += String(*distanceValue);
      //Serial3.flush();
      
      Serial3.print(strSend);
      Serial.print(strSend);
      runned();
    }

    void debug() {
      Serial.println("arduino");
      Serial.println(strSend);
    }
};
