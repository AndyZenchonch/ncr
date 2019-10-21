#include "BS83B24C.h"
#include "ncr_sensor.h"
#include "hal_type.h"
#include "ncr_system.h"
#include "ncr_key.h"
#include "stdlib.h"
#include "ncr_sw.h"

static volatile ncr_tyte ncr	__attribute__((at(0x080)));



void reset(void){
	_wdtc = 0b01010000;		//125ms
	_fhiden = 0;
	_fsiden = 0;
	asm("HALT");
	while(1);	
}

/*
* 看门狗每125ms重启一次MCU
*/
void gotoSleepMode(void){
	swGpioClear();
	_wdtc = 0b01010010;		//125ms
	_fhiden = 0;
	_fsiden = 0;
	asm("HALT");
	while(1);	
}

void statusLEDFlush(void){
	if(ncr.lowBatWaringFlag == 0){
		LOWBAT_LED_PIN = 1;
		//STATUS_LED_PIN = 0;
		//delay(40);
		//STATUS_LED_PIN = 1;
		ncr.wdtTimeStemps = 0;
	}else{
		STATUS_LED_PIN = 1;
		LOWBAT_LED_PIN = 0;
		delay(40);
		LOWBAT_LED_PIN = 1;
		ncr.wdtTimeStemps = 0;		
	}
	_clrwdt();		
}

/*切换配对通道，在配对模式下，该函数执行几次，则配对通道向下切换几次*/
void holdRestButtonPush(void){
	delay(500);
	HOLDRESET_OUT_ID = OUTPUT;
	delay(5);
	HOLARESET_OUT_PIN = LOW;
	delay(200);
	HOLARESET_OUT_PIN = HIGH;
	delay(600);
}

uint8_t chxTemp = 0x00;
uint32_t systemTicksTimeStamp = 0;
uint32_t ch1TimeStamp = 0;
uint32_t ch2TimeStamp = 0;
uint32_t ch3TimeStamp = 0;
uint32_t ch4TimeStamp = 0;
uint32_t ch5TimeStamp = 0;
uint32_t ch6TimeStamp = 0;

