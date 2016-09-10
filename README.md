# Setup

For this class today, you'll need to install:

- [Arduino IDE 1.6.8 or higher](http://www.arduino.cc/en/Main/Software)
- [CP2104 USB driver](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx)
- ESP8266 Board Package: [detailed instructions here](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide). Enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json` into Additional Board Manager URLs field in the Arduino preferences. Then, use the Board manager to install the ESP8266 package.

## Install the Arduino libraries

- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel/archive/master.zip): for using the OLED display
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

## DisplayTime

What if we want to display the time on the screen? We have to combine TimeApi and DisplayTest!

Feel free to copy the solution in DisplayTime_Solution, but you can also do this part by modifying DisplayTest.

## PixelTest

Run without modifications, using your Feather HUZZAH as well as the Neopixel FeatherWing. It should blink some pixels!

Let's dig into programming with Neopixels a bit.

**Your turn!** Try to do the following:

- Implement a fade effect, so that the display gradually becomes brighter, and then dims back down.

- Implement a gradient effect, so that the display starts out blue and fades to white.

Check out the solution in PixelFade if you get stuck.

## SunriseClock

Now for the grand finale. We're going to make a sunrise alarm "lamp". The idea is:

- Set the wake-up time in your Arduino code
- Poll the time API to check if it's the right time
- If so, gradually turn on the lamp



# Future work

This is just the beginning of what you can do with your kit! Here's a couple of ideas:

- Add a buzzer or other sound-making device, so that your alarm "lamp" can also be a normal alarm clock & beep when it's time to _really_ wake up

- Have the Feather act like a web server, so that you can send a POST request to change the alarm time

- Find an awesome diffuser to put your "lamp" inside of, so it looks like an actual lamp