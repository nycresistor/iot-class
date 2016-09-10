
#include <ESP8266WiFi.h>

const char* ssid     = "NYCR24";
const char* password = "clubmate";
int8_t utc_offset = -5; // hours off of UTC, e.g. EST is -5 
const char* location = "brooklyn%2C%20ny";

const char* path_prefix = "/v1/public/yql?q=select%20item.condition.code%2C%20astronomy%20%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22";
const char* path_postfix = "%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";
const char* host = "query.yahooapis.com";
const int httpPort = 80;


int16_t weathercode = -1;
int16_t createhour, createmin;

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

uint32_t timekeep=0xFFFF;

void loop() {
  uint32_t currTime = millis();
  // every 30 seconds (or if there's a rollover/first time running, update the weather!
  if ((timekeep > currTime)  || (currTime > (timekeep + 30000))) {
    timekeep = currTime;
    updateWeather();
  }

}


void updateWeather() {
  
  Serial.print("Connecting to "); Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  
  // We now create a URI for the request

  String url = String(path_prefix) + String(location) + String(path_postfix);
  
  Serial.print("Requesting URL: ");  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);

  weathercode = -1;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    int i = line.indexOf(String("\"sunrise\":"));
    if (i < 0) continue;
    Serial.println(line);
    String sunriseSubstring = (line.substring(i+11));
    Serial.println(sunriseSubstring);
    int sunriseHour = sunriseSubstring.toInt();
    String sunriseMin = sunriseSubstring.substring(sunriseSubstring.indexOf(String(":")));
    Serial.println(sunriseHour);
    Serial.println(sunriseMin);
    

    i = line.indexOf(String("\"sunset\":"));
    if (i < 0) continue;

    // extract hour and minute
//    i = line.indexOf(String("\"created\":"));
//    if (i < 0) continue;
//    createhour = (line.substring(i+22)).toInt();
//    createmin = (line.substring(i+25)).toInt();
  }
  
  Serial.println("Closing connection");

  // convert from UTC to local
//  createhour += 24;
//  createhour += utc_offset;
//  createhour %= 24;
//  Serial.print("\nWeather code: "); Serial.print(weathercode);
//  Serial.print(" @ "); Serial.print(createhour); Serial.print(":"); Serial.println(createmin);

  // Get the current time of day, between 0 and 65535
//  uint16_t timeofday = map((createhour * 60) + createmin, 0, 1440, 0, 65535);
//
//  Serial.print("Time of day = "); Serial.print(timeofday); Serial.println("/65535");

}