void lose(void){
	uint8_t currentTemp = ncr.pairChannel;
	uint32_t lowPulseWidth = 0;
	/*第一通道被配置过，则检测第一通道是否失联*/
//	if((ncr.pairChannel & 0x80) != 0x00){
					STATUS_LED_PIN = HIGH;
					LOWBAT_LED_PIN = HIGH;	
		if(MONITORING_1_PIN == LOW){
			if((chxTemp & 0x80) == 0x00){
				ch1TimeStamp = systemTicksTimeStamp;
				chxTemp |= 0x80;
			}
		}else{
			if((chxTemp & 0x80) != 0x00){
				chxTemp &= ~0x80;
				lowPulseWidth = systemTicksTimeStamp - ch1TimeStamp;
				if((lowPulseWidth > 2) && (lowPulseWidth < 20)){	//接收到失联信号
					ncr.pairChannel &= ~(0x80);			
				}else if(/*(lowPulseWidth > 30) && (lowPulseWidth < 80)*/lowPulseWidth > 30){	//失联后重新接入
					ncr.pairChannel |= 0x80;
					STATUS_LED_PIN = LOW;
					LOWBAT_LED_PIN = LOW;
				}
			}
		}
//	}
					STATUS_LED_PIN = HIGH;
					LOWBAT_LED_PIN = HIGH;	
	/*第二通道被配置过，则检测第一通道是否失联*/
//	if((ncr.pairChannel & 0x40) != 0x00){
		if(MONITORING_2_PIN == LOW){
			if((chxTemp & 0x40) == 0x00){
				ch2TimeStamp = systemTicksTimeStamp;
				chxTemp |= 0x40;
			}
		}else{
			if((chxTemp & 0x40) != 0x00){
				chxTemp &= ~0x40;
				lowPulseWidth = systemTicksTimeStamp - ch2TimeStamp;
				if((lowPulseWidth > 2) && (lowPulseWidth < 20)){	//接收到失联信号
					ncr.pairChannel &= ~(0x40);
				}else if(/*(lowPulseWidth > 30) && (lowPulseWidth < 80)*/lowPulseWidth > 30){	//失联后重新接入
					ncr.pairChannel |= 0x40;
					STATUS_LED_PIN = LOW;
					LOWBAT_LED_PIN = LOW;					
				}
			}
		}
					STATUS_LED_PIN = HIGH;
					LOWBAT_LED_PIN = HIGH;		
//	}
	/*第三通道被配置过，则检测第一通道是否失联*/
	//if((ncr.pairChannel & 0x20) != 0x00){
		
		if(MONITORING_3_PIN == LOW){
			if((chxTemp & 0x20) == 0x00){
				ch3TimeStamp = systemTicksTimeStamp;
				chxTemp |= 0x20;
			}
		}else{
			if((chxTemp & 0x20) != 0x00){
				chxTemp &= ~0x20;
				lowPulseWidth = systemTicksTimeStamp - ch3TimeStamp;
				if((lowPulseWidth > 2) && (lowPulseWidth < 20)){	//接收到失联信号
					ncr.pairChannel &= ~(0x20);
				}else if(/*(lowPulseWidth > 30) && (lowPulseWidth < 80)*/lowPulseWidth > 30){	//失联后重新接入
					ncr.pairChannel |= 0x20;
					STATUS_LED_PIN = LOW;
					LOWBAT_LED_PIN = LOW;				
				}
			}
		}
					STATUS_LED_PIN = HIGH;
					LOWBAT_LED_PIN = HIGH;		
	//}
	/*第四通道被配置过，则检测第一通道是否失联*/
	//if((ncr.pairChannel & 0x10) != 0x00){
		if(MONITORING_4_PIN == LOW){
			if((chxTemp & 0x10) == 0x00){
				ch4TimeStamp = systemTicksTimeStamp;
				chxTemp |= 0x10;
			}
		}else{
			if((chxTemp & 0x10) != 0x00){
				chxTemp &= ~0x10;
				lowPulseWidth = systemTicksTimeStamp - ch4TimeStamp;
				if((lowPulseWidth > 2) && (lowPulseWidth < 20)){	//接收到失联信号
					ncr.pairChannel &= ~(0x10);
				}else if(/*(lowPulseWidth > 30) && (lowPulseWidth < 80)*/lowPulseWidth > 30){	//失联后重新接入
					ncr.pairChannel |= 0x10;
					STATUS_LED_PIN = LOW;
					LOWBAT_LED_PIN = LOW;					
				}
			}
		}
						STATUS_LED_PIN = HIGH;
					LOWBAT_LED_PIN = HIGH;	
//	}
	/*第五通道被配置过，则检测第一通道是否失联*/
//	if((ncr.pairChannel & 0x08) != 0x00){
		if(MONITORING_5_PIN == LOW){
			if((chxTemp & 0x08) == 0x00){
				ch5TimeStamp = systemTicksTimeStamp;
				chxTemp |= 0x08;
			}
		}else{
			if((chxTemp & 0x08) != 0x00){
				chxTemp &= ~0x08;
				lowPulseWidth = systemTicksTimeStamp - ch5TimeStamp;
				if((lowPulseWidth > 2) && (lowPulseWidth < 20)){	//接收到失联信号
					ncr.pairChannel &= ~(0x08);
				}else if(/*(lowPulseWidth > 30) && (lowPulseWidth < 80)*/lowPulseWidth > 30){	//失联后重新接入
					ncr.pairChannel |= 0x08;
					STATUS_LED_PIN = LOW;
					LOWBAT_LED_PIN = LOW;					
				}
			}
		}
					STATUS_LED_PIN = HIGH;
					LOWBAT_LED_PIN = HIGH;		
//	}
	/*第六通道被配置过，则检测第一通道是否失联*/
//	if((ncr.pairChannel & 0x04) != 0x00){
		if(MONITORING_6_PIN == LOW){
			if((chxTemp & 0x04) == 0x00){
				ch6TimeStamp = systemTicksTimeStamp;
				chxTemp |= 0x04;
			}
		}else{
			if((chxTemp & 0x04) != 0x00){
				chxTemp &= ~0x04;
				lowPulseWidth = systemTicksTimeStamp - ch6TimeStamp;
				if((lowPulseWidth > 2) && (lowPulseWidth < 20)){	//接收到失联信号
					ncr.pairChannel &= ~(0x04);
				}else if(/*(lowPulseWidth > 30) && (lowPulseWidth < 80)*/lowPulseWidth > 30){	//失联后重新接入
					ncr.pairChannel |= 0x04;
					STATUS_LED_PIN = LOW;
					LOWBAT_LED_PIN = LOW;					
				}
			}
		}
//	}	
	if(currentTemp != ncr.pairChannel){
		zh_memoryWriteByte(0x00, ncr.pairChannel);
	}
}


