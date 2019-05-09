#include <DHT.h>  // Including library for dht
 
#define DHTPIN D4          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);
 
void setup() 
{
       Serial.begin(9600); 
}
 
void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.print(" degrees Celcius, Humidity: ");
      Serial.print(h);
      delay(5000);            

}
