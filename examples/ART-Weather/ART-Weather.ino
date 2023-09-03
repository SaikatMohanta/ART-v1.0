#include <Wire.h>
#include <SFEBMP180.h>
#include <DHT.h>
#include <ART.h>

// Define ART parameters
const int inputSize = 2;  // Dew Point and Barometric Pressure
const int prototypeSize = 2;  // Two categories: Clear (High Pressure) and Rainy (Low Pressure)
const float vigilance = 0.8;

// Create an instance of the ART network
ART art(inputSize, prototypeSize, vigilance);

// Define sensor pins
const int dhtPin = 2;  // Pin for the DHT11 sensor
DHT dht(dhtPin, DHT11);

// Create an instance of the BMP180 sensor
SFEBMP180 bmp;

// Define thresholds for classifying weather patterns
const float dewPointThreshold = 15.0;  // Adjust this threshold as needed
const float pressureThreshold = 1013.25;  // Adjust this threshold as needed

void setup() {
  Serial.begin(9600);

  // Initialize sensors
  dht.begin();
  bmp.begin();

  // Initialize the ART network
  float clearWeather[inputSize] = {20.0, 1015.00};  // Dew Point and Barometric Pressure for Clear Weather
  float rainyWeather[inputSize] = {10.0, 1010.50};  // Dew Point and Barometric Pressure for Rainy Weather

  art.initialize(clearWeather);  // Initialize category for Clear Weather
  art.initialize(rainyWeather);  // Initialize category for Rainy Weather
}

void loop() {
  // Read sensor data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float dewPoint = calculateDewPoint(temperature, humidity);
  float pressure = bmp.getPressure() / 100.0;  // Convert to hPa

  // Create input vector for the ART network
  float input[inputSize] = {dewPoint, pressure};

  // Classify sensor readings
  int category = art.classify(input);

  // Perform actions based on the category
  if (category == 0) {  // Clear Weather
    Serial.println("Clear Weather (High Pressure)");
  } else if (category == 1) {  // Rainy Weather
    Serial.println("Rainy Weather (Low Pressure)");
  }

  delay(5000);  // Delay to control the rate of prediction (adjust as needed)
}

// Function to calculate dew point
float calculateDewPoint(float temperature, float humidity) {
  float a = 17.27;
  float b = 237.7;
  float alpha = ((a * temperature) / (b + temperature)) + log(humidity / 100.0);
  float dewPoint = (b * alpha) / (a - alpha);
  return dewPoint;
}
