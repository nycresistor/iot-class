// Libraries
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// WiFi parameters
#define WLAN_SSID       "NYCR24"
#define WLAN_PASS       "clubmate"

// Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "bme14"
#define AIO_KEY         "47427099c49ee7a809475caa3fc04386d1dd0e4b"

int inputPin = A0;

// CHANGE THESE BASED ON YOUR SENSOR READINGS
const int dryVal = 567;
const int wetVal = 367;

// Functions
void connect();
int readHumidity();

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup feeds for temperature & humidity
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt,  AIO_USERNAME "/feeds/humidity");

/*************************** Sketch Code ************************************/

void setup() {
  Serial.begin(115200);
  Serial.println(F("Adafruit IO Example"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();

  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());

  // connect to adafruit io
  connect();
}

void loop() {
  // ping adafruit io a few times to make sure we remain connected
  if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      connect();
  }


  // Grab the current state of the sensor
  int humidity_data = readHumidity();

  // Publish data
  if (!humidity.publish(humidity_data)) {
    Serial.println(F("Failed to publish humidity"));
  } else {
    Serial.print(F("Humidity published: "));
    Serial.println(humidity_data);
  }

  // Repeat every minute
  delay(60000);

}

int readHumidity() {
  int sensorVal = analogRead(inputPin);
  return (int)(100*(dryVal-sensorVal)/(dryVal-wetVal));
}

// connect to adafruit io via MQTT
void connect() {

  Serial.print(F("Connecting to Adafruit IO... "));

  int8_t ret;

  while ((ret = mqtt.connect()) != 0) {

    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(5000);

  }

  Serial.println(F("Adafruit IO Connected!"));

}
