#include <stdint.h>
#include "iodefine.h"
#include "da.h"

/**************DA変換の初期設定*****************/
void initDA(void){
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(DA) = 0;
	SYSTEM.PRCR.WORD = 0xA500;


	PORT0.PDR.BIT.B5 = 0;
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.P05PFS.BYTE = 0x80;
	MPC.PWPR.BYTE =0x80;
	PORT0.PMR.BIT.B5 = 0;

	DA.DACR.BYTE = 0x3F;

	DA.DADR1 = 0;
	DA.DACR.BYTE = 0xFF;

}

void setDA(uint16_t da){
	DA.DADR1 = da;
	DA.DACR.BIT.DAOE1=1;
}

uint16_t getDA(){
	return DA.DADR1;
};
