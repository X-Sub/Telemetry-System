/* ###################################################################
**     Filename    : Events.h
**     Project     : IMU I2C Code Test
**     Processor   : MCF51QE128CLK
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2015-07-17, 18:57, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "CI2C1.h"


void CI2C1_OnReceiveData(void);
/*
** ===================================================================
**     Event       :  CI2C1_OnReceiveData (module Events)
**
**     Component   :  CI2C1 [InternalI2C]
**     Description :
**         This event is invoked when I2C finishes the reception of the
**         data successfully. This event is not available for the SLAVE
**         mode and if both RecvChar and RecvBlock are disabled. This
**         event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void CI2C1_OnTransmitData(void);
/*
** ===================================================================
**     Event       :  CI2C1_OnTransmitData (module Events)
**
**     Component   :  CI2C1 [InternalI2C]
**     Description :
**         This event is invoked when I2C finishes the transmission of
**         the data successfully. This event is not available for the
**         SLAVE mode and if both SendChar and SendBlock are disabled.
**         This event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

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
