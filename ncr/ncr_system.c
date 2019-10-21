#include "ncr_system.h"
#include "BS83B24C.h"
#include "hal_type.h"
#include "ncr_sensor.h"
#include "ncr_key.h"
#include "stdlib.h"

uint16_t toneDelay[13] = {0, 455, 357, 303, 263, 1432, 1517, 758, 851, 637, 1136, 1703, 1276};

/*1ms延时函数*/
void delay(unsigned long value){
	int i = 0;
	unsigned int j = 0;
	value++;
	
	for(i = 0; i < value; i++){
		while(j--){
			_nop();
			_nop();
			_nop();
			_nop();
			_nop();
			_nop();
			_nop();
			_nop();
			_nop();
			_clrwdt();
		}
		j = 100;
	}
}

void keysPushWaring(void){
	_pd1 = 1;
	toneMode(3);
	delay(50);
	_pd1 = 0;
	toneMode(0);
}

void powerOnLEDBlink(void){
	uint8_t i = 3;
	uint8_t lowFlag = 0;
	
	while(i){
		if((MONITORING_1_PIN == LOW) && (MONITORING_2_PIN == LOW)){
			STATUS_LED_PIN = LOW;
			LOWBAT_LED_PIN = LOW;
			if(lowFlag == 0){
				lowFlag = 1;
			}
		}else{
			if(lowFlag == 1){
				lowFlag = 0;
				i--;
			}
			STATUS_LED_PIN = HIGH;
			LOWBAT_LED_PIN = HIGH;			
		}	
		_clrwdt();	
	}
	STATUS_LED_PIN = HIGH;
	LOWBAT_LED_PIN = HIGH;
	delay(1500);
}

void checkPowerOnLEDBlink(void){
	uint8_t i = 1;
	uint8_t lowFlag = 0;
	
	while(i){
		if((MONITORING_1_PIN == LOW) && (MONITORING_2_PIN == LOW)){
			STATUS_LED_PIN = LOW;
			LOWBAT_LED_PIN = LOW;
			if(lowFlag == 0){
				lowFlag = 1;
			}
		}else{
			if(lowFlag == 1){
				lowFlag = 0;
				i--;
			}
			STATUS_LED_PIN = HIGH;
			LOWBAT_LED_PIN = HIGH;			
		}	
		_clrwdt();	
	}
	STATUS_LED_PIN = HIGH;
	LOWBAT_LED_PIN = HIGH;
	delay(500);
}

static uint8_t checkOtherPin(void){
	if((MONITORING_1_PIN == LOW) &&
		 (MONITORING_2_PIN == LOW) &&
		 (MONITORING_3_PIN == LOW) &&
		 (MONITORING_4_PIN == LOW) &&
		 (MONITORING_5_PIN == LOW) &&
		 (MONITORING_6_PIN == LOW)){
		 
		 	return 1;
		 }
	return 0;
}

uint8_t pair(uint8_t ch){
	uint16_t cnt = 0;
	uint16_t timeout = 0;
	uint8_t flag = 0;
	
	while(1){
		switch(ch){
			case 0:
				if(MONITORING_1_PIN == LOW){
					if(flag == 0){
						flag = 1;
						cnt = 0;
					}else{
						cnt++;
					}
				}else{
					if(flag == 1){
						flag = 0;
						if(abs(cnt - 200) < 15){	//配对成功
							return 1;	
						}else{
							cnt = 0;
						}
					}
				}
			break;
			case 1:
				if(MONITORING_2_PIN == LOW){
					if(flag == 0){
						flag = 1;
						cnt = 0;
					}else{
						cnt++;
					}
				}else{
					if(flag == 1){
						flag = 0;
						if(abs(cnt - 200) < 15){	//配对成功
							return 1;	
						}else{
							cnt = 0;
						}
					}
				}
			break;
			case 2:
				if(MONITORING_3_PIN == LOW){
					if(flag == 0){
						flag = 1;
						cnt = 0;
					}else{
						cnt++;
					}
				}else{
					if(flag == 1){
						flag = 0;
						if(abs(cnt - 200) < 15){	//配对成功
							return 1;	
						}else{
							cnt = 0;
						}
					}
				}
			break;
			case 3:
				if(MONITORING_4_PIN == LOW){
					if(flag == 0){
						flag = 1;
						cnt = 0;
					}else{
						cnt++;
					}
				}else{
					if(flag == 1){
						flag = 0;
						if(abs(cnt - 200) < 15){	//配对成功
							return 1;	
						}else{
							cnt = 0;
						}
					}
				}
			break;
			case 4:
				if(MONITORING_5_PIN == LOW){
					if(flag == 0){
						flag = 1;
						cnt = 0;
					}else{
						cnt++;
					}
				}else{
					if(flag == 1){
						flag = 0;
						if(abs(cnt - 200) < 15){	//配对成功
							return 1;	
						}else{
							cnt = 0;
						}
					}
				}
			break;
			case 5:
				if(MONITORING_6_PIN == LOW){
					if(flag == 0){
						flag = 1;
						cnt = 0;
					}else{
						cnt++;
					}
				}else{
					if(flag == 1){
						flag = 0;
						if(abs(cnt - 200) < 15){	//配对成功
							return 1;	
						}else{
							cnt = 0;
						}
					}
				}
			break;
		}
		
		if(PAIR_PIN == LOW){	
			timeout = 0;
			//while(checkOtherPin() == 0);
			//return 0;	
		}
		
		if(checkOtherPin() == 1){
			delay(2500);
			return 0;
		}
		
		timeout++;
		if(timeout >= 3000)	//配对超时
			//return 0;
			break;
		delay(10);	
	}
	return 0;	
}

