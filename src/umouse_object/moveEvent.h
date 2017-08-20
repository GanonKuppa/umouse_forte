#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include <myUtil.hpp>
#include <uart.h>
#include "machineParameters.h"
#include "imu.hpp"
#include "mouse.h"
//#include <Core>
//#include <Geometry>
#include <queue>
#include "timer.h"
#include "communication.h"

using namespace robot_object;



using std::queue;
namespace peri = peripheral_RX71M;
using peri::getElapsedMsec;
using peri:: waitmsec;

//using namespace Eigen;
//#define EIGEN_DONT_VECTORIZE
//#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT

class BaseMoveEvent{
public:
    virtual bool isEnd()=0;
    virtual Vector2f calcDuty()=0;

    Vector2f dutyFF_ang(float target_ang_a, float target_ang_v){
        UMouse &mouse = UMouse::getInstance();
        Vector2f duty(0.0f, 0.0f);

        //必要な力(回転成分)
        float F_rotation = INERTIA * DEG2RAD(target_ang_a) / TREAD;
        //モータとモータドライバの抵抗値
        float R = COIL_RES + FET_RES;
        //必要なトルク
        float torque_L = (- F_rotation)*(0.5* DIA_TIRE/GEAR_RATIO);
        float torque_R = (+ F_rotation)*(0.5* DIA_TIRE/GEAR_RATIO);
        //左右輪の速度
        float v_L = - TREAD * PI * target_ang_v/360.0;
        float v_R = + TREAD * PI * target_ang_v/360.0;
        //左右モーターの回転数
        float rpm_L = v_L * 60.0 /(PI * DIA_TIRE);
        float rpm_R = v_R * 60.0 /(PI * DIA_TIRE);

        duty.x = (R*torque_L / K_T + K_E * rpm_L) / mouse.Vcc;
        duty.y = (R*torque_R / K_T + K_E * rpm_R) / mouse.Vcc;

        return duty;
    };

    Vector2f dutyFF_v(float target_a, float target_v){
        UMouse &mouse = UMouse::getInstance();
        Vector2f duty(0.0f, 0.0f);

        //必要な力(直進成分)
        float F_forward = MASS*target_a/2.0;
        //モータとモータドライバの抵抗値
        float R = COIL_RES + FET_RES;
        //必要なトルク
        float torque_L = F_forward * (0.5* DIA_TIRE/GEAR_RATIO);
        float torque_R = F_forward * (0.5* DIA_TIRE/GEAR_RATIO);
        //左右輪の速度
        float v_L = target_v;
        float v_R = target_v;
        //左右モーターの回転数
        float rpm_L = v_L * 60.0 /(PI * DIA_TIRE);
        float rpm_R = v_R * 60.0 /(PI * DIA_TIRE);

        duty.x = (R*torque_L / K_T + K_E * rpm_L) / mouse.Vcc;
        duty.y = (R*torque_R / K_T + K_E * rpm_R) / mouse.Vcc;

        return duty;
    };

};






#ifdef MEMO
class NormalMoveEvent : public BaseMoveEvent{

public:
    float target_ang;           //追従目標角度
    float target_ang_v;         //追従目標角速度
    float target_ang_a;         //追従目標角加速度

    float target_x;             //追従目標位置
    float target_v;             //追従目標速度
    float target_a;             //追従目標加速度

    float accum_x;
    float accum_ang; //角度積算値

    float error_v;
    float error_int_v;

    float error_ang_v;
    float error_int_ang_v;

    float error_ang;
    float error_int_ang;

    float Kp_v;
    float Ki_v;
    float Kd_v;

    float Kp_ang_v;
    float Ki_ang_v;
    float Kd_ang_v;

    float Kp_ang;
    float Ki_ang;
    float Kd_ang;

