/**
 * @file   ad.h
 * @brief  adの設定
 *
 * @date 2016/9/24
 * @author ryota
 */


#pragma once

#include <stdint.h>

namespace peripheral_RX71M{

    void initAD(void);

    uint16_t startAD_AN000(void);
    uint16_t startAD_AN001(void);
    uint16_t startAD_AN002(void);
    uint16_t startAD_AN003(void);
    uint16_t startAD_AN004(void);
    uint16_t startAD_AN005(void);
    uint16_t startAD_AN006(void);
    uint16_t startAD_AN007(void);
    uint16_t startAD_AN108(void);
    uint16_t startAD_AN109(void);
    uint16_t startAD_AN110(void);
    void startAD_All(void);

    uint16_t getAD_AN000(void);
    uint16_t getAD_AN001(void);
    uint16_t getAD_AN002(void);
    uint16_t getAD_AN003(void);
    uint16_t getAD_AN004(void);
    uint16_t getAD_AN005(void);
    uint16_t getAD_AN006(void);
    uint16_t getAD_AN007(void);
    uint16_t getAD_AN108(void);
    uint16_t getAD_AN109(void);
    uint16_t getAD_AN110(void);
    void getAD_All(uint16_t *array);

}



