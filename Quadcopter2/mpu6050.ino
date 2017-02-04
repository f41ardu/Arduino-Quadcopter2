/*
   Devlopment Branch
*/
// To support a direkt connected MPU6050 on Arduino some rework is still required
// This code is primarily based on the I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class using DMP (MotionApps v2.0)
// 6/21/2012 by Jeff Rowberg <jeff@rowberg.net>
/*  Hardware setup:
  MPU6050 Breakout --------- Arduino
  3.3V --------------------- 3.3V
  SDA ----------------------- A4
  SCL ----------------------- A5
  GND ---------------------- GND
  INT ---------------------- See PIN_MPU in Configuration.h
  See comments below
*/
/*
   This variables are private to MPU6050.ini
   angleX,angleY,angleZ are global variables used in the main code
*/
// MPU Definitions
// class default I2C address is 0x68
MPU6050 mpu;
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// code begins here
/*
     Four functions:
     dmpDataReady (could be solved using an _state variable)
     mpu_init
     mpu_update (called coniniously from loop)
     mpu_ypr calculate YAW, PITCH and ROLL
*/
// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================
// Needed by MPU6050
void dmpDataReady() {
  latest_interrupted_pin = PCintPort::arduinoPin;
  if ( latest_interrupted_pin == PIN_MPU) mpuInterrupt = true;
}
// ================================================================
// ===               MPU INIT ROUTINE                           ===
// ================================================================
void mpu_init() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  mpu.initialize();
  // enable Arduino interrupt detection
  pinMode(PIN_MPU, INPUT);
  digitalWrite(PIN_MPU, HIGH); // Pullup
  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
  delay(500);
  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();
  // supply your own gyro offsets here, scaled for min sensitivity
  /*
    mpu.setXGyroOffset(1);
    mpu.setYGyroOffset(2);
    mpu.setZGyroOffset(2);
    mpu.setZAccelOffset(2); // 1688 factory default for my test chip
  */
  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    PCintPort::attachInterrupt(PIN_MPU, &dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;
    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
}
// ================================================================
// ===               MPU Calculate YPR ROUTINE                  ===
// ================================================================
void  mpu_ypr() {
  // Quaternions and parameters for 6 DoF sensor fusion calculations
  Quaternion q;          // [w, x, y, z]         quaternion container
  float angles[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
  VectorFloat gravity;    // [x, y, z]            gravity vector
  if (!dmpReady) return;
  // wait for MPU interrupt or extra packet(s) available
  while (!mpuInterrupt && fifoCount < packetSize) {
    // do nothing here
  }
  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  // get current FIFO count
  fifoCount = mpu.getFIFOCount();
  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    //    Serial.println(F("FIFO overflow!"));
    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;
    // get quaternion values in InvenSense Teapot format and store them in q
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    // uncerttain if this is necessaary (it is used in the Processing teapot example)
    if (q.w >= 2.0f) q.w = -4.0f + q.w;
    if (q.x >= 2.0f) q.x = -4.0f + q.x;
    if (q.y >= 2.0f) q.y = -4.0f + q.y;
    if (q.z >= 2.0f) q.z = -4.0f + q.z;
    mpu.dmpGetYawPitchRoll(angles, &q, &gravity);
    mpu.getMotion6(&ACC.x, &ACC.y, &ACC.z, &GYRO.x, &GYRO.y, &GYRO.z);
    // YAW,PITCH,ROLL in degress
    /* for (int i = 0; i < 3; i++) {
      angles[i] = angles[i] * 180. / PI; // index 0 = YAW, 1 = PITCH, 2 = ROLL
      }
    */
    // index 0 = YAW, 1 = PITCH, 2 = ROLL
    quad.pitch = angles[1] * PI2DEG;
    quad.roll  = angles[2] * PI2DEG;
    quad.yaw   = angles[0] * PI2DEG;
  }
}


