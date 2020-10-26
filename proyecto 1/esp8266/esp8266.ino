// ACE2 2S 2020
// Created by: Leonel Aguilar

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>

//posibles peticiones
#define reqLocation 0 // location?ubicacion=0&
#define reqDelivery 1 // delivery?peso=200&estado=0;

#define DEBUG 1       // 

#define CountData 6 // cantidad de ints a recibir como maxio, si se neceistan mas de 16 
// se debe modificar los ciclos de repeticón

const int16_t I2CArduino = 0x8;

void debug(String val) {
#if DEBUG
  Serial.println(String(">> ") + val);
#endif
}

const char *ssid = "TIGO-5248";
const char *password = "2D9657312043";
const char *host = "http://18.221.3.244:3000/";

String route;
char cRoute;
String package;

int traveling_array[4] = { 0, 0, 0, 0 };
int old_traveling[4] =  { 0, 0, 0, 0 };

int shipping_array[2] = { 0, 0 };
int old_shipping[2] = { 0, 0 };

int valuePing = 120;
char state_from_server = 0; // 0 desactivado // 1 activado
bool state = 0; //apagado

String paramDataLocation[] = {
  "ubicacion",
  "estado",
  "angulo",
  "distancia"
};

String paramDataDelivery[] = {
  "peso", //al regresar se envia 0
  "estado"
};

String paramStatus[] {
  "consulta"
};

//setup del modulo esp_826

//realizar una peticion HTTP y retornar el valor que agrego en string
String app_request(String link) {
  //si el modulo esta conectado a internet
  if (WiFi.status() == WL_CONNECTED) {
    //debug("Conectado a internet");
    HTTPClient http;
    //realizar la peticion http
    http.begin(host + link);

    // debug("Realizando get: " + link);
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

  //Inicalización del la comunicación I2C
  //con los pines D1 y D2 y el canal 8 (modo slave)

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

String resultState;
int httpCodeState = 0;
String result ;
bool notified = false;
char old_state_fs = 0;
char high;
char low;

bool equalTravel() {
  for ( int i = 0; i < 4; i++) {
    if (old_traveling[i] != traveling_array[i]) {
      return false;
    }
  }
  return true;
}

bool equalShipping () {
  for (int i = 0; i < 2; i++)  {
    if (old_shipping[i] != shipping_array[i]) {
      return false;
    }
  }
  return true;
}


// The loop function runs over and over again forever
void loop() {
  delay(1500);
  //Serial.println(String(traveling_array[0]));

  Wire.requestFrom(8, 12);//0x08 = 8;

  //Serial.println("Esperando datos");
  while (Wire.available() < 12) {}

  for (int i = 0; i < 4; i++) {
    low = Wire.read();
    high = Wire.read();
    traveling_array[i] = low << 8 | high ;
  }
  
  for (int i = 0; i < 2; i++) {
    low = Wire.read();
    high = Wire.read();
    shipping_array[i] = low << 8 | high ;
  }

  if (!equalTravel()) {
    package = paramDataLocation[0] + "=" + String(traveling_array[0]);
    package += "&" + paramDataLocation[1] + "=" + String(traveling_array[1]);
    package += "&" + paramDataLocation[2] + "=" + String(traveling_array[2] == 120 ? 'x' : 'y');
    package += "&" + paramDataLocation[3] + "=" + String(traveling_array[3]);
    process_api_request( 0, package);
    for (int j = 0; j < 4; j++)  {
      old_traveling[j] = traveling_array[j];
    }
    //old_traveling = traveling_array;
  }
  if (!equalShipping()) {
    package =  paramDataDelivery[0] + "=" + String(shipping_array[0]);
    package += "&" + paramDataDelivery[1] + "=" + String(shipping_array[1]);
    process_api_request( 1, package);
    for (int j = 0; j < 2; j ++ ) {
      old_shipping[j] = shipping_array[j];
    }
    // old_shipping = shipping_array;
  }

  if (traveling_array[0] == 0) {
    process_api_request(2, "consulta=0");

    if (state_from_server != old_state_fs) {
      sendStatus();
      old_state_fs = state_from_server;
    }
  }
}

// funcion que se ejecuta cuanod se solicitan bytes del master (arduino)
void sendStatus() {
  Wire.beginTransmission(8);
  Wire.write(state_from_server);
  Wire.endTransmission();
}
