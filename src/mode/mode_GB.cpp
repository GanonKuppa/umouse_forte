/*
 * mode_GB.cpp
 *
 *  Created on: 2017/02/25
 *      Author: ryota
 */



#include <stdint.h>
#include "mode_GB.h"
#include "tactsw.h"
#include "timer.h"
#include "fcled.h"
#include "sound.h"
#include "uart.hpp"
#include "imu.hpp"
#include "gamepad.h"

void mode_GB(){
    Gamepad &gamepad = Gamepad::getInstance();
	myprintf3("GB mode\n");

	  while(1) {
	           waitmsec(100);
	           if (gamepad.B < 1000 ) break;
	       }
	    //myprintf3("ジャイロをキャリブレーションします。\n");
	    MPU9250 &imu1 = MPU9250::getInstance();
	    //imu2.calibOmegaOffset();
	    //myprintf3("ジャイロのキャリブレーションが終わりました。\n");

	    while (1) {
	           waitmsec(10);

	           if (gamepad.B > 10 ) {
	               SEB();
	               myprintf3("select! \n");
	               waitmsec(1000);
	               break;
	           }
	       }

	    while (1) {
	        waitmsec(100);
	        myprintf3("%d, %d, %d, %d \n",
	                imu1.omega_raw[0],imu1.omega_raw[1],imu1.omega_raw[2],imu1.temp_raw
	        );

	        if (gamepad.B > 1000 ) {
	            SEB();
	            myprintf3("select! \n");
	            waitmsec(1000);
	            return;
	        }
	    }

}

