#include <Arduino.h>
#include <ESP32Servo.h>

const int PINS[8] = {13, 14, 16, 17, 18, 19, 23, 25};
Servo servos[8];
const int LIGHT_PINS[8] = {4, 5, 21, 22, 26, 27, 32, 33};

void setLights(bool on) {
  for (int i = 0; i < 8; i++) digitalWrite(LIGHT_PINS[i], on ? HIGH : LOW);
  Serial.printf("Luces: %s\n", on ? "ON" : "OFF");
}

// score: 1.0 = orden, 0.0 = caos
void applyScore(float harmony) {
  Serial.printf("Score: %.1f\n", harmony);
  for (int i = 0; i < 8; i++) {
    float chaos = (1.0 - harmony) * random(-60, 61);
    int angle = constrain(60 + (int)chaos, 0, 180);
    servos[i].write(angle);
    Serial.printf("  motor %d -> %d grados\n", i, angle);
  }
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
  for (int i = 0; i < 8; i++) {
    servos[i].setPeriodHertz(50);
    servos[i].attach(PINS[i], 500, 2400);
    servos[i].write(90);
    pinMode(LIGHT_PINS[i], OUTPUT);
  }
  setLights(true);
}

void loop() {
  applyScore(1.0);
  delay(3000);
  applyScore(0.5);
  delay(3000);
  applyScore(0.0);
  delay(3000);
}