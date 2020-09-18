
// ACE2 2S 2020
// Created by: Leonel Aguilar
// Adapted by: DamC

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266Ping.h>


#include <Wire.h>


//posibles peticiones
#define reqLocation 0 // location?ubicacion=0&
#define reqDelivery 1 // delivery?peso=200&estado=0;




#define DEBUG 1
#define I2CAddressArduino 8
#define CountData 5 // cantidad de ints a recibir como maxio, si se neceistan mas de 16 
// se debe modificar los ciclos de repeticón



void debug(String val) {
#if DEBUG
  Serial.println(String(">> ") + val);
#endif
}

const char *ssid = "Red1";
const char *password = "Luch0Luch0";
const char *host = "http://18.188.84.47:3000/";

String route;
char cRoute;
String package;
int Data[CountData];
//cantidad de ping en ese instante:

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
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  //Inicalización del la comunicación I2C
  //con los pines D1 y D2 y el canal 8 (modo slave)
  Wire.begin(D1, D2, I2CAddressArduino);
  Wire.onReceive(reciveEvents);
  Wire.onRequest(requestEvents);

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

    debug(result);

    return result;
  }

  return "";
}

#include "api_def.h";
String resultState;
int httpCodeState = 0;
String result ;
// The loop function runs over and over again forever
void loop() {



  delay(valuePing * 2.5);
  //se pide estatus del estado del carrito
  if (WiFi.status() == WL_CONNECTED) {
    debug("Conectado a internet");
    HTTPClient http;
    //realizar la peticion http
    http.begin("http://18.188.84.47:3000/state?consulta=0");
    
    debug("Realizando get: http://18.188.84.47:3000/state?consulta=0");
    httpCodeState = http.GET();
    resultState = "";
    //Check the returning code
    if (httpCodeState > 0) {
      result += http.getString();
    }
    debug(result);
    //close connection
    http.end();
  }

  process_api_request(0, "ubicacion=0&estado=0&angulo=0&distancia=0");
  delay(1000);
  process_api_request(1, "peso=150&estado=0");
  process_api_request(0, "ubicacion=1&estado=1&angulo=0&distancia=0");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=1&angulo=0&distancia=10");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=1&angulo=0&distancia=50");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=1&angulo=0&distancia=100");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=1&angulo=0&distancia=150");
  delay(500);
  //detecto un bache
  process_api_request(0, "ubicacion=1&estado=3&angulo=0&distancia=200");
  delay(1500);
  //se quito el obstaculo
  process_api_request(0, "ubicacion=1&estado=1&angulo=90&distancia=250");
  delay(500);
  process_api_request(1, "peso=150&estado=1");
  process_api_request(0, "ubicacion=2&estado=1&angulo=90&distancia=270");
  delay(3500);
  process_api_request(1, "peso=0&estado=2");
  process_api_request(0, "ubicacion=1&estado=2&angulo=90&distancia=260");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=2&angulo=90&distancia=210");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=2&angulo=90&distancia=150");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=3&angulo=90&distancia=150");
  delay(5500);
  process_api_request(0, "ubicacion=1&estado=2&angulo=90&distancia=100");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=2&angulo=90&distancia=50");
  delay(500);
  process_api_request(0, "ubicacion=0&estado=0&angulo=0&distancia=0");
}
// funcion que se ejecuta cuanod se solicitan bytes del master (arduino)
void requestEvents() {
  //se enviará el ping del server al arduino y el estado del carrito

  Wire.write(valuePing);
  Wire.write(state_from_server);


}
// función que se ejecuta al recibir bytes del master (arduino)
void reciveEvents(int numBytes) {
  //se recibirán los datos a leer

  if (numBytes > 1) {
    // se lee los bytes recibidos y se añaden a array Data
    for (int i = 0; i < numBytes; i += 2) {
      //se llenan el array de ints
      Data[i / 2] = Wire.read();
      Data[i / 2] << 8;
      Data[i / 2] |= Wire.read();
    }

    // se manda a la API cuando se llena el array de data
    //si arma la cadena con los parametros que determina cRoute

    if (cRoute == reqLocation ) {
      package = paramDataLocation[0] + "=" + String(Data[0]);
      package += "&" + paramDataLocation[1] + "=" + String(Data[1]);
      package += "&" + paramDataLocation[2] + "=" + String(Data[2]);
      package += "&" + paramDataLocation[3] + "=" + String(Data[3]);
    } else if (cRoute == reqDelivery ) {
      package =  paramDataDelivery[0] + "=" + String(Data[0]);
      package += "&" + paramDataDelivery[1] + "=" + String(Data[1]);

    } else  {
      debug("error crítico");
    }
    /// se envia a la api
    //process_api_request(package, cRoute);
    Serial.println(package);
    Serial.println(route);

  }
  else {

    cRoute = Wire.read();


  }
}