    void paramInit(){
        target_ang   = 0.0;           //追従目標角度
        target_ang_v =0.0;         //追従目標角速度
        target_ang_a =0.0 ;         //追従目標角加速度
        accum_ang = 0.0 ;

        error_int_ang = 0.0;
        error_int_v = 0.0;

        Kp_v = 0.0;
        Ki_v = 0.0;
        // Kd_v;

        Kp_ang_v = 0.0;
        Ki_ang_v = 0.0;
        // Kd_and_v;

        Kp_ang = 0.0;
        Ki_ang = 0.0;
        Kd_ang = 0.0;

    };

    virtual bool isEnd()=0;
    virtual void trajectoryPlanning()=0;

    void updateDuty(){
        UMouse &mouse = UMouse::getInstance();
        trajectoryPlanning();
        integrate();
        updatePidError();
        Vector2f duty(0.0f, 0.0f);

        duty = dutyFF() + dutyFB() + dutyWall();
        float duty_L = duty(0);
        float duty_R = duty(1);
        //mouse.setDuty_L(duty_L);
        //mouse.setDuty_R(duty_R);

    };

    void integrate(){
        UMouse& mouse = UMouse::getInstance();
        //追従目標の積分処理
        target_ang   += target_ang_v * DELTA_T;
        target_ang_v += target_ang_a * DELTA_T;

        target_x += target_v * DELTA_T;
        target_v += target_a * DELTA_T;
        accum_ang += mouse.v_enc * DELTA_T;
    };

    void updatePidError(){
        //*******フィードバック制御のゲイン***********//
        Kp_v = 0.9;//.5;
        //float Kd_v = 0.3;//;
        Ki_v = 0.3;//0.1;

        Kp_ang_v = 0.0093;
        Ki_ang_v = 0.00042;

        Kp_ang = 0.0005;//0.005;
        Ki_ang = 0.00005;//0.003;
        Kd_ang = 0.0;//0.001;
        //*********************************//
        UMouse& mouse = UMouse::getInstance();
        //速度と角度と角速度の偏差
        error_v     = target_v     - mouse.v_enc;
        error_ang   = target_ang   - accum_ang;
        error_ang_v = target_ang_v - mouse.ang_v;
        //速度と角度と角速度のI項
        error_int_v += error_v;
        error_int_ang += error_ang;
        error_int_ang_v += error_ang_v;

        //I項のリミッター
        if(ABS(error_int_v) > 50.0){
            if(error_int_v > 0) error_int_v = 50.0 ;
            if(error_int_v < 0) error_int_v = -50.0;
        }

        if(ABS(error_int_ang_v) > 1200.0 ){
                if(error_int_ang_v > 0) error_int_ang_v = 1200.0;
                if(error_int_ang_v < 0) error_int_ang_v = -1200.0;
        }

        /*
        if(move_state != ROTATION){
            error_int_ang_v=0.0;
        }
        */

        if(ABS(error_int_ang) > 300.0 ){
            if(error_int_ang > 0) error_int_ang = 300.0;
            if(error_int_ang < 0) error_int_ang = -300.0;
        }


    };

    Vector2f dutyFF(){
        UMouse &mouse = UMouse::getInstance();
        Vector2f duty(0.0f, 0.0f);

        //必要な力(直進成分)
        float F_forward = MASS*target_a/2.0;
        //必要な力(回転成分)
        float F_rotation = INERTIA * DEG2RAD(target_ang_a) / TREAD;
        //モータとモータドライバの抵抗値
        float R = COIL_RES + FET_RES;
        //必要なトルク
        float torque_L = (F_forward - F_rotation)*(0.5* DIA_TIRE/GEAR_RATIO);
        float torque_R = (F_forward + F_rotation)*(0.5* DIA_TIRE/GEAR_RATIO);
        //左右輪の速度
        float v_L = target_v - TREAD * PI * target_ang_v/360.0;
        float v_R = target_v + TREAD * PI * target_ang_v/360.0;
        //左右モーターの回転数
        float rpm_L = v_L * 60.0 /(PI * DIA_TIRE);
        float rpm_R = v_R * 60.0 /(PI * DIA_TIRE);

        duty(0) = (R*torque_L / K_T + K_E * rpm_L) / mouse.Vcc;
        duty(1) = (R*torque_R / K_T + K_E * rpm_R) / mouse.Vcc;


        return duty;
    };

