
#include "iodefine.h"
#include "fcled.h"


#define LED_R_PIN   PORTA.PODR.BIT.B2 //R PA2
#define LED_G_PIN	PORTA.PODR.BIT.B3 //G PA3
#define LED_B_PIN	PORT1.PODR.BIT.B5 //B P15



/////////////////////////////////////////////////////////////////////
void LED_R::setState(uint8_t state){
	LED_R_PIN = 1-state;

};
/////////////////////////////////////////////////////////////////////
void LED_G::setState(uint8_t state){
	LED_G_PIN = 1-state;
};
/////////////////////////////////////////////////////////////////////
void LED_B::setState(uint8_t state){
	LED_B_PIN = 1-state;
};







