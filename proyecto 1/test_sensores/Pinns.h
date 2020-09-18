
//pines analogicos para el sensor ultrasonico frontla
#define echoUltraSonicFront A12
#define triggerUltraSonicFront A13


//pines digitales del sensor de linea:
#define lineFollower_S1_RO  49
#define lineFollower_S2_RI  47
#define lineFollower_S3_C  45
#define lineFollower_S4_LI  43
#define lineFollower_S5_LO  41
#define lineFollower_Bump  39
#define lineFollower_Near  37 //blanco

blanco, gris, morado, azul, verde, amarillo naranja, rojo, gris

//pines digitales para el sensor de peso: 

//pines digitales para el sensor de peso
#define wgtData 29
#define wgtClock 27

//direcciones I2C 
#define I2CAddressESP 8
#define I2CAddressGSCP 0x64


// pines de estado 
#define led_line 28





void setup_arduino () {
  //Inicializacion de pines del sensor HS-20 frontal
  pinMode(echoUltraSonicFront,INPUT);
  pinMode(triggerUltraSonicFront, OUTPUT);



  //Inicializacion de pines del seguidor de linea
  pinMode(lineFollower_S1_RO, INPUT); 
  pinMode(lineFollower_S2_RI, INPUT); 
  pinMode(lineFollower_S3_C,INPUT);
  pinMode(lineFollower_S4_LI, INPUT);
  pinMode(lineFollower_S5_LO, INPUT); 
  pinMode(lineFollower_Bump, INPUT); 
  pinMode(lineFollower_Near, INPUT);  

  //Inicializacion de pines para el led de estado
  pinMode(led_line, OUTPUT);
  
}
