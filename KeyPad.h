/*
 * KeyPad.h
 *
 *  Created on: Jul 4, 2022
 *      Author: prana
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	uint8_t   ColumnSize;
	uint8_t   RowSize;
	uint16_t  LastKey;

}KeyPad_t;

void      KeyPad_Init(void);
uint16_t  KeyPad_WaitForKey(uint32_t	Timeout_ms);
char      KeyPad_WaitForKeyGetChar(uint32_t	Timeout_ms);

#endif /* INC_KEYPAD_H_ */
