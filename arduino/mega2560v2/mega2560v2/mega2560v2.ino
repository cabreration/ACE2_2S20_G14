// Librerias

// Funcion para leer el nivel del peso
int read_weight() {
  return 200;
}


// Funcion para leer el nivel del spray
int read_spray_level() {
  return 100;
}

// Obtener los valores a enviar a la API
String get_string_to_send() {
  return "peso=" + String(read_weight()) + "&spray=" + String(read_spray_level());
}

// Esperar a que el modulo esp8266 realice todas sus operaciones
void wait_module() {
  // Esperar a que el modulo devuelva un mensaje de "continuar"
  char test;
  Serial.println(F(">> Esperando modulo esp8266..."));
  while (1) {
    delay(100);
    if (Serial3.available() > 0) {
      test = Serial3.read();
      Serial.print(test);
      if (test == '#') {
        break;
      }
    }
  }
  
  Serial.println(F("\n>> Espera finalizada"));
}

// Arduino setup
void setup() {
  // Configuracion de los serials
  Serial .begin(115200);
  Serial3.begin(115200);

  // Configuracion de los sensores

  // Inicializacion del arduino
  Serial.println(F(">> ** INICIANDO ARDUINO **"));
}

String string_to_send;

// Arduino loop, 16 MHz
void loop() {

  Serial.println(F("\n******"));
  Serial.println(F(">> Enviando informacion de los sensores a la API"));

  // Obtener el string que se enviara a la API
  string_to_send = get_string_to_send();

  Serial.print(F(">> Valor a enviar: "));
  Serial.println(string_to_send);

  // Enviar inicio de API
  Serial.println(F(">> Enviando 'arduino'..."));
  Serial3.println(F("arduino"));
  
  wait_module();

  // Enviar valor a escribir en la API
  Serial.println(F(">> Enviando valor a la API..."));
  Serial3.println(string_to_send);
  
  Serial.println(F(">> Envio finalizado."));

  // Hacer este loop cada 15 segundos
  delay(15000);
}
