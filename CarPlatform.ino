void setup() {
  Serial.begin(115200);
  Serial.println("Starting");
  OBS_setup();
  Serial.println("Started");
}

// the loop function runs over and over again forever
void loop() {
  OBS_loop();
  
  //Serial.println(".");
  
}