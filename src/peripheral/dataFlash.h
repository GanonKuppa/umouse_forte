/*
 * dataFlash.h
 *
 *  Created on: 2017/08/19
 *      Author: ryota
 */

#pragma once

#include <stdint.h>


namespace peripheral_RX71M{

    bool initDataFlash();
    uint8_t readDataFlash(uint32_t org);
    bool readDataFlash(uint32_t org, void* dst, uint32_t len);
    bool eraseCheckDataFlash(uint32_t org, uint32_t len);
    bool eraseDataFlash(uint32_t org);
    bool eraseAllDataFlash();
    bool writeDataFlash(uint32_t org, const void* src, uint32_t len);
    bool writeDataFlash(uint32_t org, uint8_t data);

}





