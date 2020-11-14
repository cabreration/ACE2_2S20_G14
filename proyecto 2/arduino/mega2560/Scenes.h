
//Control de escenas de la pantalla
enum TftScene {
  START,
  SECURE,
  ENTER_OBJECTS,
  TEMP,
  SANITIZE_HANDS,
  REMOVE_OBJECTS,
  ENTER_DOOR,
  DESINFECTING_DOOR
};


//escena actual, en la que se encuentra el sistema
TftScene currentScene = START;

//revisa si la escena actual cambio desde la ultima lectura
boolean hasChanged = true;

//Obtener la escena actual de la pantalla
TftScene getCurrentScene(void) {
  if (hasChanged) {
    hasChanged = false;
  }
  return currentScene;
}

//cambiar la escena actual a una nueva, enviada como parametro
void changeCurrentScene(TftScene newScene) {
  hasChanged = true;
  currentScene = newScene;
}

//Deja que el usuario pueda dibujar el patron en la pantalla
int allowPrint(void) {
  while (!Touch_getXY()) {
    ;
  }

  long clickedAt = millis();

  tpIndex = 0;
  tpOrder = 0;
  resetTouchedPoints();

  //revisar si el valor que se ingresa
  //es ingresado en menos de 200 ms de estar presionado
  while (millis() - clickedAt <= 200) {
    while (Touch_getXY()) {
      if (pixel_y > 230) {
        continue;
      }

      int boxSize = tft.width() / 12;
      tft.fillRect(pixel_x - boxSize * 0.5, pixel_y - boxSize * 0.5, boxSize, boxSize, BLUE);
      //revisar si el punto esta dentro de los circulos del patron
      checkIfInside();

      clickedAt = millis();
    }
  }
}


//Imprimir estado inicial del sistema
//el estado inicial muestra el nombre del producto
//los creadores
//y un mensaje que muestra que se esta esperando al modo seguro
void printFirstScene(void)
{
  tft.fillScreen(BLACK);

  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(5, 10);
  tft.println(F("Ingresa con tu telefono..."));

  int curr_radius = 10;
  int max_radius = 40;
  int inc = 1;
  int color = getRandomColor();

  while (!enabled) {
    if (Serial.available()) {
      String value = Serial.readString();
      Serial.println(value);

      if (value.indexOf("start") >= 0) {
        enabled = true;
      }
    }
    //esperar a la api
    if (curr_radius > max_radius) {
      inc = -1;
    } else if (curr_radius <= 10) {
      inc = 1;
      color = getRandomColor();

      tft.setCursor(60, 85);
      tft.setTextSize(7);
      tft.setTextColor(color);
      tft.println("ED3");
    }

    if (inc == 1) {
      tft.drawCircle(120, 225, curr_radius, color);
    }
    else {
      tft.drawCircle(120, 225, curr_radius, BLACK);
    }

    curr_radius += inc;
    delay(50);
  }

  enabled = false;
  estado = 2;

  changeCurrentScene(ENTER_OBJECTS);
}

//Imprime la escena de la clave de seguridad
//Este no sale de aca hasta que se termina de
//realizar el patron
void printSecureScene(void) {
  tft.fillScreen(BLACK);
  tft.setCursor(0, 260);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("Ingrese el    patron");

  while (!isCorrect) {

    int cw = tft.width() / 4;
    int top = printPatronCircles(cw);

    //activar la pantalla touch para recibir el input del usuario
    allowPrint();

    //imprimir de nuevo, si estuvo bien, transicionar a la otra vista
    printPatronCircles(cw, true);
    delay(1500);
  }

  changeCurrentScene(START);
  isCorrect = false;
}

