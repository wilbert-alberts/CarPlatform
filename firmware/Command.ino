
// Command handles incoming commands from the serial and provides results.
// 
// Available commands:
//
// OBS_off
// OBS_sweep <min> <max>
// OBS_stare <dir> 
// OBS_getRecent
//     Out: direction
//     Out: distance
// OBS_getFull
//     Out: <sweep_min>
//     Out: <sweep_max>
//     Out: distance (at -sweep)
//     Out: distance (at -sweep+1)
//     ...
//     Out: distance (at 0)
//     ...
//     Out: distance (at sweep-1)
//     Out: distance (at sweep)
//
// SUP_getSupply
//     Out: supply voltage
// 
// MOT_lr <left> <right>
// MOT_sd <speed> <direction>
// MOT_off
// MOT_get
//    Out: <left>
//    Out: <right>
// 
// LIN_get
//    OUT: line sensor output in low nibble


#define CMD_BUFFERSIZE (40)

static char     cmd_buffer[CMD_BUFFERSIZE];
static uint8_t  cmd_cursor = 0;

static void   cmd_processCmd();
static int8_t cmd_getInt8(int8_t* dest);


void CMD_setup()
{
  for (cmd_cursor=0; cmd_cursor<CMD_BUFFERSIZE; cmd_cursor++)
    cmd_buffer[cmd_cursor]=0; 
  cmd_cursor = 0;
}


void CMD_loop()
{
  static char ch;
  while (Serial.available()>0) {
    ch = Serial.read();
    if ((ch==' ') || (ch=='\n') || (ch=='\r')) {
      cmd_buffer[cmd_cursor] = 0;
      if (cmd_cursor>0)
        cmd_processCmd();
      cmd_cursor = 0;  
    }
    else {
      cmd_buffer[cmd_cursor] = ch;
      cmd_cursor++;
      if (cmd_cursor==CMD_BUFFERSIZE) {
        cmd_cursor = 0;
      }
    }
  }
}


static int8_t cmd_getInt8(int8_t* dest)
{
  long l = Serial.parseInt();
  *dest  = (int8_t) l;
  return 0;
}

static int8_t cmd_getInt(int* dest)
{
  long l = Serial.parseInt();
  *dest  = (int) l;
  return 0;
}

static void cmd_processCmd()
{
  /*
  Serial.println("cmd_processCmd()");
  Serial.print(">");
  Serial.print(cmd_buffer);
  Serial.println("<");
  */
  if (strcmp(cmd_buffer, "OBS_off") ==0 ) {
    OBS_off();
    Serial.println("OK");
    return;
  }
  
  if (strcmp(cmd_buffer, "OBS_sweep") ==0 ) {
    int8_t sweepMin;
    int8_t sweepMax;
    
    if (cmd_getInt8(&sweepMin) ==0) {
      if (cmd_getInt8(&sweepMax) == 0) {
            OBS_sweep(sweepMin, sweepMax);        
      }
    }
    return;
  }

  if (strcmp(cmd_buffer, "OBS_stare") ==0 ) {
    int8_t arg;
    if (cmd_getInt8(&arg) == 0) {
      OBS_stare(arg);
      Serial.println("OK");
    }
    return;
  }

  if (strcmp(cmd_buffer, "OBS_getRecent") ==0 ) {
    int8_t dir;
    uint8_t dist;    
    OBS_getRecent();
    Serial.println("OK");
    return;
  }

  if (strcmp(cmd_buffer, "OBS_getSweep") ==0 ) {
    int8_t dir;
    uint8_t dist;    
    OBS_getSweep();
    Serial.println("OK");
    return;
  }

  if (strcmp(cmd_buffer, "SUP_getSupply") ==0 ) {
    Serial.println(SUP_toVoltage());
    Serial.println("OK");
    return;
  }

  if (strcmp(cmd_buffer, "WHL_off") == 0) {
    WHL_off();
    Serial.println("OK");
    return;
  }

  if (strcmp(cmd_buffer, "WHL_LR") == 0) {
    WHL_off();
    int left;
    int right;
    if (cmd_getInt(&left) == 0) {
      if (cmd_getInt(&right) == 0) {
        WHL_setLeftRight(left, right);
        Serial.println("OK");
        return;
      }
    }
          
    Serial.println("ERROR");
    return;
  }

  if (strcmp(cmd_buffer, "WHL_SD") == 0) {
    WHL_off();
    int velo;
    int dir;
    if (cmd_getInt(&velo) == 0) {
      if (cmd_getInt(&dir) == 0) {
        WHL_setSpeedDirection(velo, dir);
        Serial.println("OK");
        return;
      }
    }
          
    Serial.println("ERROR");
    return;
  }

  if (strcmp(cmd_buffer, "WHL_get") == 0) {
    WHL_getLeftRight();
    Serial.println("OK");
    return;
  }

  if (strcmp(cmd_buffer, "LIN_get") == 0) {
    LIN_getLineSensor();    
    Serial.println("OK");
    return;
  }

  Serial.println("Error: Illegal command");  
}



