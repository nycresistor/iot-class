# Setup

For this class today, you'll need to install:

- [Arduino IDE 1.6.8 or higher](http://www.arduino.cc/en/Main/Software)
- [CP2104 USB driver](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx)
- ESP8266 Board Package: [detailed instructions here](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide). Enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json` into Additional Board Manager URLs field in the Arduino preferences. Then, use the Board manager to install the ESP8266 package.

## Install the Arduino libraries

- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306/archive/master.zip): for using the OLED display
- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library/archive/master.zip)
# Instructions

## Blink

Run without modifications, just using your Feather HUZZAH.

Confirm that it works by looking at your Feather - is the LED blinking?

**Bonus points:** modify the sketch to change the blinking pattern (faster, slower, morse code, etc...)

## WifiTest

Run without modifications, just using your Feather HUZZAH.

Confirm that the WiFi test is working by inspecting the serial monitor.

## TimeApi

Run without modifications, just using your Feather HUZZAH.

Confirm that it works by inspecting the serial monitor. Is it printing the current time?

## DisplayTest

Run  without modifications, using your Feather HUZZAH as well as the OLED FeatherWing. It should display a message!

**Bonus points:** Modify the sketch to print your own message.

**Super bonus points:** Can you make the text scroll across the screen? You'll need to know how to program with *loops* to make this happen...

