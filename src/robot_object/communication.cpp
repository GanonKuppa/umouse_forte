/*
 * communication.cpp
 *
 *  Created on: 2017/08/13
 *      Author: ryota
 */


#include "communication.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include "uart.h"
#include "timeInterrupt.h"
#include "timer.h"
#include "ad.h"
#include "phaseCounting.h"
#include "pwm.h"

#include "sound.h"
#include "imu.hpp"
#include "tactsw.h"
#include "fcled.h"
#include "wallsensor.hpp"
#include "gamepad.h"

#include "maze.h"
#include "mouse.h"
#include "parameterManager.h"

#include "myUtil.hpp"

#include <deque>
#include <queue>


using std::deque;
using std::queue;

namespace peri = peripheral_RX71M;



static void set2ByteVal(uint8_t *buf, uint16_t index, float val,float prop);
static void set2ByteVal(uint8_t *buf, uint16_t index, uint16_t val);
static void set2ByteVal(uint8_t *buf, uint16_t index, int16_t val);
static void set2ByteVal(uint8_t *buf, uint16_t index, uint32_t val);
static void set2ByteVal(uint8_t *buf, uint16_t index, int32_t val);
static void set4ByteVal(uint8_t *buf, uint16_t index, uint32_t val);

namespace robot_object{

    static const uint16_t PERIODIC_MSG_LEN = 400;
    static const uint16_t CMD_SIZE  = 16;
    static queue<uint8_t> printfBuff;
    static uint8_t periodicMsg[PERIODIC_MSG_LEN];

    static void packDataMaze(uint8_t part_num, uint8_t *buf);
    static void packData(uint8_t *buf);

    /***********同期printf関数******************/
    int printfSync(const char *fmt, ...) {
        static char buffer[1000];
        int len;

        va_list ap;
        va_start(ap, fmt);

        len = vsprintf(buffer, fmt, ap);
        peri::putnbyteSCI1(buffer, len);
        va_end(ap);
        return len;
    }


    /***********非同期printf関数******************/
    int printfAsync(const char *fmt, ...) {
        static char buffer[1000];
        int len;

        va_list ap;
        va_start(ap, fmt);

        len = vsprintf(buffer, fmt, ap);

        for (int c = 0; c < len; c++) {
            printfBuff.push(buffer[c]);
        }

        va_end(ap);
        return len;
    }


    void fetchCommand()
    {
        static bool first_recieve_flag = false;
        int16_t last_cmd_index = -1;
        for(int i=0;i<peri::recieveBuffCount-4;i++){
            if(peri::recieveBuffCount-i > CMD_SIZE &&
                peri::recieveBuff[i+0]==99 &&
                peri::recieveBuff[i+1]==109 &&
                peri::recieveBuff[i+2]==100
            ){

                if(first_recieve_flag == false){
                    SED();
                    first_recieve_flag = true;
                }

                if(peri::recieveBuff[i+3] == 254 && peri::recieveBuff[i+4] == 253){
                    Gamepad &gamepad = Gamepad::getInstance();
                    gamepad.updateCommand(&peri::recieveBuff[i]);
                }

                if(peri::recieveBuff[i+3] == 251){
                    ParameterManager &pm = ParameterManager::getInstance();

                    pm.writeCommand(&peri::recieveBuff[i]);
                }

                last_cmd_index = i;
                break;
            }
        }

        if (last_cmd_index != -1){
            for(int ind = last_cmd_index + CMD_SIZE;
                    ind < peri::recieveBuffCount;
                    ind++){
                peri::recieveBuff[ind -(last_cmd_index + CMD_SIZE)] = peri::recieveBuff[ind];
            }
            peri::recieveBuffCount = peri::recieveBuffCount - (last_cmd_index + CMD_SIZE);
        }
    }

    /***********periodicMsgを送る******************/
    void sendPeriodicMsg() {
        packData(periodicMsg);
        peri::putnbyteSCIFA9(periodicMsg, PERIODIC_MSG_LEN);
    }

