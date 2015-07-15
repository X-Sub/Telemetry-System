/* ###################################################################
**     Filename    : Events.c
**     Project     : X-Sub MCU Firmware
**     Processor   : MCF51QE128CLK
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2015-05-30, 09:28, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
/*Mis includes*/
#include "xSub.h"



/*
 * Variables
 */
bool led0x00 = FALSE; //0x00 sMCU_OK Led
bool led0x01 = FALSE; //0x01 sCom_In Led
bool led0x02 = FALSE; //0x02 sPC_OK  Led
bool led0x03 = FALSE; //0x03
bool led0x04 = FALSE; //0x04
bool led0x05 = FALSE; //0x05
bool led0x06 = FALSE; //0x06
bool led0x07 = FALSE; //0x07

byte SerialIn;

//Tiempo
byte tLed = 0x00;
byte tMotor = 0x00;

/*
** ===================================================================
**     Event       :  Aux_Int_OnInterrupt (module Events)
**
**     Component   :  Aux_Int [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

//Resolucion de 10 ms
void Aux_Int_OnInterrupt(void)
{
	//Bucle para 100 ms de leds
	if(tLed != 10-1)
	{
		tLed++;
	}
	else
	{
		//Control de leds de status
					if(led0x00 == TRUE) sMCU_OK_NegVal(); //0x00
					else sMCU_OK_SetVal();
					if(led0x01 == TRUE) sCom_In_NegVal(); //0x01
					else sCom_In_SetVal();
					if(led0x02 == TRUE) sPC_OK_NegVal(); //0x02
					else sPC_OK_SetVal();
					tLed = 0;
	}
	
	
	//Bucle para 100 ms de leds
	if(tMotor != 2-1)
	{
		tMotor++;
	}
	else
	{
		
	}
	
} 

/*
** ===================================================================
**     Event       :  SerialCom_OnRxChar (module Events)
**
**     Component   :  SerialCom [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  SerialCom_OnRxChar(void)
{
  /* Write your code here ... */
	sPC_OK_W();
	
	(void)SerialCom_RecvChar(&SerialIn);
	setMotorSpeed256(SerialIn,1);
	(void)SerialCom_SendChar(SerialIn);
	//(void)SerialCom_ClearRxBuf();
	//(void)SerialCom_ClearTxBuf();
}

/*
** ===================================================================
**     Event       :  SerialCom_OnTxChar (module Events)
**
**     Component   :  SerialCom [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  SerialCom_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  RESET_INTERRUPT_OnInterrupt (module Events)
**
**     Component   :  RESET_INTERRUPT [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RESET_INTERRUPT_OnInterrupt(void)
{
  /* place your RESET_INTERRUPT interrupt procedure body here*/
	setMotorSpeed1024(0,2);
	delay(2000);

}

/*
** ===================================================================
**     Event       :  ADC_OnEnd (module Events)
**
**     Component   :  ADC [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ADC_OnEnd(void)
{
  /* Write your code here ... */
}


/* END Events */

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
