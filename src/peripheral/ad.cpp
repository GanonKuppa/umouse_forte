/*
 * ad.cpp
 *
 *  Created on: 2016/09/23
 *      Author: ryota
 */

#include <stdint.h>

#include "iodefine.h"
#include "ad.h"

/**
 * AN000 :AD_VBAT     1個
 *   P40
 * AN001-AN007:       7個
 *   P41,P42,P43,P44,P45,P46,P47
 * AN108,AN109,AN110: 3個
 * 合計 11個のADピンを使用
 *   PD0,PD1,PD2
 */




/***********AD変換初期化******************/
void initAD(void){
	SYSTEM.PRCR.WORD = 0xA502;
		MSTP(S12AD) = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	SYSTEM.PRCR.WORD = 0xA502;
		MSTP(S12AD1) = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	//AN000: AD_VBAT
	PORT4.PDR.BIT.B0    = 0;
	PORT4.PMR.BIT.B0    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.P40PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;

	//AN001
	PORT4.PDR.BIT.B1    = 0;
	PORT4.PMR.BIT.B1    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.P41PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;

	//AN002
	PORT4.PDR.BIT.B2    = 0;
	PORT4.PMR.BIT.B2    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.P42PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;

	//AN003
	PORT4.PDR.BIT.B3    = 0;
	PORT4.PMR.BIT.B3    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.P43PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;

	//AN004
	PORT4.PDR.BIT.B4    = 0;
	PORT4.PMR.BIT.B4    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.P44PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;

	//AN005
	PORT4.PDR.BIT.B5    = 0;
	PORT4.PMR.BIT.B5    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.P45PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;

	//AN006
	PORT4.PDR.BIT.B6    = 0;
	PORT4.PMR.BIT.B6    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.P46PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;

	//AN007
	PORT4.PDR.BIT.B7    = 0;
	PORT4.PMR.BIT.B7    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.P47PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;

	//AN108
	PORTD.PDR.BIT.B0    = 0;
	PORTD.PMR.BIT.B0    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.PD0PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;

	//AN109
	PORTD.PDR.BIT.B1    = 0;
	PORTD.PMR.BIT.B1    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.PD1PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;

	//AN110
	PORTD.PDR.BIT.B2    = 0;
	PORTD.PMR.BIT.B2    = 0;
	MPC.PWPR.BIT.B0WI   = 0;
	MPC.PWPR.BIT.PFSWE  = 1;
	MPC.PD2PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE  = 0;
	MPC.PWPR.BIT.B0WI   = 1;


	S12AD.ADCSR.BIT.EXTRG = 1;
	S12AD.ADCSR.BIT.TRGE = 1;
	S12AD.ADCSR.BIT.ADCS = 0;

	S12AD1.ADCSR.BIT.EXTRG = 1;
	S12AD1.ADCSR.BIT.TRGE = 1;
	S12AD1.ADCSR.BIT.ADCS = 0;

}
/***********AD変換開始関数****************/
uint16_t startAD_AN000(void){
	S12AD.ADANSA0.WORD = 0x0001;
	S12AD.ADADS0.BIT.ADS0 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD.ADCSR.BIT.ADST == 1);
	return S12AD.ADDR0;
}

uint16_t startAD_AN001(void){
	S12AD.ADANSA0.WORD = 0x0002;
	S12AD.ADADS0.BIT.ADS0 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD.ADCSR.BIT.ADST == 1);
	return S12AD.ADDR1;
}

uint16_t startAD_AN002(void){
	S12AD.ADANSA0.WORD = 0x0004;
	S12AD.ADADS0.BIT.ADS0 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD.ADCSR.BIT.ADST == 1);
	return S12AD.ADDR2;
}

uint16_t startAD_AN003(void){
	S12AD.ADANSA0.WORD = 0x0008;
	S12AD.ADADS0.BIT.ADS0 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD.ADCSR.BIT.ADST == 1);
	return S12AD.ADDR3;
}

uint16_t startAD_AN004(void){
	S12AD.ADANSA0.WORD = 0x0010;
	S12AD.ADADS0.BIT.ADS0 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD.ADCSR.BIT.ADST == 1);
	return S12AD.ADDR4;
}

uint16_t startAD_AN005(void){
	S12AD.ADANSA0.WORD = 0x0020;
	S12AD.ADADS0.BIT.ADS0 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD.ADCSR.BIT.ADST == 1);
	return S12AD.ADDR5;
}

uint16_t startAD_AN006(void){
	S12AD.ADANSA0.WORD = 0x0040;
	S12AD.ADADS0.BIT.ADS0 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD.ADCSR.BIT.ADST == 1);
	return S12AD.ADDR6;
}

uint16_t startAD_AN007(void){
	S12AD.ADANSA0.WORD = 0x0080;
	S12AD.ADADS0.BIT.ADS0 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD.ADCSR.BIT.ADST == 1);
	return S12AD.ADDR7;
}


uint16_t startAD_AN108(void){
	S12AD1.ADANSA0.WORD = 0x0100;
	S12AD1.ADADS1.BIT.ADS1 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD1.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD1.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD1.ADCSR.BIT.ADST == 1);
	return S12AD1.ADDR8;
}

uint16_t startAD_AN109(void){
	S12AD1.ADANSA0.WORD = 0x0200;
	S12AD1.ADADS1.BIT.ADS1 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD1.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD1.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD1.ADCSR.BIT.ADST == 1);
	return S12AD1.ADDR9;
}

uint16_t startAD_AN110(void){
	S12AD1.ADANSA0.WORD = 0x0400;
	S12AD1.ADADS1.BIT.ADS1 = 0x0000; //1:変換値加算モード選択 0：非選択
	//S12AD.ADADC.BIT.ADC   = 3; //加算回数の選択 4times変換 3times加算
	S12AD1.ADCER.BIT.ADRFMT = 0; //右詰めフォーマット

	S12AD1.ADCSR.BIT.ADST = 1;
	//S12AD.ADSTRGR.BIT.ADSTRS = 0;
	while(S12AD1.ADCSR.BIT.ADST == 1);
	return S12AD1.ADDR10;
}

void startAD_All(void){
	startAD_AN000();
	startAD_AN001();
	startAD_AN002();
	startAD_AN003();
	startAD_AN004();
	startAD_AN005();
	startAD_AN006();
	startAD_AN007();
	startAD_AN108();
	startAD_AN109();
	startAD_AN110();
}

