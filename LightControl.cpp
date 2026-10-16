
#include <Arduino.h>

#include "Config.h"
#include "LightControl.h"

// NGUONG ANH SANG
const int DARK_THRESHOLD = 1800;
const int LIGHT_THRESHOLD = 2200;

// DOI THANH FALSE NEU CAM BIEN DAO CHIEU
const bool HIGH_IS_BRIGHT = true;

bool lightState = false;

unsigned long lastLightRead = 0;

void setupLight() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  digitalWrite(LED_PIN, LOW);

  Serial.println("MODULE ANH SANG SAN SANG");
}

void updateLight() {
  if (millis() - lastLightRead < 200) {
    return;
  }

  lastLightRead = millis();

  int lightValue = analogRead(LDR_PIN);

  if (HIGH_IS_BRIGHT) {
    if (lightValue < DARK_THRESHOLD) {
      lightState = true;
    }
    else if (lightValue > LIGHT_THRESHOLD) {
      lightState = false;
    }
  }
  else {
    if (lightValue > LIGHT_THRESHOLD) {
      lightState = true;
    }
    else if (lightValue < DARK_THRESHOLD) {
      lightState = false;
    }
  }

  digitalWrite(
    LED_PIN,
    lightState ? HIGH : LOW
  );
}
