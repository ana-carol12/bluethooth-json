#include "Led.h" 
#include <Arduino.h>

int ledState = LOW;             
unsigned long beforeTime = 0; 
const long interval = 500;      

void setupLED(int ledPin) {
	pinMode(ledPin, OUTPUT);
}

void turnOnLED(int ledPin) {
	digitalWrite(ledPin, HIGH);
}

void turnOffLED(int ledPin) {
	digitalWrite(ledPin, LOW);
}

void blinkLed(int ledPin) {
  unsigned long currentTime = millis();

  if (currentTime - beforeTime >= interval) {
    beforeTime = currentTime;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(ledPin, ledState);
  }
}