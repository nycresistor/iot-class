void setup() {
  pinMode(0, OUTPUT);
}

void loop() {
  Serial.println("Hey! I'm in a loop!");
  digitalWrite(0, HIGH);
  delay(500);
  digitalWrite(0, LOW);
  delay(500);
}
