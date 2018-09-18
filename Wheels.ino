// Wheels
// Allow control over left and right wheel

#define WHL_AUTONOMOUS_TIMEOUT (3000)

#define WHL_LEFT_FORWARD   (5)
#define WHL_LEFT_BACKWARD  (6)

#define WHL_RIGHT_FORWARD  (10)
#define WHL_RIGHT_BACKWARD (11)

static unsigned long whl_lastCmd=0;
static boolean whl_moving=false;

void WHL_setup()
{
  whl_moving=false;
}

void WHL_loop()
{
  static unsigned long now;

  now = millis();
  if ((whl_moving) && (now-whl_lastCmd>WHL_AUTONOMOUS_TIMEOUT)) {
    WHL_off();
  }
}

void WHL_setLeftRight(int left, int right)
{
  // -256 < left,right < 256
  // positive means: move forward
  // negative means: move backward


  if (left<=0) {
    analogWrite(WHL_LEFT_BACKWARD, -left);
    analogWrite(WHL_LEFT_FORWARD, 0);
  }
  else {
    analogWrite(WHL_LEFT_BACKWARD, 0);
    analogWrite(WHL_LEFT_FORWARD, left);    
  }

  if (right<=0) {
    analogWrite(WHL_RIGHT_BACKWARD, -left);
    analogWrite(WHL_RIGHT_FORWARD, 0);
  }
  else {
    analogWrite(WHL_RIGHT_BACKWARD, 0);
    analogWrite(WHL_RIGHT_FORWARD, left);    
  }

  whl_moving=((left!=0) || (right!=0 ));
  whl_lastCmd=millis();
}

void WHL_off()
{
  analogWrite(WHL_RIGHT_BACKWARD, 0);
  analogWrite(WHL_RIGHT_FORWARD, 0);
  analogWrite(WHL_LEFT_BACKWARD, 0);
  analogWrite(WHL_LEFT_FORWARD, 0);    
  whl_moving=false; 
}

void WHL_setSpeedDirection(int speed, int direction)
{
  // -256 < speed < 256
  // positive means: move forward
  // negative means: move backward

  // -100 < direction < 100
  // positive means: turn right
  // negative means: turn left

  int delta = 0;
  int right = 0;
  int left;

  if (direction >=0) {
    // turn right means reduce speed of right wheel
    delta = speed * direction/100;
    right = speed - delta;

    left = speed;
  }
  else {
    delta = speed * (-direction)/100;
    left = speed - delta;

    right = speed;
  }

  WHL_setLeftRight(left, right);
}