void hold30loop(void){
	uint8_t exitFlag = 0;
	uint8_t keyFlag = 1;
	uint16_t holdFlag = 0;
	uint16_t holdTime = 0;
	HOLARESET_OUT_PIN = LOW;
	while(1){
		if((MONITORING_1_PIN == LOW) && (MONITORING_2_PIN == LOW) && (MONITORING_4_PIN == LOW) && (MONITORING_5_PIN == LOW) && (MONITORING_6_PIN == LOW))
			break;
		
		if(holdTime > 100)
			break;
			//return;
			
		if(holdTime < 1){
			STATUS_LED_PIN = 0;
			_pd1 = 1;
			toneMode(2);
		}else{
			toneMode(0);
			_pd1 = 0;
			STATUS_LED_PIN = 1;
		}
		
		holdTime++;
		delay(50);				
	}
	delay(200);
	HOLARESET_OUT_PIN = HIGH;
	
	holdTime = 0;
	
	if(HOLD_PIN == HIGH) keyFlag = 0;
	while(1){		
		if(MONITORING_1_PIN == HIGH){
			exitFlag++;
		}
		if(MONITORING_2_PIN == HIGH){
			exitFlag++;
		}
		if(MONITORING_3_PIN == HIGH){
			exitFlag++;
		}				
		if(MONITORING_4_PIN == HIGH){
			exitFlag++;
		}
		if(MONITORING_5_PIN == HIGH){
			exitFlag++;
		}
		if(MONITORING_6_PIN == HIGH){
			exitFlag++;
		}				
	
		if(exitFlag >= 2){
			break;
		}
		exitFlag = 0;
		
		if(holdTime > 3000){
			break;
		}
		
		if(HOLD_PIN == LOW){
			keysPushWaring();
			if(keyFlag == 0)
				break;
		}else{
			keyFlag = 0;
		}
		holdTime++;
		delay(100);
	}

	if(holdFlag == 0){
		HOLARESET_OUT_PIN = LOW;
		delay(200);
		HOLARESET_OUT_PIN = HIGH;
	}
	while(HOLD_PIN == LOW);	
	while(MONITORING_1_PIN == LOW);
	while(MONITORING_2_PIN == LOW);
	while(MONITORING_3_PIN == LOW);
	while(MONITORING_4_PIN == LOW);
	while(MONITORING_5_PIN == LOW);
	while(MONITORING_6_PIN == LOW);
	delay(1000);
}


