
//pines analogicos para el sensor ultrasonico
#define echoUltraSonic A8
#define triggerUltraSonic A9

//pines digitales para los sensores de proximidad
#define proximitySensorA A0
#define proximitySensorB A1

//pin digital para la bomba de agua
#define wPump A10

//pies de salida de pines
#define ledA A11
#define ledB A12
#define ledC A13

//pine digitales para el sensor de peso
#define wgtData 24
#define wgtClock 22

//intervalos de tiempo
//tiempo de conexion
#define interval_connection 15000
//tiempo de lectura de sensores de proximidad y de peso
#define interval_sensors 150
//intervalo del uso de la bomba de agua
#define interval_wPump 6000
