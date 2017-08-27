/*
 * parameterManager.h
 *
 *  Created on: 2017/08/27
 *      Author: ryota
 */

#pragma once

#include<stdint.h>

namespace robot_object{

    class ParameterManager{
    public:
       static ParameterManager& getInstance(){
           static ParameterManager instance;
           return instance;
       }
       bool write(uint16_t val_num, float val);
       float read(uint16_t val_num);
    private:
        ParameterManager(){};
        ~ParameterManager(){};
        ParameterManager(ParameterManager&){};

    };

}
