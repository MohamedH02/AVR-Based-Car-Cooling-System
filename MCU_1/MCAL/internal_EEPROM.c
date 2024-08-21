/******************************************************************************
 *
 * Module: Internal EEPROM
 *
 * File Name: internal_EEPROM.c
 *
 * Description: Source file for the internal EEPROM driver
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#include "internal_EEPROM.h"
#include "..\common_macros.h"
#include "avr/io.h"
#include <avr/delay.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
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
 *              The function waits until the EEPROM is ready for a new write operation,
 *              sets the address and data registers, and then triggers the EEPROM write operation.
 *
 *              Assembly instructions are used here to directly manipulate specific registers
 *              to trigger the EEPROM write operation, ensuring precise control over the number of clocks.
 *******************************************************************************/
void INTERNAL_EEPROM_writeByte(uint16 Address, uint8 Data) {
	/* Wait for the completion of any previous write operation */
	while(EECR & (1<<EEWE));

	/* Set up the address registers */
	EEARL = Address;
	EEARH = (Address >> 8);

	/* Load the data into the data register */
	EEDR = Data;

	/* Start the EEPROM write by setting the EEMWE bit using assembly instruction */
	asm("SBI 0x1C,2");

	 /* Trigger the write operation by setting the EEWE bit using assembly instruction */
	asm("SBI 0x1C,1");

}

/******************************************************************************
 * Service Name: INTERNAL_EEPROM_readByte
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): Address - The memory address to read from within the EEPROM
 * Parameters (inout): None
 * Parameters (out): uint8 - The byte of data read from the specified address
 * Return value: uint8 - The byte of data read from the specified address
 * Description: Reads a single byte of data from a specified address in the internal EEPROM.
 *              The function waits until the EEPROM and the Self-Programming Mode (SPM) are
 *              ready for a new operation, sets the address registers, and triggers the
 *              EEPROM read operation.
 *******************************************************************************/
uint8 INTERNAL_EEPROM_readByte(uint16 Address) {
	/* Wait for the completion of any previous write operation */
	while(EECR & (1<<EEWE));

	/* Wait until the Self-Programming Mode (SPM) is ready */
	while(SPMCR & (1<<SPMEN));

	/* Set up the address registers */
	EEARL = Address;
	EEARH = (Address >> 8);

	/* Start the EEPROM read by setting the EERE bit */
	SET_BIT(EECR,EERE);

	 /* Return the data from the data register */
	return EEDR;
}
