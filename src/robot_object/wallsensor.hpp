#ifndef WALLSENSOR_H
#define WALLSENSOR_H

#include "iodefine.h"
#include "stdint.h"
#include <deque>

using std::deque;
namespace peri = peripheral_RX71M;


class WallSensor{

private:
    const uint8_t BUFF_SIZE = 5;
    bool enable;

    WallSensor(){
        enable = true;
        ahead_on = 0;
        left_on  = 0;
        right_on = 0;

        ahead_off = 0;
        left_off = 0;
        right_off = 0;
        for(uint8_t i=0;i<BUFF_SIZE;i++){
            ahead.push_front(0);
            right.push_front(0);
            left.push_front(0);
        }

    };
    WallSensor(WallSensor&){
        enable = true;
        ahead_on = 0;
        left_on = 0;
        right_on = 0;

        ahead_off = 0;
        left_off = 0;
        right_off = 0;
        for(uint8_t i=0;i<BUFF_SIZE;i++){
            ahead.push_front(0);
            right.push_front(0);
            left.push_front(0);
        }

    };
    ~WallSensor(){
        enable = false;
    };
public:

    int16_t ahead_on;
    int16_t left_on;
    int16_t right_on;

    int16_t ahead_off;
    int16_t left_off;
    int16_t right_off;

    deque<int16_t> ahead;
    deque<int16_t> left;
    deque<int16_t> right;

    void turnOffAllLed(){
        PORTD.PODR.BIT.B3 = 0;
        PORTD.PODR.BIT.B4 = 0;
        PORTD.PODR.BIT.B5 = 0;
        PORTE.PODR.BIT.B2 = 0;
    };

    void turnOnAllLed(){
        if(enable == true){
            PORTD.PODR.BIT.B3 = 1; //右
            PORTD.PODR.BIT.B4 = 1; //前
            PORTD.PODR.BIT.B5 = 1;   //左
            PORTE.PODR.BIT.B2 = 1; //前
        }
        else{
            turnOffAllLed();
        }
    }

    void updateAllOffVal(){
        right_off = peri::startAD_AN003(); //右センサ
        left_off  = peri::startAD_AN002(); //左センサ
        ahead_off = peri::startAD_AN004()+peri::startAD_AN001(); //右前センサ
        //ahead_off = peri::startAD_AN001(); //左前センサ
    };

    void updateAllOnVal(){
        right_on = peri::startAD_AN003(); //右センサ
        left_on  = peri::startAD_AN002(); //左センサ
        ahead_on = peri::startAD_AN004()+peri::startAD_AN001(); //前センサ
    }

    void turnOnAheadLed(){
        PORTD.PODR.BIT.B4 = 1; //前
        PORTE.PODR.BIT.B2 = 1; //前
    };
    void turnOnLeftLed(){
        PORTD.PODR.BIT.B5 = 1; //左
    };
    void turnOnRightLed(){
        PORTD.PODR.BIT.B3 = 1; //右
    };

    void updateAheadOnVal(){
        ahead_on = peri::startAD_AN004()+peri::startAD_AN001(); //前センサ
    };
    void updateLeftOnVal(){
        left_on  = peri::startAD_AN002(); //左センサ
    };
    void updateRightOnVal(){
        right_on = peri::startAD_AN003(); //右センサ
    };

    void modulateVal(){
        int16_t ah_mod = ahead_on - ahead_off;
        int16_t l_mod  = left_on - left_off;
        int16_t r_mod  = right_on - right_off;

        ahead.push_front(ah_mod);
        left.push_front(l_mod);
        right.push_front(r_mod);

        ahead.pop_back();
        left.pop_back();
        right.pop_back();
    };

    static WallSensor& getInstance(){
        static WallSensor instance;
        return instance;
    }

    void setEnable(bool en){
        enable = en;
        if(enable == false)turnOffAllLed();
    };

};




#endif
