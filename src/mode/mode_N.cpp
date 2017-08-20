/*
 * mode_N.cpp
 *
 *  Created on: 2017/02/25
 *      Author: ryota
 */

#include <stdint.h>
#include <uart.h>
#include "mode_N.h"
#include "tactsw.h"
#include "timer.h"
#include "fcled.h"
#include "sound.h"
#include "imu.hpp"

#include "gamepad.h"

#include "communication.h"

using namespace robot_object;




void mode_N() {
    Gamepad &gamepad = Gamepad::getInstance();
    printfAsync("N mode\n");

    while(1) {
           waitmsec(100);
           if (gamepad.B < 1000 ) break;
       }
    printfAsync("ジャイロをキャリブレーションします。\n");
    Icm20608G &imu2 = Icm20608G::getInstance();
    imu2.calibOmegaOffset();
    printfAsync("ジャイロのキャリブレーションが終わりました。\n");

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
        printfAsync("%f, %f, %f, %d, %d, %d\n",
                imu2.omega_f[0],imu2.omega_f[1],imu2.omega_f[2],
                imu2.omega_c[0],imu2.omega_c[1],imu2.omega_c[2]
        );

        if (gamepad.B > 1000 ) {
            SEB();
            printfAsync("select! \n");
            waitmsec(1000);
            return;
        }
    }
}
