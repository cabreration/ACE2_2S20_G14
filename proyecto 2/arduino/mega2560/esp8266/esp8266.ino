// Created by: Leonel Aguilar

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>

// se debe modificar los ciclos de repeticón
const int16_t I2CArduino = 0x8;

void debug(String val) {
  Serial.println(String(">> ") + val);
}

const char *ssid = "TIGO-5248";
const char *password = "2D9657312043";
const char *host = "http://34.71.99.202/";

int valuePing = 120;        //
char state_from_server = 0; // 0 Desactivado - 1 Activado
bool state = 0;             // Apagado
String paramsRuta1 = "";

//setup del modulo esp_826

//realizar una peticion HTTP y retornar el valor que agrego en string
String app_request(String link) {
  //si el modulo esta conectado a internet
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    //realizar la peticion http
    http.begin(host + link);

    int httpCode = http.GET();
    String result = "";

    //Check the returning code
    if (httpCode > 0) {
      result += http.getString();
    }

    //close connection
    http.end();
    debug(result);

    return result;
  }

  return "";
}

#include "api_def.h";

void setup() {

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  Wire.begin(4, 5);

  debug("");
  debug("Iniciando conexion con la red:");
  debug(ssid);
  debug("Clave de acceso:");
  debug(password);

  Serial.begin(115200);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#if DEBUG
    Serial.print(".");
#endif
  }

  debug("");
  debug("Conectado exitosamente a la red.");
}

// The loop function runs over and over again forever
void loop() {

  Serial.println(">> Esperando arduino");
  Wire.requestFrom(8, 5);
  while (Wire.available() < 5) { }

  byte state = Wire.read();

  int temp = Wire.read() << 8 + Wire.read();
  int tim = Wire.read() << 8 + Wire.read();

  Serial.println(">> Estado: " + String(state));
  Serial.println(">> Temperatura: " + String(temp));
  Serial.println(">> Tiempo: " + String(tim));

  switch (state) {
    case 1:
      Serial.println(">> Revisando si hay nuevos usuarios...");
      process_api_request(0);
      Serial.println(">> STATUS DEL SERVER: " + String(state_from_server));
      sendStatus();
      break;

    case 3:
      Serial.println(">> Enviando temperatura y tiempo");
      paramsRuta1 = String(temp) + "&tiem=" + String(tim);
      process_api_request(1);
      break;

    default:
      Serial.println(">> Ignorando estado...");
      break;
  }


  delay(1000);
}

// funcion que se ejecuta cuanod se solicitan bytes del master (arduino)
void sendStatus() {
  Wire.beginTransmission(8);
  Wire.write(state_from_server);
  Wire.endTransmission();
}
