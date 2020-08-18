#include "HX711.h"
#include "Thread.h"
#include "ThreadController.h"
#include <TimerOne.h>


class WeightThread: public Thread {
byte pinData = 0; 
byte pinClock = 0; 
HX711 sWeight;
float calibration = 20280.0; //factor de calibración para el sensor

 public: 
  long zeroFactor = 0;
  float weigthValue = 0.0;

WeightThread ( byte _pinData, byte _pinClock): pinClock {_pinClock}, pinData{ _pinData }, Thread() 
{
  sWeight.begin(pinData, pinClock); 
  sWeight.set_scale(); 
  sWeight.tare(); 
  sWeight.set_scale(calibration);
  zeroFactor = sWeight.read_average();   
}

void run () 
{
 weigthValue = sWeight.get_units(); 
 runned();
  }  
};
