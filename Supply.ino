// Supply sensor
// Supply sensor reads and monitors power supply.

#define SUP_INPUT (0)

static float sup_toVoltage();

static int sup_supply;      // current power


void SUP_setup()
{
  Serial.print("Supply sensor ... ");
  analogReference(INTERNAL);
  Serial.println("started.");
}

void SUP_loop()
{
  sup_supply = analogRead(SUP_INPUT);
  
  //Serial.print("Supply: ");
  //Serial.println(SUP_toVoltage());
}

static float SUP_toVoltage()
{
  return sup_supply * 7.2466 / 1024.0;
}

