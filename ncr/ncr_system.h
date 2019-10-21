#ifndef _NCR_SYSTEM_H
#define _NCR_SYSTEM_H
#include "hal_type.h"

extern uint8_t waringEnable;

uint8_t pair(uint8_t ch);


void delay(unsigned long value);
void ptmtToneConfig(void);

void toneMode(uint8_t nMode);

void beep(uint8_t mode, uint16_t time);

void doBee(uint8_t mode, uint16_t *beeIndex);

void hold30loop(void);

void zh_memoryWriteByte(unsigned char addr, unsigned char data);
unsigned char zh_memoryReadByte(unsigned char addr);

void keysPushWaring(void);

void holdLow(void);

#endif
