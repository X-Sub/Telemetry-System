// MPU-6050 Gy-521
// By Danilo D
// April 2015
// Public Domain

#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
//Aceleraciones H-> High, L -> Low
byte AcXH,AcXL;
byte AcYH,AcYL;
byte AcZH,AcZL;

//Velocidades Angulares H-> High, L -> Low
byte GyXH,GyXL;
byte GyYH,GyYL;
byte GyZH,GyZL;

//Temp
byte TmpH,TmpL;


void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
}

void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers

  AcXH = Wire.read();
  AcXL = Wire.read();

  AcYH = Wire.read();
  AcYL = Wire.read();

  AcZH = Wire.read();
  AcZL = Wire.read();

  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  TmpH = Wire.read();
  TmpL = Wire.read();


 GyXH = Wire.read();
 GyXL = Wire.read();

 GyYH = Wire.read();
 GyYL = Wire.read();

 GyZH = Wire.read();
 GyZL = Wire.read();

  //Simulink toma el primer byte y lo hace el menos significativo

  Serial.write(AcZL);
  Serial.write(AcZH);
  Serial.write('\0');

  //Serial.write(0xFF);
  delay(20);
}
