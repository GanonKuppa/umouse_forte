#ifndef MOUSE_H
#define MOUSE_H


#include <stdint.h>
#include <math.h>
#include <myUtil.hpp>

#include "iodefine.h"
#include "pwm.h"
#include "phaseCounting.h"

#include "maze.h"
#include "machineParameters.h"
#include "math.h"
#include "imu.hpp"


namespace peri = peripheral_RX71M;
//#include <Core>
//#include <Geometry>
//using namespace Eigen;
//#define EIGEN_DONT_VECTORIZE
//#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT



enum direction_e {
    E = 0, NE, N, NW, W, SW, S, SE
};

template <typename T>
class Coor2D {
    T x;
    T y;
};

class Vector2f {
public:
    float x;
    float y;

    Vector2f(float x_0, float y_0){
        x = x_0;
        y = y_0;
    }

    float operator [](int n){
        if(n == 0) return x;
        if(n == 1) return y;
        return 0.0;
    }

};


class UMouse {
public:
    // -32768 から 32767


    volatile float t_a;       //event側で更新     x 1000
    volatile float t_v;       //event側で更新     x 3000
    volatile float t_x;       //event側で更新     x 3000
    volatile float accum_x;   //event側で更新     x 3000

    volatile float t_ang_a;   //event側で更新    x 100
    volatile float t_ang_v;   //event側で更新    x 100
    volatile float t_ang;   //event側で更新    x 100
    volatile float accum_ang; //event側で更新    x 100
    volatile float gyro_ang_v;// -2000deg/secから+2000deg/sec

    volatile float wall_P;    //event側で更新  -10.0から10.0   x 3000
    volatile float wall_I;    //event側で更新  -10.0から10.0   x 3000
    volatile float wall_D;    //event側で更新  -10.0から10.0   x 3000

    volatile float v_P;       //event側で更新  -10.0から10.0   x 3000
    volatile float v_I;       //event側で更新  -10.0から10.0   x 3000
    volatile float v_D;       //event側で更新  -10.0から10.0   x 3000

    volatile float ang_v_P;   //event側で更新  -10.0から10.0   x 3000
    volatile float ang_v_I;   //event側で更新  -10.0から10.0   x 3000
    volatile float ang_v_D;   //event側で更新  -10.0から10.0   x 3000

    volatile float ang_P;     //event側で更新  -10.0から10.0   x 3000
    volatile float ang_I;     //event側で更新  -10.0から10.0   x 3000
    volatile float ang_D;     //event側で更新  -10.0から10.0   x 3000

    volatile float v_FF;      //event側で更新  -1.0から1.0     x 3000
    volatile float ang_FF;    //event側で更新  -1.0から1.0     x 3000

    volatile float v;
    volatile float a_v; //前方向加速度 x1000
    volatile float a_h; //横方向加速度 x1000

    volatile float duty_L;
    volatile float duty_R;

    volatile direction_e direction;
    volatile Coor2D<float> ab_position;
    volatile Coor2D<uint16_t> coor;
    volatile Coor2D<uint16_t> start;
    volatile Coor2D<uint16_t> goal;

    volatile float ang;
    volatile float ang_v;
    volatile float ang_a;

    volatile Coor2D <float> v_g;
    volatile Coor2D <float> x_g;
    volatile Coor2D <float> a_g;

    volatile Maze maze;
    volatile Maze mazeBuf[5];

    volatile float v_enc_R;
    volatile float v_enc_L;

    volatile float v_enc;
    volatile float v_acc;

    volatile float ang_gyro;
    volatile float ang_mag;

    volatile float Vcc;

    static UMouse& getInstance() {
        static UMouse instance;
        return instance;
    };

    void update(){
        static uint16_t R_ENC_pre;
        static uint16_t L_ENC_pre;
        static uint16_t R_ENC_now;
        static uint16_t L_ENC_now;

        //**************エンコーダ値の読み取り************************//

        R_ENC_pre = R_ENC_now;
        L_ENC_pre = L_ENC_now;
        R_ENC_now = peri::getCountMTU1();
        L_ENC_now = peri::getCountMTU1();

        int32_t count_diff_R = (int32_t)(R_ENC_now - R_ENC_pre);
        int32_t count_diff_L = (int32_t)(L_ENC_now - L_ENC_pre);
        //オーバーフロー対策
        if( count_diff_R > 32768 )  count_diff_R -= 65536;
        if( count_diff_R < -32768 ) count_diff_R += 65536;
        if( count_diff_L > 32768 )  count_diff_L -= 65536;
        if( count_diff_L < -32768 ) count_diff_L += 65536;

        //エンコーダより計測された速度
        v_enc_R = (PI* DIA_TIRE / GEAR_RATIO * (float)(count_diff_R)/512.0)/ DELTA_T;
        v_enc_L = (PI* DIA_TIRE / GEAR_RATIO * (float)(count_diff_L)/512.0)/ DELTA_T;
        //v_enc = (v_enc_R + v_enc_L) * 0.5;
        MPU9250 &imu = MPU9250::getInstance();
        float omega = DEG2RAD(imu.omega_f[2]);
        v_enc = sqrtf( constrainL(
                                   0.5 * (  v_enc_R * v_enc_R
                                   + v_enc_L * v_enc_L
                                   - 0.5 * omega * omega * TREAD * TREAD)
                                   ,0.0)
        );
        //角速度をセット
        gyro_ang_v = MPU9250::getInstance().omega_f[2];
        //電圧の算出
        Vcc = 15.1 / 5.1 * (S12AD.ADDR0) * 3.3 / 4096;
        //加速度センサから遠心力を除去
        float r = 0.0564717;  // 9mm 55.75mm
        float theta = DEG2RAD(9.17042483);
        float c_force = r * DEG2RAD(gyro_ang_v) * DEG2RAD(gyro_ang_v);
        a_v = MPU9250::getInstance().acc_f[1] + c_force * cosf(theta);
        a_h = MPU9250::getInstance().acc_f[0] + c_force * sinf(theta);

    }

    void setDuty(float duty_l, float duty_r){
        setDuty_L(duty_l);
        setDuty_R(duty_r);
    }

    void setDuty_R(float duty){
        duty_R = duty;

        if(duty == 0.0){
            PORT1.PODR.BIT.B3 = 0;
            PORT1.PODR.BIT.B2 = 0;
        }
        else if(duty > 0){
            PORT1.PODR.BIT.B3 = 0;
            PORT1.PODR.BIT.B2 = 1;
        }
        else{
            PORT1.PODR.BIT.B3 = 1;
            PORT1.PODR.BIT.B2 = 0;
        }
        peri::setDutyMTU3(ABS(duty));
    };
    void setDuty_L(float duty){
        duty_L = duty;

        if(duty == 0.0){
            PORT2.PODR.BIT.B0 = 0;
            PORT1.PODR.BIT.B7 = 0;
        }
        else if(duty > 0){
            PORT2.PODR.BIT.B0 = 1;
            PORT1.PODR.BIT.B7 = 0;
        }
        else{
            PORT2.PODR.BIT.B0 = 0;
            PORT1.PODR.BIT.B7 = 1;
        }
        peri::setDutyMTU4(ABS(duty));
    };


private:
    UMouse() {};
    ~UMouse() {};
    UMouse(UMouse&) {};





};

#endif
