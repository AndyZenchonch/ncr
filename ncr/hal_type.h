#ifndef _HAL_TYPE_H
#define _HAL_TYPE_H

#define INPUT	1
#define OUTPUT	0


#define HIGH	1
#define LOW		0

#define TRUE	1
#define FALSE   0

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;


typedef struct{
	#if 0
	uint32_t systemTimeStemp;
	uint32_t ch1TimeTicks;
	uint32_t ch2TimeTicks;
	uint32_t ch3TimeTicks;
	uint32_t ch4TimeTicks;
	uint32_t ch5TimeTicks;
	uint32_t ch6TimeTicks;
	uint8_t chxTemp;
	#endif
	
	uint16_t wdtTimeStemps;
	
	uint8_t pairChannel;
	uint8_t loseConnect;
	
	uint8_t alarmFlag;	//ÆÕÍ¨±¨¾¯
	uint8_t lowBatWaringFlag;	//Ç·Ñ¹±¨¾¯
	
	uint8_t firstAlarmFlag;
}ncr_tyte;


#endif

