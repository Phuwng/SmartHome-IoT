
#include <Arduino.h>
#include <Keypad.h>
#include <ESP32Servo.h>

#include "Config.h"
#include "DoorControl.h"

// KHAI BAO KEYPAD
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {
  ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN
};

byte colPins[COLS] = {
  COL1_PIN, COL2_PIN, COL3_PIN, COL4_PIN
};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS
);

Servo doorServo;

// MAT KHAU MO CUA
const String PASSWORD = "1234";

String enteredPassword = "";

const int DOOR_CLOSE_ANGLE = 0;
const int DOOR_OPEN_ANGLE = 90;

const unsigned long DOOR_OPEN_TIME = 5000;
const unsigned long LOCK_TIME = 30000;

bool doorIsOpen = false;
unsigned long doorOpenAt = 0;

int wrongAttempts = 0;
bool isLocked = false;
unsigned long lockedAt = 0;

// MO CUA
void openDoor() {
  doorServo.write(DOOR_OPEN_ANGLE);
  doorIsOpen = true;
  doorOpenAt = millis();

  Serial.println("MAT KHAU DUNG - CUA DA MO");
}

// DONG CUA
void closeDoor() {
  doorServo.write(DOOR_CLOSE_ANGLE);
  doorIsOpen = false;

  Serial.println("CUA DA DONG");
}

// KHOI TAO
void setupDoor() {
  doorServo.setPeriodHertz(50);
  doorServo.attach(SERVO_PIN, 500, 2400);

  closeDoor();

  Serial.println("MODULE CUA SAN SANG");
}

// XU LY KEYPAD
void updateDoor() {
  unsigned long now = millis();

  // TU DONG DONG CUA SAU 5 GIAY
  if (doorIsOpen &&
      now - doorOpenAt >= DOOR_OPEN_TIME) {
    closeDoor();
  }

  // KHOA BAN PHIM SAU 3 LAN NHAP SAI
  if (isLocked) {
    if (now - lockedAt < LOCK_TIME) {
      return;
    }

    isLocked = false;
    wrongAttempts = 0;

    Serial.println("KEYPAD DA MO KHOA");
  }

  char key = keypad.getKey();

  if (!key) return;

  // XOA MAT KHAU
  if (key == '*') {
    enteredPassword = "";
    Serial.println("DA XOA MAT KHAU");
    return;
  }

  // XAC NHAN MAT KHAU
  if (key == '#') {
    if (enteredPassword == PASSWORD) {
      wrongAttempts = 0;
      openDoor();
    } else {
      wrongAttempts++;

      Serial.println("SAI MAT KHAU");

      if (wrongAttempts >= 3) {
        isLocked = true;
        lockedAt = now;

        Serial.println("KHOA KEYPAD 30 GIAY");
      }
    }

    enteredPassword = "";
    return;
  }

  // NHAP CAC CHU SO
  if (key >= '0' && key <= '9') {
    if (enteredPassword.length() < 8) {
      enteredPassword += key;

      Serial.println("DA NHAP MOT SO");
    }
  }
}