    Vector2f dutyFB(){
        Vector2f duty(0.0f, 0.0f);

        float FB_v     = Kp_v     * error_v     + Ki_v     * error_int_v;
        float FB_ang_v = Kp_ang_v * error_ang_v + Ki_ang_v * error_int_ang_v;
        float FB_ang   = Kp_ang   * error_ang   + Ki_ang   * error_int_ang    + Kd_ang * error_ang_v;

        duty(0) = FB_v - FB_ang_v - FB_ang;
        duty(1) = FB_v + FB_ang_v + FB_ang;

        return duty;
    };

    Vector2f dutyWall(){
        Vector2f duty(0.0f, 0.0f);

        return duty;
    };

};
#endif


class SimplePivotTurn : public BaseMoveEvent{

public:
    volatile float target_ang;
    volatile float target_ang_v;
    volatile float target_ang_a;

    volatile float target_v;

    volatile float Kp_ang;
    volatile float Ki_ang;
    volatile float Kd_ang;

    volatile float Kp_ang_v;
    volatile float Ki_ang_v;
    volatile float Kd_ang_v;

    volatile float Kp_v;
    volatile float Ki_v;
    volatile float Kd_v;

    volatile float error_ang;
    volatile float error_int_ang;
    volatile float error_ang_pre;
    volatile float error_d_ang;

    volatile float error_ang_v;
    volatile float error_int_ang_v;
    volatile float error_ang_v_pre;
    volatile float error_d_ang_v;

    volatile float error_v;
    volatile float error_int_v;
    volatile float error_d_v;
    volatile float error_v_pre;

    volatile float ang_a;
    volatile float end_ang;
    volatile float accum_ang;
    volatile float accum_v;

    volatile uint8_t scene_num;

    SimplePivotTurn(float ang){
        target_ang = 0.0;
        target_ang_v = 0.0;
        target_ang_a = 0.0;
        end_ang = ang;
        accum_ang = 0.0;

        error_ang = 0.0;
        error_int_ang = 0.0;
        error_ang_pre = 0.0;
        error_d_ang = 0.0;

        Kp_ang = 0.0;
        Ki_ang = 0.0;
        Kd_ang = 0.0;//0.001;

        error_ang_v = 0.0;
        error_int_ang_v = 0.0;
        error_ang_v_pre = 0.0;
        error_d_ang_v = 0.0;


        Kp_ang_v = 0.0012;
        Ki_ang_v = 0.0004;
        Kd_ang_v = 0.0;//0.001;


        target_v = 0.0;
        accum_v = 0.0;
        error_v = 0.0;
        error_int_v = 0.0;
        error_v_pre = 0.0;
        error_d_v = 0.0;
        Kp_v = 0.00;
        Ki_v = 0.000;
        Kd_v = 0.000;


        ang_a  = SIGN(ang) * 360.0;
        scene_num = 0;
    };