void printEnterObjects() {

  tft.fillScreen(BLACK);
  // caja
  tft.fillRect(30, 60, 180, 100, YELLOW);
  //apertura
  tft.fillRect(40, 100, 160, 50, BLACK);
  //flecha
  tft.fillRect(110, 155, 10, 35, RED);
  tft.fillTriangle(100, 165, 130, 165, 115, 150, RED);

  for (int i = 0; i < 5; i++) {
    tft.fillRect(0, 200, 240, 120, BLACK);
    // cajitas // objetos
    if (i == 2) {
      tft.fillRect(75, 125, 20, 20, GREEN);
    } else if (i == 3) {
      tft.fillRect(105, 125, 20, 20, GREEN);
    } else if (i == 4) {
      tft.fillRect(135, 125, 20, 20, GREEN);
    }
    //texto
    tft.setCursor(20, 200);
    tft.setTextSize(5);
    tft.setTextColor(GREEN);
    tft.print("INGRESA");
    tft.setCursor(20, 245);
    tft.setTextSize(3);
    tft.setTextColor(WHITE);
    tft.print("TUS OBJETOS");
    delay(1500);
  }


  tft.fillScreen(BLACK);
  // caja
  tft.fillRect(30, 60, 180, 100, YELLOW);
  //apertura
  tft.fillRect(40, 100, 160, 50, BLACK);

  tft.fillRect(75, 125, 20, 20, GREEN);
  tft.fillRect(105, 125, 20, 20, GREEN);
  tft.fillRect(135, 125, 20, 20, GREEN);

  for (int i = 0; i < 3; i++) {
    //flecha
    tft.fillRect(110, 105, 10, 10, CYAN);
    tft.fillTriangle(100, 115, 130, 115, 115, 120, CYAN);

    //texto
    tft.setCursor(5, 200);
    tft.setTextSize(3);
    tft.setTextColor(CYAN);
    tft.print("DESINFECTANDO");
    tft.setCursor(20, 245);
    tft.setTextSize(3);
    tft.setTextColor(WHITE);
    tft.print("TUS OBJETOS");

    wp.sanitizeObjects();
        
    tft.fillRect(100, 105, 30, 15, BLACK);
    tft.fillRect(5, 200, 235, 120, BLACK);
    delay(500);
  }

  changeCurrentScene(TEMP);
}

void printFaceAndEyes(int color) {
  // cara
  tft.drawCircle(120, 100, 79, color);
  tft.drawCircle(120, 100, 80, color);
  tft.drawCircle(120, 100, 81, color);
  tft.drawCircle(120, 100, 82, color);

  // ojo derecho
  tft.drawCircle(100, 90, 10, color);
  tft.drawCircle(100, 90, 11, color);
  tft.drawCircle(100, 90, 12, color);
  tft.drawCircle(100, 90, 13, color);

  // ojo izquierdo
  tft.drawCircle(140, 90, 10, color);
  tft.drawCircle(140, 90, 11, color);
  tft.drawCircle(140, 90, 12, color);
  tft.drawCircle(140, 90, 13, color);
}

void printSmileFace(void) {

  // boca feliz
  tft.drawCircle(120, 100, 60, GREEN);
  tft.drawCircle(120, 100, 61, GREEN);
  tft.drawCircle(120, 100, 62, GREEN);
  tft.drawCircle(120, 100, 63, GREEN);

  tft.fillRect(50, 20, 140, 110, BLACK);

  printFaceAndEyes(GREEN);
}

void printSadFace(int color) {
  tft.drawCircle(120, 180, 50, color);
  tft.drawCircle(120, 180, 51, color);
  tft.drawCircle(120, 180, 52, color);
  tft.drawCircle(120, 180, 53, color);

  tft.fillRect(50, 150, 140, 110, BLACK);

  printFaceAndEyes(color);
}

