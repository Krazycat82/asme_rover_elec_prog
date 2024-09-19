const int motorPin = 13;   // Motor connected to pin 13
#define PWM 12
#define DIR 2
int motorSpeed = 0;        // Variable to store motor speed (0-255)

void setup() {
  // Set motor pin as output
  pinMode(motorPin, OUTPUT);
  digitalWrite(PWM, LOW);
  pinMode(DIR, OUTPUT);
  digitalWrite(DIR, LOW);
  
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  Serial.println("Enter motor speed (0-255) or commands (F: forward, R: reverse, S: stop):");
}

int PWM_value;
bool direction;

void loop() {
  // Check if data is available in the serial buffer
  #define delayTime 100
  if (Serial.available()) {
    // Read the incoming data
    char command = Serial.read();
    
    // Handle speed control if numbers are entered
    if (command >= '0' && command <= '9') {
      motorSpeed = (motorSpeed * 10) + (command - '0');  // Build the number from digits
    }

    // Handle commands
    if (command == 'F' || command == 'f') {
      // Forward direction
      Serial.println("Motor running forward");
      direction = 0;
      digitalWrite(DIR, direction);
      analogWrite(PWM, motorSpeed);  // Set speed
      motorSpeed = 0;  // Reset speed input
    } else if (command == 'R' || command == 'r') {
      // Reverse direction (invert the control logic if using an H-bridge)
      Serial.println("Motor running reverse");
      direction = 1;
      digitalWrite(DIR, direction);
      analogWrite(PWM, motorSpeed);  // This is just for an example. In reality, you'd toggle direction pins on a motor driver.
      motorSpeed = 0;  // Reset speed input
    } else if (command == 'S' || command == 's') {
      // Stop motor
      Serial.println("Motor stopped");
      analogWrite(PWM, 0);  // Turn off the motor
      motorSpeed = 0;  // Reset speed input
    }
  }
}