#include <TinyGPSPlus.h>
#include "MPU9250.h"

TinyGPSPlus gps;
MPU9250 IMU(Wire, 0x68);
int status;

void setup() {
 Serial.begin(115200);
 Serial2.begin(9600);
 pinMode(LED_BUILTIN, OUTPUT);
 delay(3000);

 status = IMU.begin();
 if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while (1) {}
 }
}

void loop() {
 IMU.readSensor();

 Serial.print(IMU.getAccelX_mss(), 6);
 Serial.print("\t");
 Serial.print(IMU.getAccelY_mss(), 6);
 Serial.print("\t");
 Serial.print(IMU.getAccelZ_mss(), 6);
 Serial.print("\t");
 Serial.print(IMU.getGyroX_rads(), 6);
 Serial.print("\t");
 Serial.print(IMU.getGyroY_rads(), 6);
 Serial.print("\t");
 Serial.print(IMU.getGyroZ_rads(), 6);
 Serial.print("\t");
 Serial.print(IMU.getMagX_uT(), 6);
 Serial.print("\t");
 Serial.print(IMU.getMagY_uT(), 6);
 Serial.print("\t");
 Serial.print(IMU.getMagZ_uT(), 6);
 Serial.print("\t");
 Serial.println(IMU.getTemperature_C(), 6);

 while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);  
      displayInfo();
 if (millis() > 5000 && gps.charsProcessed() < 10)
 {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
 }
}

void displayInfo()
{
 Serial.print(F("Location: "));
 if (gps.location.isValid()){
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print("Lng: ");
    Serial.print(gps.location.lng(), 6);
    Serial.println();
 }  
 else
 {
    Serial.print(F("INVALID"));
 }
}