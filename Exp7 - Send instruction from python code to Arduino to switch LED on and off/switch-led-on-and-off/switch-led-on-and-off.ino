
// ----- OLED Screen -----
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_I2C_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ----- DHT22 AM2302 Temp and Humidity Sensor -----
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

// ----- Global Variables for Sensor Readings and Timing -----
float temperature;
float humidity;

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 2000; // Update every 2 seconds (2000 ms)

// Define the built-in LED pin for clarity
const int ledPin = LED_BUILTIN; 


void setup() {
  
  Serial.begin(9600);

  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Ensure LED is off at the start

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS);
  dht.begin();

  // Perform an initial reading to have values ready from the start
  updateSensorReadings();
  
}



void loop() {
  
  unsigned long currentTime = millis();

  // 1. NON-BLOCKING SENSOR UPDATE
  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;
    updateSensorReadings();
  }

  // 2. ALWAYS-ON SERIAL COMMAND LISTENER 
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equals("READ_SENSORS")) {
      sendDataOverSerial();
    }
    // Handle the command to turn the LED ON
    else if (command.equals("LED_ON")) {
      digitalWrite(ledPin, HIGH);
      Serial.println("OK: LED turned on"); // Send confirmation
    }
    // Handle the command to turn the LED OFF
    else if (command.equals("LED_OFF")) {
      digitalWrite(ledPin, LOW);
      Serial.println("OK: LED turned off"); // Send confirmation
    }
  }

  
}




// ----- Helper Functions -----

// Reads sensors and updates the global variables AND the OLED display
void updateSensorReadings() {
  
  sensors_event_t event;

  // Get temperature
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    temperature = event.temperature;
  }

  // Get humidity
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    humidity = event.relative_humidity;
  }

  // Now, update the physical display with these new values
  updateOLED();
  
}



// Sends the current values from the global variables over serial
void sendDataOverSerial() {
  
  Serial.print("{\"temperature\": ");
  Serial.print(temperature, 2);
  Serial.print(", \"humidity\": ");
  Serial.print(humidity, 2);
  Serial.println("}");
  
}

// Updates the OLED screen with the current global variable values
void updateOLED() {
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 5);
  display.print("Temperature");
  display.setCursor(0, 17);
  display.setTextSize(2);
  display.print(temperature);
  display.print(" ");
  display.print((char)247); // Degree symbol
  display.print("C");

  display.setCursor(0, 37);
  display.setTextSize(1);
  display.print("Humidity");
  display.setCursor(0, 49);
  display.setTextSize(2);
  display.print(humidity);
  display.print(" %");
  
  display.display();
  
}
