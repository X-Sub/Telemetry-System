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





//Cambia el Status de un LED
//Hace que se mantenga encendido o titilando si està activo.
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
	lStatus(0x01,FALSE);
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
	spDC = (CENTERDC); //0xED71 = 7.24% = 60788
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
//SERVOS

  /*Pan*/
void servoPanAngle(word Angle)//Resolución de 0 - 179
{
	Angle = map(Angle,0,179,MINSERVOUS,MAXSERVOUS);
	S_PanCamera_SetDutyUS(Angle);
}

void servoPan1024(word In)//Resolución de 0 - 1023 (0 - 0x1023)
{
	In = map(In,0,1023,MINSERVOUS,MAXSERVOUS);
	S_PanCamera_SetDutyUS(In);
}

   /*Tilt*/
void servoTiltAngle(word Angle)//Resolución de 0 - 179
{
	Angle = map(Angle,0,179,MINSERVOUS,MAXSERVOUS);
	S_TiltCamera_SetDutyUS(Angle);
}

void servoTilt1024(word In)//Resolución de 0 - 1023 (0 - 0x1023)
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











