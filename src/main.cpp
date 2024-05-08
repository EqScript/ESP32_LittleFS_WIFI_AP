#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <FS.h>
#include "LittleFS_func.h"

const char* ssid = "Blue Systems AP";
const char* password = "88888888";

const bool FORMAT_LITTLEFS_IF_FAILED = true;

AsyncWebServer server(80);

// Define the GPIO pin for the LED
const int LED_PIN = 8;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("[*] System boot...");
  delay(1000);
   Serial.println("[*] LittleFS init...");
  // Initialize LittleFS
  if (!LittleFS.begin()) {
    Serial.print("[!] LittleFS volume not found, formatting...");
    if (FORMAT_LITTLEFS_IF_FAILED) {
      LittleFS.format();
      LittleFS.begin();
    } else {
      Serial.print("[!] LittleFS format disabled, exiting FS setup...");
    }
  } else {
    Serial.print("[*] LittleFS started!");
  }
  Serial.println("[*] Starting AP...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress address = WiFi.softAPIP();

  Serial.print("[*] Access Point Started, SSID: ");
  Serial.println(ssid);
  Serial.print("[*] IP Address: ");
  Serial.println(address);

  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
   Serial.println("[*] Starting server...");
  // Define the route to handle LED control requests
  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request) {
    String state = request->getParam("state")->value();
    if (state == "on") {
      digitalWrite(LED_PIN, HIGH);
      request->send(200, "text/plain", "LED turned on");
    } else if (state == "off") {
      digitalWrite(LED_PIN, LOW);
      request->send(200, "text/plain", "LED turned off");
    } else {
      request->send(400, "text/plain", "Invalid LED state");
    }
  });

  // Serve index.html for root path
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/html/index.html", "text/html");
  });

  // Optionally map static files under /html/ path
  server.serveStatic("/", LittleFS, "/html/");

  server.begin();
  Serial.println("[*] Web server started!");
}

void loop() {}