    //迷路の壁情報を送る
    //32 x 32の迷路データを4つに分割
    void packDataMaze(uint8_t part_num, uint8_t *buf) {
        buf[0] = part_num;
        UMouse &mouse = UMouse::getInstance();
        uint8_t ind = 1;

        if (part_num == 0) {
            for (int i = 0; i < 16; i++) {
                buf[ind + 0 + i * 4] = ((mouse.maze.walls_vertical[i] & 0x000000ff)
                        >> 0);
                buf[ind + 1 + i * 4] = ((mouse.maze.walls_vertical[i] & 0x0000ff00)
                        >> 8);
                buf[ind + 2 + i * 4] = ((mouse.maze.walls_vertical[i] & 0x00ff0000)
                        >> 16);
                buf[ind + 3 + i * 4] = ((mouse.maze.walls_vertical[i] & 0xff000000)
                        >> 24);
            }
        }

        if (part_num == 1) {
            for (int i = 0; i < 15; i++) {
                buf[ind + 0 + i * 4] = ((mouse.maze.walls_vertical[i + 16]
                        & 0x000000ff) >> 0);
                buf[ind + 1 + i * 4] = ((mouse.maze.walls_vertical[i + 16]
                        & 0x0000ff00) >> 8);
                buf[ind + 2 + i * 4] = ((mouse.maze.walls_vertical[i + 16]
                        & 0x00ff0000) >> 16);
                buf[ind + 3 + i * 4] = ((mouse.maze.walls_vertical[i + 16]
                        & 0xff000000) >> 24);
            }
        }

        if (part_num == 2) {
            for (int i = 0; i < 16; i++) {
                buf[ind + 0 + i * 4] =
                        ((mouse.maze.walls_horizontal[i] & 0x000000ff) >> 0);
                buf[ind + 1 + i * 4] =
                        ((mouse.maze.walls_horizontal[i] & 0x0000ff00) >> 8);
                buf[ind + 2 + i * 4] =
                        ((mouse.maze.walls_horizontal[i] & 0x00ff0000) >> 16);
                buf[ind + 3 + i * 4] =
                        ((mouse.maze.walls_horizontal[i] & 0xff000000) >> 24);
            }
        }

        if (part_num == 3) {
            for (int i = 0; i < 15; i++) {
                buf[ind + 0 + i * 4] = ((mouse.maze.walls_horizontal[i + 16]
                        & 0x000000ff) >> 0);
                buf[ind + 1 + i * 4] = ((mouse.maze.walls_horizontal[i + 16]
                        & 0x0000ff00) >> 8);
                buf[ind + 2 + i * 4] = ((mouse.maze.walls_horizontal[i + 16]
                        & 0x00ff0000) >> 16);
                buf[ind + 3 + i * 4] = ((mouse.maze.walls_horizontal[i + 16]
                        & 0xff000000) >> 24);
            }
        }
    }

