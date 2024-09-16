#include "PPMEncoder.h"     // I swear to god if I have to write my own PPM library
#include <SPI.h>

#define LEFT_PPM_PIN 5    // pins chosen for Arduino Uno Rev3, verify output pins for Mega
#define RIGHT_PPM_PIN 6

// global variables... yes it is technically bad practice fuck off
float left_speed;
float right_speed;

void setup() {
  // put your setup code here, to run once:
  ppmEncoder.begin(LEFT_PPM_PIN);
  ppmEncoder.begin(RIGHT_PPM_PIN);


}

void loop() {
  // put your main code here, to run repeatedly:
  get_IV();
  get_pot_speeds();
  read_message();
  check_nominal();      // function needs to be called before any operating parameters are changed

  set_speeds();
}

void get_message()    // may not remain a void function, DARREN finalize radio type
{

}

void get_pot_speeds()   // function for testing PPM, DO NOT COMPILE FOR ROBOT
{
  left_speed = analogRead(A0) / 1024;     // noise floor implementation may be necessary, check ADC bit count (N) divide by 2^N
  right_speed = analogRead(A1) / 1024;

  return;
}

void get_IV()   // check voltages and currents via SPI
{
  
  return;
}

void check_nominal()    // self-check for nominal operating conditions, else send warning, error, or shutdown
{
  
  return;
}

void set_speeds()
{

  return;
}