#include <Arduino.h>

#define WORKINGPROBE A0

void setup() {
  Serial.begin(9600);

  pinMode(WORKINGPROBE, INPUT);
}

void loop() {
  Serial.println(analogRead(WORKINGPROBE));
  Serial.println("Voltage: " + String(analogRead(WORKINGPROBE) * (5.0 / 1023.0)) + "V");
  delay(1000);
}