    bool isEnd(){
        static uint32_t time_count = 0;

        if( scene_num == 0){
            printfAsync("%d\n",scene_num);
            target_ang_a = ang_a;
            scene_num++;
        }

        if( ABS(target_ang) >= ABS(end_ang)*1.0/2.0 &&
            scene_num == 1){
            printfAsync("%d\n",scene_num);
            error_int_ang = 0.0;
            target_ang_a = 0.0;
            scene_num++;
        }

        if( ABS(target_ang) >= ABS(end_ang)*1.0/2.0 &&
            scene_num == 2 ){
            printfAsync("%d\n",scene_num);
            error_int_ang *= -1.0;
            target_ang_a = - ang_a;
            scene_num++;
        }
        if((ABS(target_ang) >= ABS(end_ang)     ||
            SIGN(ang_a) != SIGN(target_ang_v) ) &&
            scene_num == 3){
            printfAsync("%d\n",scene_num);
            target_ang_a = 0.0;
            target_ang_v = 0.0;
            target_ang = end_ang;
            scene_num ++;
            time_count = getElapsedMsec();
            Kp_ang = 0.0021;
            Ki_ang = 0.00032;
            Kd_ang = 0.01;//0.001;
            Kp_ang_v = 0.0;
            Ki_ang_v = 0.0;
            Kd_ang_v = 0.0;
            Kp_v = 0.00;
            Ki_v = 0.000;
            Kd_v = 0.000;

            error_int_ang = 0.0;
        }

        if(getElapsedMsec() - time_count > 1000 &&
            scene_num == 4){
            return true;
        }

        return false;
    };

    Vector2f calcDuty(){
        MPU9250 &imu = MPU9250::getInstance();
        Vector2f duty(0.0,0.0);
        UMouse &m = UMouse::getInstance();

        accum_v += m.a_v * DELTA_T;


        //ターゲットの積分
        target_ang_v += target_ang_a * DELTA_T;
        target_ang   += target_ang_v * DELTA_T;
        accum_ang    += imu.omega_f[2] * DELTA_T;

        //角度
        error_ang   = target_ang - accum_ang;
        error_d_ang = error_ang - error_ang_pre;
        error_ang_pre = error_ang;
        error_int_ang   += error_ang;
        error_int_ang = constrain(error_int_ang, -200.0, 200.0);
        //角速度
        error_ang_v   = target_ang_v - imu.omega_f[2];
        error_d_ang_v = error_ang_v - error_ang_v_pre;
        error_ang_v_pre = error_ang_v;
        //角度と角速度のI項
        error_int_ang_v   += error_ang_v;
        error_int_ang_v = constrain(error_int_ang_v, -200.0, 200.0);


        error_v   = target_v - SIGN(accum_v) * m.v_enc;
        error_d_v = error_v - error_v_pre;
        error_v_pre = error_v;

        error_int_v   += error_v;
        error_int_v = constrain(error_int_v, -200.0, 200.0);


        float FB_v = (  Kp_v * error_v
                     + Ki_v * error_int_v
                     + Kd_v * error_d_v)
                     * 8.4/m.Vcc;

        float FB_ang   = (  Kp_ang * error_ang
                         + Ki_ang * error_int_ang
                         + Kd_ang * error_d_ang)
                         * 8.4/m.Vcc;

        float FB_ang_v   = (  Kp_ang_v * error_ang_v
                         + Ki_ang_v * error_int_ang_v
                         + Kd_ang_v * error_d_ang_v)
                         * 8.4/m.Vcc;


        //計算した各種変数をmouseにセット

        m.t_ang_a = target_ang_a ;
        m.t_ang_v = target_ang_v;
        m.t_ang   = target_ang;
        m.accum_ang = accum_ang;

        m.ang_P = Kp_ang * error_ang;
        m.ang_I = Ki_ang * error_int_ang;
        m.ang_D = Kd_ang * error_d_ang;

        m.ang_v_P = Kp_ang_v * error_ang_v;
        m.ang_v_I = Ki_ang_v * error_int_ang_v;
        m.ang_v_D = Kd_ang_v * error_d_ang_v;


        m.v_P = Kp_v * error_v;
        m.v_I = Ki_v * error_int_v;
        m.v_D = Kd_v * error_d_v;
        m.t_v = SIGN(accum_v) * m.v_enc;

        Vector2f FF_ang_duty = dutyFF_ang(target_ang_a, target_ang_v);
        m.ang_FF = FF_ang_duty.x;

        FB_ang = constrain(FB_ang, -0.20, 0.20);

        duty.x =  FB_ang + FB_ang_v + FB_v + FF_ang_duty.x;//左
        duty.y = -FB_ang - FB_ang_v + FB_v + FF_ang_duty.y;//右

        return duty;
    };


};

