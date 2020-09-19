// ACE2 2S 2020
// Leonel Aguilar

#ifndef API_DEF
#define API_DEF



// En este archivo se deben escribir todas
// las funciones con cada ruta que se consumira de la API

// Definir la cantidad de rutas y funciones a registrar
const int routeCount = 3;
String state_str = "inactivo";

// Definir todas las rutas a consumir en la api en este arreglo
// solo agregar un nombre simple y unico, que sera el enviado
// por el arduino para saber que funcion realizar
String routes[] = {
  "traveling",
  "shipping",
  "status"
};
//variables de posicion: 
int current_distance = 0;
int current_angle = 0; 

// Enviar el valor del estado actual de la ruta
// - La ruta utilizada para esta funcion es: ruta
// - Los valores a recibir son: un string que contiene el paquete con info a enviar
void sendTravel(String* package) {

  // Leer y limpiar el paquete enviado por el arduino
  // solo contiene valores numericos enteros con los paremetros state=0;
  // concatenar la cadena

  debug("Realizando peticion [sendTravel]");
  app_request(routes[0] + "?" + *package);
}

//Enviar el valor de la posicion actual en una ubicacion de un plano X,Y

void sendShipping(String* package) {
  debug("Realizando peticion [sendShipping]");
  app_request(routes[1] + "?" + *package);
}

void sendStatus(String* package) {
  debug("Realizanod petición [sendStatus]"); 
  String state_str = app_request(routes[2] + "?" + *package);
  state_str.trim();
  if ( state_str == "activo") {
    state_from_server = 1; 
  }else {
    state_from_server = 0;
  }
}


// Definir como un par ordenad todas las funciones
// que haran las rutas previamente definidas en el arreglo "routes"
// cada vez que se haga match con un valor del arreglo se llamara a
// la funcion contenida en este arreglo en el mismo indice
// donde se encontro la ruta
void (*functions[routeCount]) (String *) = {
  sendTravel,
  sendShipping, 
  sendStatus
};


int routeCheckIndex = 0;

// Procesar una llamada hacia la API
void process_api_request(int route, String package) {
  debug(String("Encontrando la ruta: ") + route);
  // comparar con cada elemento del arreglo de nombres de rutas
  if (route >= routeCount) {
    debug("eror crítico: ruta " + String(routeCount) + "no encontrada");
  } else {
    debug(String("Ruta identificada ruta almacenada: ") + routes[route]);
    debug("Llamando a la funcion emparejada de la ruta");
    (*functions[route])(&package);
  }
}

#endif
