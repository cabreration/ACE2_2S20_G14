#include <Adafruit_MLX90614.h>

// Controlador para el sensor MLX90614 GY-906
class Temperature {

  private:
    Adafruit_MLX90614 mlx;
    const int try_count = 10;
    float total = 0;

  public:
    //iniciar el sensor de temperatura
    Temperature() {
      mlx.begin();
    }

    //sensar los datos del pulso
    float get() {
      total = 0;
      // Realizar un promedio de lecturas de temperatura
      for (int i = 0; i < try_count; i++) {
        total += mlx.readObjectTempC();
        delay(100);
      }

      return total / try_count;
    }

};

Temperature temperature;
