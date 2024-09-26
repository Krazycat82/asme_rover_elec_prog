#include <SoftwareSerial.h>

SoftwareSerial hc12(11, 10); // RX, TX

void setup() {
  Serial.begin(9600);  // Start Serial for Monitor
  hc12.begin(9600);    // Start HC-12 communication
}

void loop() {
  // Check if there is any data available from HC-12
  if (hc12.available()) {
    String receivedString = hc12.readStringUntil('\n'); // Read until newline
    Serial.print("Received: "); // Print received data to Serial Monitor
    Serial.println(receivedString);
  }
}