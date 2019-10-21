#ifndef _NCR_SW_H
#define	_NCR_SW_H

#include "BS83B24C.h"

#define	TONE_MODE_1		1
#define TONE_MODE_2		2
#define TONE_MODE_3		3

#define	ONE_SHOT		1
#define	OSCILLATING		2
#define	CONTINUOUSCLOSURE	3

#define SW1_HIGH_BIT_ID		_pbc4
#define SW1_LOW_BIT_ID		_pbc5

#define SW2_HIGH_BIT_ID		_pbc6
#define SW2_LOW_BIT_ID		_pbc7

#define SW1_HIGH_BIT_PIN	_pb4
#define SW1_LOW_BIT_PIN		_pb5

#define SW2_HIGH_BIT_PIN	_pb6
#define SW2_LOW_BIT_PIN		_pb7


void sw1DefaultConfig(void);
void sw2DefaultConfig(void);

extern void swGpioClear(void);

#endif

