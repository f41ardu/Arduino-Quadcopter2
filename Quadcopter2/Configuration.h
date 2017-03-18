/*
 *  Devlopment Branch variables
 */
#define SAFE

//------QUAD TYPE -----------
// #define QUADX 1
#define QUADP 1
#define YAW_DIRECTION 1
// define YAW_DIRECTION -11

//-------PID Config----------
#define ROLL_PID_KP  0.250
#define ROLL_PID_KI  0.950
#define ROLL_PID_KD  0.011
#define ROLL_PID_MIN  -200.0
#define ROLL_PID_MAX  200.0

#define PITCH_PID_KP  0.250
#define PITCH_PID_KI  0.950
#define PITCH_PID_KD  0.011
#define PITCH_PID_MIN  -200.0
#define PITCH_PID_MAX  200.0

#define YAW_PID_KP  0.680
#define YAW_PID_KI  0.500
#define YAW_PID_KD  0.0001
#define YAW_PID_MIN  100.0
#define YAW_PID_MAX  100.0

//-------------------------



//-------RX Config----------
#define THROTTLE_RMIN  1000
#define THROTTLE_SAFE_SHUTOFF 1120
#define THROTTLE_RMAX  1900
#define THROTTLE_RMID  1470

#define ROLL_RMIN  THROTTLE_RMIN
#define ROLL_RMAX  THROTTLE_RMAX
#define ROLL_WMIN  -30
#define ROLL_WMAX  30

#define PITCH_RMIN  THROTTLE_RMIN
#define PITCH_RMAX  THROTTLE_RMAX
#define PITCH_WMIN  -30
#define PITCH_WMAX  30

#define YAW_RMIN  THROTTLE_RMIN
#define YAW_RMAX  THROTTLE_RMAX
#define YAW_WMIN  -30
#define YAW_WMAX  30

//-------IMU Config-----------
//#define ADDR_SLAVE_I2C 0x68
//#define PACKET_SIZE 42

//-------Debug Config---------
#define DEBUG_OUTPUT
// #define DEBUG_ANGLES
// #define DEBUG_ACC
// #define DEBUG_GYRO
// #define DEBUG_PID
// #define DEBUG_RX
// #define DEBUG_MOTORS
// #define DEBUG_LOOP_TIME
#define DEBUG_YAWPITCHROLL
//----------------------------

//-------Motor PWM Levels
#define ROTOR_ZERO_LEVEL  1000
#define ROTOR_ARM_START  1500
#define ROTOR_MAX_LEVEL  2000


//-------RX PINS-------------
#define RX_PINS_OFFSET 2
#define PIN_RX_ROLL 3
#define PIN_RX_PITCH 4
#define PIN_RX_THROTTLE 5
#define PIN_RX_YAW 6

//-------ROTOR PINS-----------
#define PIN_ROTOR0  7
#define PIN_ROTOR1  9
#define PIN_ROTOR2  10
#define PIN_ROTOR3  11

//-------MPU6050 PIN-------
#define PIN_MPU 12  // we use pin 12 (see PinChangeInt for details)

//-------LED PINS-------------
#define HEARTBEAT_LED 13

/*
      Code from Multiww_2 output.cpp
    #define PIDMIX(X,Y,Z) rcCommand[THROTTLE] + axisPID[ROLL]*X + axisPID[PITCH]*Y + YAW_DIRECTION * axisPID[YAW]*Z
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


