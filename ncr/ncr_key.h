#ifndef _NCR_KEY_H_
#define _NCR_KEY_H_

#include "BS83B24C.h"

/*��λ���������alarm out������Ƿѹ������ʧ������*/
#define RESET_ID	_pbc0
#define RESET_PIN	_pb0

/*��ͣ�������ڴ���״̬�°�һ�°�������30S��ͣʱ��*/
#define HOLD_ID		_pbc1
#define HOLD_PIN	_pb1

/*��԰������ڴ���״̬�°�һ�°����������״̬*/
#define PAIR_ID		_pbc2
#define PAIR_PIN	_pb2

/*����������Ϣ���ڴ���״̬�°�һ�°����������ͨ���������Ϣ*/
#define CLEARCHANNEL_ID		_pbc3
#define	CLEARCHANNEL_PIN	_pb3

void ncrHalKeyConfig(void);

#endif

