//code based on the one thanks to tatuvidas.com
//https://www.tautvidas.com/blog/2015/09/measuring-temperature-with-ds18b20-temperature-sensor/
#include <OneWire.h>
#include <DallasTemperature.h>

// Sensor input pin
#define DATA_PIN D3
// How many bits to use for temperature values: 9, 10, 11 or 12
#define SENSOR_RESOLUTION 12
// Index of sensors connected to data pin, default: 0
#define SENSOR_INDEX 0

OneWire oneWire(DATA_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress sensorDeviceAddress;

void setup() {
  Serial.begin(9600);

  sensors.begin();
  sensors.getAddress(sensorDeviceAddress, 0);
  sensors.setResolution(sensorDeviceAddress, SENSOR_RESOLUTION);
}


void loop() {
  sensors.requestTemperatures();
  // Measurement may take up to 750ms

  float temperatureInCelsius = sensors.getTempCByIndex(SENSOR_INDEX);
  float temperatureInFahrenheit = sensors.getTempFByIndex(SENSOR_INDEX);

  Serial.print("Temperature(ºC): ");
  Serial.print(temperatureInCelsius, 4);
  Serial.print("\n");
  delay(5000);
}
