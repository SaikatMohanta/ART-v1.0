#include "ARTLibrary.h"
#include <SFE_BMP180.h>
#include <DHT.h>

ARTLibrary art(0.91);  // Set the vigilance parameter

// Define pin connections for BMP180 sensor
const int bmp180SdaPin = A4;
const int bmp180SclPin = A5;

// Define pin connections for DHT22 sensor
const int dhtPin = 2;
DHT dht(dhtPin, DHT22);

// Define weather categories
enum WeatherCategory {
  SUNNY,
  CLOUDY,
  RAINY,
  STORMY
};

void setup() {
  // Initialize the ART network
  art.initialize(3, 4);  // 3 inputs (Temperature, Pressure, Humidity), 4 categories (Weather patterns)

  // Initialize the BMP180 sensor
  BMP180 bmp180;
  bool bmp180Status = bmp180.begin(bmp180SdaPin, bmp180SclPin);
  
  // Initialize the DHT22 sensor
  dht.begin();
}

void loop() {
  // Read sensor values
  float temperature = readTemperature();
  float pressure = readPressure();
  float humidity = readHumidity();

  normalizedTemerature = normalize(temperature, -10, 60);// degree celcius
  normalizedHumidity = normalize(humidity, 0, 100);// %
  normalizedPressure = normalize(pressure, 950, 1050);// miliBar
  normalizedDewPoint = normalize(dewPoint, -10, 60);// degree celcius
  
  // Convert sensor values to ART input
  float input[3] = {temperature, pressure, humidity};

  // Train the ART network with the input
  art.train(input);

  // Classify the input using the trained network
  int category = art.classify(input);

  // Map the category to a weather pattern
  WeatherCategory weather;
  switch (category) {
    case 0:
      weather = SUNNY;
      break;
    case 1:
      weather = CLOUDY;
      break;
    case 2:
      weather = RAINY;
      break;
    case 3:
      weather = STORMY;
      break;
    default:
      weather = SUNNY;
      break;
  }

  // Print the predicted weather pattern
  switch (weather) {
    case SUNNY:
      Serial.println("Sunny");
      break;
    case CLOUDY:
      Serial.println("Cloudy");
      break;
    case RAINY:
      Serial.println("Rainy");
      break;
    case STORMY:
      Serial.println("Stormy");
      break;
  }

  delay(5000);  // Wait for 5 seconds before taking the next reading
}

float readTemperature() {
  // Read temperature from DHT22 sensor
  float temperature = dht.readTemperature();
  return temperature;
}

float readPressure() {
  // Read pressure from BMP180 sensor
  float pressure = 0.0;
  if (bmp180.measurePressure()) {
    pressure = bmp180.getPressure();
  }
  return pressure;
}

float readHumidity() {
  // Read humidity from DHT22 sensor
  float humidity = dht.readHumidity();
  return humidity;
}

float calculateDewPoint(float temperature, float humidity) {
  float A = 17.27;
  float B = 237.7;
  float alpha = ((A * temperature) / (B + temperature)) + log(humidity / 100.0);
  float dp = (B * alpha) / (A - alpha);
  return dp;
}

// Helper function to normalize sensor data between 0 and 1
float normalize(float value, float min, float max) {
  float norm = (value - min) / (max - min);
  return norm;
}
