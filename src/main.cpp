#include <Arduino.h>

#define WORKINGPROBE A0

void setup() {
  Serial.begin(9600);
  // analogReference(EXTERNAL);
  pinMode(WORKINGPROBE, INPUT);
} 

void loop() {
  Serial.println(analogRead(WORKINGPROBE) - 512);
  // Serial.println("Voltage: " + String(analogRead(WORKINGPROBE) * (1.1 / 1023.0)) + "V");
  delay(500);
}
