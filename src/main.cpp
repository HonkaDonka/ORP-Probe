#include <Arduino.h>

#define ORPPROBE A0

long total = 0;               // Running total of readings
int times = 0;                // Number of readings
float average = 0;            // Calculated average value

float vOffset = 0.0;          // Voltage offset

unsigned long previousMillis = 0;
const long interval = 1000;   // Interval in milliseconds (1 second)

void setup() {
  Serial.begin(9600);           // Initialize serial communication
}

void loop() {

  // Read the analog input
  int sensorValue = analogRead(ORPPROBE);

  // Add the reading to the total and increment the times variable
  total += sensorValue;
  times++;

  unsigned long currentMillis = millis();
  // Check if the interval has passed
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the average was printed
    previousMillis = currentMillis;
    // Calculate the average
    average = total / times;
    // Print the average to the serial monitor
    float avgV = average * (5.0 / 1023.0) + vOffset;

    Serial.print("Average Voltage: ");
    Serial.println(avgV, 2);
    // Reset the total and times variables

    float calcPPM = 10164 * (sqrt(avgV - 0.38) + 0.0048);

    Serial.print("Calculated PPM: ");
    Serial.println(calcPPM);


    total = 0;
    times = 0;
  }
}
