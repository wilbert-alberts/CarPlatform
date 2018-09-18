#include <Servo.h>

// Obstacle sensor
// Obstacle sensor can be in three states:
// OFF: does not do anything at all
// STARE: keeps orientation of sensor steady and continuously measures obstacle distance
//        requires desired orientation of sensor
//        provides distance to object
// SWEEP: sweep orientation of sensor from left to right and back and continuously performs measurements
//        requires nothing
// 

#define OBS_TRIGGERPIN (3)
#define OBS_ECHOPIN    (4)

#define OBS_SERVO      (9)

#define OBS_MODE_OFF     (0)
#define OBS_MODE_STARE   (1)
#define OBS_MODE_SWEEP   (2)

#define OBS_SWEEP_LEFT    (-1)
#define OBS_SWEEP_RIGHT   ( 1)

#define OBS_SWEEP_MIN     (-90)
#define OBS_SWEEP_MAX     ( 90)

// Array to hold result as specified in angles from -90 to 90 (including)
// This implies that size of array needs to be 181!
typedef uint8_t OBS_View[181];

static uint8_t  obs_mode        = OBS_MODE_STARE;  // One of OBS_MODE_*
static OBS_View obs_view;                          // Array holding results
static int8_t   obs_direction   = 0;               // Actual direction of sensor
static uint8_t  obs_sweepTo     = OBS_SWEEP_LEFT;  // One of OBS_SWEEP_*
static int8_t   obs_servoOffset = -10;             // Servo offset w.r.t. straight ahead (0 degrees)
static int8_t   obs_sweepMin = OBS_SWEEP_MIN;
static int8_t   obs_sweepMax = OBS_SWEEP_MAX;



static Servo obs_servo;

static void obs_loopStare();
static void obs_loopSweep();
static void obs_readSensor();
static void obs_setDirection(uint8_t direction);



void OBS_setup()
{
  uint8_t i;
  Serial.print("Starting obstacle sensor ... ");
 
  obs_mode = OBS_MODE_STARE;
  for (i=0; i<181; i++) { 
    obs_view[i] = 0;
  }

  pinMode(OBS_TRIGGERPIN, OUTPUT);
  pinMode(OBS_ECHOPIN, INPUT);
  digitalWrite(OBS_TRIGGERPIN, LOW);

  obs_servo.attach(OBS_SERVO);

  OBS_stare(0);
  Serial.println("started.");
}

void OBS_loop()
{
  switch (obs_mode) {
  case OBS_MODE_OFF:
    return;
  case OBS_MODE_STARE:
    obs_loopStare();
    return;
  case OBS_MODE_SWEEP:
    obs_loopSweep();
    return;
  default:
    return;
  }
}

void OBS_off()
{
  obs_mode = OBS_MODE_OFF;
}

void OBS_stare(int8_t direction)
{
  obs_setDirection(direction);
  obs_mode = OBS_MODE_STARE;
}

void OBS_sweep(int8_t swMin, int8_t swMax)
{
  obs_sweepMin = swMin;
  obs_sweepMax = swMax;
  if (swMin<OBS_SWEEP_MIN) {
    Serial.println("Error: min must be at least -90");
    return;
  }
  if (swMax>OBS_SWEEP_MAX) {
    Serial.println("Error: max must be less then 90");
    return;
  }
  if (swMin>swMax) {
    Serial.println("Error: min must be less then max");
    return;
  }
  obs_mode = OBS_MODE_SWEEP;
  Serial.println("OK");
}

void OBS_getRecent()
{
  Serial.print(obs_direction);
  Serial.print('\t');
  Serial.println(obs_view[90+obs_direction]);
}

void OBS_getSweep()
{
  for (int8_t d=obs_sweepMin; d<= obs_sweepMax; d++) {
    Serial.print(d);
    Serial.print('\t');
    Serial.println(obs_view[90+d]);
  }
}

static void obs_setDirection(int8_t direction)
{
  obs_direction = direction;  
  if (obs_direction<-90)
    obs_direction = -90;
  if (obs_direction>90)
    obs_direction = 90;
  obs_servo.write(90+direction+obs_servoOffset);
}

static void obs_loopStare()
{
  obs_readSensor();
  //Serial.print("Obstacle at: ");
  //Serial.println(obs_view[90+obs_direction]);
}

static void obs_loopSweep()
{
  // Direct sensor into next direction
  int8_t d = obs_direction;
  d = d + obs_sweepTo;
  if (d<obs_sweepMin) {
    d = obs_sweepMin+1;
    obs_sweepTo = OBS_SWEEP_RIGHT;
  }
  else {
    if (d>obs_sweepMax) {
      d=obs_sweepMax-1;
      obs_sweepTo = OBS_SWEEP_LEFT;
    }    
  }
  obs_setDirection(d);

  // Read sensor and store result
  obs_readSensor();
  //Serial.print("At ");
  //Serial.print(obs_direction);
  //Serial.print(" I see first obstacle at: ");
  //Serial.println(obs_view[90+obs_direction]);
}

static void obs_readSensor()
{
  long duration;
  uint8_t distance;  
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(OBS_TRIGGERPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(OBS_TRIGGERPIN, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(OBS_ECHOPIN, HIGH);
  
  // Calculating the distance
  distance= (uint8_t)(duration*0.034/2.0);  

  obs_view[obs_direction+90] = distance;
}
