/*
 * Production Branch
 */
void control_update(){
  throttle=map(rx_values[2],THROTTLE_RMIN,THROTTLE_RMAX,MOTOR_ZERO_LEVEL,MOTOR_MAX_LEVEL);
  
  setpoint_update();
  pid_update();
  pid_compute();


/* 
 *  See Multiww_2 output.cpp
 *  #define PIDMIX(X,Y,Z) rcCommand[THROTTLE] + axisPID[ROLL]*X + axisPID[PITCH]*Y + YAW_DIRECTION * axisPID[YAW]*Z
  #if defined( MY_PRIVATE_MIXING )
    #include MY_PRIVATE_MIXING
  #elif defined( BI )
    motor[0] = PIDMIX(+1, 0, 0); //LEFT
    motor[1] = PIDMIX(-1, 0, 0); //RIGHT
    servo[4] = (SERVODIR(4,2) * axisPID[YAW]) + (SERVODIR(4,1) * axisPID[PITCH]) + get_middle(4); //LEFT
    servo[5] = (SERVODIR(5,2) * axisPID[YAW]) + (SERVODIR(5,1) * axisPID[PITCH]) + get_middle(5); //RIGHT
  #elif defined( TRI )
    motor[0] = PIDMIX( 0,+4/3, 0); //REAR
    motor[1] = PIDMIX(-1,-2/3, 0); //RIGHT
    motor[2] = PIDMIX(+1,-2/3, 0); //LEFT
    servo[5] = (SERVODIR(5, 1) * axisPID[YAW]) + get_middle(5); //REAR
  #elif defined( QUADP )
    motor[0] = PIDMIX( 0,+1,-1); //REAR
    motor[1] = PIDMIX(-1, 0,+1); //RIGHT
    motor[2] = PIDMIX(+1, 0,+1); //LEFT
    motor[3] = PIDMIX( 0,-1,-1); //FRONT
  #elif defined( QUADX )
    motor[0] = PIDMIX(-1,+1,-1); //REAR_R
    motor[1] = PIDMIX(-1,-1,+1); //FRONT_R
    motor[2] = PIDMIX(+1,+1,+1); //REAR_L
    motor[3] = PIDMIX(+1,-1,-1); //FRONT_L
 */

  
  // yaw control disabled for stabilization testing...
  m0 = throttle + pid_pitch_out ;//+ pid_yaw_out;
  m1 = throttle + pid_roll_out ;//- pid_yaw_out;
  m2 = throttle - pid_pitch_out ;//+ pid_yaw_out;
  m3 = throttle - pid_roll_out ;//- pid_yaw_out;
  
  #ifdef SAFE
    if(throttle < THROTTLE_SAFE_SHUTOFF)
    {
      m0 = m1 = m2 = m3 = MOTOR_ZERO_LEVEL;
    }
  #endif



 
  
  update_motors(m0, m1, m2, m3);
}

void setpoint_update() {
  // here we allow +- 20 for noise and sensitivity on the RX controls...
  // ROLL rx at mid level?
  if(rx_values[0] > THROTTLE_RMID - 20 && rx_values[0] < THROTTLE_RMID + 20)
    pid_roll_setpoint = 0;
  else
    pid_roll_setpoint = map(rx_values[0],ROLL_RMIN,ROLL_RMAX,ROLL_WMIN,ROLL_WMAX);
  //PITCH rx at mid level?
  if(rx_values[1] > THROTTLE_RMID - 20 && rx_values[1] < THROTTLE_RMID + 20)
    pid_pitch_setpoint = 0;
  else
    pid_pitch_setpoint = map(rx_values[1],PITCH_RMIN,PITCH_RMAX,PITCH_WMIN,PITCH_WMAX);
  //YAW rx at mid level?
  if(rx_values[3] > THROTTLE_RMID - 20 && rx_values[3] < THROTTLE_RMID + 20)
    pid_yaw_setpoint = 0;
  else
    pid_yaw_setpoint = map(rx_values[3],YAW_RMIN,YAW_RMAX,YAW_WMIN,YAW_WMAX);
}
