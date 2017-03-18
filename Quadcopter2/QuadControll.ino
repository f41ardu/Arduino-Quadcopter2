/*
  *  Devlopment Branch variables
*/

// #define PIDMIX(X,Y,Z) rcCommand[THROTTLE] + axisPID[ROLL]*X + axisPID[PITCH]*Y + YAW_DIRECTION * axisPID[YAW]*Z
#define MOTORMIX(X,Y,Z) throttle + roll.out*X  +  pitch.out*Y + yaw.out*Z

void quad_update(struct SENSOR_YPR *_quad) {

  throttle = map(rx_values[2], THROTTLE_RMIN, THROTTLE_RMAX, ROTOR_ZERO_LEVEL, ROTOR_MAX_LEVEL);
  setpoint_update();
  roll.in = _quad->roll;   // angleX
  pitch.in = _quad->pitch;  // angleY
  yaw.in = _quad->yaw;;    // angleZ
  pidRoll.Compute();
  pidPitch.Compute();
  pidYaw.Compute();
  
// PIDMIX(PID,PITCH,YAW) 
#if defined( QUADP )
  m0 = MOTORMIX( 0, +1, -1); //REAR
  m1 = MOTORMIX(-1, 0, +1); //RIGHT
  m2 = MOTORMIX(+1, 0, +1); //LEFT
  m3 = MOTORMIX( 0, -1, -1); //FRONT
#elif defined( QUADX )
  m0 = MOTORMIX(-1, +1, -1); //REAR_R
  m1 = MOTORMIX(-1, -1, +1); //FRONT_R
  m2 = MOTORMIX(+1, +1, +1); //REAR_L
  m3 = MOTORMIX(+1, -1, -1); //FRONT_L
#endif

#ifdef SAFE
  if (throttle < THROTTLE_SAFE_SHUTOFF)
{
  m0 = m1 = m2 = m3 = ROTOR_ZERO_LEVEL;
}
#endif
update_rotors(m0, m1, m2, m3);
}

void setpoint_update() {
  // here we allow +- 20 for noise and sensitivity on the RX controls...
  // ROLL rx at mid level?
  if (rx_values[0] > THROTTLE_RMID - 20 && rx_values[0] < THROTTLE_RMID + 20)
    roll.setpoint = 0;
  else
    roll.setpoint = map(rx_values[0], ROLL_RMIN, ROLL_RMAX, ROLL_WMIN, ROLL_WMAX);
  //PITCH rx at mid level?
  if (rx_values[1] > THROTTLE_RMID - 20 && rx_values[1] < THROTTLE_RMID + 20)
    pitch.setpoint = 0;
  else
    pitch.setpoint = map(rx_values[1], PITCH_RMIN, PITCH_RMAX, PITCH_WMIN, PITCH_WMAX);
  //YAW rx at mid level?
  if (rx_values[3] > THROTTLE_RMID - 20 && rx_values[3] < THROTTLE_RMID + 20)
    yaw.setpoint = 0;
  else
    yaw.setpoint = map(rx_values[3], YAW_RMIN, YAW_RMAX, YAW_WMIN, YAW_WMAX);
}