class SimpleTrape : public BaseMoveEvent{

public:
    volatile float target_ang;
    volatile float target_ang_v;
    volatile float target_ang_a;

    volatile float target_x;
    volatile float target_v;
    volatile float target_a;

    volatile float Kp_ang;
    volatile float Ki_ang;
    volatile float Kd_ang;

    volatile float Kp_ang_v;
    volatile float Ki_ang_v;
    volatile float Kd_ang_v;

    volatile float Kp_v;
    volatile float Ki_v;
    volatile float Kd_v;

    volatile float error_ang;
    volatile float error_int_ang;
    volatile float error_ang_pre;
    volatile float error_d_ang;

    volatile float error_ang_v;
    volatile float error_int_ang_v;
    volatile float error_ang_v_pre;
    volatile float error_d_ang_v;

    volatile float error_v;
    volatile float error_int_v;
    volatile float error_d_v;
    volatile float error_v_pre;

    volatile float ang_a;
    volatile float end_x;
    volatile float accum_ang;
    volatile float accum_v;

    volatile uint8_t scene_num;

    SimpleTrape(float x){
        end_x = x;
        target_a = 1.0;

        target_ang = 0.0;
        target_ang_v = 0.0;
        target_ang_a = 0.0;
        accum_ang = 0.0;

        error_ang = 0.0;
        error_int_ang = 0.0;
        error_ang_pre = 0.0;
        error_d_ang = 0.0;

        Kp_ang = 0.0;
        Ki_ang = 0.0;
        Kd_ang = 0.0;//0.001;

        error_ang_v = 0.0;
        error_int_ang_v = 0.0;
        error_ang_v_pre = 0.0;
        error_d_ang_v = 0.0;


        Kp_ang_v = 0.0012;
        Ki_ang_v = 0.0004;
        Kd_ang_v = 0.0;//0.001;


        target_v = 0.0;
        accum_v = 0.0;
        error_v = 0.0;
        error_int_v = 0.0;
        error_v_pre = 0.0;
        error_d_v = 0.0;
        Kp_v = 0.01;
        Ki_v = 0.001;
        Kd_v = 0.001;
        printfAsync("Trape\n");

        scene_num = 0;
    };

    bool isEnd(){
        static uint32_t time_count = 0;

        if( scene_num == 0){
            target_a = 1.0;
            printfAsync("%d\n",scene_num);
            scene_num++;
        }

        if( ABS(target_x) >= ABS(end_x)*1.0/2.0 &&
            scene_num == 1){
            printfAsync("%d\n",scene_num);
            target_a = 0.0;
            scene_num++;
        }

        if( ABS(target_x) >= ABS(end_x)*1.0/2.0 &&
            scene_num == 2 ){
            printfAsync("%d\n",scene_num);
            target_a = - 1.0;
            scene_num++;
        }
        if((ABS(target_x) >= ABS(end_x)     ||
            target_v < 0.0) &&
            scene_num == 3){
            printfAsync("%d\n",scene_num);
            target_a = 0.0;
            target_v = 0.0;
            target_x = end_x;
            scene_num ++;
            time_count = getElapsedMsec();
            Kp_ang_v = 0.0;
            Ki_ang_v = 0.0;
            Kd_ang_v = 0.0;
            Kp_v = 0.00;
            Ki_v = 0.000;
            Kd_v = 0.000;

            error_int_ang = 0.0;
        }

        if(getElapsedMsec() - time_count > 1000 &&
            scene_num == 4){
            return true;
        }

        return false;
    };

