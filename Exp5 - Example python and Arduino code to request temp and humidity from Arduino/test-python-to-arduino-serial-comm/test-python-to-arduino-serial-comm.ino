// Includes for OLED and DHT sensor remain the same...
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Definitions for screen and sensor remain the same...
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_I2C_ADDRESS 0x3C

#define DHTPIN 2
#define DHTTYPE DHT22

// Instances remain the same...
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT_Unified dht(DHTPIN, DHTTYPE);



void setup() {
  // Start Serial communication at 9600 baud rate
  Serial.begin(9600);

  // Initialize display and sensor
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS);
  dht.begin();

  // Initial display message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Ready for commands...");
  display.display();
}



void loop() {

  
  // Check if there is data available to read from the serial port
  if (Serial.available() > 0) {
    // Read the incoming command until a newline character is received
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove any whitespace

    // Check if the command is the one we're looking for
    if (command.equals("READ_SENSORS")) {
      readAndSendData();
    }
  }

  
}



void readAndSendData() {
  sensors_event_t event;
  float temperature, humidity;

  // Get temperature reading
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    temperature = event.temperature;
  } else {
    temperature = -999; // Error value
  }

  // Get humidity reading
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    humidity = event.relative_humidity;
  } else {
    humidity = -999; // Error value
  }
  
  // --- Format data as a JSON string and send it over serial ---
  Serial.print("{\"temperature\": ");
  Serial.print(temperature, 2); // Send with 2 decimal places
  Serial.print(", \"humidity\": ");
  Serial.print(humidity, 2); // Send with 2 decimal places
  Serial.println("}");

  // Also update the local OLED display
  updateOLED(temperature, humidity);
}



void updateOLED(float temp, float hum) {
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.print("Temperature");
  display.setCursor(0, 17);
  display.setTextSize(2);
  display.print(temp);
  display.print(" ");
  display.print((char)247);
  display.print("C");

  display.setTextSize(1);
  display.setCursor(0, 37);
  display.print("Humidity");
  display.setCursor(0, 49);
  display.setTextSize(2);
  display.print(hum);
  display.print(" %");
  display.display();
}
