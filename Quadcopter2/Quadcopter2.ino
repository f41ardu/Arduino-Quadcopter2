/*
   Arduino Quadcopter2

   For Version number see ReleaseNumber[] below

   Devlopment Branch variables

*/

// global libs
#include <PID_v1.h>
#include <PinChangeInt.h>
#include "I2Cdev.h"
#include <MPU6050_6Axis_MotionApps20.h>
#include <Servo.h>

//local libs
#include "pinclass2.h"
// Configuration file
#include "Configuration.h"
#include "common.h"

// Release and Build
char VersionNumber[] = "0.1.3";
char ReleaseNumber[] = "0.0";
char build[] = "N/A";

// LEDs
PinClass2 heartbeat(HEARTBEAT_LED, 500, 500);

// RX Signals
int throttle = THROTTLE_RMIN;
volatile int rx_values[4]; // ROLL, PITCH, THROTTLE, YAW

// PID variables
struct QUAD_PID roll; 
struct QUAD_PID pitch; 
struct QUAD_PID yaw; 

// Motors
int m0, m1, m2, m3; // Front, Right, Back, Left

// Helper
unsigned long  lastUpdate;
int currentMillis, previousMillis, waitTime = 20000;
#define PI2DEG  180.0f / PI;

void setup()
{
  SENSOR_YPR quad;
  #ifdef DEBUG_OUTPUT
  Serial.begin(38400);
  while (!Serial);
  Serial.println("Debug Output ON");
#endif
  rx_initialize();
  mpu_init();
  rotors_initialize();
  pid_initialize();
  rotors_arm();
  // Wait waittime (~ 20 s) that MPU can level and store first conjugated Quaternion in HQ.
  // to define initial HOME position (Angles ~ 0°)
  heartbeat.timechange(250, 100);
  previousMillis = millis();
  while ((currentMillis - previousMillis) < waitTime) {
    mpu_ypr(&quad);
    heartbeat.flash();
    currentMillis = millis();
#ifdef DEBUG_OUTPUT
    debug_process(&quad);
#endif
  }
  // Here we go
  heartbeat.timechange(500, 500);
}

void loop()
{
  SENSOR_YPR quad;
  heartbeat.flash();
  mpu_ypr(&quad);
  quad_update(&quad);
#ifdef DEBUG_OUTPUT
  debug_process(&quad);
#endif
  lastUpdate = micros();
}



