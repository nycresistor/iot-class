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

uint32_t getColor(int step) {
  int partial = step - 50;
  if (partial < 0) { partial = 0; }
  partial = (partial / 150.0) * step;
  
  int red = step;
  int green = partial;
  int blue = partial;
  return pixels.Color(red, green, blue);
}

void fade(int interval) {
  for (int t = 0; t < 150; t++) {
    for (int p=0; p<NUMPIXELS; p++) {
      pixels.setPixelColor(p, getColor(t));
    }
    pixels.show();
    delay(interval);
  }
}

void loop() {
  fade(5000);
}

