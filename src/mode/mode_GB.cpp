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
#include "wallsensor.hpp"

using namespace robot_object;


void mode_GB(){
    Gamepad &gamepad = Gamepad::getInstance();
	printfAsync("GB mode\n");

	  while(1) {
	           waitmsec(100);
	           if (gamepad.B < 1000 ) break;
	       }
	    printfAsync("壁センサの調整。\n");

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
	        //printfAsync("%d, %d, %d, %d \n",
	        //        imu1.omega_raw[0],imu1.omega_raw[1],imu1.omega_raw[2],imu1.temp_raw
	        //);
	        WallSensor &ws = WallSensor::getInstance();
            printfAsync("%d, %d, %d \n",
                ws.isLeft(), ws.isAhead(), ws.isRight()
            );


	        if (gamepad.B > 1000 ) {
	            SEB();
	            printfAsync("select! \n");
	            waitmsec(1000);
	            return;
	        }
	    }

}

