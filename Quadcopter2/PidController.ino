/*
 * Devlopment Branch
 */
// https://oscarliang.com/quadcopter-pid-explained-tuning/
// PID variables
struct QUAD_PID roll; 
struct QUAD_PID pitch; 
struct QUAD_PID yaw; 

PID pidRoll(&roll.in,   &roll.out,  &roll.setpoint,  ROLL_PID_KP, ROLL_PID_KI, ROLL_PID_KD, REVERSE);
PID pidPitch(&pitch.in, &pitch.out, &pitch.setpoint, PITCH_PID_KP, PITCH_PID_KI, PITCH_PID_KD, REVERSE);
PID pidYaw(&yaw.in,     &yaw.out,   &yaw.setpoint,   YAW_PID_KP, YAW_PID_KI, YAW_PID_KD, DIRECT); 

void pid_initialize() {
  pidRoll.SetOutputLimits(ROLL_PID_MIN,ROLL_PID_MAX);
  pidPitch.SetOutputLimits(PITCH_PID_MIN,PITCH_PID_MAX);
  pidYaw.SetOutputLimits(YAW_PID_MIN,YAW_PID_MAX);
  pidRoll.SetMode(AUTOMATIC);
  pidPitch.SetMode(AUTOMATIC);
  pidYaw.SetMode(AUTOMATIC);
  pidRoll.SetSampleTime(10);
  pidPitch.SetSampleTime(10);
  pidYaw.SetSampleTime(10);
}


