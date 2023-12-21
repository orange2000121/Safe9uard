/*
  Complete project details: https://RandomNerdTutorials.com/esp32-https-requests/
  Based on the BasicHTTPSClient.ino example found at Examples > BasicHttpsClient
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "AIRLAB";
const char* password = "76497649";

void setup() {
  Serial.begin(115200);
  Serial.println();
  // Initialize Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

int httpsPost(float speed, bool emergency, float latitude, float longitude) {
  WiFiClientSecure* client = new WiFiClientSecure;
  int httpCode;
  if (client) {
    // set secure client without certificate
    client->setInsecure();
    //create an HTTPClient instance
    HTTPClient https;

    //Initializing an HTTPS communication using the secure client
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, "https://ardianbunawan100.wixsite.com/safe9uard/_functions-dev/NumberOfPeople")) {  // HTTPS
      Serial.print("[HTTPS] POST...\n");
      // start connection and send HTTP header
      String data = "{\"speed\":" + String(speed) + ",\"emergency\":" + (emergency ? "true" : "false")+ ",\"lat\":" + String(latitude) + ",\"lon\":" + String(longitude) + "}";
      httpCode = https.POST(data);
      Serial.print("http code");
      Serial.println(httpCode);
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          // print server response payload
          String payload = https.getString();
          Serial.print("payload: ");
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    }
  } else {
    Serial.printf("[HTTPS] Unable to connect\n");
    return false;
  }
  return httpCode;
}
void loop() {
  httpsPost(14, true, 0, 0);
  Serial.println();
  Serial.println("Waiting 2min before the next round...");
  delay(5000);
}