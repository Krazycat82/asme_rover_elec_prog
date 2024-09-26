#include <SoftwareSerial.h>

SoftwareSerial hc12(11, 10); // RX, TX

void setup() {
  Serial.begin(9600);  // Start Serial for Monitor
  hc12.begin(9600);    // Start HC-12 communication
}

void loop() {
  // Check if there is any data in the Serial buffer
  if (Serial.available()) {
    String inputString = Serial.readStringUntil('\n'); // Read input until newline
    hc12.println(inputString); // Send the input over HC-12
    Serial.print("Sent: ");     // Print sent data to Serial Monitor
    Serial.println(inputString);
  }
}

