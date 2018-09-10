
void setup() {
  Serial.begin(115200);
  if (!Serial) { ; }
  
  Serial.println("Starting");
  SUP_setup();
  OBS_setup();
  LIN_setup();
  CMD_setup();
  WHL_setup();
  Serial.println("Started");
}

// the loop function runs over and over again forever
void loop() {
  SUP_loop();
  OBS_loop();
  LIN_loop();
  CMD_loop();
  WHL_loop();
}
