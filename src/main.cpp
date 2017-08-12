/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  micromouse                             */
/*      FILE         :  micromouse.cpp                         */
/*      DESCRIPTION  :  Main Program                           */
/*      CPU SERIES   :  RX700                                  */
/*      CPU TYPE     :  RX71M                                  */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/

/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 08/07/2013                                        */
/************************************************************************/

#include "iodefine.h"

#ifdef CPPAPP
//Initialize global constructors
extern "C" void __main() {
    static int initialized;
    if (!initialized) {
        typedef void (*pfunc)();
        extern pfunc __ctors[];
        extern pfunc __ctors_end[];
        pfunc *p;

        initialized = 1;
        for (p = __ctors_end; p > __ctors;)
            (*--p)();
    }
}

#endif 

#include <stdint.h>

#include <array>
#include "clock.h"
#include "uart.hpp"
#include "gpio.h"
#include "timeInterrupt.hpp"
#include "spi.h"
#include "timer.h"
#include "ad.h"
#include "pwm.h"
#include "phaseCounting.h"
#include <imu.hpp>
#include "da.h"
#include "myUtil.h"
#include "sound.h"
#include "tactsw.h"
#include "fcled.h"
#include "mode.h"

#include "maze.h"
#include "mouse.h"
#include "wallsensor.hpp"
#include "gamepad.h"

#include "moveEvent.h"

using namespace std;

//プロトタイプ宣言
void periperalInit();
void startUpInit();
uint16_t temp_V=0;
//-------------タイマ割り込み関数---------------//
extern "C" void timeInterrupt(void);

//250usec毎に呼ばれる
void timeInterrupt(void) {
    //http://japan.renesasrulz.com/cafe_rene/f/69/t/1515.aspx 多重割り込み　資料
    __builtin_rx_setpsw('I');

    static uint64_t countIntNum = 0;

    //--------------------------------------//
    MPU9250 &imu1 = MPU9250::getInstance();
    Icm20608G &imu2 = Icm20608G::getInstance();
    TactSw &tsw = TactSw::getInstance();
    FcLed &fcled = FcLed::getInstance();
    WallSensor &wallSen = WallSensor::getInstance();
    Gamepad &gamepad = Gamepad::getInstance();
    EventList &events = EventList::getInstance();
    UMouse &mouse = UMouse::getInstance();

    //UARTの送受信処理
    if (countIntNum % 7 == 0) {
        sendDatafromTransBuff();
    }
    retrieveDatafromFRDR();

    //30msec毎の処理
    if (countIntNum % 120 == 0) {
        sendPeriodicMsg();
    }
    //1msec毎の処理
    if(countIntNum % 4 == 0){
        if(getElapsedMsec()>5000){
            imu1.update();
            imu2.update();
        }
    }
    if (countIntNum % 4 == 1){

        tsw.update();
        fcled.update();
        gamepad.update();
        events.update();
    }
    if (countIntNum % 4 == 2){
        mouse.update();
    }


    float vol_f = 15.1 / 5.1 * (S12AD.ADDR0) * 3.3 / 4096;
    if (countIntNum % 1000 == 0){
        if(vol_f < 6.8)famima();
    }

    //リセットコマンドの監視
    if(gamepad.BACK >0 &&
       gamepad.LB >0 &&
       gamepad.LT >0 ){
       SYSTEM.PRCR.WORD = 0xA502;
       SYSTEM.SWRR = 0xA501;
    }

    //ブートモードへの変更
    if(gamepad.RB > 0 &&
       gamepad.RT > 0 &&
       gamepad.START > 0){
        PORTD.PODR.BIT.B7 = 0; //PICの入力ピンをローにする
    }



    //壁センサの更新処理
    switch(countIntNum % 4){
        case 0:
            wallSen.updateAllOffVal();
            wallSen.turnOnLeftLed();
            break;
        case 1:
            wallSen.updateLeftOnVal();
            wallSen.turnOffAllLed();
            wallSen.turnOnRightLed();
            break;
        case 2:
            wallSen.updateRightOnVal();
            wallSen.turnOffAllLed();
            wallSen.turnOnAheadLed();
            break;
        case 3:
            wallSen.updateAheadOnVal();
            wallSen.turnOffAllLed();
            wallSen.modulateVal();
            break;
    }

    //毎回行う処理
    soundUpdate();
    startAD_AN000(); //電源

    countIntNum++;
    endTimeuCountIntCMT0();

}

