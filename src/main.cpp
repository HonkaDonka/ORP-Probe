#include <Arduino.h>

#define ORPPROBE A0
#define RLEDPIN 2
#define GLEDPIN 3
#define BLEDPIN 4

long total = 0;               // Running total of readings
int times = 0;                // Number of readings
float average = 0;            // Calculated average value

float vOffset = 0.0;          // Voltage offset

unsigned long previousMillis = 0;
const long interval = 1000;   // Interval in milliseconds (1 second)

void setup() {
  Serial.begin(9600);         // Initialize serial communication

  pinMode(RLEDPIN, OUTPUT);
  pinMode(GLEDPIN, OUTPUT);
  pinMode(BLEDPIN, OUTPUT);
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
    Serial.println(avgV);
    // Reset the total and times variables

    int calcPPM = 10164 * (sqrt(avgV - 0.38) + 0.0048) - 400;

    // Adjust based on the specified PPM range
    Serial.print("Calculated PPM: ");
    if (!(calcPPM == calcPPM)) {    // Checks if the value is NaN
      calcPPM = 0;
    } else if (calcPPM > 5000) {
      calcPPM = 5000;
    }
    
    Serial.println(calcPPM);

    // Set the LED color based on the PPM value
    if (0 < calcPPM && calcPPM <= 2000) {
      digitalWrite(RLEDPIN, HIGH);
      digitalWrite(GLEDPIN, LOW);
      digitalWrite(BLEDPIN, LOW);
    }
    if (2000 < calcPPM && calcPPM <= 4000) {
      digitalWrite(GLEDPIN, HIGH);
      digitalWrite(RLEDPIN, LOW);
      digitalWrite(BLEDPIN, LOW);
    }
    if (4000 < calcPPM && calcPPM <= 5000) {
      digitalWrite(BLEDPIN, HIGH);
      digitalWrite(RLEDPIN, LOW);
      digitalWrite(GLEDPIN, LOW);
    }

    total = 0;
    times = 0;
  }
}
