// SmartHome: mo phong co ban tren Tinkercad (Arduino Uno).
// TMP36 = nhiet do; bien tro = do am gia lap; cong tac = lua gia lap.
// A0: TMP36, A1: do am, A2: gas, D2: lua, D8: coi.
const byte TEMP_PIN = A0, HUMIDITY_PIN = A1, GAS_PIN = A2;
const byte FLAME_PIN = 2, BUZZER_PIN = 8;
const int GAS_THRESHOLD = 600; // Gia tri ADC, khong phai ppm.
float temperature, humidity;

void setupEnvironment() {
  pinMode(FLAME_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}
float getTemperature() { return temperature; }
float getHumidity() { return humidity; }

void updateEnvironment() {
  temperature = (analogRead(TEMP_PIN) * 5.0 / 1023.0 - 0.5) * 100.0;
  humidity = analogRead(HUMIDITY_PIN) * 100.0 / 1023.0;
  int gas = analogRead(GAS_PIN);
  bool fire = digitalRead(FLAME_PIN) == LOW;
  bool gasAlarm = gas >= GAS_THRESHOLD;
  bool alarm = fire || gasAlarm;
  digitalWrite(LED_BUILTIN, alarm ? HIGH : LOW);
  if (alarm) tone(BUZZER_PIN, 2000);
  else noTone(BUZZER_PIN);

  Serial.print("Nhiet do: "); Serial.print(getTemperature(), 1);
  Serial.print(" C | Do am (gia lap): "); Serial.print(getHumidity(), 1);
  Serial.print(" % | Gas ADC: "); Serial.print(gas);
  Serial.print(" | Lua: "); Serial.print(fire ? "CO" : "KHONG");
  Serial.print(" | Trang thai: ");
  if (fire) Serial.print("CANH BAO CHAY ");
  if (gasAlarm) Serial.print("CANH BAO GAS");
  if (!alarm) Serial.print("AN TOAN");
  Serial.println();
}
void setup() {
  Serial.begin(115200);
  setupEnvironment();
}
void loop() {
  updateEnvironment();
  delay(500);
}
