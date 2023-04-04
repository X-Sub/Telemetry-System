/*
 * OneWire.h
 *
 *  Created on: Oct 17, 2015
 *      Author: ddtdanilo
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

// Configure UART for 1-Wire RESET timing
byte onewireReset();
byte onewireWriteByte(byte byteIn);
byte onewireReadByte();
byte onewireBit(byte bit);
// Wake up every 5 seconds and write to the server
float awakeAndGetTemp();


#endif /* ONEWIRE_H_ */
