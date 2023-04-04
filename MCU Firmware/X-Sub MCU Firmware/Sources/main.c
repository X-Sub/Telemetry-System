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
**		Universidad Simón Bolívar (USB)
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
#include "CS1.h"
#include "I2C.h"
#include "PresenciaAgua2.h"
#include "PresenciaAgua1.h"
#include "S_Wire.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
/*Mis includes*/
#include "xSub.h"
#include "OneWire.h"

void main(void)
{
  /* Write your local variable definition here */
	byte byteDC = 0x00;
	word DC = 0;
	word DC2 = 0x0000;
	byte pDC = 0; //%
	word err = 0x00;
	
	byte Agua1 = 0x00;
	byte Agua2 = 0x00;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  //delay(5000);
  /*
  sMCU_OK_W();
  sCom_In_W();
  sPC_OK_NW();
  initMxSub(1);
  */
  //initMxSub(1);
 //delay(100);
  
  
  /**********I2C test********/
  //initMPU();
  //initHMC6352();
  //sMCU_OK_W();
  //sPC_OK_W();
  //(void)initxSub();
  
  //sPC_OK_W();
  if(initxSub() == 0xFF)
  {
	  sMCU_OK_W();
  }
  else sMCU_OK_NW();
  getDataAll();
  for(;;)
  {	  
	  getDataAll();
	  envioData();
	  //delay(10);
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
