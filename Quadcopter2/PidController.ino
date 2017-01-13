/*
 * Devlopment Branch
 */
// https://oscarliang.com/quadcopter-pid-explained-tuning/



PID pidRoll(&pid_roll_in,   &pid_roll_out,  &pid_roll_setpoint,  ROLL_PID_KP, ROLL_PID_KI, ROLL_PID_KD, REVERSE);
PID pidPitch(&pid_pitch_in, &pid_pitch_out, &pid_pitch_setpoint, PITCH_PID_KP, PITCH_PID_KI, PITCH_PID_KD, REVERSE);
PID pidYaw(&pid_yaw_in,     &pid_yaw_out,   &pid_yaw_setpoint,   YAW_PID_KP, YAW_PID_KI, YAW_PID_KD, DIRECT); 


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

void pid_update(){
/*  angleZ = ypr[0] * 180 / M_PI; // YAW
    angleY = ypr[1] * 180 / M_PI; // PITCH
    angleX = ypr[2] * 180 / M_PI; // ROLL
 */   
  pid_roll_in = angles[2];   // angleX
  pid_pitch_in = angles[1];  // angleY
  pid_yaw_in = angles[0];    // angleZ 
}

void pid_compute() {
   pidRoll.Compute();
   pidPitch.Compute();
   pidYaw.Compute();
}