void gotoWaring(void){
	/*先判断报警模式*/
	uint8_t waringMode = 0;
	uint8_t beeMode = 0;
	uint16_t waringTimeIndex = 0;
	uint16_t singleTimeIndex = 0;
	
	if(SW1_HIGH_BIT_PIN == HIGH) beeMode |= 0x02;
	else beeMode &= ~(0x02); 
	
	if(SW1_LOW_BIT_PIN == HIGH) beeMode |= 0x01;
	else beeMode &= ~(0x01); 
	
	if(SW2_HIGH_BIT_PIN == HIGH) waringMode |= 0x02;
	else waringMode &= ~(0x02); 
	
	if(SW2_LOW_BIT_PIN == HIGH) waringMode |= 0x01;
	else waringMode &= ~(0x01); 
	
	//if(beeMode == 0x02)	beeMode = 4;
	
	
	if(waringMode == 1){	//One-Shot
		NURSECALL_PIN = LOW;
		waringTimeIndex = 0;
		singleTimeIndex = 31;
		while(1){
			doBee(beeMode, &waringTimeIndex);
			if(RESET_PIN == LOW){
				keysPushWaring();
				HOLARESET_OUT_PIN = LOW;
				delay(10);
				while(ALARM_OUT_PIN == LOW){		
					delay(10);
				}
				HOLARESET_OUT_PIN = HIGH;
				ncr.alarmFlag = 0;
				break;
			}
			lose();
			if(singleTimeIndex > 0){
					singleTimeIndex--;
			}else{
				NURSECALL_PIN = HIGH;
			}	
			
			if(ALARM_OUT_PIN == HIGH){
				ncr.alarmFlag = 0;
				delay(10);
				break;
			}	
			delay(30);
			
			STATUS_LED_PIN = HIGH;
			LOWBAT_LED_PIN = HIGH;			
			systemTicksTimeStamp++;				
			waringTimeIndex++;		
		}				
	}else if(waringMode == 2){	//Oscillating	
		waringTimeIndex = 0;
		singleTimeIndex = 0;
		while(1){
			doBee(beeMode, &waringTimeIndex);
			if(RESET_PIN == LOW){
				keysPushWaring();
				HOLARESET_OUT_PIN = LOW;
				delay(10);
				while(ALARM_OUT_PIN == LOW){		
					delay(10);
				}
				HOLARESET_OUT_PIN = HIGH;
				ncr.alarmFlag = 0;
				break;
			}	
			lose();
			if(singleTimeIndex == 10){
				NURSECALL_PIN = !NURSECALL_PIN;
				singleTimeIndex = 0;	
			}
			
			if(ALARM_OUT_PIN == HIGH){
				ncr.alarmFlag = 0;
				delay(10);
				break;
			}	
			delay(30);
			
			systemTicksTimeStamp++;	
			waringTimeIndex++;
			singleTimeIndex++;		
		}		
	}else{						//Continuous Closure
		NURSECALL_PIN = LOW;
		singleTimeIndex = 0;
		while(1){
			doBee(beeMode, &waringTimeIndex);
			if(RESET_PIN == LOW){
				keysPushWaring();
				HOLARESET_OUT_PIN = LOW;
				delay(10);
				while(ALARM_OUT_PIN == LOW){		
					delay(10);
				}
				HOLARESET_OUT_PIN = HIGH;
				ncr.alarmFlag = 0;
				break;
			}
			lose();
			if(ALARM_OUT_PIN == HIGH){
				ncr.alarmFlag = 0;
				delay(10);
				break;
			}	
			delay(30);
			
			systemTicksTimeStamp++;				
			waringTimeIndex++;
			singleTimeIndex++;		
		}		
	}			
	toneMode(0);
	NURSECALL_PIN = HIGH;
	RFPROMPT_TONE_EN_PIN = HIGH;
	delay(1000);
//	reset();
}