    Vector2f calcDuty(){
        MPU9250 &imu = MPU9250::getInstance();
        Vector2f duty(0.0,0.0);
        UMouse &m = UMouse::getInstance();

        //ターゲットの積分
        target_ang_v += target_ang_a * DELTA_T;
        target_ang   += target_ang_v * DELTA_T;
        accum_ang    += imu.omega_f[2] * DELTA_T;
        //速度
        target_v += target_a * DELTA_T;
        target_x += target_v * DELTA_T;

        //角度
        error_ang   = target_ang - accum_ang;
        error_d_ang = error_ang - error_ang_pre;
        error_ang_pre = error_ang;
        error_int_ang   += error_ang;
        error_int_ang = constrain(error_int_ang, -200.0, 200.0);
        //角速度
        error_ang_v   = target_ang_v - imu.omega_f[2];
        error_d_ang_v = error_ang_v - error_ang_v_pre;
        error_ang_v_pre = error_ang_v;
        //角度と角速度のI項
        error_int_ang_v   += error_ang_v;
        error_int_ang_v = constrain(error_int_ang_v, -200.0, 200.0);


        error_v   = target_v - m.v_enc;
        error_d_v = error_v - error_v_pre;
        error_v_pre = error_v;

        error_int_v   += error_v;
        error_int_v = constrain(error_int_v, -20.0, 20.0);


        float FB_v = (  Kp_v * error_v
                     + Ki_v * error_int_v
                     + Kd_v * error_d_v)
                     * 8.4/m.Vcc;

        float FB_ang   = (  Kp_ang * error_ang
                         + Ki_ang * error_int_ang
                         + Kd_ang * error_d_ang)
                         * 8.4/m.Vcc;

        float FB_ang_v   = (  Kp_ang_v * error_ang_v
                         + Ki_ang_v * error_int_ang_v
                         + Kd_ang_v * error_d_ang_v)
                         * 8.4/m.Vcc;


        //計算した各種変数をmouseにセット

        m.t_ang_a = target_ang_a ;
        m.t_ang_v = target_ang_v;
        m.t_ang   = target_ang;
        m.accum_ang = accum_ang;

        m.t_a = target_a;
        m.t_v = target_v;
        m.t_x = target_x;


        m.ang_P = Kp_ang * error_ang;
        m.ang_I = Ki_ang * error_int_ang;
        m.ang_D = Kd_ang * error_d_ang;

        m.ang_v_P = Kp_ang_v * error_ang_v;
        m.ang_v_I = Ki_ang_v * error_int_ang_v;
        m.ang_v_D = Kd_ang_v * error_d_ang_v;


        m.v_P = Kp_v * (target_v - m.v_enc);//error_v;
        float temp = target_v -m.v_enc;
        if(target_v > m.v_enc){
            printfAsync("-----\n");
            printfAsync("%f %f %f \n",target_v, m.v_enc, target_v - m.v_enc);
            printfAsync("%f %x\n",temp,*(int*)&temp);
        }
        if(target_v - m.v_enc < 0 ){
            printfAsync("====\n");
            printfAsync("%f %f %f \n",target_v, m.v_enc, target_v - m.v_enc);
            printfAsync("%f %x\n",temp,*(int*)&temp);

        }

        m.v_I = Ki_v * error_int_v;
        m.v_D = Kd_v * error_d_v;

        Vector2f FF_ang_duty = dutyFF_ang(target_ang_a, target_ang_v);
        m.ang_FF = FF_ang_duty.x;

        FB_ang = constrain(FB_ang, -0.20, 0.20);

        //duty[0] =  FB_ang + FB_ang_v + FB_v;//左
        //duty[1] = -FB_ang - FB_ang_v + FB_v;//右
        duty.x = FB_v;//左
        duty.y = FB_v;//右

        //duty += FF_ang_duty;
        return duty;
    };


};




class Stop : public BaseMoveEvent{

public:
    uint32_t count = 0;
    uint32_t count_end;

    Stop(uint32_t stop_ms){
        count_end = stop_ms;
    }

    bool isEnd(){

        if(count < count_end) return false;
        else return true;
    };

