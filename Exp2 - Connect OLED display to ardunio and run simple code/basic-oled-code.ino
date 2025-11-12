
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// If the screen remains blank this I2C address may need to be changed.
// This video shows how to get the I2C address of your OLED screen:
// https://www.youtube.com/watch?v=6JZDT__BNCU

#define SCREEN_I2C_ADDRESS 0x3C  // Also try 0x3D


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() {
  
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS);
  display.clearDisplay();
  
}

void loop() {

  // Notes:
  // 1. Screen size is 128 pixels x 64 pixels
  // 2. (0,0) is in the top left corner - (x,y)
  // 3. On my display: The first 16 rows are yellow and
  // the remaining 48 are blue.
  
  display.setTextSize(1);
  display.setTextColor(WHITE); // WHITE means: Turn on the pixel

  // Print the word: Temperature
  display.setCursor(0,5);
  display.print("Temperature");

  // Print the word: Humidity
  display.setCursor(0,37);
  display.print("Humidity");

  // Display the temperature value
  display.setCursor(0,17);
  display.setTextSize(2);
  display.print("25");
  display.print(" ");
  display.print((char)247);
  display.print("C");

  // Display the humidity value
  display.setCursor(0,49);
  display.setTextSize(2);
  display.print("50");
  display.print(" %");

  // This must be included to display the text
  // on the screen.
  display.display();
  
}
