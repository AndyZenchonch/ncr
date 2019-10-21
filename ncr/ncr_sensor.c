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
	/*��Կ������ţ�����͵�ƽ���������*/
	PROGRAMING_OUT_ID = OUTPUT;
	PROGRAMING_OUT_PIN = HIGH;
	
	/*���ø����ţ�����ģ�ⰴť��������¼������л�����ͬ�����ͨ��*/
	HOLDRESET_OUT_ID = OUTPUT;
	HOLARESET_OUT_PIN = HIGH;
	_pcpu |= 0b00100000;
	
	/*����ģ�鿪��ʹ�����ţ��͵�ƽʹ��*/
	CLEARALLCHANNELS_ID = OUTPUT;
	CLEARALLCHANNELS_PIN = LOW;
	
	/*��������ڣ�����ʱ���ÿڴ��ڵ͵�ƽ*/
	ALARM_OUT_ID = INPUT;	//���ó�����ģʽ
	
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
	sw2DefaultConfig();	//���ó�����
	#endif
	swGpioClear();
}


