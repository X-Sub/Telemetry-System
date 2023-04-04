/*
 * xSub.c
 *
 *  Created on: Jun 11, 2015
 *      Author: ddtdanilo
 */

/*Includes*/
#include "Cpu.h"
#include "Events.h"
#include "M1_ESC.h"
#include "M2_ESC.h"
#include "M3_ESC.h"
#include "M4_ESC.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/*Mis includes*/
#include "xSub.h"
#include "OneWire.h"




//Cambia el Status de un LED
//Hace que se mantenga encendido o titilando si est� activo.
void lStatus(byte nLed, bool status)
{
	switch(nLed)
	{
		case 0x00:
			led0x00 = status;
			break;
			
		case 0x01:
			led0x01 = status;		
			break;
			
		case 0x02:
			led0x02 = status;				
			break;
		
		case 0x03:
			led0x03 = status;				
			break;
			
		case 0x04:
			led0x04 = status;				
			break;
		
		case 0x05:
			led0x05 = status;		
			break;
					
		case 0x06:
			led0x06 = status;				
			break;
			
		case 0x07:
			led0x07 = status;						
			break;
				
	}
}

//Activa a sMCU_OK
void sMCU_OK_W()
{
	lStatus(0x00,TRUE);
}

//Desactiva a sMCU_OK
void sMCU_OK_NW()
{
	lStatus(0x00,FALSE);
}

//Muestra titilando a sPC_OK
void sCom_In_W()
{
	lStatus(0x01,TRUE);
}

//Muestra titilando a sPC_OK
void sCom_In_NW()
{
	lStatus(0x01,FALSE);
}

//Muestra titilando a sPC_OK
void sPC_OK_W()
{
	lStatus(0x02,TRUE);
}

//Muestra titilando a sPC_OK
void sPC_OK_NW()
{
	lStatus(0x02,FALSE);
}

//paraliza el MCU por el tiempo time en ms
void delay(word time)
{
	//sPC_OK_W();
	Cpu_Delay100US(time*10);
}


//Inicializa los motores
void initMxSub(byte tipo){
	if(tipo == 1)//HK 30A
	{
	word spDC;
	M1_ESC_Enable();
	M2_ESC_Enable();
	M3_ESC_Enable();
	M4_ESC_Enable();
	spDC = CENTERDC; //0xED71 = 7.24% = 60788
	M1_ESC_SetRatio16(spDC);
	M2_ESC_SetRatio16(spDC);
	M3_ESC_SetRatio16(spDC);
	M4_ESC_SetRatio16(spDC);
	delay(5000);
	}
	
	if(tipo == 2)//Skywing
		{
		word spDC;
		M1_ESC_Enable();
		M2_ESC_Enable();
		M3_ESC_Enable();
		M4_ESC_Enable();
		spDC = MAXFORWARD;
		M1_ESC_SetRatio16(spDC);
		M2_ESC_SetRatio16(spDC);
		M3_ESC_SetRatio16(spDC);
		M4_ESC_SetRatio16(spDC);
		delay(5000);
		}
	

}

//Coloca un DC a todos los motores
void setDC(word Speed)
{
 (void)M1_ESC_SetRatio16(Speed);
 (void)M2_ESC_SetRatio16(Speed);
 (void)M3_ESC_SetRatio16(Speed);
 (void)M4_ESC_SetRatio16(Speed);
}

//Setea la velocidad de los motores de manera individual. Rango de 10 bits-> 0 - 1023
void setMotorSpeed1024(word Speed,byte Motor){
	
	Speed = map(Speed,0,1023,MAXFORWARD,MAXBACKWARD);
	
	switch(Motor){
	
	case 1:
		    (void)M1_ESC_SetRatio16(CENTERDC);
			(void)M1_ESC_SetRatio16(Speed);
	case 2:
		    (void)M2_ESC_SetRatio16(CENTERDC);
			(void)M2_ESC_SetRatio16(Speed);
	case 3:
		    (void)M3_ESC_SetRatio16(CENTERDC);
			(void)M3_ESC_SetRatio16(Speed);
	case 4:
		    (void)M4_ESC_SetRatio16(CENTERDC);
			(void)M4_ESC_SetRatio16(Speed);	
	}
}

