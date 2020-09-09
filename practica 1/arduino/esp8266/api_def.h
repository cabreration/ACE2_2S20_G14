// ACE2 2S 2020
// Leonel Aguilar

#ifndef API_DEF
#define API_DEF

// En este archivo se deben escribir todas
// las funciones con cada ruta que se consumira de la API

// Enviar el valor del peso, existencia de objetos y nivel del spray al servidor
// - La ruta utilizada para esta funcion es: arduino
// - Los valores a recibir son: un string que contiene el paquete con info a enviar
void sendMetrics() {
  waitSerial();
  // Leer y limpiar el paquete enviado por el arduino
  // por ejemplo, el peso=valor&spray=valor&objeto=valor
  // solo contiene valores numericos enteros
  String package = Serial.readString();
  package.trim();

  debug("Realizando peticion [sendMetrics]");
  app_request(String("arduino?") + String(package));
}

// Definir la cantidad de rutas y funciones a registrar
const int routeCount = 1;

// Definir todas las rutas a consumir en la api en este arreglo
// solo agregar un nombre simple y unico, que sera el enviado
// por el arduino para saber que funcion realizar
String routes[routeCount] = {
  "arduino"
};

// Definir como un par ordenad todas las funciones
// que haran las rutas previamente definidas en el arreglo "routes"
// cada vez que se haga match con un valor del arreglo se llamara a
// la funcion contenida en este arreglo en el mismo indice
// donde se encontro la ruta
void (*functions[routeCount])() = {
  sendMetrics
};


int routeCheckIndex = 0;

// Procesar una llamada hacia la API
void process_api_request(String request_name) {
  debug(String("Encontrando la ruta: ") + request_name);
  // comparar con cada elemento del arreglo de nombres de rutas
  for (routeCheckIndex = 0; routeCheckIndex < routeCount; routeCheckIndex++) {
    debug(String("Comparando con la ruta almacenada: ") + routes[routeCheckIndex]);
    debug(String(routes[routeCheckIndex] == request_name));
    // si la ruta proporcionada es igual a la ruta que esta almacenada
    if (request_name.equals(routes[routeCheckIndex])) {
      
      Serial.write('#');
      
      debug("Llamando a la funcion emparejada de la ruta");
      // llamar a la funcion desde el arreglo de funciones, que esta emparejada
      // con la ruta que se encontro
      
      delay(500);
      (*functions[routeCheckIndex])();
      // el proceso puede ser finalizado
      break;
    }
  }
}

#endif
