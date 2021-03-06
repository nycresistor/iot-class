
#include <ESP8266WiFi.h>

const char* ssid     = "NYCR24";
const char* password = "clubmate";

char* host = "www.timeapi.org";
char* url = "/est/now?hour:%25H%25nminute:%25M";

int hour;
int minute;

String timeString(int hours, int minutes) {
  String hourStr;
  String minStr;

  if (hours < 10) {
    hourStr = String("0") + hours;
  } else {
    hourStr = String(hours);
  }
  if (minutes < 10) {
    minStr = String("0") + minutes;
  } else {
    minStr = String(minutes);
  }

  return String("The time is: ") + hourStr + ":" + minStr;
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

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  delay(5000);
  getTime();
}
