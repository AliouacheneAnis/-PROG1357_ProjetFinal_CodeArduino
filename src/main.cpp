#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "Ste-adele 2";
const char* password = "abcd1234";

// Replace with the IP address or hostname of your Java server
const char* serverUrl = "http://10.0.0.88:8080/data";

//get random temperature
int getWaterLevel() {
  // replace with your function to get the temperature data from sensor
  // this is just a dummy implementation that returns a random value between 20 and 30
  return random(0, 10);
}


void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi network with SSID and password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int WaterLevel = getWaterLevel(); // replace with your function to get the temperature data

  // Send temperature data to Java server over HTTP POST request
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
  String requestBody = "{\"data\": " + String(WaterLevel) + "}";
  http.POST(requestBody);
  Serial.println(requestBody);
  http.end();

  delay(5000); // wait 5 seconds before sending the next temperature data
}