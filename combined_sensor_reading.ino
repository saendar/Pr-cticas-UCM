
// Robo India Tutorial 
// Simple code upload the tempeature and humidity data using thingspeak.com
// Hardware: NodeMCU,DHT11

#include <dht.h>
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

dht DHT;
#define DHT22_PIN D5
#define DATA_PIN D3          
#define SENSOR_RESOLUTION 12
#define SENSOR_INDEX 0

OneWire oneWire(DATA_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress sensorDeviceAddress;

String apiKey = "HN4EB3YAOJQY24TD";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "iPhone de Enrique";     // replace with your wifi ssid and wpa2 key
const char *pass =  "diablodos2";
const char* server = "api.thingspeak.com";
const double VCC = 3.3;             // NodeMCU on board 3.3v vcc
const double R2 = 10000;            // 10k ohm series resistor
const double adc_resolution = 1023; // 10-bit adc
const double A = 0.001129148;   // thermistor equation parameters
const double B = 0.000234125;
const double C = 0.0000000876741; 

int u=0;
float Lectura_Analogica=0;

WiFiClient client;
 
void setup() 
{
       Serial.begin(9600);
       delay(10);
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");

        sensors.begin();
        sensors.getAddress(sensorDeviceAddress, 0);
        sensors.setResolution(sensorDeviceAddress, SENSOR_RESOLUTION);
 
}
 
void loop() 
{
  
      sensors.requestTemperatures();
      float temperatureInCelsius = sensors.getTempCByIndex(SENSOR_INDEX);
      double Vout, Rth, tempresistor, adc_value; 
      adc_value = analogRead(A0);
      Vout = (adc_value * VCC) / adc_resolution;
      Rth = (VCC * R2 / Vout) - R2;
      tempresistor = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)),3))));
      tempresistor = tempresistor - 273.15;
      int chk = DHT.read22(DHT22_PIN);
      float t = (DHT.temperature);      
      
      
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(temperatureInCelsius);
                             postStr +="&field2=";
                             postStr += String(tempresistor);
                             postStr +="&field3=";
                             postStr += String(t);
                             postStr += "\r\n\r\n\r\n";                             
                             
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperatura DHT: ");
                             Serial.print(t);
                             Serial.print(" Temperatura Termoresistor ");
                             Serial.print(tempresistor);
                             Serial.print(" Temperatura DS18B20: ");
                             Serial.print(temperatureInCelsius);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(15000);
}
