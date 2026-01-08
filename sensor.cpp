#include "sensor.h"

// construtor 
SensorDHT::SensorDHT() : sensor(PINO, TIPO) {
    
}

// o begin que ficará no setup
void SensorDHT::inicializar() {
    sensor.begin();
}

// leitura de temperatura
float SensorDHT::lerTemperaturaC() {

    return sensor.readTemperature();
}

// leitura de umidade
float SensorDHT::lerUmidade() {

    return sensor.readHumidity();
}