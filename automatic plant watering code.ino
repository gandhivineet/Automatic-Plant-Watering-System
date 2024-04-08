#include <DHT.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define MOISTURE_SENSOR A0 // Analog pin connected to the soil moisture sensor
#define PUMP_PIN  9   // Digital pin connected to the L298N motor driver for pump

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
  dht.begin();
}

void loop() {
  // Read soil moisture level
  int moistureLevel = analogRead(MOISTURE_SENSOR);

  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Soil Moisture: ");
  Serial.print(moistureLevel);
  Serial.print("\tTemperature: ");
  Serial.print(temperature);
  Serial.print(" °C\tHumidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Check if soil moisture level is below a threshold
  if (moistureLevel < 500) {
    Serial.println("Soil is dry. Watering the plant.");
    turnOnPump(); // Turn on the pump to water the plant
    delay(5000); // Water for 5 seconds
    turnOffPump(); // Turn off the pump
  }

  delay(1000); // Delay between readings
}

// Function to turn on the pump
void turnOnPump() {
  digitalWrite(PUMP_PIN, HIGH); // Turn on the pump
}

// Function to turn off the pump
void turnOffPump() {
  digitalWrite(PUMP_PIN, LOW); // Turn off the pump
}
