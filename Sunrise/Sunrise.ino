#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            15
#define NUMPIXELS      32

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* ssid     = "NYCR24";
const char* password = "clubmate";

char* host = "www.timeapi.org";
char* url = "/est/now?hour:%25H%25nminute:%25M";

int hour;
int minute;

int goalHour = 8;
int goalMinute = 30;
int minutesBefore = 30; // Amount of time to fade in the clock

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

bool wakeupStart(int hour, int minute) {
  // Calculate ideal start time
  int startingHour = goalHour;
  int startingMinute = goalMinute - minutesBefore;
  if (startingMinute < 0) {
    startingMinute = startingMinute + 60;
    startingHour = goalHour - 1;
  }

  // If we're within 5 minutes of that, time to start!
  return (
    hour == startingHour && 
    startingMinute <= minute && 
    minute < startingMinute + 5);
}

void getTime() {
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // This will send the request to the server
  client.println(String("GET ") + url + " HTTP/1.1");
  client.print("Host: ");
  client.println("www.timeapi.org");
  client.println("User-Agent: curl/7.43.0");
  client.println();
  delay(800);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');

    int i = line.indexOf("hour:");
    if (i < 0) continue;
    hour = (line.substring(i+5)).toInt() + 1;

    i = line.indexOf("minute:");
    if (i < 0) continue;
    minute = (line.substring(i+7)).toInt();

    Serial.println(timeString(hour, minute));
  }
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
  getTime(); // this updates the hour and minute variables
  if (wakeupStart(hour, minute)) {
    fade(5000);
  }
  delay(60000); // Wait one minute
}

