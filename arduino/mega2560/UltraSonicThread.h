
#include "Thread.h"
#include "ThreadController.h"
#include <TimerOne.h>

class UltraSonicThread: public Thread {
    byte echo;
    byte trigger;

    long duration = 0;
  public:
    int distance = 0;
    
    UltraSonicThread(byte _echo, byte _trigger ): echo{_echo}, trigger{_trigger}, Thread()
    {
      pinMode(echo, INPUT);
      pinMode(trigger, OUTPUT);
    }
    
    void run()
    {
      digitalWrite(trigger, LOW);
      delayMicroseconds(2);
      digitalWrite(trigger, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger, LOW);
      duration = pulseIn(echo, HIGH);
      distance = (duration * 0.034 / 2 ) * 10;
      runned();
    }
};
