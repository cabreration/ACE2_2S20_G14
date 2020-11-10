#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define TEMP_TRY_LENGTH 50.0

void setup() {
  mlx.begin();
  Serial.begin(9600);
}

void getTemp() {
  float total = 0;
  for (int i = 0; i < TEMP_TRY_LENGTH; i++) {
    float tmp = mlx.readObjectTempC();
    Serial.println(">> " + String(i) + " -> " + String(tmp));
    total += tmp;

    delay(250);
  }

  Serial.println(">> Total: " + String(total));
  total /= TEMP_TRY_LENGTH;

  Serial.println(" Temperatura promedio: " + String(total));
}

void loop() {
  if (Serial.available() > 0) {
    String e = Serial.readString();
    e.trim();
    getTemp();
  }
  
  delay(1000);
}
