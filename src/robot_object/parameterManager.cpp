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
#include <typeinfo>

namespace peri = peripheral_RX71M;


namespace robot_object{

    template<typename T>
    bool ParameterManager::registration(uint16_t val_num, T& r_val){
        uint16_t index = val_num *64;
        if(peri::eraseCheckDataFlash(index, 64) == false){
            peri::eraseDataFlash(index);
        };
        uint8_t len = sizeof(T);
        uint8_t hoge = 0;
        uint8_t* adr = reinterpret_cast<uint8_t*>(r_val);
        parameterList[val_num] = {adr, typeid(T)};
        return peri::writeDataFlash(index, &hoge , len);
//        return false;
    }
/*
    bool ParameterManager::registration(uint16_t val_num, void* p_val, type_e val_type){

        parameterList[val_num] = {reinterpret_cast<uint8_t*>(p_val) ,val_type};

        uint16_t index = val_num * 64;
        if(peri::eraseCheckDataFlash(index, 64) == false){
            peri::eraseDataFlash(index);
        };

        uint8_t len;
        if(val_type == INT8 || UINT8)len=1;
        else if(val_type == INT16 || UINT16)len=2;
        else if(val_type == INT32 || UINT32)len=4;
        else if(val_type == FLOAT)len =4;
        else return false;

        return peri::writeDataFlash(index, p_val, len);
    }
*/

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




