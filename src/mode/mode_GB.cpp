/*
 * mode_GB.cpp
 *
 *  Created on: 2017/02/25
 *      Author: ryota
 */



#include <stdint.h>
#include <uart.h>
#include "mode_GB.h"
#include "tactsw.h"
#include "timer.h"
#include "fcled.h"
#include "sound.h"
#include "imu.hpp"
#include "gamepad.h"

#include "communication.h"

using namespace robot_object;


void mode_GB(){
    Gamepad &gamepad = Gamepad::getInstance();
	printfAsync("GB mode\n");

	  while(1) {
	           waitmsec(100);
	           if (gamepad.B < 1000 ) break;
	       }
	    //printfAsync("ジャイロをキャリブレーションします。\n");
	    MPU9250 &imu1 = MPU9250::getInstance();
	    //imu2.calibOmegaOffset();
	    //printfAsync("ジャイロのキャリブレーションが終わりました。\n");

	    while (1) {
	           waitmsec(10);

	           if (gamepad.B > 10 ) {
	               SEB();
	               printfAsync("select! \n");
	               waitmsec(1000);
	               break;
	           }
	       }

	    while (1) {
	        waitmsec(100);
	        printfAsync("%d, %d, %d, %d \n",
	                imu1.omega_raw[0],imu1.omega_raw[1],imu1.omega_raw[2],imu1.temp_raw
	        );

	        if (gamepad.B > 1000 ) {
	            SEB();
	            printfAsync("select! \n");
	            waitmsec(1000);
	            return;
	        }
	    }

}

