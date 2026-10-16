
#include <Arduino.h>
#include <math.h>

#include "Config.h"
#include "FanControl.h"
#include "Environment.h"

bool fanState = false;

void setupFan() {
  pinMode(FAN_PIN, OUTPUT);

  digitalWrite(FAN_PIN, LOW);

  Serial.println("MODULE QUAT SAN SANG");
}

void updateFan() {
  // LAY NHIET DO TU MODULE NGUOI 2
  float temperature = getTemperature();

  // MAT DU LIEU THI TAT QUAT
  if (isnan(temperature)) {
    fanState = false;
    digitalWrite(FAN_PIN, LOW);
    return;
  }

  if (temperature >= FAN_ON_TEMP) {
    fanState = true;
  }
  else if (temperature <= FAN_OFF_TEMP) {
    fanState = false;
  }

  digitalWrite(
    FAN_PIN,
    fanState ? HIGH : LOW
  );
}
