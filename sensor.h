#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <DHT.h>

#define PINO D5
#define TIPO DHT11

class SensorDHT {
  private:
    DHT sensor;

  public:
    SensorDHT();
    void inicializar();
    float lerTemperaturaC();
    float lerUmidade();
};



#endif