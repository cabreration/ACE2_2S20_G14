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


#define CountData 6 // cantidad de ints a recibir como maxio, si se neceistan mas de 16 
// se debe modificar los ciclos de repeticón



const int16_t I2CArduino= 0x8;

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
  //Serial.begin(115200);

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
bool notified = false;
char old_state_fs = 0;
char high; 
char low;
// The loop function runs over and over again forever
void loop() {
  delay(1500);

  old_state_fs = state_from_server;
  process_api_request(2, "consulta=0");
  if (state_from_server != old_state_fs) {
    sendStatus();
  }
  Wire.requestFrom(8, 12);//0x08 = 8;

  while (Wire.available()<12) {}
  for(int i = 0; i< 6; i++) {
      low = Wire.read();
      high = Wire.read();
      Data[i] = low << 8 | high ;

  }

  package = paramDataLocation[0] + "=" + String(Data[0]);
  package += "&" + paramDataLocation[1] + "=" + String(Data[1]);
  package += "&" + paramDataLocation[2] + "=" + String(Data[2]);
  package += "&" + paramDataLocation[3] + "=" + String(Data[3]);
  //process_api_request( 0, package);

  package =  paramDataDelivery[0] + "=" + String(Data[4]);
  package += "&" + paramDataDelivery[1] + "=" + String(Data[5]);
  //process_api_request( 1,package);



 /*  while (Serial.available() != true){
    }
    Serial.read();
  process_api_request(0, "ubicacion=0&estado=0&angulo=x&distancia=0");
  delay(1000);
   while (Serial.available() != true){
    }
    Serial.read();
    process_api_request(0, "ubicacion=0&estado=0&angulo=x&distancia=0");
  delay(1000);
   while (Serial.available() != true){
    }
    Serial.read();
  process_api_request(1, "peso=150&estado=0");
   while (Serial.available() != true){
    }
    Serial.read();
  process_api_request(0, "ubicacion=1&estado=1&angulo=x&distancia=0");
  delay(500);
   while (Serial.available() != true){
    }
    Serial.read();
  process_api_request(0, "ubicacion=1&estado=1&angulo=x&distancia=10");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=1&angulo=x&distancia=50");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=1&angulo=x&distancia=100");
  delay(500);
    //detecto un bache
  process_api_request(0, "ubicacion=1&estado=3&angulo=x&distancia=125");
  delay(1500);
  process_api_request(0, "ubicacion=1&estado=1&angulo=x&distancia=150");
  delay(500);
  //detecto un bache
  process_api_request(0, "ubicacion=1&estado=3&angulo=y&distancia=0");
  delay(1500);
  //se quito el obstaculo
  process_api_request(0, "ubicacion=1&estado=1&angulo=y&distancia=40");
  delay(500);
  process_api_request(1, "peso=150&estado=1");
  process_api_request(0, "ubicacion=2&estado=1&angulo=y&distancia=130");
  delay(500); 
  process_api_request(1, "peso=150&estado=1");
  process_api_request(0, "ubicacion=2&estado=1&angulo=y&distancia=150");
  delay(3500);
  
  
  process_api_request(1, "peso=0&estado=2");
  process_api_request(0, "ubicacion=1&estado=2&angulo=y&distancia=0");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=2&angulo=y&distancia=50");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=2&angulo=y&distancia=100");
  delay(500);
  // se detecto un obstaculo
  process_api_request(0, "ubicacion=1&estado=3&angulo=y&distancia=130");
  delay(5500);  
  process_api_request(0, "ubicacion=1&estado=2&angulo=y&distancia=150");
  delay(500);
   //se detecto un obstaculo
  process_api_request(0, "ubicacion=1&estado=3&angulo=x&distancia=0");
  delay(1500);
  process_api_request(0, "ubicacion=1&estado=2&angulo=y&distancia=50");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=2&angulo=y&distancia=100");
  delay(500);
  process_api_request(0, "ubicacion=1&estado=2&angulo=y&distancia=150");
  delay(500);
  process_api_request(0, "ubicacion=0&estado=0&angulo=x&distancia=0");
  
  while (Serial.available() != true){
    }
    */
}
// funcion que se ejecuta cuanod se solicitan bytes del master (arduino)


void sendStatus(){

  Wire.beginTransmission(8);
  Wire.write(state_from_server);
  Wire.endTransmission();
}
