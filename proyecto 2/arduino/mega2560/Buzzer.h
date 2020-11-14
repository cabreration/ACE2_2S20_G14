
class Buzzer {
  private:
    boolean quiet = false;
  public:
    Buzzer() {
      pinMode(22, OUTPUT);
      digitalWrite(22, HIGH);
    }

    void beep(int tim) {
      if (quiet) {
        return;
      }
      for (int i = 0; i < 10; i++) {
        digitalWrite(22, LOW);
        delay(tim);
        digitalWrite(22, HIGH);
      }
    }

    void alarm() {
      if (quiet) {
        return;
      }
      for (int i = 0; i < 5; i++) {
        beep(75);
        delay(100);
      }
    }
};

Buzzer buzzer;