void printTempScene(void) {

  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setCursor(20, 30);
  tft.setTextSize(6);
  tft.print("Acerca");
  tft.setCursor(80, 85);
  tft.print("el ");
  tft.setTextColor(MAGENTA);
  tft.setCursor(20, 140);
  tft.print("SENSOR");

  tft.setCursor(20, 210);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Iniciando en ");
  tft.setTextColor(RED);
  tft.setTextSize(6);

  for (int i = 5; i > 0; i--) {
    tft.setCursor(100,  250);
    tft.print(String(i));
    delay(750);
    tft.fillRect(0, 238, 300, 200, BLACK);
  }

  tft.fillScreen(BLACK);

  tft.setCursor(20, 85);
  tft.setTextSize(6);
  tft.setTextColor(RED);
  tft.print("ESPERA");
  tft.setCursor(20, 140);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Leyendo tu   temperatura");

  tft.fillCircle(60, 250, 25, WHITE);
  tft.fillCircle(61, 250, 20, RED);
  float total = temperature.get();
  buzzer.beep(50);

  tft.fillCircle(120, 250, 25, WHITE);
  tft.fillCircle(121, 250, 20, YELLOW);
  total += temperature.get();
  buzzer.beep(50);

  tft.fillCircle(180, 250, 25, WHITE);
  tft.fillCircle(181, 250, 20, GREEN);
  total += temperature.get();
  buzzer.beep(50);

  total /= 3;

  if (total > 35.5 && total < 36.1) {
    total += 0.5;
  } else if (total > 37.2) {
    total -= 1;
  }

  temperaturaTotal = floor(total * 100);

  tft.fillScreen(BLACK);

  int color;

  if (total > 37.2) {
    color = RED;
  } else if (total < 36.0) {
    color = BLUE;
  } else {
    color = GREEN;
  }

  if (color == GREEN) {
    printSmileFace();
  } else {
    printSadFace(color);
  }

  tft.setCursor(30, 205);
  tft.setTextSize(6);
  tft.setTextColor(color);
  tft.print(String(total));
  tft.setCursor(95, 260);
  tft.setTextSize(3);
  tft.print("O");
  tft.setTextSize(6);
  tft.setCursor(90, 260);
  tft.print(" C");

  if (color != GREEN) {
    buzzer.alarm();

    tft.fillScreen(BLACK);
    tft.setTextColor(RED);
    tft.setCursor(15, 30);
    tft.setTextSize(4);
    tft.print("NORMALIZA");
    tft.setCursor(5, 85);
    tft.setTextSize(2);
    tft.print("tu temperatura para");
    tft.setTextColor(YELLOW);
    tft.setCursor(0, 125);
    tft.setTextSize(5);
    tft.print("INGRESAR");
    tft.setTextSize(3);
    tft.setCursor(60, 200);
    tft.setTextColor(RED);
    tft.print("Entrada");
    tft.fillRect(0, 230, 250, 60, RED);
    tft.setTextSize(4);
    tft.setCursor(30, 245);
    tft.setTextColor(YELLOW);
    tft.print("DENEGADA");

    changeCurrentScene(START);
    finalizarProceso();
    delay(1500);
  }

  else {
    changeCurrentScene(SANITIZE_HANDS);
    delay(3000);
  }
}

void printSanitizeHandsScene() {
  tft.fillScreen(BLACK);

  tft.setTextColor(WHITE);
  tft.setCursor(12, 30);
  tft.setTextSize(5);
  tft.print("Ingresa");
  tft.setTextSize(3);
  tft.setCursor(10, 85);
  tft.print("tus manos al ");
  tft.setTextColor(MAGENTA);
  tft.setCursor(20, 140);
  tft.setTextSize(3);
  tft.print("SANITIZADOR");

  tft.setCursor(10, 210);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Iniciando en ");
  tft.setTextColor(GREEN);
  tft.setTextSize(6);

  for (int i = 5; i > 0; i--) {
    tft.setCursor(100,  250);
    tft.print(String(i));
    delay(1000);
    tft.fillRect(0, 238, 300, 200, BLACK);
  }

  tft.fillScreen(BLACK);

  tft.fillCircle(120, 140, 52, CYAN);
  tft.fillTriangle(70, 123, 170, 123, 120, 40, CYAN);

  tft.setTextSize(3);
  tft.setTextColor(BLUE);

  wp.sanitizeHands();
  
  for (int i = 0; i < 5; i++) {
    delay(500);
    tft.fillRect(0, 220, 240, 100, CYAN);
    delay(500);
    tft.setCursor(33, 230);
    tft.print("DESINFECTA");
    tft.setTextSize(2);
    tft.setCursor(100, 260);
    tft.print("TUS");
    tft.setCursor(80, 280);
    tft.setTextSize(3);
    tft.print("MANOS");
    delay(1000);
  }

  changeCurrentScene(REMOVE_OBJECTS);
}

