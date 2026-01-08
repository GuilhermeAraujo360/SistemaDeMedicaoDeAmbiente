#ifndef BUZZER_H
#define BUZZER_H
#include <Arduino.h>

const int buz = D7;

void som(unsigned int tempo) {
  digitalWrite(buz, HIGH);
  delay(tempo);
  digitalWrite(buz, LOW);
}


#endif