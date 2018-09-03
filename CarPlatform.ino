
void setup() {
  Serial.begin(115200);
  if (!Serial) { ; }
  
  Serial.println("Starting");
  SUP_setup();
  OBS_setup();
  CMD_setup();
  Serial.println("Started");
}

// the loop function runs over and over again forever
void loop() {
  SUP_loop();
  OBS_loop();
  CMD_loop();
}
