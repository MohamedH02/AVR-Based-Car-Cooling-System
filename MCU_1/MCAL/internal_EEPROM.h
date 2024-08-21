/******************************************************************************
 *
 * Module: Internal EEPROM
 *
 * File Name: internal_EEPROM.h
 *
 * Description: Header file for the internal EEPROM driver
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#ifndef INTERNAL_EEPROM_H_
#define INTERNAL_EEPROM_H_

#include "..\std_types.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/******************************************************************************
 * Service Name: INTERNAL_EEPROM_writeByte
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): Address - The memory address to write to within the EEPROM
 *                  Data - The byte of data to be written to the specified address
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Writes a single byte of data to a specified address in the internal EEPROM.
 *******************************************************************************/
void INTERNAL_EEPROM_writeByte(uint16 Address, uint8 Data);

/******************************************************************************
 * Service Name: INTERNAL_EEPROM_readByte
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): Address - The memory address to read from within the EEPROM
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: uint8 - The byte of data read from the specified address
 * Description: Reads a single byte of data from a specified address in the internal EEPROM.
 *******************************************************************************/
uint8 INTERNAL_EEPROM_readByte(uint16 Address);

#endif /* INTERNAL_EEPROM_H_ */
