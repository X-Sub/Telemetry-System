/* ###################################################################
**     Filename    : main.c
**     Project     : X-Sub MCU Firmware
**     Processor   : MCF51QE128CLK
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2015-05-30, 09:28, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**		Firmware made by Danilo D. for the Mechatronics Research and Development of the
**		Universidad Sim�n Bol�var (USB)
**		www.usb.ve
**		mecatronica.labc.usb.ve
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "M1_ESC.h"
#include "M2_ESC.h"
#include "M3_ESC.h"
#include "M4_ESC.h"
#include "S_PanCamera.h"
#include "S_TiltCamera.h"
#include "sMCU_OK.h"
#include "sPC_OK.h"
#include "sCom_In.h"
#include "Aux_Int.h"
#include "SerialCom.h"
#include "RESET_INTERRUPT.h"
#include "ADC.h"
#include "LedLight1.h"
#include "LedLight2.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
/*Mis includes*/
#include "xSub.h"

void main(void)
{
  /* Write your local variable definition here */
	word DC = 0x0000;
	word DC2 = 0x0000;
	byte pDC = 0; //%
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  //delay(5000);
  (void)SerialCom_SendChar(0xFF);
  initMxSub(1);
  
  sMCU_OK_W();
  //sMCU_OK_NW();
  //sCom_In_NW();
  //sPC_OK_NW();
  //setDC(0x19C8);
  
  for(;;)
  {
	 ADC_Measure(TRUE);
	 ADC_GetValue16(&DC);
	 DC = DC >> 4;
	 //DC2 = (0xFFFF-0xFFFF*0.0535 - 0xFFFF-0xFFFF*0.0915)/2;
	 //setDC(DC2);
	 //DC2 = map(DC,0,0xFFF,0,179);
	 //DC2 = map(DC,0,0xFFF,0xED71,62200);
	 //setDC(DC2);
	 
	  //setMotorSpeed(1023,2);
	  //delay(2000);
	  //S_PanCamera_SetRatio16(520);
	 //servoPanAngle(DC2);
	 //S_PanCamera_SetDutyUS(1500);
	  /*
	  servoTiltAngle(0);
	  delay(2000);
	  //S_PanCamera_SetRatio16(0xE470);
	  servoTiltAngle(89);
	  delay(2000);
	  servoTiltAngle(179);
	  delay(2000);
	  servoTiltAngle(89);
	  delay(2000);
	  */
	  
	  
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
