
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* writeAPIKey = "O2OTIQ91IPX0G5RU";
const char* universityID = "12324274";

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
unsigned long lastUploadTime = 0;
const unsigned long uploadInterval = 20000;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("=== ESP32 ThingSpeak Project ===");
  Serial.print("University ID: ");
  Serial.println(universityID);

  Serial.println("Starting DHT22 sensor...");
  dht.begin();
  delay(2000);
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting sensor readings...");
}
void loop() {
  Serial.println();
  Serial.println("Loop is running");

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("ERROR: DHT22 reading failed!");
    Serial.println("Check VCC, GND, and DATA -> GPIO 15.");
  } else {
    Serial.print("University ID: ");
    Serial.println(universityID);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Wi-Fi disconnected. Reconnecting...");
      WiFi.begin(ssid, password);
    } else {
      Serial.println("Sending data to ThingSpeak...");

      HTTPClient http;

      String url = "http://api.thingspeak.com/update?api_key=";
      url += writeAPIKey;
      url += "&field1=" + String(temperature, 1);
      url += "&field2=" + String(humidity, 1);
      url += "&field3=" + String(universityID);

      http.begin(url);
      http.setTimeout(10000);

      int responseCode = http.GET();

      Serial.print("HTTP Response Code: ");
      Serial.println(responseCode);

      if (responseCode > 0) {
        String response = http.getString();
        response.trim();

        Serial.print("ThingSpeak Entry ID: ");
        Serial.println(response);

        if (response.toInt() > 0) {
          Serial.println("SUCCESS: Data uploaded!");
        } else {
          Serial.println("FAILED: ThingSpeak returned 0.");
          Serial.println("Check API key and update interval.");
        }
      } else {
        Serial.println("HTTP request failed.");
        Serial.println(http.errorToString(responseCode));
      }

      http.end();
    }
  }

  Serial.println("Waiting 20 seconds...");
  delay(uploadInterval);
}