    void packData(uint8_t *buf) {
        uint8_t printfDataNum = 0;
        const uint8_t printfFieldNum = 20;

        MPU9250& imu1 = MPU9250::getInstance();
        Icm20608G& imu2 = Icm20608G::getInstance();
        TactSw& tsw = TactSw::getInstance();
        WallSensor &wallSen = WallSensor::getInstance();
        UMouse &m = UMouse::getInstance();
        //header
        buf[0] = 0xff;
        buf[1] = 0xff;
        buf[2] = 0x48;
        buf[3] = 0x45;
        buf[4] = 0x41;
        buf[5] = 0x44;
        uint32_t elapsedTime = getElapsedMsec();
        set4ByteVal(buf, 8, elapsedTime);
        set2ByteVal(buf, 12, peri::getAD_AN000());
        set2ByteVal(buf, 14, peri::getAD_AN001());
        set2ByteVal(buf, 16, peri::getAD_AN002());
        set2ByteVal(buf, 18, peri::getAD_AN003());
        set2ByteVal(buf, 20, peri::getAD_AN004());
        set2ByteVal(buf, 22, peri::getAD_AN005());
        set2ByteVal(buf, 24, peri::getAD_AN006());
        set2ByteVal(buf, 26, peri::getAD_AN007());
        set2ByteVal(buf, 28, peri::getAD_AN108());
        set2ByteVal(buf, 30, peri::getAD_AN109());
        set2ByteVal(buf, 32, peri::getAD_AN110());
        set2ByteVal(buf, 34, imu1.omega_raw[0]);
        set2ByteVal(buf, 36, imu1.omega_raw[1]);
        set2ByteVal(buf, 38, imu1.omega_raw[2]);
        set2ByteVal(buf, 40, imu1.acc_raw[0]);
        set2ByteVal(buf, 42, imu1.acc_raw[1]);
        set2ByteVal(buf, 44, imu1.acc_raw[2]);
        set2ByteVal(buf, 46, imu1.mag_raw[0]);
        set2ByteVal(buf, 48, imu1.mag_raw[1]);
        set2ByteVal(buf, 50, imu1.mag_raw[2]);
        set2ByteVal(buf, 52, imu2.omega_raw[0]);
        set2ByteVal(buf, 54, imu2.omega_raw[1]);
        set2ByteVal(buf, 56, imu2.omega_raw[2]);
        set2ByteVal(buf, 58, imu2.acc_raw[0]);
        set2ByteVal(buf, 60, imu2.acc_raw[0]);
        set2ByteVal(buf, 62, imu2.acc_raw[0]);
        set2ByteVal(buf, 64, peri::getTimeuCountIntCMT0());
        set2ByteVal(buf, 66, peri::getTimeuCountIntCMT1());
        set2ByteVal(buf, 68, TPU0.TCNT);
        set2ByteVal(buf, 70, m.duty_R, 32767);
        set2ByteVal(buf, 72, m.duty_L, 32767);
        set2ByteVal(buf, 74, peri::getCountMTU1());
        set2ByteVal(buf, 76, peri::getCountMTU2());
        set2ByteVal(buf, 92, tsw.getOntime());
        set2ByteVal(buf, 92, tsw.getOntime());
        set2ByteVal(buf, 94, (int16_t)wallSen.right.at(0));
        set2ByteVal(buf, 96, (int16_t)wallSen.ahead.at(0));
        set2ByteVal(buf, 98, (int16_t)wallSen.left.at(0));


        set2ByteVal(buf, 100, m.t_ang_a, 20.0);
        set2ByteVal(buf, 102, m.t_ang_v, 20.0);
        set2ByteVal(buf, 104, m.t_ang, 20.0);
        set2ByteVal(buf, 106, m.accum_ang, 20.0);
        set2ByteVal(buf, 108, imu1.omega_c[2]);

        set2ByteVal(buf, 110, m.t_a, 1000.0);
        set2ByteVal(buf, 112, m.t_v, 3000.0);
        set2ByteVal(buf, 114, m.t_x, 3000.0);
        set2ByteVal(buf, 116, m.accum_x, 3000.0);
        set2ByteVal(buf, 118, m.a_v, 1000.0);
        set2ByteVal(buf, 120, m.a_h, 1000.0);
        set2ByteVal(buf, 122, m.v_enc, 3000.0 );
        set2ByteVal(buf, 124, m.wall_P, 3000.0);
        set2ByteVal(buf, 126, m.wall_I, 3000.0);
        set2ByteVal(buf, 128, m.wall_D, 3000.0);
        set2ByteVal(buf, 130, m.v_P, 3000.0);
        set2ByteVal(buf, 132, m.v_I, 3000.0);
        set2ByteVal(buf, 134, m.v_D, 3000.0);
        set2ByteVal(buf, 136, m.ang_P, 3000.0);
        set2ByteVal(buf, 138, m.ang_I, 3000.0);
        set2ByteVal(buf, 140, m.ang_D, 3000.0);
        set2ByteVal(buf, 142, m.ang_v_P, 3000.0);
        set2ByteVal(buf, 144, m.ang_v_I, 3000.0);
        set2ByteVal(buf, 146, m.ang_v_D, 3000.0);
        set2ByteVal(buf, 148, m.v_FF, 3000.0);
        set2ByteVal(buf, 150, m.ang_FF, 3000.0);


        //迷路データ
        static uint8_t count = 0;
        packDataMaze(count, &buf[160]);
        count++;
        if (count == 4)
            count = 0;

        //printf Data
        uint16_t start_byte = PERIODIC_MSG_LEN - printfFieldNum;
        uint16_t end_byte = PERIODIC_MSG_LEN;
        for (int i = start_byte; i < end_byte; i++) {
            if (printfBuff.empty() == false) {
                buf[i] = printfBuff.front();
                printfBuff.pop();
                printfDataNum++;
            } else {
                buf[i] = 0;
            }
        }
        //printf Data Num
        buf[7] = printfDataNum;

        //check sum
        uint8_t sum = 0;
        for (int i = 7; i < PERIODIC_MSG_LEN; i++)
            sum += buf[i];
        buf[6] = sum;
    }

    uint8_t* getPointerOfPeriodicMsg() {
        return periodicMsg;
    }


}

inline void set2ByteVal(uint8_t *buf, uint16_t index, float val,float prop){
    int16_t int_val = (int16_t)(val * prop);
    buf[index]   = (0x0000ff00 & int_val) >> 8;
    buf[index+1] = (0x000000ff & int_val)   ;
}

inline void set2ByteVal(uint8_t *buf, uint16_t index, uint16_t val){
    buf[index]   = (0x0000ff00 & val) >> 8;
    buf[index+1] = (0x000000ff & val)   ;
}

inline void set2ByteVal(uint8_t *buf, uint16_t index, int16_t val){
    buf[index]   = (0x0000ff00 & val) >> 8;
    buf[index+1] = (0x000000ff & val)   ;
}

inline void set2ByteVal(uint8_t *buf, uint16_t index, uint32_t val){
    buf[index]   = (0x0000ff00 & val) >> 8;
    buf[index+1] = (0x000000ff & val)   ;
}

inline void set2ByteVal(uint8_t *buf, uint16_t index, int32_t val){
    buf[index]   = (0x0000ff00 & val) >> 8;
    buf[index+1] = (0x000000ff & val)   ;
}

inline void set4ByteVal(uint8_t *buf, uint16_t index, uint32_t val){
    buf[index] = ((0xff000000 & val) >> 24);
    buf[index+1] = ((0x00ff0000 & val) >> 16);
    buf[index+2] = ((0x0000ff00 & val) >> 8);
    buf[index+3] = ((0x000000ff & val));
}