//Setea la velocidad de los motores de manera individual. Rango de 8 bits-> 0 - 255
void setMotorSpeed256(byte Speed,byte Motor){
	
	Speed = map(Speed,0,255,MAXFORWARD,MAXBACKWARD);
	
	switch(Motor){
	
	case 1:
		    (void)M1_ESC_SetRatio8(CENTERDC);
			(void)M1_ESC_SetRatio8(Speed);
	case 2:
		    (void)M2_ESC_SetRatio8(CENTERDC);
			(void)M2_ESC_SetRatio8(Speed);
	case 3:
		    (void)M3_ESC_SetRatio8(CENTERDC);
			(void)M3_ESC_SetRatio8(Speed);
	case 4:
		    (void)M4_ESC_SetRatio8(CENTERDC);
			(void)M4_ESC_SetRatio8(Speed);	
	}
}

//Setea la velocidad de los motores de manera individual. Rango de 10 bits-> 0 - 1023 SKYWING
void setMotorSpeed1024SW(word Speed,byte Motor){
	
	Speed = map(Speed,0,1023,MAXBACKWARD,CENTERDC);
	
	switch(Motor){
	
	case 1:
		    
			(void)M1_ESC_SetRatio16(Speed);
	case 2:
		    
			(void)M2_ESC_SetRatio16(Speed);
	case 3:
		    
			(void)M3_ESC_SetRatio16(Speed);
	case 4:
		    
			(void)M4_ESC_SetRatio16(Speed);	
	}
}
//SERVOS

  /*Pan*/
void servoPanAngle(word Angle)//Resoluci�n de 0 - 179
{
	Angle = map(Angle,0,179,MINSERVOUS,MAXSERVOUS);
	S_PanCamera_SetDutyUS(Angle);
}

void servoPan1024(word In)//Resoluci�n de 0 - 1023 (0 - 0x1023)
{
	In = map(In,0,1023,MINSERVOUS,MAXSERVOUS);
	S_PanCamera_SetDutyUS(In);
}

   /*Tilt*/
void servoTiltAngle(word Angle)//Resoluci�n de 0 - 179
{
	Angle = map(Angle,0,179,MINSERVOUS,MAXSERVOUS);
	S_TiltCamera_SetDutyUS(Angle);
}

void servoTilt1024(word In)//Resoluci�n de 0 - 1023 (0 - 0x1023)
{
	In = map(In,0,1023,MINSERVOUS,MAXSERVOUS);
	S_TiltCamera_SetDutyUS(In);
}

/****LEDS****/
 void setLEDPWM(word PWM){
	 LedLight1_SetRatio16(PWM);
	 LedLight2_SetRatio16(PWM);
 }
 
 void setLED1PWM(word PWM){
	 LedLight1_SetRatio16(PWM);
 }
 
 void setLED2PWM(word PWM){
	 LedLight2_SetRatio16(PWM);
 }


