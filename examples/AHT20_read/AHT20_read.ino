#include <Wire.h>
#include <AHT20.h>

void setup() {
  Serial.begin(115200);

  Wire.begin();

  if (!aht.begin()) { // Setup AHT20
    Serial.println("AHT20 setup error");
  }
}

void loop() {
  float t = -999, h = -999;
  if (aht.read(&t, &h)) {
    Serial.print("Temperature: ");
    Serial.print(t, 2);
    Serial.print(" *C\tHumidity: ");
    Serial.print(h, 2);
    Serial.print(" %RH");
    Serial.println();
  } else {
    Serial.println("AHT20 read error");
  }
  delay(500);
}
