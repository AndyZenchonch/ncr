#include "ncr_key.h"
#include "hal_type.h"

void ncrHalKeyConfig(void){
	_pbs0 = 0b00000000;		//引脚不复用
	
	/*配置四个按键为输入模式*/
	RESET_ID = INPUT;
	HOLD_ID = INPUT;
	PAIR_ID = INPUT;
	CLEARCHANNEL_ID = INPUT;
	
	_pbpu |= 0b00001111;	//设置上拉电阻
}
