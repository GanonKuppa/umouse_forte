/**
 * @file   clock.h
 * @brief  クロックの設定
 *
 * @date 2016/7/23
 * @author ryota
 */


#ifndef CLOCK_H
#define CLOCK_H

const unsigned int ICLK  = 96000000;
const unsigned int BCLK  = 96000000;
const unsigned int PCLKA = 96000000;
const unsigned int PCLKB = 48000000;
const unsigned int PCLKC = 48000000;
const unsigned int PCLKD = 48000000;

void initClock(void);




#endif



