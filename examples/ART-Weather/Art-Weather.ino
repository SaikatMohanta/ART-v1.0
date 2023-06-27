#include <ARTLibrary.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include <DHT.h>

#define INPUT_SIZE 4
#define CATEGORY_COUNT 3
#define VIGILANCE 0.91

SFE_BMP180 bmp180; // BMP180 sensor object
#define DHTPIN 2    // DHT11 sensor pin
#define DHTTYPE DHT11   // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE); // DHT11 sensor object

ARTLibrary art(VIGILANCE, INPUT_SIZE, CATEGORY_COUNT);

void setup() {
  Serial.begin(9600);

  // Initialize sensors
  if (!bmp180.begin()) {
    Serial.println("BMP180 initialization failed!");
    while (1); // Halt the program
  }

  dht.begin();
}

void loop() {
  // Read sensor data
  float temperature = bmp180.readTemperature();
  float humidity = dht.readHumidity();
  float dewPoint = calculateDewPoint(temperature, humidity);
  float pressure = bmp180.readPressure() / 100.0; // Convert Pa to hPa

  // Normalize sensor data
  float normalizedTemperature = normalize(temperature, -20, 85);
  float normalizedHumidity = normalize(humidity, 0, 100);
  float normalizedDewPoint = normalize(dewPoint, -20, 85);
  float normalizedPressure = normalize(pressure, 900, 1100);

  // Create input data array
  float inputData[INPUT_SIZE] = {
    normalizedTemperature,
    normalizedHumidity,
    normalizedDewPoint,
    normalizedPressure
  };

  // Predict weather pattern
  int predictedCategory = art.predict(inputData);

  // Print predicted weather pattern
  switch (predictedCategory) {
    case 0:
      Serial.println("Cloudy");
      break;
    case 1:
      Serial.println("Sunny");
      break;
    case 2:
      Serial.println("Stormy");
      break;
    
    default:
      Serial.println("Unknown");
      break;
  }

  // Train ART network with the current sensor data
  art.train(inputData);

  delay(2500);
}

// Helper function to calculate dew point
float calculateDewPoint(float temperature, float humidity) {
  float A = 17.27;
  float B = 237.7;
  float alpha = ((A * temperature) / (B + temperature)) + log(humidity / 100.0);
  float dp = (B * alpha) / (A - alpha);
  return dp;
}

// Helper function to normalize sensor data between 0 and 1
float normalize(float value, float min, float max) {
  return (value - min) / (max - min);
}
