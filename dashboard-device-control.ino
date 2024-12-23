#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>

const char* ssid = "Purna";
const char* password = "Galla4446";
String apiRoute="https://mlew-api-iot.onrender.com/get-devices";

bool isSent=false;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to WiFi");
}

void checkDeviceState(String api) {
  DynamicJsonDocument doc(1024);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(api);
    int responseCode = http.GET();
    
    if (responseCode > 0) {
      String response = http.getString();
      //Serial.println("Response: " + response);

      // Deserialize the JSON array
      DeserializationError error = deserializeJson(doc, response);
      if (error) {
        Serial.print("Deserialization failed: ");
        Serial.println(error.f_str());
        return;
      }

      // Access the array
      JsonArray array = doc.as<JsonArray>();
      for (JsonObject obj : array) {
        String deviceId = obj["device_id"];
        String state = obj["state"];

        if (deviceId == "1") { 
          Serial.print("Device State: ");
          Serial.println(state);

          // Perform action based on state
          if (state == "on") {
            Serial.println("Device 1 is ON");
          } else if (state == "off") {
            Serial.println("Device 1 is OFF");
          }
          break; // Exit the loop once device_id 1 is found
        } else if (deviceId == "2") { 
          Serial.print("Device State: ");
          Serial.println(state);

          // Perform action based on state
          if (state == "on") {
            Serial.println("Device 2 is ON");
          } else if (state == "off") {
            Serial.println("Device 2 is OFF");
          }
          break; // Exit the loop once device_id 1 is found
        } else if (deviceId == "3") { 
          Serial.print("Device State: ");
          Serial.println(state);

          // Perform action based on state
          if (state == "on") {
            Serial.println("Device 3 is ON");
          } else if (state == "off") {
            Serial.println("Device 3 is OFF");
          }
          break; // Exit the loop once device_id 1 is found
        }
      }
    } else {
      Serial.print("HTTP GET failed, error: ");
      Serial.println(responseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

void loop() { 
    checkDeviceState(apiRoute);
    delay(5000);
}