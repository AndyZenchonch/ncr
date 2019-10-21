#include "ncr_sw.h"
#include "hal_type.h"

void sw1DefaultConfig(void){
	_pbs1 = 0b00000000;		//引脚不复用
	
	/*配置为输入模式*/
	SW1_HIGH_BIT_ID = INPUT;
	SW1_LOW_BIT_ID = INPUT;

	_pbpu |= 0b00110000;	//上拉电阻
}

void sw2DefaultConfig(void){
	_pbs1 = 0b00000000;		//引脚不复用
	
	/*配置为输入模式*/
	SW2_HIGH_BIT_ID = INPUT;
	SW2_LOW_BIT_ID = INPUT;

	_pbpu |= 0b11000000;	//上拉电阻
}

void swGpioClear(void){
	SW1_HIGH_BIT_ID = OUTPUT;
	SW2_HIGH_BIT_ID = OUTPUT;
	SW1_LOW_BIT_ID = OUTPUT;
	SW2_LOW_BIT_ID = OUTPUT;
	_pbpu &= ~(0x11110000);
}
