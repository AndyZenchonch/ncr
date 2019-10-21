#ifndef _NCR_SENSOR_H
#define _NCR_SENSOR_H

/************************************�������ض���**********************************************/
/*����ԡ�ʧ����������������ź������*/
#define MONITORING_1_ID		_pac5
#define MONITORING_2_ID		_pac4
#define MONITORING_3_ID		_pac3
#define MONITORING_4_ID		_pac1
#define MONITORING_5_ID		_pac2
#define MONITORING_6_ID		_pac0

#define MONITORING_1_PIN	_pa5	
#define MONITORING_2_PIN	_pa4
#define MONITORING_3_PIN	_pa3
#define MONITORING_4_PIN	_pa1
#define MONITORING_5_PIN	_pa2
#define MONITORING_6_PIN	_pa0

/*Ƿѹ�����*/
#define LOW_BAT_ID		_pac7
#define LOW_BAT_PIN		_pa7

/*���������*/
#define	ALARM_OUT_ID	_pac6
#define ALARM_OUT_PIN	_pa6



/************************************�������ض���**********************************************/
/*LEDָʾ��*/
#define STATUS_LED_ID		_pcc0
#define LOWBAT_LED_ID		_pcc1
#define STATUS_LED_PIN		_pc0
#define LOWBAT_LED_PIN		_pc1

/*��Կ��������*/
/*�ÿ�һֱ���ڵ͵�ƽ���������ԣ�������ڸߵ�ƽ�����˳����ģʽ*/
#define PROGRAMING_OUT_ID	_pcc2
#define PROGRAMING_OUT_PIN	_pc2

/*�����������*/
#define	ALARM_TONE_ID		_pcc3
#define ALARM_TONE_PIN		_pc3

#define NURSECALL_ID		_pcc4
#define NURSECALL_PIN		_pc4

/*��λ�ͱ��������*/
#define HOLDRESET_OUT_ID	_pcc5
#define HOLARESET_OUT_PIN	_pc5

/*���������ʹ��*/
#define RFPROMPT_TONE_EN_ID		_pcc6
#define RFPROMPT_TONE_EN_PIN	_pc6

/*����ͨ����������*/
#define CLEARALLCHANNELS_ID		_pdc0
#define CLEARALLCHANNELS_PIN	_pd0

/*���ʧ����ʾ����Դ�����*/
#define PROMPT_TONE_POWER_ID	_pdc1
#define PROMPT_TONE_POWER_PIN	_pd1

void statusLowbatLedConfig(void);

void ncrGPIOConfig(void);

void powerOnLEDBlink(void);

#endif