void holdLow(void){
	uint8_t exitFlag = 0;
	uint8_t keyFlag = 1;
	uint16_t holdFlag = 0;
	uint16_t holdTime = 0;	
	
	if(HOLD_PIN == HIGH) keyFlag = 0;
	while(1){		
		if(MONITORING_1_PIN == HIGH){
			exitFlag++;
		}
		if(MONITORING_2_PIN == HIGH){
			exitFlag++;
		}
		if(MONITORING_3_PIN == HIGH){
			exitFlag++;
		}				
		if(MONITORING_4_PIN == HIGH){
			exitFlag++;
		}
		if(MONITORING_5_PIN == HIGH){
			exitFlag++;
		}
		if(MONITORING_6_PIN == HIGH){
			exitFlag++;
		}				
	
		if(exitFlag >= 2){
			break;
		}
		exitFlag = 0;
		
		if(holdTime > 3000){
			break;
		}
		
		if(HOLD_PIN == LOW){
			keysPushWaring();
			if(keyFlag == 0)
				break;
		}else{
			keyFlag = 0;
		}
		holdTime++;
		delay(100);
	}

	if(holdFlag == 0){
		HOLARESET_OUT_PIN = LOW;
		delay(200);
		HOLARESET_OUT_PIN = HIGH;
	}
	while(HOLD_PIN == LOW);	
	while(MONITORING_1_PIN == LOW);
	while(MONITORING_2_PIN == LOW);
	while(MONITORING_3_PIN == LOW);
	while(MONITORING_4_PIN == LOW);
	while(MONITORING_5_PIN == LOW);
	while(MONITORING_6_PIN == LOW);
	delay(1000);
}

void ptmtToneConfig(void){
	_ptmc0 = 0b00100000;
	_ptmc1 = 0b11000001;	//A匹配
	_ptmal = 303 & 0xff;
	_ptmah = 303 >> 8;
	_ptmae = 1;
	_mf0e = 1;
	_pton = 0;
	_emi = 1;
}

uint8_t waringEnable = 0;
void soundOff(void){
	waringEnable = 0;
    _pton = 0;
    ALARM_TONE_PIN = 0;
}

void toneMode(uint8_t nMode){
    if (!nMode){
    	 soundOff();
    }else{
    	waringEnable = 1;
        switch (nMode){
        case 1://2.2K
            _ptmal = 455 & 0xFF;
            _ptmah = 455 >> 8;
            break;
        case 2://2.8K
            _ptmal = 357 & 0xFF;
            _ptmah = 357 >> 8;
            break;
        case 3://3.3K
            _ptmal = 50 & 0xFF;	//303
            _ptmah = 50 >> 8;
            break;
        case 4://3.8K
            _ptmal = 263 & 0xFF;
            _ptmah = 263 >> 8;
            break;
        case 5://.698K // 2000000 / freq
            _ptmal = 1432 & 0xFF;
            _ptmah = 1432 >> 8;
            break;
        case 6://0.659K
            _ptmal = 1404 & 0xFF;		//1517
            _ptmah = 1404 >> 8;
            break;
        case 7://1.3K
            _ptmal = 758 & 0xFF;
            _ptmah = 758 >> 8;
            break;
        case 8://1.174K
            _ptmal = 212 & 0xFF;		//
            _ptmah = 212 >> 8;
            break;
        case 9://2.0K
            _ptmal = 637 & 0xFF;
            _ptmah = 637 >> 8;
            break;
        case 10://0.880k
            _ptmal = 1308 & 0xFF;		//1136
            _ptmah = 1308 >> 8;
            break;
        case 11://0.587k
        	_ptmal = 1450 & 0xFF;		//1703
            _ptmah = 1450 >> 8;
            break;
        case 12://0.784k				
        	_ptmal = 1342 & 0xFF;		//1276
            _ptmah = 1342 >> 8;
            break;
        }
        _pton = 1;
    }
}


void beep(uint8_t mode, uint16_t time){
	toneMode(mode);
	delay(time);	//ms
	toneMode(0);
}

