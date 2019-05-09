//
//    FILE: dht22_test.ino
//  //based on rob tillaart code
// VERSION: 0.1.03
// PURPOSE: DHT library test sketch for DHT22 && Arduino
//     URL: https://github.com/RobTillaart/Arduino
// Released to the public domain

#include <dht.h>
dht DHT;
#define DHT22_PIN D5

void setup()
{
    Serial.begin(9600);
}

void loop() 
{
  
     
    int chk = DHT.read22(DHT22_PIN);
    float t = (DHT.temperature);
    float h = (DHT.humidity);
    Serial.print("Temperature(ºC): ");
    Serial.print(t);
    Serial.print(",\t");
    Serial.print("Humidity(%): ");
    Serial.print(h);
    Serial.println("\n");
    delay(5000);
}
