#ifndef _NCR_KEY_H_
#define _NCR_KEY_H_

#include "BS83B24C.h"

/*复位按键：清除alarm out报警、欠压报警，失联报警*/
#define RESET_ID	_pbc0
#define RESET_PIN	_pb0

/*暂停按键：在待机状态下按一下按键进入30S暂停时间*/
#define HOLD_ID		_pbc1
#define HOLD_PIN	_pb1

/*配对按键：在待机状态下按一下按键进入配对状态*/
#define PAIR_ID		_pbc2
#define PAIR_PIN	_pb2

/*清除已配对信息，在待机状态下按一下按键清除所有通道已配对信息*/
#define CLEARCHANNEL_ID		_pbc3
#define	CLEARCHANNEL_PIN	_pb3

void ncrHalKeyConfig(void);

#endif

