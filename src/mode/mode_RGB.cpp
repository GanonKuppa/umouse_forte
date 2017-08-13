/*
 * mode_RGB.cpp
 *
 *  Created on: 2017/02/25
 *      Author: ryota
 */




#include <stdint.h>
#include <uart.h>
#include "mode_RGB.h"
#include "tactsw.h"
#include "timer.h"
#include "fcled.h"
#include "sound.h"
#include "mouse.h"
#include "Gamepad.h"

void mode_RGB(){
    myprintf3("RGB mode\n");
    myprintf3("ラジコン!!!!!!\n");

    Gamepad &gamepad = Gamepad::getInstance();
    UMouse  &mouse   = UMouse::getInstance();
    while(1){
        waitmsec(10);
        volatile float str_duty = gamepad.R3D_y /1024.0;
        volatile float rot_duty = gamepad.R3D_x /1024.0;
        volatile float duty_r = str_duty - rot_duty;
        volatile float duty_l = str_duty + rot_duty;
        //myprintf3("-- \n %f \n %f \n", str_duty, rot_duty);

        mouse.setDuty_R(duty_r);
        mouse.setDuty_L(duty_l);


        if (gamepad.B > 100 && gamepad.B < 200 ) {
            mouse.setDuty_R(0.0);
            mouse.setDuty_L(0.0);
            SEB();
            myprintf3("select! \n");
            waitmsec(1000);
            return;
        }

    }

}
