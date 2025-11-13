# Experiments Connecting Ai chat to an Arduino
My experiments using function calling to connect a Large Language Model (LLM) to an Arduino

## Learning Goals
- Send instructions from a chat interface to the Arduino e.g. User: Please switch on the light.
- Get the LLM to retrieve temperature and humidity sensor readings from the Arduino e.g. User: What's the temperature?

<br>

Project in progress...

<br>

## Experiments
- Exp1 - Run blink sketch on arduino<br>
  https://github.com/vbookshelf/Experiments-Connecting-Ai-Chat-to-an-Arduino/tree/main/Exp1%20-%20Run%20blink%20sketch%20on%20arduino

- Exp2 - Connect OLED display to ardunio and run simple code<br>
https://github.com/vbookshelf/Experiments-Connecting-Ai-Chat-to-an-Arduino/tree/main/Exp2%20-%20Connect%20OLED%20display%20to%20ardunio%20and%20run%20simple%20code

- Exp3 - DHT22 AM2302 run example sketch and print to serial monitor<br>
(Connecting DHT22 to Arduino: "+" to Arduino 5V, "-" to Arduino ground, "out" to Arduino pin D2)<br>
  https://github.com/vbookshelf/Experiments-Connecting-Ai-Chat-to-an-Arduino/tree/main/Exp3%20-%20DHT22%20AM2302%20run%20example%20sketch%20and%20print%20to%20serial%20monitor

- Exp4 - Display dht22 temp and humidity on oled and serial monitor<br>
https://github.com/vbookshelf/Experiments-Connecting-Ai-Chat-to-an-Arduino/tree/main/Exp4%20-%20Display%20dht22%20temp%20and%20humidity%20on%20oled%20and%20serial%20monitor
  



<br>

## Lessons learned
- Check the screen color scheme when buying the OLED display. Some OLEDS have a dual color screen. The top 16 pixel rows always display yellow and the rest of the rows display blue. These colors can't be adjusted. Unless you want these dual colors be sure to buy the monochrome display where all pixels display the same colour.
