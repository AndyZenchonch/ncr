#include "ncr_key.h"
#include "hal_type.h"

void ncrHalKeyConfig(void){
	_pbs0 = 0b00000000;		//���Ų�����
	
	/*�����ĸ�����Ϊ����ģʽ*/
	RESET_ID = INPUT;
	HOLD_ID = INPUT;
	PAIR_ID = INPUT;
	CLEARCHANNEL_ID = INPUT;
	
	_pbpu |= 0b00001111;	//������������
}
