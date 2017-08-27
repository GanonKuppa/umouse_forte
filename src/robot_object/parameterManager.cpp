/*
 * parameterManager.cpp
 *
 *  Created on: 2017/08/27
 *      Author: ryota
 */

#include<stdint.h>
#include "parameterManager.h"
#include "dataFlash.h"
#include <map>

namespace peri = peripheral_RX71M;


namespace robot_object{

    //bool ParameterManager::registration(uint16_t val_num )


    bool ParameterManager::write(uint16_t val_num, float val){
        uint16_t index = val_num * 64;
        if(peri::eraseCheckDataFlash(index, 64) == false){
            peri::eraseDataFlash(index);
        };
        return peri::writeDataFlash(index, &val, 4);

    };


    float ParameterManager::read(uint16_t val_num){
        float val;
        uint16_t index = val_num * 64;
        peri::readDataFlash(index, &val, 4);

        return val;
    };


}




