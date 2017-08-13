/*
 * uart.cpp
 *
 *  Created on: 2016/07/24
 *      Author: ryota
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <timeInterrupt.h>
#include <uart.h>

#include "timer.h"
#include "iodefine.h"
#include "clock.h"
#include "ad.h"
#include "phaseCounting.h"
#include "pwm.h"

#include "imu.hpp"
#include "tactsw.h"
#include "fcled.h"

#include "maze.h"
#include "mouse.h"
#include "wallsensor.hpp"
#include "gamepad.h"

#include "myUtil.h"

#include <queue>
#include <array>

#define PERIODIC_MSG_LEN  (250)
#define RECEIVE_BUFF_LEN  (512)
#define CMD_SIZE  (16)
//#define DEBUG_SWITCH

using std::queue;
static queue<uint8_t> transBuff;
static queue<uint8_t> printfBuff;
static uint8_t recieveBuff[RECEIVE_BUFF_LEN];
static uint16_t recieveBuffCount = 0;
static uint8_t periodicMsg[PERIODIC_MSG_LEN];
//static queue<array<uint8_t, 10>> cmdBuff;


void execCommand(uint8_t *cmd)
{
    FcLed& fcled = FcLed::getInstance();
    uint8_t id = cmd[3];

    int16_t duty_int;
    int16_t deg_int;

    int16_t rt = cmd[12];
    int16_t lt = cmd[14];
    float rt_f, lt_f;

    if(lt == 128){
        PORT2.PODR.BIT.B0 = 0;
        PORT1.PODR.BIT.B7 = 0;
        lt_f = 0.001;
        fcled.B.turn(0);
    }
    else if(lt>128){
        PORT2.PODR.BIT.B0 = 1;
        PORT1.PODR.BIT.B7 = 0;
        lt_f = 0.001+0.2*(float(lt-128)/128.0);
        fcled.B.turn(1);
    }else{
        PORT2.PODR.BIT.B0 = 0;
        PORT1.PODR.BIT.B7 = 1;
        lt_f = 0.001+0.2*(float(128-lt)/128.0);
        fcled.B.flash(100,100);
    }

    if(rt == 128){
        PORT1.PODR.BIT.B3 = 0;
        PORT1.PODR.BIT.B2 = 0;
        rt_f = 0.001;
        fcled.R.turn(0);
    }
    else if(rt>128){
        PORT1.PODR.BIT.B3 = 0;
        PORT1.PODR.BIT.B2 = 1;
        rt_f = 0.001+0.2*(float(rt-128)/128.0);
        fcled.R.turn(1);
    }else{
        PORT1.PODR.BIT.B3 = 1;
        PORT1.PODR.BIT.B2 = 0;
        rt_f = 0.001+0.2*(float(128-rt)/128.0);
        fcled.R.flash(100,100);
    }
    myprintf3("=%d,%d,%d,%d,%d\n",cmd[3],cmd[4],cmd[5],PORT1.PODR.BIT.B3,PORT1.PODR.BIT.B2);

    setDutyMTU3(rt_f);
    setDutyMTU4(lt_f);
}


void fetchCommand()
{
    int16_t last_cmd_index = -1;
    for(int i=0;i<recieveBuffCount-4;i++){
        if(recieveBuffCount-i > CMD_SIZE &&
            recieveBuff[i+0]==99 &&
            recieveBuff[i+1]==109 &&
            recieveBuff[i+2]==100
        ){
            //execCommand(&recieveBuff[i]);
            Gamepad &gamepad = Gamepad::getInstance();
            gamepad.updateCommand(&recieveBuff[i]);
            last_cmd_index = i;
            break;
        }
    }

    if (last_cmd_index != -1){
        for(int ind = last_cmd_index + CMD_SIZE;
                ind < recieveBuffCount;
                ind++){
            recieveBuff[ind -(last_cmd_index + CMD_SIZE)] = recieveBuff[ind];
        }
        recieveBuffCount = recieveBuffCount - (last_cmd_index + CMD_SIZE);
    }
}


void initSCI1(void) {
    uint32_t PCLK = PCLKB;
    SYSTEM.PRCR.WORD = 0xA502;
    MSTP( SCI1 ) = 0;        //モジュールストップを解除
    SYSTEM.PRCR.WORD = 0xA500;

    PORT3.PMR.BIT.B0 = 0;   //ピンの設定をするときはまずピンを汎用ポートに設定しておく
    PORT2.PMR.BIT.B6 = 0;
    MPC.PWPR.BIT.B0WI = 0;  //書き込み許可 0で許可
    MPC.PWPR.BIT.PFSWE = 1; //書き込み許可  1で許可
    MPC.P26PFS.BIT.PSEL = 10; //P26を TXD1に
    MPC.P30PFS.BIT.PSEL = 10; //P30を RXD1に
    MPC.PWPR.BIT.PFSWE = 0;  //PFSWEの書き込み禁止 0
    MPC.PWPR.BIT.B0WI = 1; //書き込み禁止
    PORT3.PMR.BIT.B0 = 1;   //周辺モジュールをピンに割り当て
    PORT2.PMR.BIT.B6 = 1;   //

    SCI1.SMR.BIT.CKS = 0;  //PCLK/1
    SCI1.SMR.BIT.MP = 0;
    SCI1.SMR.BIT.STOP = 0;
    SCI1.SMR.BIT.PM = 0;
    SCI1.SMR.BIT.PE = 0;
    SCI1.SMR.BIT.CHR = 0;
    SCI1.SMR.BIT.CM = 0;
    SCI1.SEMR.BIT.ABCS = 1;
    SCI1.SEMR.BIT.BGDM = 1;
    SCI1.BRR = 3 - 1;   // N = PCLK /(8*BRR)

    SCI1.SCR.BIT.RE = 1; //受信許可
    SCI1.SCR.BIT.TE = 1; //送信許可

}

void initSCI2(void) {
    uint32_t PCLK = PCLKB;
    SYSTEM.PRCR.WORD = 0xA502;
    MSTP( SCI2 ) = 0;        //モジュールストップを解除
    SYSTEM.PRCR.WORD = 0xA500;

    PORT5.PMR.BIT.B0 = 0;   //ピンの設定をするときはまずピンを汎用ポートに設定しておく
    PORT5.PMR.BIT.B6 = 0;
    MPC.PWPR.BIT.B0WI = 0;  //書き込み許可 0で許可
    MPC.PWPR.BIT.PFSWE = 1; //書き込み許可  1で許可
    MPC.P50PFS.BIT.PSEL = 10; //P50を TXD2に
    MPC.P52PFS.BIT.PSEL = 10; //P52を RXD2に
    MPC.PWPR.BIT.PFSWE = 0;  //PFSWEの書き込み禁止 0
    MPC.PWPR.BIT.B0WI = 1; //書き込み禁止
    PORT5.PMR.BIT.B0 = 1;   //周辺モジュールをピンに割り当て
    PORT5.PMR.BIT.B2 = 1;   //

    SCI2.SMR.BIT.CKS = 0;  //PCLK/2
    SCI2.SMR.BIT.MP = 0;
    SCI2.SMR.BIT.STOP = 0;
    SCI2.SMR.BIT.PM = 0;
    SCI2.SMR.BIT.PE = 0;
    SCI2.SMR.BIT.CHR = 0;
    SCI2.SMR.BIT.CM = 0;
    SCI2.SEMR.BIT.ABCS = 1;
    SCI2.SEMR.BIT.BGDM = 1;
    SCI2.BRR = 3 - 1;   // N = PCLK /(8*BRR) 現在の設定は2Mbps

    SCI2.SCR.BIT.RE = 1; //受信許可
    SCI2.SCR.BIT.TE = 1; //送信許可

}

void initSCIFA9() {
    uint32_t PCLK = PCLKA;
    SYSTEM.PRCR.WORD = 0xA502;
    MSTP( SCIFA9 ) = 0;        //モジュールストップを解除
    SYSTEM.PRCR.WORD = 0xA500;

    PORTB.PMR.BIT.B6 = 0;   //ピンの設定をするときはまずピンを汎用ポートに設定しておく
    PORTB.PMR.BIT.B7 = 0;
    MPC.PWPR.BIT.B0WI = 0;  //書き込み許可 0で許可
    MPC.PWPR.BIT.PFSWE = 1; //書き込み許可  1で許可
    MPC.PB6PFS.BIT.PSEL = 0b1010; //RXD9に
    MPC.PB7PFS.BIT.PSEL = 0b1010; //TXD2に
    MPC.PWPR.BIT.PFSWE = 0;  //PFSWEの書き込み禁止 0
    MPC.PWPR.BIT.B0WI = 1; //書き込み禁止
    PORTB.PMR.BIT.B6 = 1;   //周辺モジュールをピンに割り当て
    PORTB.PMR.BIT.B7 = 1;   //

    SCIFA9.SMR.BIT.CKS = 0;
    SCIFA9.SEMR.BIT.ABCS0 = 1;
    SCIFA9.SEMR.BIT.BGDM = 1;
    SCIFA9.BRR = 6 - 1;
    SCIFA9.FCR.BIT.TTRG = 0b11;

    //受信設定
    SCIFA9.FCR.BIT.RTRG = 0b11;
    SCIFA9.SCR.BIT.RE = 1;

    //送信設定
    //IEN(SCIFA9,TXIF9) = 1;//割り込み要求を許可
    //IR(SCIFA9,TXIF9)=0;//割り込みステータフラグをクリア

    //SCIFA9.SCR.BIT.TEIE = 1;
    SCIFA9.SCR.BIT.TE = 1;
    //SCIFA9.SCR.BIT.TIE = 1;

}

/***********1byte送信関数*******************/
void put1byte(char c) {
    while ( SCI1.SSR.BIT.TEND == 0)
        ;
    SCI1.TDR = c;
}
/***********nbyte送信関数*******************/
void putnbyte(char *buf, int len) {
    int c;

    for (c = 0; c < len; c++) {
        put1byte(buf[c]);
    }
}
/***********自作printf関数******************/
int myprintf(const char *fmt, ...) {
    static char buffer[1000];
    int len;

    va_list ap;
    va_start(ap, fmt);

    len = vsprintf(buffer, fmt, ap);
    putnbyte(buffer, len);
    va_end(ap);
    return len;
}

