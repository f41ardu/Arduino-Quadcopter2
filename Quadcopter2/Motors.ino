/*
 * Devlopment Branch
 */
Servo rotor0, rotor1, rotor2,  rotor3;

void rotors_initialize(){
  
  rotor0.attach(PIN_ROTOR0);
  rotor1.attach(PIN_ROTOR1);
  rotor2.attach(PIN_ROTOR2);
  rotor3.attach(PIN_ROTOR3);
  
  rotor0.writeMicroseconds(ROTOR_ZERO_LEVEL);
  rotor1.writeMicroseconds(ROTOR_ZERO_LEVEL);
  rotor2.writeMicroseconds(ROTOR_ZERO_LEVEL);
  rotor3.writeMicroseconds(ROTOR_ZERO_LEVEL);

}

void rotors_arm(){

  rotor0.writeMicroseconds(ROTOR_ZERO_LEVEL);
  rotor1.writeMicroseconds(ROTOR_ZERO_LEVEL);
  rotor2.writeMicroseconds(ROTOR_ZERO_LEVEL);
  rotor3.writeMicroseconds(ROTOR_ZERO_LEVEL);

}

void update_rotors(int m0, int m1, int m2, int m3)
{
  
  rotor0.writeMicroseconds(m0);
  rotor1.writeMicroseconds(m1);
  rotor2.writeMicroseconds(m2);
  rotor3.writeMicroseconds(m3);
  
}
