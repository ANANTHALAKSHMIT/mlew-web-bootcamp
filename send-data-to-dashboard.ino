#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char* ssid = "Veera Lakshmi";
const char* password = "talari12365";
String apiRoute="https://the-achievers-api.onrender.com/store?label=";
String alertRoute=https://the-achievers-api.onrender.com/alert?type=";

bool isSent=false;
DHT dht(23,DHT11);

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
  dht.begin();
}

void sendDataToDashboard(String api){
  if(WiFi.status()==WL_CONNECTED){
    HTTPClient http;
    http.begin(api);
    int responseCode=http.GET();
    if(responseCode>0){
      String response=http.getString();
      Serial.println(response);
      http.end();
    }
  }
}
void loop() {
    float h=dht.readHumidity();
    float t=dht.readTemperature();

    if(isnan(h)||isnan(t)) {
      Serial.println("DHT Error");
      return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(",Temperature: ");
    Serial.println(t);

    sendDataToDashboard(apiRoute+"Humidity"+"&value="+String(h));
    delay(2000);
    sendDataToDashboard(apiRoute+"Temperature"+"&value="+String(t));
    delay(2000);    

    if(h>80 && !isSent){
      sendDataToDashboard(alertRoute+"danger"+"&message=Humidity Out of Range");
      isSent=true;
    } 
    if(h<80){
      isSent=false;
    }
}