/***********1byte送信関数*******************/
void put1byte2(char c) {
    while ( SCI2.SSR.BIT.TEND == 0)
        ;
    SCI2.TDR = c;
}
/***********nbyte送信関数*******************/
void putnbyte2(char *buf, int len) {
    int c;

    for (c = 0; c < len; c++) {
        put1byte2(buf[c]);
    }
}
/***********自作printf関数******************/
int myprintf2(const char *fmt, ...) {
    static char buffer[1000];
    int len;

    va_list ap;
    va_start(ap, fmt);

    len = vsprintf(buffer, fmt, ap);
    putnbyte2(buffer, len);
    va_end(ap);
    return len;
}

/***********nbyte送信関数*******************/
void putnbyte3(uint8_t *buf, uint16_t len) {
    int c;

    for (c = 0; c < len; c++) {
        transBuff.push(buf[c]);
    }

}
/***********受信バッファの中身を取り出す関数******************/
void retrieveDatafromFRDR(){
    uint8_t *periMes = getPointerOfPeriodicMsg();
    periMes[107] = SCIFA9.FDR.BIT.R;
    periMes[109] = SCIFA9.FSR.BIT.RDF;
    if(SCIFA9.FSR.BIT.BRK == 1)SCIFA9.FSR.BIT.BRK = 0;
    if(SCIFA9.LSR.BIT.ORER == 1)SCIFA9.LSR.BIT.ORER = 0;
    if(SCIFA9.FDR.BIT.R == 0) return;
    while (SCIFA9.FDR.BIT.R != 0){
        recieveBuff[recieveBuffCount%512] = (uint8_t)(SCIFA9.FRDR);
        //myprintf3("%d\n",recieveBuff[recieveBuffCount%512]);
        recieveBuffCount ++;
        recieveBuffCount %= 512;
    }

    fetchCommand();
}
/*************送信バッファの中身を送信する関数***************/
//この関数を周期的に呼び出す
int sendDatafromTransBuff() {
    if (SCIFA9.FDR.BIT.T > 0)
        return transBuff.size();
    while (SCIFA9.FDR.BIT.T < 0x10) {
        if (transBuff.empty() == true)
            return 0;
        SCIFA9.FTDR = transBuff.front();
        transBuff.pop();
    }
    return transBuff.size();
}

