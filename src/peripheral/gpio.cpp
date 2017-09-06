/**
 * @file   clock.cpp
 * @brief  GPIOピンの設定
 *
 * @date 2016/7/23
 * @author ryota
 */

#include "iodefine.h"
#include "gpio.h"
#include <stdint.h>

namespace peripheral_RX71M{
    void initGPIO(){
        //未使用ピンの処理
        PORT0.PDR.BYTE = (uint8_t)(PORT0.PDR.BYTE | 0x0F);
        PORT1.PDR.BYTE = (uint8_t)(PORT1.PDR.BYTE | 0x03);
        PORT5.PDR.BYTE = (uint8_t)(PORT5.PDR.BYTE | 0x40);
        PORT6.PDR.BYTE = (uint8_t)(PORT6.PDR.BYTE | 0xFF);
        PORT7.PDR.BYTE = (uint8_t)(PORT7.PDR.BYTE | 0xFF);
        PORT8.PDR.BYTE = (uint8_t)(PORT8.PDR.BYTE | 0xCF);
        PORT9.PDR.BYTE = (uint8_t)(PORT9.PDR.BYTE | 0xFF);
        PORTF.PDR.BYTE = (uint8_t)(PORTF.PDR.BYTE | 0x3F);
        PORTG.PDR.BYTE = (uint8_t)(PORTG.PDR.BYTE | 0xFF);
        PORTJ.PDR.BYTE = (uint8_t)(PORTJ.PDR.BYTE | 0x20);


        //FCLED
        PORTA.PDR.BIT.B2 = 1; //R PA2
        PORTA.PDR.BIT.B3 = 1; //G PA3
        PORT1.PDR.BIT.B5 = 1; //B P15

        //PORTC.PDR.BIT.B6 = 1;
        //PORTC.PDR.BIT.B5 = 1;
        //PORTC.PDR.BIT.B4 = 1;
        //PORTC.PDR.BIT.B2 = 1;
        //PORTC.PODR.BIT.B2 = 1;
        //SWITCH
        PORTE.PDR.BIT.B3 = 0; //PE3
        PORTE.PCR.BIT.B3 = 1; //プルアップ有効

        //motor driver左

        //	PORT1.PDR.BIT.B4 = 1; MTU3
        PORT1.PDR.BIT.B3 = 1;
        PORT1.PDR.BIT.B2 = 1;

        //	PORT1.PODR.BIT.B4 = 1;
        PORT1.PODR.BIT.B3 = 0;
        PORT1.PODR.BIT.B2 = 0;

        //motor driver 右

        //	PORT2.PDR.BIT.B1 = 1; MTU4
        PORT2.PDR.BIT.B0 = 1;
        PORT1.PDR.BIT.B7 = 1;

        PORT2.PODR.BIT.B0 = 0;
        PORT1.PODR.BIT.B7 = 0;

        //センサLED
        PORTD.PDR.BIT.B3 = 1;
        PORTD.PDR.BIT.B4 = 1;
        PORTD.PDR.BIT.B5 = 1;
        PORTE.PDR.BIT.B2 = 1;

        PORTD.PODR.BIT.B3 = 0;
        PORTD.PODR.BIT.B4 = 0;
        PORTD.PODR.BIT.B5 = 0;
        PORTE.PODR.BIT.B2 = 0;

        //PICの入力ピン
        PORTD.PDR.BIT.B7  = 1;
        PORTD.PODR.BIT.B7 = 1;

        //上基板LED
        PORTD.PDR.BIT.B2 = 1;
        PORT4.PDR.BIT.B5 = 1;
        PORTD.PODR.BIT.B2 = 1;
        PORT4.PODR.BIT.B5 = 1;


    }
}
