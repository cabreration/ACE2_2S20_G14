void setup() {
  // put your setup code here, to run once:
  pinMode(22, OUTPUT);
  digitalWrite(22, HIGH);
  Serial.begin(9600);
  Serial.println("Iniciado");
}

void beep(int tim) {
  for (int i = 0; i < 10; i++) {
    digitalWrite(22, LOW);
    delay(tim);
    digitalWrite(22, HIGH);
  }
}

void alarm() {
  for (int i = 0; i < 4; i++) {
    beep(75);
    delay(250);
  }
  delay(250);
  for (int i = 0; i < 4; i++) {
    beep(50);
    delay(500);
  }
  for (int i = 0; i < 4; i++) {
    beep(75);
    delay(1500);
  }
  for (int i = 0; i < 4; i++) {
    beep(75);
    delay(250);
  }
}

void loop() {
  delay(10000);
}
