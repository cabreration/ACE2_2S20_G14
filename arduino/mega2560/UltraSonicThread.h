
#include "Thread.h"
#include "ThreadController.h"
#include <TimerOne.h>

class UltraSonicThread: public Thread {
  private:
    byte echo;
    byte trigger;

    long duration = 0;

  public:
    float distance = 0.0f;
    
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
      distance = (float) duration * 0.034 / 2;
      runned();
    }
};
