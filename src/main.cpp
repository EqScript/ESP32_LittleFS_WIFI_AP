#include <WiFi.h>
#include <AsyncTCP.h> // Provides functionalities for asynchronous TCP connections
#include <ESPAsyncWebServer.h>
#include <LittleFS.h> // For storing HTML/CSS files
#include <FS.h>
#include "LittleFS_func.h"

const char* ssid = "Blue Systems AP";
const char* password = "88888888";

const bool FORMAT_LITTLEFS_IF_FAILED = true;

AsyncWebServer server(80); // Declare server object globally

void setup() {
  Serial.begin(115200);

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

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress address = WiFi.softAPIP();

  Serial.print("[*] Access Point Started, SSID: ");
  Serial.println(ssid);
  Serial.print("[*] IP Address: ");
  Serial.println(address);

  // Define HTML content with blue background and white header
  const char index_html[] PROGMEM = R"(<!DOCTYPE html>
<html>
  <head>
    <title>Blue Systems</title>
    <style>
      /* Set the margin and padding of the body to 0 */
      body {
        margin: 0;
        padding: 0;
        /* Set the background to a linear gradient from top to bottom */
        background-image: linear-gradient(to bottom, #002, #006, #007);
        height: 100vh; /* Set the height of the body to 100% of the viewport height */
      }

      /* Set the margin and padding of the header to 0 */
      header {
        margin: 0;
        padding: 0;
        /* Set the height of the header to 100% of the viewport height */
        height: 100vh;
        background-color: transparent; /* Set the background color of the header to transparent */
        display: flex; /* Use flexbox to center the content */
        flex-direction: column;
        justify-content: center;
        align-items: center;
      }

      h1 {
        color: #ddd;
        font-family: 'Eurostyle', sans-serif;
        font-size: 64px;
        text-shadow: 12px 10px 10px #000;
        margin: 0;
      }

      h3 {
        color: #ddd;
        font-family: 'century-gotic', sans-serif;
        font-size: 36px;
        text-shadow: 12px 10px 10px #000;
        margin: 20px 0 0 0;
      }
    </style>
  </head>
  <body>
    <header>
      <h1><b>Blue Systems</b></h1>
      <h3><em>ESP32-WROOM-32U Board</em></h3>
    </header>
  </body>
</html>)";

  // Serve index.html for root path
    server.on("/", HTTP_GET, [index_html](AsyncWebServerRequest *request) {
    request->send(200, "text/html", index_html);
    });

  // Optionally map static files under /html/ path
  server.serveStatic("/", LittleFS, "/html/");

  // Start the web server
  server.begin();
  Serial.println("[*] Web server started!");
}

void loop() {
  // ... (your other code here) ...
}
