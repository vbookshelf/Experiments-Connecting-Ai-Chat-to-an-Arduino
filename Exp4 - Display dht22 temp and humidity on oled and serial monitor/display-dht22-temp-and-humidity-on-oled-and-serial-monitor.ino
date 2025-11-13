
// ----- OLED Screen -----

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_I2C_ADDRESS 0x3C  // Also try 0x3D

// Create an instance of the Adafruit_SSD1306 class
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// ----- DHT22 AM2302 Temp and Humidity Sensor -----

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2     // (Pin D2) Digital pin connected to the DHT sensor
#define DHTTYPE    DHT22     // DHT 22 (AM2302)

// Create an instance of the DHT class
DHT_Unified dht(DHTPIN, DHTTYPE);

// Define a variable
uint32_t delayMS;




void setup() {

  // ----- Serial monitor -----
  Serial.begin(9600);

  // ----- OLED Screen -----
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS);
  display.clearDisplay();
  

  // ----- DHT22 AM2302 Temp and Humidity Sensor -----
  dht.begin();
  
  // Temperature and humodity should only be read after a min of 2 seconds
  delayMS = 2000;
  
}



void loop() {

  // Delay between measurements.
  delay(delayMS);

  // Declare a variable of type  sensors_event_t
  sensors_event_t event;

  // Declare two variables of type float
  float temperature, humidity;

  // Get temperature event and store its value.
  dht.temperature().getEvent(&event);

  
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    temperature = 0; // Or some other default error value
  }
  else {
    temperature = event.temperature;
    Serial.print(F("Temperature: "));
    Serial.print(temperature);
    Serial.println(F("°C"));
  }

  // Get humidity event and store its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
    humidity = 0; // Or some other default error value
  }
  else {
    humidity = event.relative_humidity;
    Serial.print(F("Humidity: "));
    Serial.print(humidity);
    Serial.println(F("%"));
  }

  Serial.println();

  

  // ----- Print the temperature and humidity on the OLED Screen -----
  
  // Clear the display buffer to remove old data.
  display.clearDisplay();
  
  //display.setTextSize(1);
  display.setTextColor(WHITE);

  // Print the word: Temperature
  display.setCursor(0,5);
  display.setTextSize(1);
  display.print("Temperature");

  // Display the temperature value
  display.setCursor(0,17);
  display.setTextSize(2);
  display.print(temperature);
  display.print(" ");
  display.print((char)247); // Degree symbol
  display.print("C");


  // Print the word: Humidity
  display.setCursor(0,37);
  display.setTextSize(1);
  display.print("Humidity");

  // Display the humidity value
  display.setCursor(0,49);
  display.setTextSize(2);
  display.print(humidity);
  display.print(" %");

  // This must be included to display the text on the screen.
  display.display();
  
}