//MAPEA
long map(long x, long in_min,long in_max,long out_min, long out_max){
	return (x-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;
}


/*I2C*/

byte writeRegisterI2C(byte reg, byte data)//manera sencilla de editar un registro
{
	byte DATA[2];
	byte MPU = 0x68;
	word Sent;
	byte err;
	DATA[0] = reg; // registro a editar
	DATA[1] = data; // data a enviar
	err = I2C_SendBlock(DATA,2,&Sent);
	return err;
}

void initMPU()//Inicializa la IMU
{
	byte err;
	byte reg = 0x6B; // PWR_MGMT_1 register
	byte data = 0x00; // set to zero (wakes up the MPU-6050)
	(void)I2C_SelectSlave(MPU);
	while(writeRegisterI2C(reg,data) != ERR_OK);
	delay(10);
	while(writeRegisterI2C(MPU6050_ACCEL_CONFIG,MPU6050_AFS_SEL_4G) != ERR_OK);//+-4G
	while(writeRegisterI2C(MPU6050_GYRO_CONFIG,MPU6050_FS_SEL_1000) != ERR_OK);//+-1000�/s
}


//Obtener data de la IMU. data debe ser de tama�o 14
void dataMPU(byte dataIn[])
{
	word Sent;
	(void)I2C_SelectSlave(MPU);
	while(I2C_SendChar(0x3B) != ERR_OK);
	while(I2C_RecvBlock(dataIn,14,&Sent) != ERR_OK);
}

void initHMC6352()//Inicializa la IMU
{
	byte err;
	byte reg = 0x6B; // PWR_MGMT_1 register
	byte data = 0x00; // set to zero (wakes up the MPU-6050)
	(void)I2C_SelectSlave(HMC6352);
}

//Obtener data del magnetometro. data debe ser de tama�o 2
void dataHMC6352(byte dataIn[])
{
	word Sent;
	(void)I2C_SelectSlave(HMC6352);
	while(I2C_SendChar('A') != ERR_OK){(void)SerialCom_SendChar(0xFF);};
	while(I2C_RecvBlock(dataIn,2,&Sent) != ERR_OK);
}

//Envio de data a PC
void dataTrans(byte dataOut[], byte tam)
{
	byte i = 0;
	for(i = 0;i<tam;i++){
		(void)SerialCom_SendChar(dataOut[i]);
	}
}

//envio de toda la data
void envioData()
{
	//dataTrans(data,SIZEPACKAGE);
	word error;
	(void)SerialCom_SendBlock(data,SIZEPACKAGE,&error);
}

void initVFisicas(){
	//Genera la numeraci�n de la posici�n
	STATUS.pos = 0;
	tempExterna.HIGH.pos = 1;
	tempExterna.LOW.pos = 2;
	tempInterna.HIGH.pos = 3;
	tempInterna.LOW.pos = 4;
	presExterna.HIGH.pos = 5;
	presExterna.LOW.pos = 6;
	aceleracionX.HIGH.pos = 7;
	aceleracionX.LOW.pos = 8;
	aceleracionY.HIGH.pos = 9;
	aceleracionY.LOW.pos = 10;
	aceleracionZ.HIGH.pos = 11;
	aceleracionZ.LOW.pos = 12;
	velAngularX.HIGH.pos = 13;
	velAngularX.LOW.pos = 14;
	velAngularY.HIGH.pos = 15;
	velAngularY.LOW.pos = 16;
	velAngularZ.HIGH.pos = 17;
	velAngularZ.LOW.pos = 18;
	velLineal.HIGH.pos = 19;
	velLineal.LOW.pos = 20;
	angBrujula.HIGH.pos = 21;
	angBrujula.LOW.pos = 22;
	presenciaAgua.pos = 23;
	cargaBaterias.pos = 24;
	XOR.pos = 25;
	finTrama.pos = 26;
}

void vFisicas2Array(){
	
	data[0] = STATUS.data;
	data[1] = tempExterna.HIGH.data;
	data[2] = tempExterna.LOW.data;
	data[3] = tempInterna.HIGH.data;
	data[4] = tempInterna.LOW.data;
	data[5] = presExterna.HIGH.data;
	data[6] = presExterna.LOW.data;
	data[7] = aceleracionX.HIGH.data;
	data[8] = aceleracionX.LOW.data;
	data[9] = aceleracionY.HIGH.data;
	data[10] = aceleracionY.LOW.data;
	data[11] = aceleracionZ.HIGH.data;
	data[12] = aceleracionZ.LOW.data;
	data[13] = velAngularX.HIGH.data;
	data[14] = velAngularX.LOW.data;
	data[15] = velAngularY.HIGH.data;
	data[16] = velAngularY.LOW.data;
	data[17] = velAngularZ.HIGH.data;
	data[18] = velAngularZ.LOW.data;
	data[19] = velLineal.HIGH.data;
	data[20] = velLineal.LOW.data;
	data[21] = angBrujula.HIGH.data;
	data[22] = angBrujula.LOW.data;
	data[23] = presenciaAgua.data;
	data[24] = cargaBaterias.data;
	data[25] = XOR.data;
	data[26] = finTrama.data;
}

//Inicializaci�n MCU

byte initxSub(){
	STATUS.data  = 0xA0;
	tempExterna.HIGH.data = 0x00;
	tempExterna.LOW.data = 0x00;
	tempInterna.HIGH.data = 0x00;
	tempInterna.LOW.data = 0x00;
	presExterna.HIGH.data = 0x00;
	presExterna.LOW.data = 0x00;
	aceleracionX.HIGH.data = 0x00;
	aceleracionX.LOW.data = 0x00;
	aceleracionY.HIGH.data = 0x00;
	aceleracionY.LOW.data = 0x00;
	aceleracionZ.HIGH.data = 0x00;
	aceleracionZ.LOW.data = 0x00;
	velAngularX.HIGH.data = 0x00;
	velAngularX.LOW.data = 0x00;
	velAngularY.HIGH.data = 0x00;
	velAngularY.LOW.data = 0x00;
	velAngularZ.HIGH.data = 0x00;
	velAngularZ.LOW.data = 0x00;
	velLineal.HIGH.data = 0x00;
	velLineal.LOW.data = 0x00;
	angBrujula.HIGH.data = 0x00;
	angBrujula.LOW.data = 0x00;
	presenciaAgua.data = 0x00;
	cargaBaterias.data = 0x00;
	XOR.data = 0x00;
	finTrama.data = 0xFF;
	
	initVFisicas();
	vFisicas2Array();
	
	//Dispositivos
	//initMPU();
	//initHMC6352();
	//initMxSub(1);
	
	return 0xFF;
	
	
}