    Vector2f calcDuty(){
        Vector2f duty(0.0,0.0);

        duty.x = 0.0;
        duty.y = 0.0;
        MPU9250 &imu = MPU9250::getInstance();

        if(ref_index < 200){
            omega_x[ref_index] = imu.omega_raw[0];
            omega_y[ref_index] = imu.omega_raw[1];
            omega_z[ref_index] = imu.omega_raw[2];

            acc_x[ref_index] = imu.acc_raw[0];
            acc_y[ref_index] = imu.acc_raw[1];
            acc_z[ref_index] = imu.acc_raw[2];

            ref_index++;
        }

        if(count == 200){
            setRefGyro();
        }
        if(count == 201){
            setRefAcc();
        }


        UMouse &m = UMouse::getInstance();
        m.t_a = 0.0;
        m.t_v = 0.0;
        m.t_x = 0.0;
        m.accum_x =0.0;
        m.t_ang_a = 0.0;
        m.t_ang_v = 0.0;
        m.t_ang = 0.0;
        m.accum_ang = 0.0;

        m.a_v = 0.0;
        m.a_h = 0.0;

        m.wall_P =0.0;
        m.wall_I =0.0;
        m.wall_D =0.0;

        m.v_P =0.0;
        m.v_I =0.0;
        m.v_D = 0.0;

        m.ang_v_P = 0.0;
        m.ang_v_I = 0.0;
        m.ang_v_D = 0.0;

        m.ang_P = 0.0;
        m.ang_I = 0.0;
        m.ang_D = 0.0;

        count++;
        return duty;
    };

private:
    uint32_t ref_index = 0;
    int16_t omega_x[200];
    int16_t omega_y[200];
    int16_t omega_z[200];

    float omega_x_sum = 0.0;
    float omega_y_sum = 0.0;
    float omega_z_sum = 0.0;

    int16_t acc_x[200];
    int16_t acc_y[200];
    int16_t acc_z[200];

    float acc_x_sum = 0.0;
    float acc_y_sum = 0.0;
    float acc_z_sum = 0.0;


    void setRefGyro(){
        MPU9250 &imu = MPU9250::getInstance();

        uint16_t ref_num = ref_index;
        quickSort_int16(omega_x,0 ,ref_num -1);
        quickSort_int16(omega_y,0 ,ref_num -1);
        quickSort_int16(omega_z,0 ,ref_num -1);

        for(int i=ref_num/4;i<(ref_num*3/4 +1) ;i++)
        {
            omega_x_sum += (float)(omega_x[i]);
            omega_y_sum += (float)(omega_y[i]);
            omega_z_sum += (float)(omega_z[i]);
        }
        imu.omega_ref[0] = (int16_t)(omega_x_sum/(float)ref_num *2.0);
        imu.omega_ref[1] = (int16_t)(omega_y_sum/(float)ref_num *2.0);
        imu.omega_ref[2] = (int16_t)(omega_z_sum/(float)ref_num *2.0);
    }

    void setRefAcc(){
        MPU9250 &imu = MPU9250::getInstance();
        uint16_t ref_num = ref_index;
        quickSort_int16(acc_x,0 ,ref_num -1);
        quickSort_int16(acc_y,0 ,ref_num -1);
        quickSort_int16(acc_z,0 ,ref_num -1);

        for(int i=ref_num/4;i<(ref_num*3/4 +1) ;i++)
        {
            acc_x_sum += (float)(acc_x[i]);
            acc_y_sum += (float)(acc_y[i]);
            acc_z_sum += (float)(acc_z[i]);
        }
        imu.acc_ref[0] = (int16_t)(acc_x_sum/(float)ref_num *2.0);
        imu.acc_ref[1] = (int16_t)(acc_y_sum/(float)ref_num *2.0);
        imu.acc_ref[2] = (int16_t)(acc_z_sum/(float)ref_num *2.0);
        printfAsync("====mpu9250======\n acc offset %d, %d, %d\n",imu.acc_ref[0],imu.acc_ref[1],imu.acc_ref[2] );

    }

};



