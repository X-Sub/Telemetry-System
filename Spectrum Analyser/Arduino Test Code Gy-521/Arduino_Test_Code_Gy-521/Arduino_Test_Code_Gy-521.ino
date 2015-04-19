// MPU-6050 Gy-521
// By Danilo D
// April 2015
// Public Domain

#include<Wire.h>
#define MPU6050_ACCEL_CONFIG       0x1C   // R/W
#define MPU6050_AFS_SEL_4G 0x08 //Config para +-4G
#define MPU6050_GYRO_CONFIG 0x1B //R/W
#define MPU6050_FS_SEL_1000 0x10 //Config para +-1000º/s

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
  
  MPU6050_write_reg(MPU6050_ACCEL_CONFIG,MPU6050_AFS_SEL_4G);//+-4G
  MPU6050_write_reg(MPU6050_GYRO_CONFIG,MPU6050_FS_SEL_1000);//+-1000º/s
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

  Serial.write(GyYL);
  Serial.write(GyYH);
  Serial.write('\0');

  //Serial.write(0xFF);
  delay(20);
}
















// MPU6050_write
//
// This is a common function to write multiple bytes to an I2C device.
//
// If only a single register is written,
// use the function MPU_6050_write_reg().
//
// Parameters:
//   start : Start address, use a define for the register
//   pData : A pointer to the data to write.
//   size  : The number of bytes to write.
//
// If only a single register is written, a pointer
// to the data has to be used, and the size is
// a single byte:
//   int data = 0;        // the data to write
//   MPU6050_write (MPU6050_PWR_MGMT_1, &c, 1);
//
int MPU6050_write(int start, const uint8_t *pData, int size)
{
  int n, error;

  Wire.beginTransmission(MPU);
  n = Wire.write(start);        // write the start address
  if (n != 1)
    return (-20);

  n = Wire.write(pData, size);  // write data bytes
  if (n != size)
    return (-21);

  error = Wire.endTransmission(true); // release the I2C-bus
  if (error != 0)
    return (error);

  return (0);         // return : no error
}


// MPU6050_write_reg
//
// An extra function to write a single register.
// It is just a wrapper around the MPU_6050_write()
// function, and it is only a convenient function
// to make it easier to write a single register.
//
int MPU6050_write_reg(int reg, uint8_t data)
{
  int error;

  error = MPU6050_write(reg, &data, 1);

  return (error);
}