void gotoLowBatWaring(void){
	/*先判断报警模式*/
	uint8_t waringMode = 0;
	uint8_t beeMode = 0;
	uint16_t waringTimeIndex = 0;
	uint16_t singleTimeIndex = 0;
	uint8_t ledBlinkIndex = 0;
	
	if(SW1_HIGH_BIT_PIN == HIGH) beeMode |= 0x02;
	else beeMode &= ~(0x02); 
	
	if(SW1_LOW_BIT_PIN == HIGH) beeMode |= 0x01;
	else beeMode &= ~(0x01); 
	
	if(SW2_HIGH_BIT_PIN == HIGH) waringMode |= 0x02;
	else waringMode &= ~(0x02); 
	
	if(SW2_LOW_BIT_PIN == HIGH) waringMode |= 0x01;
	
	//if(beeMode == 0x02)	beeMode = 5;

	STATUS_LED_PIN = 1;
	
	if(waringMode == 1){	//One-Shot
		NURSECALL_PIN = LOW;
		waringTimeIndex = 0;
		singleTimeIndex = 31;
		
		while(1){
			if(ledBlinkIndex == 0){
				LOWBAT_LED_PIN = LOW;
			}else{
				LOWBAT_LED_PIN = HIGH;
			}
			doBee(beeMode, &waringTimeIndex);
			if(RESET_PIN == LOW){
				ncr.lowBatWaringFlag = 2;
				delay(10);
				break;
			}
			
			if(singleTimeIndex > 0){
					singleTimeIndex--;
			}else{
				NURSECALL_PIN = HIGH;
			}	
			
			if(LOW_BAT_PIN == HIGH){
				delay(5);
				ncr.lowBatWaringFlag = 0;
				break;
			}
			
			delay(35);
			ledBlinkIndex++;
			if(ledBlinkIndex >= 150)	ledBlinkIndex = 0;
			waringTimeIndex++;		
		}				
	}else if(waringMode == 2){	//Oscillating	
		waringTimeIndex = 0;
		singleTimeIndex = 0;
		while(1){
			if(ledBlinkIndex == 0){
				LOWBAT_LED_PIN = LOW;
			}else{
				LOWBAT_LED_PIN = HIGH;
			}			
			
			doBee(beeMode, &waringTimeIndex);
			if(RESET_PIN == LOW){
				delay(10);
				ncr.lowBatWaringFlag = 2;
				break;
			}	
			
			if(singleTimeIndex == 10){
				NURSECALL_PIN = !NURSECALL_PIN;
				singleTimeIndex = 0;	
			}
			
			if(LOW_BAT_PIN == HIGH){
				delay(5);
				ncr.lowBatWaringFlag = 0;
				break;
			}
	
			delay(35);
			ledBlinkIndex++;
			if(ledBlinkIndex >= 150)	ledBlinkIndex = 0;			
			waringTimeIndex++;
			singleTimeIndex++;		
		}		
	}else{						//Continuous Closure
		NURSECALL_PIN = LOW;
		singleTimeIndex = 0;
		while(1){
			if(ledBlinkIndex == 0){
				LOWBAT_LED_PIN = LOW;
			}else{
				LOWBAT_LED_PIN = HIGH;
			}				
			doBee(beeMode, &waringTimeIndex);
			if(RESET_PIN == LOW){
				delay(10);
				ncr.lowBatWaringFlag = 2;
				break;
			}	
			
			if(LOW_BAT_PIN == HIGH){
				delay(5);
				ncr.lowBatWaringFlag = 0;
				break;
			}	
	
			delay(35);
			ledBlinkIndex++;
			if(ledBlinkIndex >= 150)	ledBlinkIndex = 0;
			waringTimeIndex++;
			singleTimeIndex++;		
		}		
	}			
	toneMode(0);
	NURSECALL_PIN = HIGH;		
}

