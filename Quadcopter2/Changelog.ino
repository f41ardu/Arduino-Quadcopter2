/* 
 *  Changelog (in reverse order, current first)
 *  
 *  Devlopment Branch
 *  
 *  2017-02-07 f41ardu moved PID variables back to main ino
 *  
 *  2017-02-07 f41ardu moved pid strict into pidcontroler.ino
 * disabled quad limitation 
 *  
 *  2017-02-07 f41ardu introduced struct for pid variables
 *  
 *  2017-02-07 f41ardu removed volatile from struct, moved all sensor variables into one structure 
 *  see common.h, removed common sensor and passing SENSOR struct as pointer in functions.  
 *  Simplified PidController.ino and moved compute into Quadcontroll
 *  
 *  2017-02-04 f41ardu volatile struct 
 *  
 *  2017-02-04 f41ardu removed mpu_update and merged into mpu_ypr
 *  
 *  2017-02-04 f41ardu introduced motormix
 *  
 *  2017-01-15 f41ardu - moved Quaterion variables into functions (mpu6050.ino) 
 *  Removed comments in pinclass2.cpp
 *  
 *  2017-01-15 f41ardu - introduce struct variables to store YAWPITCHROLL and ACC and GYRO values from sensor 
 *  Introduce common.h to for structs
 *  
 *  2017-01-13 f41ardu - start devlopement
 *  
 */
