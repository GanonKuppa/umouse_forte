/*
 * parameterManager.h
 *
 *  Created on: 2017/08/27
 *      Author: ryota
 */

#pragma once

#include<stdint.h>
#include<map>
#include<string>
#include<utility>

namespace robot_object{

    enum type_e{
       INT8,
       UINT8,
       INT16,
       UINT16,
       INT32,
       UINT32,
       FLOAT
    };



    class ParameterManager{
    public:
        static ParameterManager& getInstance(){
            static ParameterManager instance;
            return instance;
        }
        bool write(uint16_t val_num, float val);
        float read(uint16_t val_num);

        bool wiriteUint(uint16_t val_num, uint32_t val);
        bool wiriteFloat(uint16_t val_num, float val);
        bool wiriteInt(uint16_t val_num, int32_t val);

        uint32_t readUint(uint16_t val_num);
        float readFloat(uint16_t val_num);
        int32_t readInt(uint16_t val_num);

//      bool registration(uint16_t val_num, void* p_val, type_e val_type);
        template<typename T>
        bool registration(uint16_t val_num, T& r_val);

    private:

        ParameterManager(){};
        ~ParameterManager(){};
        ParameterManager(ParameterManager&){};
        std::map<uint16_t,std::pair<uint8_t*,type_e>> parameterList;
    };

}
