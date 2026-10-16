#include "DoorControl.h"
#include "LightControl.h"
#include "FanControl.h"
#include "Environment.h"

void setup() {
  Serial.begin(115200);

  // Khoi tao cac module
  setupDoor();
  setupLight();
  setupEnvironment();
  setupFan();

  Serial.println("SMART HOME - BRANCH 1 READY");
}

void loop() {
  // Xu ly mo cua bang mat khau
  updateDoor();

  // Dieu khien den tu dong
  updateLight();

  // Cap nhat nhiet do, do am
  updateEnvironment();

  // Dieu khien quat theo nhiet do
  updateFan();
}