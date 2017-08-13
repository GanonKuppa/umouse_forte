/*
 * uart.h
 *
 *  Created on: 2016/07/24
 *      Author: ryota
 */

#pragma once

#include <stdint.h>

void initSCI1();
void put1byte(char c);
void putnbyte(char *buf,int len);
int myprintf(const char *fmt, ...);

void initSCI2();
void put1byte2(char c);
void putnbyte2(char *buf,int len);
int myprintf2(const char *fmt, ...);

void initSCIFA9();
void putnbyte3(uint8_t *buf,uint16_t len);

void retrieveDatafromFRDR();
int sendDatafromTransBuff();
int myprintf3(const char *fmt, ...);
int myprintf3_Dbg(const char *fmt, ...);

void sendPeriodicMsg();
void packData(uint8_t *buf);

uint8_t* getPointerOfPeriodicMsg();
void set2ByteVal(uint16_t index, float val, float prop);
void set2ByteVal(uint16_t index, uint16_t val);


