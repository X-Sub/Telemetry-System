/*
 * Init.c
 *
 *  Created on: Jul 9, 2015
 *      Author: ddtdanilo
 */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/*Mis includes*/
#include "xSub.h"
//#include "OneWire.h"

/*I2C*/

byte MPU6050_ACCEL_CONFIG = 0x1C;   // R/W
byte MPU6050_AFS_SEL_4G = 0x08; //Config para +-4G
byte MPU6050_GYRO_CONFIG = 0x1B; //R/W
byte MPU6050_FS_SEL_1000 = 0x10; //Config para +-1000º/s
byte MPU = 0x68;  // I2C address of the MPU-6050
byte HMC6352 = 0x21;  // I2C address of the HMC6352 Compass

/*Puerto Serial*/
byte SIZEBUFFERIN = 5;
byte SIZEBUFFEROUT = 27;

/*Constantes de Motores*/
word CENTERDC = 0xED71; //7.2432% = 0xFFFF-0x128A = 65536-4747
word MAXFORWARD = 59162;
word MAXBACKWARD = 62200;
//word MINSERVOUS = 500;
//word MAXSERVOUS = 3000;
word MINSERVOUS = 900; //useg
word MAXSERVOUS = 3300; //useg


/*Variables físicas*/
byte  SIZEPACKAGE = 27;

vFisica8  STATUS;
vFisica16 tempExterna;
vFisica16 tempInterna;
vFisica16 presExterna;
vFisica16 aceleracionX;
vFisica16 aceleracionY;
vFisica16 aceleracionZ;
vFisica16 velAngularX;
vFisica16 velAngularY;
vFisica16 velAngularZ;
vFisica16 velLineal;
vFisica16 angBrujula;
vFisica8  presenciaAgua;
vFisica8  cargaBaterias;
vFisica8  XOR;
vFisica8  finTrama;


