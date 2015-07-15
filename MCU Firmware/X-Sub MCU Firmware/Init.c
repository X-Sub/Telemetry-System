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

void initVFisicas(){
	//Genera la numeración de la posición
	STATUS.pos = 0;
	tempExterna.HIGH.pos = STATUS.pos + 1;
	tempExterna.LOW.pos = tempExterna.HIGH.pos + 1;
	tempInterna.HIGH.pos = tempExterna.LOW.pos + 1;
	tempInterna.LOW.pos = tempInterna.HIGH.pos + 1;
	presExterna.HIGH.pos = tempInterna.LOW.pos + 1;
	presExterna.LOW.pos = presExterna.HIGH.pos + 1;
	aceleracionX.HIGH.pos = presExterna.LOW.pos + 1;
	aceleracionX.LOW.pos = aceleracionX.HIGH.pos + 1;
	/*
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
	*/
}
void vFisicas2Array(byte paquete[]){
	
}
