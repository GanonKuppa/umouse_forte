/*
 * parameterManager.h
 *
 *  Created on: 2017/08/27
 *      Author: ryota
 */

#pragma once

#include<stdint.h>
#include<string>
#include<map>


namespace robot_object{



    class ParameterManager{
    public:
        std::map<uint16_t, uint32_t> adrMap;
        std::map<std::string,uint16_t> strkeyMap;

        static ParameterManager& getInstance(){
            static ParameterManager instance;
            return instance;
        }

        void init();

        template<typename T>
        bool write(uint16_t val_num, T val);

        template<typename T>
        T read(uint16_t val_num);

        template<typename T>
        bool write(std::string key, T val);

        template<typename T>
        T read(std::string key);


        template<typename T>
        void registration(uint16_t val_num, T& r_val);
        void setStrkey(uint16_t val_num, std::string key);

        bool writeCommand(uint8_t *commnd);

        //管理下においた変数たち
        float pivot_ang_v_P;  //0
        float pivot_ang_v_I;  //1
        float pivot_ang_v_D;  //2
        float pivot_ang_v_LI; //3

        float pivot_ang_P;    //4
        float pivot_ang_I;    //5
        float pivot_ang_D;    //6
        float pivot_ang_LI;   //7

        float pivot_v_P;      //8
        float pivot_v_I;      //9
        float pivot_v_D;      //10
        float pivot_v_LI;     //11

        float straight_ang_v_P;  //12
        float straight_ang_v_I;  //13
        float straight_ang_v_D;  //14
        float straight_ang_v_LI; //15

        float straight_v_P;      //16
        float straight_v_I;      //17
        float straight_v_D;      //18
        float straight_v_LI;     //19




    private:

        ParameterManager(){};
        ~ParameterManager(){};
        ParameterManager(ParameterManager&){};
    };

}



