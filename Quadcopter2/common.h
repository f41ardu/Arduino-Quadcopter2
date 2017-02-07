/*  
 * Common Variables  
 * 
 * Devlopment Branch  
 */


struct SENSOR_YPR {
// angles
  float yaw;
  float pitch;
  float roll;
// gyro
  int16_t gx;
  int16_t gy;
  int16_t gz;
// acc
  int16_t ax;
  int16_t ay;
  int16_t az;
};

struct QUAD_PID {
  double in; 
  double out; 
  double setpoint;
}; 

