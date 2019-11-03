#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include "SSD1306Wire.h"
#include <ArduinoJson.h>

ESP8266WebServer server(80); //creating the server at port 80
ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
SSD1306Wire display(0x3c, D1, D2);

void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();

void setup() {
  Serial.begin(115200);
  wifiMulti.addAP("TELUS1484", "hf7nhddxc6");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  String ipaddr = WiFi.localIP().toString();
  
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, ipaddr);
  display.display();
  server.on("/post", getTemp);

  //configuring the server wherein you configure your url and function name, you can also mention your method(GET,POST..) if u want i.e server.on("/yourURL", method,function);

  server.begin();
}

void getTemp() {
  if (server.hasArg("plain")== false){ //Check if body received
    server.send(200, "text/plain", "Body not received");
    Serial.println("Body not received");
    return;
  }
  
  String message = "Body received:\n";
  message += server.arg("plain");
  message += "\n";
  server.send(200, "text/plain", message);
  Serial.println(message);
  String temp = server.arg("plain");

  Serial.println(temp);
      
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawHorizontalLine(52, 13, 25);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0, "CPU");
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, temp);
  display.display();
}

void loop() {
  server.handleClient(); //this is required for handling the incoming requests
}