uint8_t chxPair(uint8_t ch, uint8_t i){
	uint8_t re = 0;
	/*如果该通道没有配对，则进行配对*/
	if((ncr.pairChannel & ch) != 0){
		/*切换配对通道*/
		holdRestButtonPush();
		return 2;
	}else{	
		HOLDRESET_OUT_ID = INPUT;
		
		re = pair(i);
		if(re == 0){	//配对超时
			PROGRAMING_OUT_PIN = HIGH;
			PROMPT_TONE_POWER_PIN = LOW;
			beep(5,200);
			delay(10);
			beep(5,200);
			PROGRAMING_OUT_PIN = LOW;
			return 0;
		}else if(re == 1){			//配对成功
			ncr.pairChannel |= ch;
			
			zh_memoryWriteByte(0x00, ncr.pairChannel);
			delay(2000);
			return 1;
		}
	}
	return 0;
}

void pair15sLoop(void){
	uint8_t i = 0;

	uint8_t result = 0;
	//ncr.pairChannel = 0x00;
	
	//if((ncr.pairChannel & 0x80))
	
	PROGRAMING_OUT_PIN = LOW;
	delay(10);

	/*最多一次性配6路通道*/
	for(i = 0; i < 6;){
		if(i == 0){
			result = chxPair(0x80, i);
			if((result == 0) || (result == 1))		//超时
				break;
			else
				i = 1;
		}else if(i == 1){
			result = chxPair(0x40, i);
			if((result == 0) || (result == 1))		//超时
				break;
			else
				i = 2;			
		}else if(i == 2){
			result = chxPair(0x20, i);
			if((result == 0) || (result == 1))		//超时
				break;
			else
				i = 3;			
		}else if(i == 3){
			result = chxPair(0x10, i);
			if((result == 0) || (result == 1))		//超时
				break;
			else
				i = 4;			
		}else if(i == 4){
			result = chxPair(0x08, i);
			if((result == 0) || (result == 1))		//超时
				break;
			else
				i = 5;			
		}else if(i == 5){
			result = chxPair(0x04, i);
			if((result == 0) || (result == 1))		//超时
				break;
			else
				i = 6;			
		}else{
			break;
		}
	}

	PROGRAMING_OUT_PIN = HIGH;
}

/*清除所有配对*/
void clearAllChannel(void){
	uint16_t cnt = 0;

	uint8_t flag = 0;	
	uint8_t index = 0;
	
	uint8_t clearAllCnt = 0;
	
	CLEARALLCHANNELS_PIN = HIGH;
	delay(1000);
	HOLARESET_OUT_PIN = LOW;
	delay(1000);
	CLEARALLCHANNELS_PIN = LOW;
	while(1){
		if((MONITORING_2_PIN == LOW) /*&& (MONITORING_3_PIN == LOW)*/){
			if(flag == 0){
				flag = 1;
				cnt = 0;
			}else{
				cnt++;
			}
		}else if((MONITORING_2_PIN == HIGH) /*&& (MONITORING_3_PIN == HIGH)*/){
			if(flag == 1){
				flag = 0;
				if(abs(cnt - 100) < 20){	//检测到一个低电平
					index++;	
				}
			}
		}
		
		clearAllCnt++;
		
		if(index == 0){
			if(clearAllCnt < 5){
				_pd1 = 1;
				toneMode(3);
				STATUS_LED_PIN = 0;
			}else if(clearAllCnt < 100){
				toneMode(0);
				_pd1 = 0;
				STATUS_LED_PIN = 1;
			}else{
				clearAllCnt = 0;
			}
		}else{
			toneMode(0);
			STATUS_LED_PIN = 1;
		}
		
		if(index >= 3)
			break;
		delay(10);
	}
	delay(1000);
	HOLARESET_OUT_PIN = HIGH;
	ncr.pairChannel = 0x00;
	ncr.loseConnect = 0x00;
}

void reConnect(void){
	uint8_t currentTemp = ncr.pairChannel;
	
	if((_pa & 0x3f) == 0x00)
		return;
	
	if(MONITORING_1_PIN == LOW){
			ncr.pairChannel |= 0x80;
	}
	if(MONITORING_2_PIN == LOW){
			ncr.pairChannel |= 0x40;
	}
	if(MONITORING_3_PIN == LOW){
		ncr.pairChannel |= 0x20;
	}		
	if(MONITORING_4_PIN == LOW){
		ncr.pairChannel |= 0x10;
	}
	if(MONITORING_5_PIN == LOW){
		ncr.pairChannel |= 0x08;
	}
	if(MONITORING_6_PIN == LOW){
		ncr.pairChannel |= 0x04;
	}
	
	if(currentTemp != ncr.pairChannel){
		zh_memoryWriteByte(0x00, ncr.pairChannel);
	}	
}

