#include "ncr_sensor.h"
#include "BS83B24C.h"
#include "hal_type.h"
#include "ncr_sw.h"

void statusLowbatLedConfig(void){
	STATUS_LED_ID = OUTPUT;
	LOWBAT_LED_ID = OUTPUT;
	
	STATUS_LED_PIN = HIGH;
	LOWBAT_LED_PIN = HIGH;
}

void ncrGPIOConfig(void){
	/*配对控制引脚，输出低电平，进行配对*/
	PROGRAMING_OUT_ID = OUTPUT;
	PROGRAMING_OUT_PIN = HIGH;
	
	/*配置该引脚，用于模拟按钮输出，按下几次则切换到不同的配对通道*/
	HOLDRESET_OUT_ID = OUTPUT;
	HOLARESET_OUT_PIN = HIGH;
	_pcpu |= 0b00100000;
	
	/*无线模组开关使能引脚，低电平使能*/
	CLEARALLCHANNELS_ID = OUTPUT;
	CLEARALLCHANNELS_PIN = LOW;
	
	/*报警输入口，报警时，该口处于低电平*/
	ALARM_OUT_ID = INPUT;	//配置成输入模式
	
	RFPROMPT_TONE_EN_ID = OUTPUT;
	RFPROMPT_TONE_EN_PIN = HIGH;
	
	ALARM_TONE_ID = OUTPUT;
	ALARM_TONE_PIN = LOW;
	
	NURSECALL_ID = OUTPUT;
	NURSECALL_PIN = HIGH;
	
	PROMPT_TONE_POWER_ID = OUTPUT;
	PROMPT_TONE_POWER_PIN = LOW;
	
	LOW_BAT_ID = INPUT;
	
	MONITORING_1_ID = INPUT;
	MONITORING_2_ID = INPUT;
	MONITORING_3_ID = INPUT;
	MONITORING_4_ID = INPUT;
	MONITORING_5_ID = INPUT;
	MONITORING_6_ID = INPUT;	
	_papu |= 0b00111111;				
	
	#if 0
	sw1DefaultConfig();
	sw2DefaultConfig();	//配置成输入
	#endif
	swGpioClear();
}


