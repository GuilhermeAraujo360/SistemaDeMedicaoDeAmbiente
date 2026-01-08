//|==================================================================|
//| Código Servidor, feito para rodar no Arduino WeMos com o modulo  |
//| da esp8266, feito por: Guilherme Araujo - 568268                 |
//|                                                                  |
//|==================================================================|
#include <ESP8266WiFi.h>
#include "sensor.h"
#include "buzzer.h"
#include "led.h"


const char* ssid = "MOB-FATIMA";
String senha = "mob283627";

// Porta do servidor, que usará uma conexão TPC
const uint16_t porta  = 8080; 


WiFiServer server(porta);

// esse é o sensor DHT11, uma classe, a implementação encontra-se em "sensor.h"
SensorDHT gear;

void setup() {
  Serial.begin(115200);
  pinMode(buz, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(buz, LOW);
  digitalWrite(led, LOW);
  gear.inicializar();
  


  WiFi.begin(ssid, senha.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Aguardado conexão...  ");
    Serial.flush();
  }
  
  Serial.println("\nWiFi conectado.");
  

  server.begin();
  
  Serial.print("Sistema Phoenix foi iniciado na porta:  ");
  Serial.println(porta);
  Serial.print("IP para conexão:  ");
  Serial.println(WiFi.localIP()); 
}

void loop() {

  WiFiClient client = server.available();

  if (client) {
    Serial.println("\nConectado");
    client.println("Conectado ao sistema Phoenix");
    piscar(1000);
    client.flush();
    som(1000);

    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        line.trim(); 
        line.toUpperCase();


        Serial.print("Comando recebido: ");
        Serial.println(line);

        if (line == "TEMPERATURA") {
          float t = gear.lerTemperaturaC();
          client.println(t);
          client.flush();
          Serial.println("Temperatura enviada");
          piscar(1000);
          som(300);

        }
        else if (line == "UMIDADE") {
          float u = gear.lerUmidade();
          client.println(u);
          client.flush();
          Serial.println("Umidade enviada");
          piscar(1000);
          som(300);

        }
        else if (line == "SAIR") {
          Serial.println("Encerrando conexão");
          piscar(1000);
          som(300);
          break;
        }
        else {
          client.println("Comando invalido");
          client.flush();
        }
      }
      delay(500);
    }

    client.stop();
    piscar(1000);
  }
}



