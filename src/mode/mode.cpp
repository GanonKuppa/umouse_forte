#include <stdint.h>
#include <uart.h>
#include "mode.h"
#include "mode_N.h"
#include "mode_R.h"
#include "mode_G.h"
#include "mode_B.h"
#include "mode_RG.h"
#include "mode_RB.h"
#include "mode_GB.h"
#include "mode_RGB.h"

#include "tactsw.h"
#include "timer.h"
#include "fcled.h"
#include "sound.h"
#include "gamepad.h"
#include <string>

using std::string;

#include "communication.h"

using namespace robot_object;


void modeSelect() {
    uint8_t mode_change = 0;
    uint8_t mode_num = 8;

    TactSw& tsw = TactSw::getInstance();
    FcLed& fcled = FcLed::getInstance();
    Gamepad& gamepad = Gamepad::getInstance();

    void (*mode_func[])() = {
        mode_N, mode_B, mode_G, mode_GB,
        mode_R, mode_RB, mode_RG, mode_RGB
    };
    fcled.turn(0, 0, 0);
    printfAsync("############ MD select ################\n");
    printfAsync("Choose the MD .\n");
    printfAsync(" 宴会芸                                        :0 N   \n"); //000 0
    printfAsync(" 自律走行                                    :1 B   \n"); //001 1
    printfAsync(" DEBUG MODE           :2 G   \n"); //010 2
    printfAsync(" 斜め最短走行                             :3 GB  \n"); //011 3
    printfAsync(" 音楽室                                        :4 R   \n"); //100 4
    printfAsync(" 最短走行                                    :5 RB  \n"); //101 5
    printfAsync(" 探索走行                                    :6 RG  \n"); //110 6
    printfAsync(" Circit running       :7 RGB \n"); //111 7
    printfAsync("++++++++++++++++++++++++++++++++\n");

    while (1) {
        waitmsec(1);

        if (tsw.getOntime() > 10 ) {
            while (tsw.getOntime() > 10) {
                waitmsec(1);
                if (tsw.getOntime() > 1000 && tsw.getOntime() < 2000) {
                    //決定時の動作
                    SEB();
                    mode_func[mode_change]();
                    waitmsec(1000);
                    return;
                }
            }

            mode_change = (mode_change + 1) % mode_num;
            printfAsync("botton pressed! %d\n", mode_change);

            SEA();
            uint8_t r = (mode_change & 0x04) >> 2;
            uint8_t g = (mode_change & 0x02) >> 1;
            uint8_t b = mode_change & 0x01;
            fcled.turn(r, g, b);
        }

        if(gamepad.cross_y == 1){
            //uint32_t time_pre = getElapsedMsec();
            while(gamepad.cross_y==1){
                waitmsec(100);
                //if(getElapsedMsec() - time_pre > 250)break;
            }
            mode_change = (mode_change - 1 + mode_num) % mode_num;
            printfAsync("botton pressed! %d\n", mode_change);
            SEA();
            uint8_t r = (mode_change & 0x04) >> 2;
            uint8_t g = (mode_change & 0x02) >> 1;
            uint8_t b = mode_change & 0x01;
            fcled.turn(r, g, b);
        }

        if(gamepad.cross_y == -1){
            //uint32_t time_pre = getElapsedMsec();
            while(gamepad.cross_y==-1){
                waitmsec(100);
                //if(getElapsedMsec() - time_pre > 250)break;
            }
            mode_change = (mode_change + 1) % mode_num;
            printfAsync("botton pressed! %d\n", mode_change);
            SEA();
            uint8_t r = (mode_change & 0x04) >> 2;
            uint8_t g = (mode_change & 0x02) >> 1;
            uint8_t b = mode_change & 0x01;
            fcled.turn(r, g, b);
        }

        if (gamepad.B > 1000 ) {
            SEB();
            printfAsync("select! \n");
            mode_func[mode_change]();
            waitmsec(1000);
            return;
        }





    }
}