/***********自作printf関数******************/
int myprintf3(const char *fmt, ...) {
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

int myprintf3_Dbg(const char *fmt, ...) {
#ifdef DEBUG_SWITCH
    static char buffer[1000];
    int len;

    va_list ap;
    va_start(ap, fmt);

    len = vsprintf(buffer, fmt, ap);

    for(int c = 0; c < len; c++) {
        printfBuff.push(buffer[c]);
    }

    va_end(ap);
    return len;
#endif
    return -1;
}

/***********periodicMsgを送る******************/
void sendPeriodicMsg() {
    packData(periodicMsg);
    putnbyte3(periodicMsg, PERIODIC_MSG_LEN);
}

//迷路の壁情報を送る
//
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
    //elapsed time
    unsigned int elapsedTime = getElapsedMsec();
    buf[8] = ((0xff000000 & elapsedTime) >> 24);
    buf[9] = ((0x00ff0000 & elapsedTime) >> 16);
    buf[10] = ((0x0000ff00 & elapsedTime) >> 8);
    buf[11] = ((0x000000ff & elapsedTime));
    //bat vol
    uint16_t vol = S12AD.ADDR0;
    buf[12] = ((0x0000ff00 & vol) >> 8);
    buf[13] = ((0x000000ff & vol));

    buf[14] = ((0x0000ff00 & S12AD.ADDR1) >> 8);
    buf[15] = ((0x000000ff & S12AD.ADDR1));

    buf[16] = ((0x0000ff00 & S12AD.ADDR2) >> 8);
    buf[17] = ((0x000000ff & S12AD.ADDR2));

    buf[18] = ((0x0000ff00 & S12AD.ADDR3) >> 8);
    buf[19] = ((0x000000ff & S12AD.ADDR3));

    buf[20] = ((0x0000ff00 & S12AD.ADDR4) >> 8);
    buf[21] = ((0x000000ff & S12AD.ADDR4));

    buf[22] = ((0x0000ff00 & S12AD.ADDR5) >> 8);
    buf[23] = ((0x000000ff & S12AD.ADDR5));

    buf[24] = ((0x0000ff00 & S12AD.ADDR6) >> 8);
    buf[25] = ((0x000000ff & S12AD.ADDR6));

    buf[26] = ((0x0000ff00 & S12AD.ADDR7) >> 8);
    buf[27] = ((0x000000ff & S12AD.ADDR7));

    buf[28] = ((0x0000ff00 & S12AD1.ADDR8) >> 8);
    buf[29] = ((0x000000ff & S12AD1.ADDR8));

    buf[30] = ((0x0000ff00 & S12AD1.ADDR9) >> 8);
    buf[31] = ((0x000000ff & S12AD1.ADDR9));

    buf[32] = ((0x0000ff00 & S12AD1.ADDR10) >> 8);
    buf[33] = ((0x000000ff & S12AD1.ADDR10));

    buf[34] = ((0x0000ff00 & (imu1.omega_raw[0])) >> 8);
    buf[35] = ((0x000000ff & imu1.omega_raw[0]));

    buf[36] = ((0x0000ff00 & (imu1.omega_raw[1])) >> 8);
    buf[37] = ((0x000000ff & imu1.omega_raw[1]));

    buf[38] = ((0x0000ff00 & (imu1.omega_raw[2])) >> 8);
    buf[39] = ((0x000000ff & imu1.omega_raw[2]));

    buf[40] = ((0x0000ff00 & (imu1.acc_raw[0])) >> 8);
    buf[41] = ((0x000000ff & imu1.acc_raw[0]));

    buf[42] = ((0x0000ff00 & (imu1.acc_raw[1])) >> 8);
    buf[43] = ((0x000000ff & imu1.acc_raw[1]));

    buf[44] = ((0x0000ff00 & (imu1.acc_raw[2])) >> 8);
    buf[45] = ((0x000000ff & imu1.acc_raw[2]));

    buf[46] = ((0x0000ff00 & (imu1.mag_raw[0])) >> 8);
    buf[47] = ((0x000000ff & imu1.mag_raw[0]));

    buf[48] = ((0x0000ff00 & (imu1.mag_raw[1])) >> 8);
    buf[49] = ((0x000000ff & imu1.mag_raw[1]));

    buf[50] = ((0x0000ff00 & (imu1.mag_raw[2])) >> 8);
    buf[51] = ((0x000000ff & imu1.mag_raw[2]));

    buf[52] = ((0x0000ff00 & (imu2.omega_raw[0])) >> 8);
    buf[53] = ((0x000000ff & imu2.omega_raw[0]));

    buf[54] = ((0x0000ff00 & (imu2.omega_raw[1])) >> 8);
    buf[55] = ((0x000000ff & imu2.omega_raw[1]));

    buf[56] = ((0x0000ff00 & (imu2.omega_raw[2])) >> 8);
    buf[57] = ((0x000000ff & imu2.omega_raw[2]));

    buf[58] = ((0x0000ff00 & (imu2.acc_raw[0])) >> 8);
    buf[59] = ((0x000000ff & imu2.acc_raw[0]));

    buf[60] = ((0x0000ff00 & (imu2.acc_raw[1])) >> 8);
    buf[61] = ((0x000000ff & imu2.acc_raw[1]));

    buf[62] = ((0x0000ff00 & (imu2.acc_raw[2])) >> 8);
    buf[63] = ((0x000000ff & imu2.acc_raw[2]));

    buf[64] = ((0x0000ff00 & (getTimeuCountIntCMT0())) >> 8);
    buf[65] = ((0x000000ff & getTimeuCountIntCMT0()));

    buf[66] = ((0x0000ff00 & (getTimeuCountIntCMT1())) >> 8);
    buf[67] = ((0x000000ff & getTimeuCountIntCMT1()));
//
    buf[68] = ((0x0000ff00 & (TPU0.TCNT)) >> 8);
    buf[69] = ((0x000000ff & TPU0.TCNT));
/*
    uint16_t duty_int_r = uint16_t(getDutyMTU3() * 65535.0);
    buf[70] = ((0x0000ff00 & (duty_int_r)) >> 8);
    buf[71] = ((0x000000ff & duty_int_r));
    uint16_t duty_int_l = uint16_t(getDutyMTU4() * 65535.0);
    buf[72] = ((0x0000ff00 & (duty_int_l)) >> 8);
    buf[73] = ((0x000000ff & duty_int_l));
*/
    set2ByteVal(70, m.duty_R, 32767);
    set2ByteVal(72, m.duty_L, 32767);

    buf[74] = ((0x0000ff00 & (MTU1.TCNT)) >> 8);
    buf[75] = ((0x000000ff & MTU1.TCNT));

    buf[76] = ((0x0000ff00 & (MTU2.TCNT)) >> 8);
    buf[77] = ((0x000000ff & MTU2.TCNT));

    buf[78] = ((0x0000ff00 & (tsw.getOntime())) >> 8);
    buf[79] = ((0x000000ff & (tsw.getOntime())));

    buf[94] = ((0x0000ff00 & (wallSen.right.at(0))) >> 8);
    buf[95] = ((0x000000ff & (wallSen.right.at(0))));

    buf[96] = ((0x0000ff00 & (wallSen.ahead.at(0))) >> 8);
    buf[97] = ((0x000000ff & (wallSen.ahead.at(0))));

    buf[98] = ((0x0000ff00 & (wallSen.left.at(0))) >> 8);
    buf[99] = ((0x000000ff & (wallSen.left.at(0))));

    //buf[100] = ((0x0000ff00 & (recieveBuff.size())) >> 8);
    //buf[101] = ((0x000000ff & (recieveBuff.size()))     );

    //buf[102] = ((0x0000ff00 & (recieveBuff.front())) >> 8);
    //buf[103] = ((0x000000ff & (recieveBuff.front()))     );
/*
    buf[104] = ((0x0000ff00 & ((uint8_t)(SCIFA9.FDR.BIT.R))) >> 8);
    buf[105] = ((0x000000ff & ((uint8_t)(SCIFA9.FDR.BIT.R)))     );

    Gamepad &gamepad = Gamepad::getInstance();

    buf[114] = (0x0000ff00 & gamepad.A) >> 8;
    buf[115] = (0x000000ff & gamepad.A)     ;

    buf[116] = (0x0000ff00 & gamepad.B) >> 8;
    buf[117] = (0x000000ff & gamepad.B)     ;

    buf[118] = (0x0000ff00 & gamepad.X) >> 8;
    buf[119] = (0x000000ff & gamepad.X)     ;

    buf[120] = (0x0000ff00 & gamepad.Y) >> 8;
    buf[121] = (0x000000ff & gamepad.Y)     ;

    buf[122] = (0x0000ff00 & gamepad.RB) >> 8;
    buf[123] = (0x000000ff & gamepad.RB)    ;

    buf[124] = (0x0000ff00 & gamepad.LB) >> 8;
    buf[125] = (0x000000ff & gamepad.LB)     ;

    buf[126] = (0x0000ff00 & gamepad.BACK) >> 8;
    buf[127] = (0x000000ff & gamepad.BACK)     ;

    buf[128] = (0x0000ff00 & gamepad.START) >> 8;
    buf[129] = (0x000000ff & gamepad.START)     ;

    buf[130] = (0x0000ff00 & gamepad.RT) >> 8;
    buf[131] = (0x000000ff & gamepad.RT)     ;

    buf[132] = (0x0000ff00 & gamepad.LT) >> 8;
    buf[133] = (0x000000ff & gamepad.LT)     ;

    buf[134] = (0x0000ff00 & gamepad.cross_x) >> 8;
    buf[135] = (0x000000ff & gamepad.cross_x)     ;

    buf[136] = (0x0000ff00 & gamepad.cross_y) >> 8;
    buf[137] = (0x000000ff & gamepad.cross_y)     ;

    buf[138] = (0x0000ff00 & gamepad.R3D_x) >> 8;
    buf[139] = (0x000000ff & gamepad.R3D_x)     ;

    buf[140] = (0x0000ff00 & gamepad.R3D_y) >> 8;
    buf[141] = (0x000000ff & gamepad.R3D_y)     ;

    buf[142] = (0x0000ff00 & gamepad.L3D_x) >> 8;
    buf[143] = (0x000000ff & gamepad.L3D_x)     ;

    buf[144] = (0x0000ff00 & gamepad.L3D_y) >> 8;
    buf[145] = (0x000000ff & gamepad.L3D_y)      ;
*/
    set2ByteVal(100, m.t_ang_a, 20.0);
    set2ByteVal(102, m.t_ang_v, 20.0);
    set2ByteVal(104, m.t_ang, 20.0);
    set2ByteVal(106, m.accum_ang, 20.0);
    set2ByteVal(108, imu1.omega_c[2]);

    set2ByteVal(110, m.t_a, 1000.0);
    set2ByteVal(112, m.t_v, 3000.0);
    set2ByteVal(114, m.t_x, 3000.0);
    set2ByteVal(116, m.accum_x, 3000.0);
    set2ByteVal(118, m.a_v, 1000.0);
    set2ByteVal(120, m.a_h, 1000.0);
    set2ByteVal(122, m.v_enc, 3000.0 );
    set2ByteVal(124, m.wall_P, 3000.0);
    set2ByteVal(126, m.wall_I, 3000.0);
    set2ByteVal(128, m.wall_D, 3000.0);
    set2ByteVal(130, m.v_P, 3000.0);
    set2ByteVal(132, m.v_I, 3000.0);
    set2ByteVal(134, m.v_D, 3000.0);
    set2ByteVal(136, m.ang_P, 3000.0);
    set2ByteVal(138, m.ang_I, 3000.0);
    set2ByteVal(140, m.ang_D, 3000.0);
    set2ByteVal(142, m.ang_v_P, 3000.0);
    set2ByteVal(144, m.ang_v_I, 3000.0);
    set2ByteVal(146, m.ang_v_D, 3000.0);
    set2ByteVal(148, m.v_FF, 3000.0);
    set2ByteVal(150, m.ang_FF, 3000.0);





    //迷路データ
    static uint8_t count = 0;
    packDataMaze(count, &buf[160]);
    count++;
    if (count == 4)
        count = 0;

    //printf Data
    //myprintf("Buff:%d\n",printfBuff.size());
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

void set2ByteVal(uint16_t index, float val,float prop){
    int16_t int_val = (int16_t)(val * prop);
    periodicMsg[index]   = (0x0000ff00 & int_val) >> 8;
    periodicMsg[index+1] = (0x000000ff & int_val)   ;
}

void set2ByteVal(uint16_t index, uint16_t val){
    periodicMsg[index]   = (0x0000ff00 & val) >> 8;
    periodicMsg[index+1] = (0x000000ff & val)   ;
}


uint8_t* getPointerOfPeriodicMsg() {
    return periodicMsg;
}

