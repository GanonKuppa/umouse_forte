/*
 * mode_N.cpp
 *
 *  Created on: 2017/02/25
 *      Author: ryota
 */




#include <stdint.h>
#include <uart.h>
#include "mode_R.h"
#include "tactsw.h"
#include "timer.h"
#include "fcled.h"
#include "sound.h"
#include "pwm.h"

#include "communication.h"

using namespace robot_object;


void mode_R(){
	printfAsync("R mode\n");
}