void printRemoveObjectsScene(void) {
  tft.fillScreen(BLACK);
  // caja
  tft.fillRect(30, 60, 180, 100, YELLOW);
  //apertura
  tft.fillRect(40, 100, 160, 50, BLACK);

  tft.fillRect(75, 125, 20, 20, CYAN);
  tft.fillRect(105, 125, 20, 20, CYAN);
  tft.fillRect(135, 125, 20, 20, CYAN);

  for (int i = 0; i < 5; i++) {

    //apertura
    tft.fillRect(40, 100, 160, 50, BLACK);

    // cajitas // objetos
    if ( i == 1 ) {
      tft.fillRect(75, 125, 20, 20, CYAN);
      tft.fillRect(105, 125, 20, 20, CYAN);
      tft.fillRect(135, 125, 20, 20, CYAN);
    }
    else if ( i == 2 ) {
      tft.fillRect(75, 125, 20, 20, CYAN);
      tft.fillRect(105, 125, 20, 20, CYAN);
    }
    else if ( i == 3 ) {
      tft.fillRect(75, 125, 20, 20, CYAN);
    }

    //flecha
    tft.fillRect(110, 135, 10, 35, RED);
    tft.fillTriangle(100, 170, 130, 170, 115, 185, RED);

    tft.fillRect(0, 200, 240, 120, BLACK);
    //texto
    tft.setCursor(20, 200);
    tft.setTextSize(5);
    tft.setTextColor(CYAN);
    tft.print("REMUEVE");
    tft.setCursor(20, 245);
    tft.setTextSize(3);
    tft.setTextColor(WHITE);
    tft.print("TUS OBJETOS");
    delay(1500);
  }

  changeCurrentScene(ENTER_DOOR);
}

void printDoor(void) {
  // PUERTA
  tft.fillRect(60, 30, 110, 170, WHITE);
  tft.fillRect(65, 35, 100, 160, BLACK);
  tft.fillRect(70, 40, 90, 150, WHITE);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 300);

  // PICAPORTE
  tft.fillCircle(150, 120, 5, BLACK);
}

void printPassDoorScene(void) {
  tft.fillScreen(BLACK);

  printDoor();

  tft.print("PASE ADELANTE...");

  // FLECHA
  for (int i = 0; i < 5; i++) {
    tft.fillRect(85, 115, 40, 10, RED);
    tft.fillTriangle(125, 110, 125, 130, 145, 120, RED);

    tft.setTextSize(5);
    tft.setCursor(15, 210);
    tft.setTextColor(WHITE);
    tft.print("INGRESO");
    tft.setTextSize(4);

    tft.setCursor(15, 250);
    tft.setTextColor(GREEN);
    tft.print("PERMITIDO");

    delay(1200);

    if (i < 4) {
      tft.fillRect(85, 110, 60, 20, WHITE);
      tft.fillRect(15, 210, 225, 80, BLACK);

      delay(300);
    }
  }

  changeCurrentScene(DESINFECTING_DOOR);
}

void printDesinfectingDoor(void) {
  tft.fillScreen(BLACK);

  tft.fillScreen(BLACK);

  printDoor();

  tft.print("PROCESO FINALIZADO...");

  wp.sanitizeDoor();

  // FLECHA
  for (int i = 0; i < 5; i++) {
    tft.fillRect(85, 115, 40, 10, BLUE);
    tft.fillTriangle(125, 110, 125, 130, 145, 120, BLUE);

    tft.setTextSize(3);
    tft.setCursor(5, 210);
    tft.setTextColor(WHITE);
    tft.print("DESINFECTANDO");
    tft.setTextSize(4);

    tft.setCursor(25, 250);
    tft.setTextColor(MAGENTA);
    tft.print("PUERTA");

    delay(500);

    if (i < 4) {
      tft.fillRect(85, 110, 60, 20, WHITE);
      tft.fillRect(5, 210, 235, 80, BLACK);
      delay(500);
    }
  }

  finalizarProceso();
  delay(1000);
  changeCurrentScene(START);
}
