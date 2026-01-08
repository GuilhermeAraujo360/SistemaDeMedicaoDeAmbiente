#ifndef LED_H
#define LED_H

const int led = D6   ;

void piscar(unsigned int tempo) {
  digitalWrite(led, HIGH);
  delay(tempo);
  digitalWrite(led, LOW);
}


#endif