#ifdef Memo

class PivotTurn : public BaseMoveEvent{
public:
    float ang_a;
    float ang;

    PivotTurn(float ang_){
        paramInit();
        ang = ang_;
        ang_a = 500.0;
    };

    bool isEnd(){
        return ((ABS(target_ang) >= ABS(ang)) ? true:false);
    };
    void trajectoryPlanning(){
        static uint8_t scene_num = 0;

        switch (scene_num){
            case 0:
                target_ang_a = ang_a;
                if(ABS(target_ang) >= ABS(ang)/3.0){
                    target_ang_a = 0.0;
                    scene_num ++;
                }
                break;
            case 1:
                if(ABS(target_ang) >= ABS(ang)*2.0/3.0){
                    target_ang_a *= -1.0;
                    scene_num ++;
                }
                break;
            case 2:
                if(ABS(target_ang) >= ABS(ang)){
                    target_ang_a *= 0.0;
                    scene_num ++;
                }
                break;
        }

    };

    virtual void updatePidError(){
        //*******フィードバック制御のゲイン***********//
        Kp_v = 0.9;//.5;
        //float Kd_v = 0.3;//;
        Ki_v = 0.3;//0.1;

        Kp_ang_v = 0.0093;
        Ki_ang_v = 0.00042;

        Kp_ang = 0.0005;//0.005;
        Ki_ang = 0.00005;//0.003;
        Kd_ang = 0.0;//0.001;
        //*********************************//
        UMouse& mouse = UMouse::getInstance();
        //速度と角度と角速度の偏差
        float v = mouse.v_enc_L - mouse.v_enc_R;
        error_v     = target_v     - v;
        error_ang   = target_ang   - accum_ang;
        error_ang_v = target_ang_v - mouse.ang_v;
        //速度と角度と角速度のI項
        error_int_v += error_v;
        error_int_ang += error_ang;
        error_int_ang_v += error_ang_v;

        //I項のリミッター
        if(ABS(error_int_v) > 50.0){
            if(error_int_v > 0) error_int_v = 50.0 ;
            if(error_int_v < 0) error_int_v = -50.0;
        }

        if(ABS(error_int_ang_v) > 1200.0 ){
                if(error_int_ang_v > 0) error_int_ang_v = 1200.0;
                if(error_int_ang_v < 0) error_int_ang_v = -1200.0;
        }

        /*
        if(move_state != ROTATION){
            error_int_ang_v=0.0;
        }
        */

        if(ABS(error_int_ang) > 300.0 ){
            if(error_int_ang > 0) error_int_ang = 300.0;
            if(error_int_ang < 0) error_int_ang = -300.0;
        }


    };

};
#endif

class EventList{
public:

    static EventList& getInstance(){
        static EventList instance;
        return instance;
    };
    void update(){
        if(eventList.empty() == false){
            UMouse &mouse = UMouse::getInstance();
            Vector2f duty = eventList.front()->calcDuty();
            if(eventList.front()->isEnd() == true){
                delete eventList.front();
                eventList.pop();
            }
            mouse.setDuty(duty.x, duty.y);


        }
        else{
            //UMouse &mouse = UMouse::getInstance();
            float gyro_ang_v = MPU9250::getInstance().omega_f[2];
            UMouse &mouse = UMouse::getInstance();
            mouse.accum_ang += gyro_ang_v * DELTA_T;
            mouse.t_v += mouse.a_v * DELTA_T;
        }
    }

    void push(BaseMoveEvent* moveEve){
        eventList.push(moveEve);
    }

    uint16_t getEventNum(){
        return eventList.size();
    }



private:
    queue<BaseMoveEvent*> eventList;

    EventList() {};
    ~EventList() {};
    EventList(EventList&) {};

};

#endif