void main()
{
	_hircc |= 0b00000001;	//16MHz
	while(_hircf == 0);
	_scc = 0b00000000;
	_sledc0 = 0xff;
	_sledc1 = 0xff;
	
	uint8_t holdExitFlag = 0;
	
	statusLowbatLedConfig();
	ncrGPIOConfig();
	ncrHalKeyConfig();
	
	
	ptmtToneConfig();
	ncr.pairChannel = zh_memoryReadByte(0x00);
	
	/*看门狗发生复位*/
	if(_to == 1){	
		ncr.wdtTimeStemps++;
		if(ncr.wdtTimeStemps == 40){
			statusLEDFlush();
		}
		
		/*配对*/
		if( PAIR_PIN == LOW){
			keysPushWaring();
			if(ncr.pairChannel == 0xfc){
				beep(3,200);
				delay(10);
				beep(3,200);
				delay(10);
				beep(3,200);
				delay(10);
				beep(3,200);
													
			}else{
				delay(500);
				pair15sLoop();
			}
		}
		
		/*清除所有配对信息*/
		if(CLEARCHANNEL_PIN == LOW){
			keysPushWaring();
			clearAllChannel();
			zh_memoryWriteByte(0x00, 0x00);
		}
		
		/*接受到报警信号*/
		if(ALARM_OUT_PIN == LOW){
			sw1DefaultConfig();
			sw2DefaultConfig();	//配置成输入
			delay(5);
			if(ncr.alarmFlag == 0){
				ncr.alarmFlag = 1;
				RFPROMPT_TONE_EN_PIN = LOW;
				delay(5);
				gotoWaring();
				ncr.firstAlarmFlag = 1;
				zh_memoryWriteByte(0x00, ncr.pairChannel);					
			}
		}else{
			if(ncr.alarmFlag == 1)	ncr.alarmFlag = 0;
			
			swGpioClear();
		}
		
		if(HOLD_PIN == LOW){
			//if(ncr.pairChannel != 0x00){		//只有在配对成功后，才能进入该模式HOLD模式
				//if(ncr.firstAlarmFlag != 0)
					hold30loop();
		//	}
		}
		
		if(MONITORING_1_PIN == LOW){
			holdExitFlag++;
		} 
		if(MONITORING_2_PIN == LOW){
			holdExitFlag++;
		}
		if(MONITORING_3_PIN == LOW){
			holdExitFlag++;
		}
		if(MONITORING_4_PIN == LOW){
			holdExitFlag++;
		}		
		if(MONITORING_5_PIN == LOW){
			holdExitFlag++;
		}
		if(MONITORING_6_PIN == LOW){
			holdExitFlag++;
		}
		
		if(holdExitFlag >= 2){
			holdLow();
		}
		holdExitFlag = 0;

								
		if(LOW_BAT_PIN == LOW){
			if(ncr.lowBatWaringFlag == 0){
				ncr.lowBatWaringFlag = 1;
			}
			
			if(ncr.lowBatWaringFlag == 1){
				gotoLowBatWaring();
			}
		}else{
			ncr.lowBatWaringFlag = 0;
		}
		
		reConnect();
	}
	/*上电发生复位*/
	else{
		if(ncr.pairChannel == 0xff){
			ncr.pairChannel = 0x00;
			zh_memoryWriteByte(0x00, 0x00);
		}			
		
		ncr.wdtTimeStemps = 0;

		ncr.loseConnect = 0x00;
		ncr.alarmFlag = 0;
		ncr.lowBatWaringFlag = 0;
		powerOnLEDBlink();
	}

	/*do not return*/
	gotoSleepMode();
}

void __attribute((interrupt(0x0C))) ptmtInterrupt(void){
	
	if(waringEnable == 1)
		ALARM_TONE_PIN = !ALARM_TONE_PIN;
	else
		ALARM_TONE_PIN = LOW;

	
	_mf0f = 0;
	_ptmaf = 0;
}
