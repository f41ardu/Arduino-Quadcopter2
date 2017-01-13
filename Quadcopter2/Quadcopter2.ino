/*
   Arduino Quadcopter
   Author - Ben Ripley - Aug 8, 2014
   http://www.benripley.com/development/quadcopter-source-code-from-scratch/

   Rebuild and integration MPU6050
   (Due to lack of an ARDUIMO an IMU board (GY-521) will be integrated into the main system)
   Introducing version number

   For Version number see ReleaseNumber[] below

   Production Branch 
   
*/

// global libs
#include <PID_v1.h>
#include <PinChangeInt.h>
#include "I2Cdev.h"
#include <MPU6050_6Axis_MotionApps20.h>
#include <Servo.h>

//local libs
#include "pinclass.h"
// Configuration file
#include "Configuration.h"

// Release and Build
char VersionNumber[] = "0.2.1";
char ReleaseNumber[] = "preRelease";
char build[] = "build_930322";

// LEDs
PinClass heartbeat(HEARTBEAT_LED, 500, 500);

// Angles
float angles[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
int16_t ax, ay, az;
int16_t gx, gy, gz;

// RX Signals
int throttle = THROTTLE_RMIN;
volatile int rx_values[4]; // ROLL, PITCH, THROTTLE, YAW

// PID variables
double pid_roll_in,   pid_roll_out,   pid_roll_setpoint = 0;
double pid_pitch_in,  pid_pitch_out,  pid_pitch_setpoint = 0;
double pid_yaw_in,    pid_yaw_out,    pid_yaw_setpoint = 0;

// Motors
int m0, m1, m2, m3; // Front, Right, Back, Left

// Helper
unsigned long  lastUpdate;
int currentMillis, previousMillis, waitTime = 20000;

// Quaternions and parameters for 6 DoF sensor fusion calculations
Quaternion q;          // [w, x, y, z]         quaternion container

void setup()
{
#ifdef DEBUG_OUTPUT
  Serial.begin(38400);
  while (!Serial);
  Serial.println("Debug Output ON");
#endif
  rx_initialize();
  mpu_init();
  motors_initialize();
  pid_initialize();
  motors_arm();
  // Wait waittime (~ 20 s) that MPU can level and store first conjugated Quaternion in HQ. 
  // to define initial HOME position (Angles ~ 0°) 
  heartbeat.timechange(250, 100);
  previousMillis = millis();
  while ((currentMillis - previousMillis) < waitTime) {
    mpu_update();
    heartbeat.flash();
    currentMillis = millis();
  }
  // Here we go 
  heartbeat.timechange(500, 500);
}
void loop()
{
  heartbeat.flash();
  mpu_update(); 
  mpu_ypr();
  control_update();
#ifdef DEBUG_OUTPUT
  debug_process();
#endif
  lastUpdate = micros();
}



