/*
 * mode_B.cpp
 *
 *  Created on: 2017/02/25
 *      Author: ryota
 */

#include <stdint.h>
#include <uart.h>
#include "mode_B.h"
#include "tactsw.h"
#include "timer.h"
#include "fcled.h"
#include "sound.h"
#include "gamepad.h"
#include "mouse.h"
#include "imu.hpp"

//Eigen
//#include <Core>
//#include <Geometry>

#include "moveEvent.h"
#include "communication.h"

using namespace robot_object;

void mode_B(){
    printfAsync("B mode\n");

    EventList &events = EventList::getInstance();

    //MPU9250::getInstance().calibOmegaOffset(200);

    events.push(new Stop(500));

    events.push(new SimplePivotTurn(90.0));
    events.push(new Stop(1500));
    events.push(new Stop(500));


    events.push(new SimplePivotTurn(-90.0));
    events.push(new Stop(1500));
    events.push(new Stop(500));

    //events.push(new SimpleTrape(0.18*4));

//    events.push(new SimplePivotTurn(180.0));
    events.push(new Stop(1500));
    events.push(new Stop(500));

//    events.push(new SimpleTrape(0.18*4));

//    events.push(new SimplePivotTurn(-180.0));
    events.push(new Stop(1500));
    events.push(new Stop(500));


    Gamepad &gamepad = Gamepad::getInstance();
    UMouse  &mouse   = UMouse::getInstance();
    while(1){
        waitmsec(100);

        if (gamepad.B > 100 && gamepad.B < 200 ) {
                    SEB();
                    printfAsync("select! \n");
                    waitmsec(1000);
                    return;
                }

    }

};
