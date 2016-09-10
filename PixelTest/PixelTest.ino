#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            15
#define NUMPIXELS      32

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show(); // Actually display the changes we made.
    delay(500); // Delay for half a second.
  }
}

