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
#include "mouse.h"
#include "gamepad.h"

#include "sound.h"

#include "moveEvent.h"
#include "communication.h"
#include "parameterManager.h"

using namespace robot_object;



void mode_R(){
    printfAsync("R mode\n");
    printfAsync("超信知探索\n");
    UMouse &m = UMouse::getInstance();
    EventList &events = EventList::getInstance();
    Gamepad &gamepad = Gamepad::getInstance();

    m.goal.set(1,3);
    m.start.set(0,0);
    m.coor.set(0,0);
    m.ab_position.x = 0.09;
    m.ab_position.y = 0.09;
    m.ab_ang = 90.0;
    m.direction = N;

    float v = 0.2;        //直進の最高速度
    float v_0 = 0;
    float a = 2.0;        //直進の加速度
    float v_max = 1.0;
    int8_t rot_times;
    waitmsec(1000);
    addBgmList(wily);
    events.push(new Stop(500));
    m.maze.updateWall(m.coor.x, m.coor.y, m.direction, WallSensor::getInstance());
    events.push(new Trape(0.09, v, 0.0, v, a));
    m.coor.y++;

    while(1){
        peri::waitusec(100);
        //Bボタン長押しで抜ける
        if (gamepad.B > 1000 ) {
            SEB();
            printfAsync("select! \n");
            waitmsec(1000);
            break;
        }
        //printfAsync("while\n");

        if(events.empty() == true){
            //---壁を更新
            printfAsync("----------\n");
            printfAsync("%d %d %d\n", m.coor.x, m.coor.y,m.direction);
            m.maze.updateWall(m.coor.x, m.coor.y, m.direction, WallSensor::getInstance());
            //---ゴールに着いたら探索終了
            if(m.coor == m.goal){
                events.push(new Trape(0.10, v, v, 0.0, a));
                events.push(new Stop(500));
                famima();
                break;
            }
            printfAsync("updateWall\n");
            m.maze.makeSearchMap(m.goal.x, m.goal.y);
            //m.maze.watchPotentialMap();
            printfAsync("makeSerchMap\n");
            rot_times = m.maze.getMinDirection(m.coor.x, m.coor.y, m.direction) - m.direction;
            printfAsync("%d getMinDirection\n", rot_times);
            if (rot_times == 6) rot_times = -2;
            else if(rot_times == -6) rot_times = 2;

            if(rot_times == 0){
                events.push(new Trape(0.18, v, v, v, a));
            }
            else{
                events.push(new Trape(0.10, v, v, 0.0, a));
                events.push(new Stop(500));
                events.push(new PivotTurn(45.0f * rot_times));
                events.push(new Stop(500));
                events.push(new Trape(0.08, v, 0.0, v, a));
            }
            m.direction = m.maze.getMinDirection(m.coor.x, m.coor.y, m.direction);
            if(m.direction == E)m.coor.x ++;
            else if(m.direction == N)m.coor.y++;
            else if(m.direction == W)m.coor.x--;
            else if(m.direction == S)m.coor.y--;
        }
     }

}



