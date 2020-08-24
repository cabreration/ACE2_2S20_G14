// ACE2 2S 2020
// Leonel Aguilar

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define DEBUG 0

void debug(String val) {
#if DEBUG
  Serial.println(String(">> ") + val);
#endif
}

const char *ssid = "TIGO-5248";
const char *password = "2D9657312043";

const char *host = "http://18.188.92.62:3000/";

//setup del modulo esp_826
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  debug("");

  debug("Iniciando conexion con la red:");
  debug(ssid);
  debug("Clave de acceso:");
  debug(password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#if DEBUG
    Serial.print(".");
#endif
  }
  
  debug("");
  debug("Conectado exitosamente a la red.");
}

//Esperar a que el serial este disponible
void waitSerial() {
#if DEBUG
  Serial.println(">> Esperando respuesta");
  int dt = 0;
#endif

  while (!(Serial.available() > 0)) {
#if DEBUG
    if (dt == 10) {
      dt = 0;
      Serial.println(".");
    } else {
      Serial.print(".");
    }
    delay(100);
    dt++;
#endif
  }
#if DEBUG
  Serial.println("\n>> Respuesta obtenida");
#endif
}

//realizar una peticion HTTP y retornar el valor que agrego en string
String app_request(String link) {
  //si el modulo esta conectado a internet
  if (WiFi.status() == WL_CONNECTED) {
    debug("Conectado a internet");
    HTTPClient http;
    //realizar la peticion http
    http.begin(host + link);

    debug("Realizando get: " + link);
    int httpCode = http.GET();
    String result = "";
    //Check the returning code
    if (httpCode > 0) {
      result += http.getString();
    }
    
    //close connection
    http.end();

    Serial.println(result);
    return result;
  }

  return "";
}

#include "api_def.h";

// The loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0) {
    //Obtener valor ingresado del serial
    String request_name = Serial.readString();
    request_name.trim();
    
    //procesar la llamada a la API
    process_api_request(request_name);

    //Serial.write('#');
    delay(1000);
  }
}