void doBee(uint8_t mode, uint16_t *beeIndex){
	switch(mode){
	case 0:
		if(*beeIndex < 5){
			toneMode(6);
		}else if(*beeIndex < 10){
			toneMode(10);
		}else if(*beeIndex < 25){
			toneMode(0);
		}else{
			*beeIndex = 0;
		}
	break;	
	
	case 1:
		if(*beeIndex < 5){
			toneMode(6);
		}else if(*beeIndex < 10){
			toneMode(10);
		}else if(*beeIndex < 15){
			toneMode(6);
		}else if(*beeIndex < 30){
			toneMode(0);
		}else{
			*beeIndex = 0;
		}
	break;
	
	case 2:
		if(*beeIndex < 5){
			toneMode(6);
		}else if(*beeIndex < 10){
			toneMode(11);
		}else if(*beeIndex < 25){
			toneMode(0);
		}else{
			*beeIndex = 0;
		}
	break;
	
	case 3:
		if(*beeIndex < 5){
			toneMode(11);
		}else if(*beeIndex < 10){
			toneMode(10);
		}else if(*beeIndex < 15){
			toneMode(12);
		}else if(*beeIndex < 20){
			toneMode(8);
		}else if(*beeIndex < 35){
			toneMode(0);
		}else if(*beeIndex < 40){
			toneMode(11);
		}else if(*beeIndex < 45){
			toneMode(10);
		}else if(*beeIndex < 50){
			toneMode(12);
		}else if(*beeIndex < 55){
			toneMode(8);
		}else if(*beeIndex < 95){
			toneMode(0);
		}else{
			*beeIndex = 0;
		}
	break;
	
	case 4:
		if(*beeIndex < 5){
			toneMode(8);
		}else if(*beeIndex < 10){
			toneMode(11);
		}else if(*beeIndex < 15){
			toneMode(8);
		}else if(*beeIndex < 30){
			toneMode(0);
		}else if(*beeIndex < 35){
			toneMode(8);
		}else if(*beeIndex < 40){
			toneMode(11);
		}else if(*beeIndex < 45){
			toneMode(8);
		}else if(*beeIndex < 80){
			toneMode(0);
		}else{
			*beeIndex = 0;
		}
	break;

#if 0
    case 0:
        if (*beeIndex >= 96){ //3s
            *beeIndex = 0;
            toneMode(11);
        }
        else if (*beeIndex == 7) //0.15s
        {
            toneMode(10);
        }
        else if (*beeIndex == 12) //0.30s
        {
            toneMode(12);
        }
        else if (*beeIndex == 17) //0.45s
        {
            toneMode(8);
        }
        else if (*beeIndex == 22) //0.60s
        {
            toneMode(0);
        }
        else if (*beeIndex == 31) //1.05s
        {
            toneMode(11);
        }
        else if (*beeIndex == 38) //1.20s
        {
            toneMode(10);
        }
        else if (*beeIndex == 43) //1.35s
        {
            toneMode(12);
        }
        else if (*beeIndex == 48) //1.50s
        {
            toneMode(8);
        }
        else if (*beeIndex == 53) //1.65s
        {
            toneMode(0);
        }
        break;
    case 1:
        if (*beeIndex >= 77) //2.4s
        {
            *beeIndex = 0;
            toneMode(8);
        }
        else if (*beeIndex == 7) //0.15s
        {
            toneMode(11);
        }
        else if (*beeIndex == 12) //0.30s
        {
            toneMode(8);
        }
        else if (*beeIndex == 16) //0.45s
        {
            toneMode(0);
        }
        else if (*beeIndex == 31) //0.90s
        {
            toneMode(8);
        }
        else if (*beeIndex == 40) //1.05s
        {
            toneMode(11);
        }
        else if (*beeIndex == 44) //1.20s
        {
            toneMode(8);
        }
        else if (*beeIndex == 49) //1.35s
        {
            toneMode(0);
        }
        break;
    case 2:
        if (*beeIndex >= 85) //2.66s
        {
            *beeIndex = 0;
            toneMode(5);
        }
        else if (*beeIndex == 8) //0.19s
        {
            toneMode(0);
          
        }
        else if (*beeIndex == 14) //0.38s
        {
        
            toneMode(6);
        }
        else if (*beeIndex == 22) //0.57s
        {
            toneMode(0);
          
        }
        else if (*beeIndex == 28) //0.76s
        {
     
            toneMode(12);
        }
        else if (*beeIndex == 36) //0.95s
        {
            toneMode(0);
     
        }
        break;
    case 3:
        if (*beeIndex >= 24) //0.76S
        {
            *beeIndex = 0;
 
            toneMode(5);
        }
        else if (*beeIndex == 8) //0.19s
        {
            toneMode(6);
        }
        else if (*beeIndex == 20) //0.57s
        {
            toneMode(0);
        }
        break;
    case 4:
        if (*beeIndex >= 64) //2.0S
        {
            *beeIndex = 0;
            toneMode(7);
        }
        else if (*beeIndex == 11) //0.1s
        {
            toneMode(0);
        }
        else if (*beeIndex == 15) //0.3s
        {
            toneMode(8);
        }
        else if (*beeIndex == 24) //0.5s
        {
            toneMode(0);
        }
        else if (*beeIndex == 28) //0.8s
        {
            toneMode(9);
        }
        else if (*beeIndex == 37) //1.0s
        {
            toneMode(0);
        }
        break;


		case 0:
			if(*beeIndex >= 48){
				toneMode(3);
				*beeIndex = 0;
			}
		    else if( *beeIndex == 10)
		    	toneMode(0);
		 break;
		 case 1:
		 	if(*beeIndex >= 48){
		 		toneMode(3);
		 		*beeIndex = 0;
		 	}else if(*beeIndex == 8){
		 		toneMode(0);
		 	}else if(*beeIndex == 12){
		 		toneMode(3);
		 	}else if(*beeIndex == 44){
		 		toneMode(0);
		 	}
		   break;
		 case 2:
		 	if(*beeIndex >= 48){
		 		toneMode(3);
		 		*beeIndex = 0;
		 	}else if(*beeIndex == 8){
		 		toneMode(0);
		 	}else if(*beeIndex == 12){
		 		toneMode(3);
		 	}else if(*beeIndex == 24){
		 		toneMode(3);
		 	}else if(*beeIndex == 32){
		 		toneMode(0);
		 	}
		   break;
		 case 3:
		 	if(*beeIndex >= 104){
		 		toneMode(3);
		 		*beeIndex = 0;
		 	}else if(*beeIndex == 16){
		 		toneMode(0);
		 	}else if(*beeIndex == 24){
		 		toneMode(3);
		 	}else if(*beeIndex == 40){
		 		toneMode(0);
		 	}
		   break;
		 case 4:
		 	if(*beeIndex >= 90){
		 		toneMode(2);
		 		*beeIndex = 0;
		 	}else if(*beeIndex == 13){
		 		toneMode(3);
		 	}else if(*beeIndex == 26){
		 		toneMode(0);
		 	}
		   break;
		 case 5:
		 	if(*beeIndex >= 26){
		 		toneMode(2);
		 		*beeIndex = 0;
		 	}else if(*beeIndex == 13){
		 		toneMode(3);
		 	}
		   break;
		 case 6:
		 	if(*beeIndex >= 39){
		 		toneMode(2);
		 		*beeIndex = 0;
		 	}else if(*beeIndex == 13){
		 		toneMode(3);
		 	}else if(*beeIndex == 26){
		 		toneMode(4);
		 	}
		   break;
		 case 7:
		 	if(*beeIndex >= 83){
		 		toneMode(2);
		 		*beeIndex = 0;
		 	}else if(*beeIndex == 26){
		 		toneMode(0);
		 	}else if(*beeIndex == 32){
		 		toneMode(3);
		 	}else if(*beeIndex == 38){
		 		toneMode(0);
		 	}else if(*beeIndex == 45){
		 		toneMode(3);
		 	}else if(*beeIndex == 51){
		 		toneMode(0);
		 	}
		   break;			   			   			   			   			   			   
	#endif
	}
}


