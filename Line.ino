// Line sensor
//

#define LIN_LL (0)
#define LIN_L  (1)
#define LIN_R  (2)
#define LIN_RR (7)

void LIN_setup()
{
  pinMode(LIN_LL, INPUT);
  pinMode(LIN_L,  INPUT);
  pinMode(LIN_R,  INPUT);
  pinMode(LIN_RR, INPUT);
}

void LIN_loop()
{
  
}

uint8_t LIN_getLineSensor()
{
  uint8_t result = 0;

  if (digitalRead(LIN_LL)== HIGH) {
    result += 1<<4;
  }

  if (digitalRead(LIN_L)== HIGH) {
    result += 1<<3;
  }

  if (digitalRead(LIN_R)== HIGH) {
    result += 1<<2;
  }

  if (digitalRead(LIN_RR)== HIGH) {
    result += 1<<1;
  }

  Serial.println(result);
}

