#include <SPI.h>

#define CHIPSELECT 10 // ss

void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(CHIPSELECT, OUTPUT);
  digitalWrite(CHIPSELECT, HIGH); // deselect the voltage sensor
}

void loop() {
  byte voltage = readVoltageSensor();
  Serial.println(voltage);
  delay(1000);
}

byte readVoltageSensor() {
  digitalWrite(CHIPSELECT, LOW); // select the voltage sensor
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0)); // set the SPI settings, 14 MHz, MSB first, SPI mode 0
  byte data = SPI.transfer(0xFF); // send a dummy byte to read the data
  SPI.endTransaction();
  digitalWrite(CHIPSELECT, HIGH); // deselect the voltage sensor
  return data;
}