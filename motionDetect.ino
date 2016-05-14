#include <Wire.h>

int mpu = 0x68; // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void AccelSetup() {
  // Accelerometer setup
  Wire.begin(); 
  Wire.beginTransmission(mpu);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // Wake up the MPU-6050
  Wire.endTransmission(true);
  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
}

void accelDetect(){
  Wire.beginTransmission(mpu);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(mpu,14,true);
  AcX=Wire.read();//<<8|Wire.read();
  AcY=Wire.read();//<<8|Wire.read();
  AcZ=Wire.read();//<<8|Wire.read();
 
  Tmp=Wire.read()<<8|Wire.read();
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read(); 
  delay(33);
  
  // if acceleration in X direction is greater than 20, motion is detected
  if (AcX > 20)
  {
    // motion detected (1)
    cur_acc = 1;
    delay(500);
  }
  else
  {
    //no motion detected (0)
    cur_acc = 0;
    delay(500);
  }

  if ( cur_acc == 1 & cur_acc != prev_acc)
  {
    // motion is detected for the first time
    return 1;
  }
  if ( cur_acc == 0 & cur_acc != prev_acc)
  {
    // motion is not detected for the first time
    return 0;
  }
  prev_acc = cur_acc;
}


