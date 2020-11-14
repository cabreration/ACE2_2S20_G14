

#define P_SO 17 //Bomba de agua para sanitizar objetos
#define P_SH 19 //Bomba de agua para sanitizar manos
#define P_DO 18 //Bomba de agua para sanitizar la puerta

#define P_SO_DEL 750 //Delay para la bomba de sanitizar objetos
#define P_SH_DEL 1000 //Delay para la bomba de sanitizar manos
#define P_DO_DEL 3000 //Delay para la bomba de sanitizar la puerta

class WaterPumps {

  public:
    WaterPumps() {
      pinMode(P_SO, OUTPUT);
      pinMode(P_SH, OUTPUT);
      pinMode(P_DO, OUTPUT);

      digitalWrite(P_SO, HIGH);
      digitalWrite(P_SH, HIGH);
      digitalWrite(P_DO, HIGH);
    }

    void sanitizeObjects() {
      buzzer.beep(25);
      digitalWrite(P_SO, LOW);
      delay(P_SO_DEL);
      digitalWrite(P_SO, HIGH);
    }

    void sanitizeHands() {
      buzzer.beep(25);
      digitalWrite(P_SH, LOW);
      delay(P_SH_DEL);
      digitalWrite(P_SH, HIGH);
    }

    void sanitizeDoor() {
      buzzer.beep(25);
      digitalWrite(P_DO, LOW);
      delay(P_DO_DEL);
      digitalWrite(P_DO, HIGH);
    }
};

WaterPumps wp;
