#include "Thread.h"
#include "ThreadController.h"
#include <TimerOne.h>
class StatusThread: public Thread {
  private: 
  int* distanceValue;
  int* weightValue;
  String strSend;
  
  public: 
    
    StatusThread(int* _distance,int* _weight ): distanceValue {_distance}, weightValue(_weight),Thread(){
      Serial3.begin(115200);
    }
       void run(){
       Serial3.println("arduino");
       //se envia la cadena con los valores requeridos por el módulo wifi
       //weightValue en gramos y distanceValue en milimietros
       strSend = "peso="+String(*weightValue);
       strSend+="&spray="; 
       strSend+= String(*distanceValue);
       Serial3.println(strSend); 
        runned();
      }

      void debug() {
       Serial.println("arduino");
       Serial.println(strSend);
        }
    
  
  };
