/*
 * parameterManager.cpp
 *
 *  Created on: 2017/08/27
 *      Author: ryota
 */

#include <stdint.h>
#include <string>
#include <map>

#include "parameterManager.h"
#include "dataFlash.h"
#include "communication.h"
#include "timer.h"

namespace peri = peripheral_RX71M;


namespace robot_object{


    void ParameterManager::init(){
        registration<float>(0, pivot_ang_v_P);
        registration<float>(1, pivot_ang_v_I);
        registration<float>(2, pivot_ang_v_D);
        registration<float>(3, pivot_ang_v_LI);
        registration<float>(4, pivot_ang_P);
        registration<float>(5, pivot_ang_I);
        registration<float>(6, pivot_ang_D);
        registration<float>(7, pivot_ang_LI);
        registration<float>(8, pivot_v_P);
        registration<float>(9, pivot_v_I);
        registration<float>(10, pivot_v_D);
        registration<float>(11, pivot_v_LI);
        registration<float>(12, straight_ang_v_P);
        registration<float>(13, straight_ang_v_I);
        registration<float>(14, straight_ang_v_D);
        registration<float>(15, straight_ang_v_LI);
        registration<float>(16, straight_v_P);
        registration<float>(17, straight_v_I);
        registration<float>(18, straight_v_D);
        registration<float>(19, straight_v_LI);


    }

    void ParameterManager::setStrkey(uint16_t val_num, std::string key){
        strkeyMap[key] = val_num;
    }

    //プログラム中の変数にデータフラッシュの保存域を割り当て
    //登録時に変数にデータフラッシュに保存されている値を代入
    //登録を行った変数はデータフラッシュの保存域を更新する(write関数)際に値を共に変更
    template<typename T>
    void ParameterManager::registration(uint16_t val_num, T& r_val){
        uint16_t index = val_num *64;
        //uint8_t len = sizeof(T);
        T* adr = &r_val;
        adrMap[val_num] = reinterpret_cast<uint32_t>(adr);
        r_val = read<T>(val_num);
    }

    template<typename T>
    bool ParameterManager::write(uint16_t val_num, T val){
        uint16_t index = val_num * 64;
        bool rtn;
        while(1){
            if(peri::eraseCheckDataFlash(index, 64) == false){
                peri::eraseDataFlash(index);
            };
            rtn = peri::writeDataFlash(index, &val, sizeof(T));
            printfAsync("write error!\n");
            if(read<T>(val_num) == val) break;
        }

        //val_numに変数が登録されている場合はその変数を書き換え
        if (adrMap.find(val_num) != adrMap.end() ) {
            *reinterpret_cast<T*>(adrMap[val_num]) = val;
            printfAsync("write: %f %f \n",val, *reinterpret_cast<T*>(adrMap[val_num]));
        }
        return rtn;
    }

    template<typename T>
    T ParameterManager::read(uint16_t val_num){
        T val;
        uint16_t index = val_num * 64;
        peri::readDataFlash(index, &val, sizeof(T));

        return val;
    };

    template<typename T>
    bool ParameterManager::write(std::string key, T val){
        return write(strkeyMap[key], val);
    }

    template<typename T>
    T ParameterManager::read(std::string key){
        return read<T>(strkeyMap[key]);
    };

    bool ParameterManager::writeCommand(uint8_t *command){
        uint8_t chk_sum = 0;
        for(uint8_t i=5;i<16;i++) chk_sum+= command[i];
        if(chk_sum == command[4]){
            switch(command[5]){
                case 0:
                    write<float>(command[10], *((float*)&command[6]));
                    printfAsync("%d %f %f \n",command[10], *((float*)&command[6]) ,read<float>(command[10]));
                    break;
                case 1:
                    write<uint8_t>(command[10], command[6]);
                    printfAsync("%d \n",*((uint8_t*)&command[6]));
                    break;
                case 2:
                    write<uint16_t>(command[10], *((uint16_t*)&command[6]));
                    printfAsync("%d \n",*((uint16_t*)&command[6]));
                    break;
                case 3:
                    write<uint32_t>(command[10], *((uint32_t*)&command[6]));
                    printfAsync("%d \n",*((uint32_t*)&command[6]));
                    break;
                case 4:
                    write<int8_t>(command[10], *((int8_t*)&command[6]));
                    printfAsync("%d \n",*((int8_t*)&command[6]));
                    break;
                case 5:
                    write<int16_t>(command[10], *((int16_t*)&command[6]));
                    printfAsync("%d \n",*((int16_t*)&command[6]));
                    break;
                case 6:
                    write<int32_t>(command[10], *((int32_t*)&command[6]));
                    printfAsync("%d \n",*((int32_t*)&command[6]));
                    break;

            }
        }

    }


    //テンプレートクラスの実体化
    template void ParameterManager::registration(uint16_t val_num, float& r_val);
    template void ParameterManager::registration(uint16_t val_num, uint8_t& r_val);
    template void ParameterManager::registration(uint16_t val_num, uint16_t& r_val);
    template void ParameterManager::registration(uint16_t val_num, uint32_t& r_val);
    template void ParameterManager::registration(uint16_t val_num, int8_t& r_val);
    template void ParameterManager::registration(uint16_t val_num, int16_t& r_val);
    template void ParameterManager::registration(uint16_t val_num, int32_t& r_val);

    template bool ParameterManager::write(uint16_t val_num, float val);
    template bool ParameterManager::write(uint16_t val_num, uint8_t val);
    template bool ParameterManager::write(uint16_t val_num, uint16_t val);
    template bool ParameterManager::write(uint16_t val_num, uint32_t val);
    template bool ParameterManager::write(uint16_t val_num, int8_t val);
    template bool ParameterManager::write(uint16_t val_num, int16_t val);
    template bool ParameterManager::write(uint16_t val_num, int32_t val);

    template float ParameterManager::read<float>(uint16_t val_num);
    template uint8_t ParameterManager::read<uint8_t>(uint16_t val_num);
    template uint16_t ParameterManager::read<uint16_t>(uint16_t val_num);
    template uint32_t ParameterManager::read<uint32_t>(uint16_t val_num);
    template int8_t ParameterManager::read<int8_t>(uint16_t val_num);
    template int16_t ParameterManager::read<int16_t>(uint16_t val_num);
    template int32_t ParameterManager::read<int32_t>(uint16_t val_num);

    template bool ParameterManager::write(std::string key, float val);
    template bool ParameterManager::write(std::string key, uint8_t val);
    template bool ParameterManager::write(std::string key, uint16_t val);
    template bool ParameterManager::write(std::string key, uint32_t val);
    template bool ParameterManager::write(std::string key, int8_t val);
    template bool ParameterManager::write(std::string key, int16_t val);
    template bool ParameterManager::write(std::string key, int32_t val);

    template float ParameterManager::read<float>(std::string key);
    template uint8_t ParameterManager::read<uint8_t>(std::string key);
    template uint16_t ParameterManager::read<uint16_t>(std::string key);
    template uint32_t ParameterManager::read<uint32_t>(std::string key);
    template int8_t ParameterManager::read<int8_t>(std::string key);
    template int16_t ParameterManager::read<int16_t>(std::string key);
    template int32_t ParameterManager::read<int32_t>(std::string key);



}




