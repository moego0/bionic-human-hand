#include <Servo.h>

// EMG sensor pin
const int emgPin = A0; // EMG sensor output to A0

// Servo control pins
const int servoPins[5] = {3, 5, 6, 9, 10}; // Connect each servo to these digital pins

// EMG activation threshold
const int threshold = 200; // Adjust this based on testing

// Create 5 Servo objects
Servo servos[5];

void setup() {
  // Attach each servo to its respective pin
  for (int i = 0; i < 5; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0); // Start with all servos at 0 degrees
  }

  // Begin serial communication for debugging
  Serial.begin(9600);
  Serial.println("EMG Servo Control Initialized");
}

void loop() {
  // Read EMG signal
  int emgValue = analogRead(emgPin);
  Serial.print("EMG Value: ");
  Serial.println(emgValue);

  if (emgValue > threshold) {
    // Move all servos to 90 degrees
    for (int i = 0; i < 5; i++) {
      servos[i].write(90);
    }
    Serial.println("EMG above threshold → Servos moved to 90°");
  } else {
    // Move all servos to 0 degrees
    for (int i = 0; i < 5; i++) {
      servos[i].write(0);
    }
    Serial.println("EMG below threshold → Servos moved to 0°");
  }

  delay(100); // Short delay for stability
}
