#include <DHT.h>

// Pin definitions
#define RED_PIN 3
#define GREEN_PIN 4
#define WHITE_PIN 5
#define MOTOR_IN1 6
#define MOTOR_IN2 7
#define RELAY_PIN 2
#define DHT_PIN A0
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
String command = "";

void setup() {
  Serial.begin(9600);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(WHITE_PIN, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  dht.begin();

  // Turn everything off initially
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(WHITE_PIN, LOW);
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "RED_ON") {
      digitalWrite(RED_PIN, HIGH);
    } else if (command == "RED_OFF") {
      digitalWrite(RED_PIN, LOW);
    } else if (command == "GREEN_ON") {
      digitalWrite(GREEN_PIN, HIGH);
    } else if (command == "GREEN_OFF") {
      digitalWrite(GREEN_PIN, LOW);
    } else if (command == "WHITE_ON") {
      digitalWrite(WHITE_PIN, HIGH);
    } else if (command == "WHITE_OFF") {
      digitalWrite(WHITE_PIN, LOW);
    } else if (command == "ALL_LIGHTS_ON") {
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(WHITE_PIN, HIGH);
    } else if (command == "ALL_LIGHTS_OFF") {
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(WHITE_PIN, LOW);
    } else if (command == "POWER_RELAY") {
      digitalWrite(RELAY_PIN, HIGH);
    } else if (command == "POWER_OFF_RELAY") {
      digitalWrite(RELAY_PIN, LOW);
    } else if (command == "GET_TEMP") {
      float temp = dht.readTemperature();
      if (isnan(temp)) {
        Serial.println("ERROR");
      } else {
        Serial.println(temp);
      }
    } else if (command == "gaming_mode") {
      // Example: turn on fan/motor for gaming mode
      digitalWrite(MOTOR_IN1, HIGH);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(WHITE_PIN, HIGH);  // Turn on white light
    } else if (command == "SLEEP_MODE") {
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(WHITE_PIN, LOW);
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(RELAY_PIN, LOW);
    } else if (command == "kill") {
      // Emergency mode for high temperature
      digitalWrite(RELAY_PIN, HIGH); // e.g., turn on buzzer or alert system
    }

    // Optional: send acknowledgment (you can remove this if not needed)
    // Serial.println("ACK");
  }
}