//-------------メイン関数---------------//
int main() {
    periperalInit();
    startUpInit();

    float vol_f = 15.1 / 5.1 * (S12AD.ADDR0) * 3.3 / 4096;
    if(vol_f < 7.0)famima();

    MPU9250& imu1 = MPU9250::getInstance();
    Icm20608G& imu2 = Icm20608G::getInstance();
    FcLed& fcled = FcLed::getInstance();
    myprintf3_Dbg("start: %d \n", CMTW0.CMWCNT);

    //addBgmList(otenba);
    //addBgmList(robotol);
    //addBgmList(gamecube);
    //addBgmList(togetoge);
    //addBgmList(owen);
    //addBgmList(road27);

    //addBgmList(sky_high);

    myprintf3_Dbg("end %d  \n", CMTW0.CMWCNT);
    //fcled.R.flash(100,100);
    //waitmsec(5000);
    //fcled.G.flash(1000,500);
    //bpmTest(2);
    //waitmsec(5000);
    //fcled.B.flash(100,200);
    //bpmTest(2);
    //getPointerOfPeriodicMsg()[75] = 111;
    //getPointerOfPeriodicMsg()[78] = 0xff;
    getPointerOfPeriodicMsg()[155] = 0xff;
    getPointerOfPeriodicMsg()[156] = 0xff;
    //uint8_t *periMes = getPointerOfPeriodicMsg();

    UMouse  &mouse   = UMouse::getInstance();

     while(1){
         myprintf3("entry point \n");
         ///////////////////////////////////////
         MPU9250::getInstance().calibOmegaOffset(200);
         MPU9250::getInstance().calibAccOffset(200);

         modeSelect();
     };

    return 0;
}

//各ペリフェラルの初期化
void periperalInit() {
    //クロック
    initClock();
    //IOピン
    initGPIO();
    //UART
    initSCI1();
    initSCI2();
    initSCIFA9();

    //割り込み関数
    initCMT0();
    initCMT1();

    //SPI
    initRSPI0();
    initRSPI1();

    //時間測定
    initTPU0();
    initCMTW0();
    initCMTW1();

    //AD
    initAD();

    //位相係数
    initMTU1();
    initMTU2();

    //PWM
    initMTU3();
    initMTU4();

    //DA
    initDA();
    myprintf3("-------各種ペリフェラル初期化完了-------\n");

};

//起動時の処理
void startUpInit() {


    setDutyMTU3(0.0);
    setDutyMTU4(0.0);

    setPriorityCMT0(12);
    setPriorityCMT1(15);
    startCMT0();
    myprintf3("-------CMT0割り込み開始-------\n");

    MPU9250& imu1 = MPU9250::getInstance();
    Icm20608G& imu2 = Icm20608G::getInstance();

    imu1.init();
    imu2.init();

    //sound

    startCMT1();
    myprintf3("-------CMT1割り込み開始-------\n");

    /////////////コンパイル時固有文字列/////////
    myprintf3("Compile Date\n %s\n", __DATE__);
    uint16_t compile_hash = 0;
    for (int i = 0; i < sizeof(__TIME__); i++) {
        compile_hash += __TIME__[i];
    }

    myprintf3("Compile HASH: %d\n", compile_hash);
    myprintf3("Compile TIME: %s\n", __TIME__);
    myprintf3("Compile FILE: %s\n", __FILE__);
    myprintf3("---------------------------\n");
    GB();
    waitmsec(1800);
    randomNote(compile_hash);
    waitmsec(400);
    /////////////電池電圧警告////////////////
    float vol_f = 15.1 / 5.1 * (S12AD.ADDR0) * 3.3 / 4096;
    uint8_t num_1V = uint8_t(vol_f);
    uint8_t num_0_1V = uint8_t((vol_f - float(num_1V)) * 10.0);
    for (int i = 0; i < num_1V; i++) {
        SEA();
        if (i == 4)
            waitmsec(250);
        else
            waitmsec(125);
    }
    waitmsec(125);
    for (int i = 0; i < num_0_1V; i++) {
        SEB();
        if (i == 4)
            waitmsec(250);
        else
            waitmsec(125);
    }
    waitmsec(125);

    myprintf3("===finish init====\n");

};