/*******************************************************************************
 * @fn		zh_memoryReadByte	
 * @brief	从flash中读取单个字节
 * @param	void
 * @return	void
 *******************************************************************************/
unsigned char zh_memoryReadByte(unsigned char addr){
	_emi = 0;
	_eea=addr;				//user defined address
	//_bp=01;						//setup Bank Pointer
	_mp1l=0x40;					//setup memory pointer MP1,MP1 points to EEC register
	_mp1h = 0x01;
	_rden = 1;					//set RDEN bit, enable read operations
	_rd = 1;					//start Read Cycle - set RD bit
	while(_rd == 1){
		_clrwdt1();
		_clrwdt2();				//check for read cycle end
		_clrwdt();
	}
	_mp1h = 0x00;
	_mp1l = 0x00;
	_eec = 0;
	//_bp=00;
	_emi = 1;					
	return _eed;
}


/*******************************************************************************
 * @fn		zh_memoryWriteByte	
 * @brief	向flash中写入单个字节
 * @param	void
 * @return	void
 *******************************************************************************/
void zh_memoryWriteByte(unsigned char addr, unsigned char data){
	_emi = 0;
	_eea=addr;				//user defined address
	_eed=data;				//user defined data
	//_bp=01;						//setup Bank Pointer
	_mp1l=0x40;					//setup memory pointer MP1,MP1 points to EEC register
	_mp1h = 0x01;
	_wren = 1;					//set WREN bit, enable write operations
	_wr = 1;					//start Write Cycle - set WR bit
	while(_wr == 1){
		_clrwdt1();
		_clrwdt2();				//check for write cycle end
		_clrwdt();
	}
	_eec = 0;
//	_bp=00;	
	_emi = 1;					
}
