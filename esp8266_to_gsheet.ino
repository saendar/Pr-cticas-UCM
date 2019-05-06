/*Credits to Akshaya Niraula and Sujay Phadke (electronicsguy) and Varul Jain for all their work,
this code is a mix of theirs, Kiono 2019 */
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "HTTPSRedirect.h"
#include "DebugMacros.h"

#define DHTPIN D4
DHT dht(DHTPIN, DHT11);

const char* ssid = "iPhone de Enrique";
const char* password = "diablodos2";
const char* host = "script.google.com";
const char *GScriptId = "AKfycbya6OVdGXgTl6YezpT1dVGN6JUkUwOIiOJoHI9rBzI-U0hZZmI";
const int httpsPort = 443;
const char* fingerprint = "F5:19:59:D6:6D:50:BB:DF:5E:EC:C0:9D:E7:21:10:F6:C6:03:45:B5";



HTTPSRedirect* client = nullptr;

void setup() {
  Serial.begin(115200);
  Serial.flush();
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  
 }
void loop() {
	//Set up of the sensor variables
  float humidsoil = analogRead(A0);
  float temp = dht.readHumidity();
  float humidair = dht.readTemperature();
  
  //conversion of the sensor readings into strings to be post
  String url = String("/macros/s/") + GScriptId + "/exec?parameter01=" + String(humidsoil, 1) + "&parameter02=" + String(temp, 1) + "&parameter03=" + String(humidair, 1);
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  
  Serial.print("Connecting to ");
  Serial.println(host);

  // Try to connect for a maximum of 5 times
  bool flag = false;
  for (int i=0; i<5; i++){
    int retval = client->connect(host, httpsPort);
    if (retval == 1) {
       flag = true;
       break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }

  if (!flag){
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    return;
  }
  client->GET(url, host);
  delete client;
  client = nullptr;
  delay(5000);
}
