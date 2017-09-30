#pragma once

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
#include "parameterManager.h"

using namespace robot_object;

using std::queue;
namespace peri = peripheral_RX71M;
using peri::getElapsedMsec;
using peri:: waitmsec;

//using namespace Eigen;
//#define EIGEN_DONT_VECTORIZE
//#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT

class SecondOrderEuler{
public:
    float x;
    float v;
    float a;
    float delta_t;
    void update(){
        v += delta_t * a;
        x += delta_t * v;
    }

    SecondOrderEuler(float a_0, float v_0, float x_0, float delta_t_){
        delta_t = delta_t_;
        a = a_0;
        v = v_0;
        x = x_0;
    }
};

class PidController{
public:
    float Kp;
    float Ki;
    float Kd;
    float int_lim;
    float target;
    float error_p;
    float error_i;
    float error_d;
    float error_p_pre;
    void update(float target_, float observed_val){
        target = target_;
        error_p = target - observed_val;
        error_i = constrain(error_p+error_i, -int_lim, int_lim);
        error_d = error_p - error_p_pre;
        error_p_pre = error_p;
    };
    float calc(){
        float control_val = Kp * error_p + Ki * error_i + Kd * error_d;
        return control_val;
    };

    void set(float Kp_, float Ki_, float Kd_){
        Kp = Kp_;
        Ki = Ki_;
        Kd = Kd_;
    }

    void set(float Kp_, float Ki_, float Kd_, float int_lim_){
        Kp = Kp_;
        Ki = Ki_;
        Kd = Kd_;
        int_lim = int_lim_;
    }


    PidController(float Kp_, float Ki_, float Kd_, float int_lim_){
        Kp = Kp_;
        Ki = Ki_;
        Kd = Kd_;
        int_lim = int_lim_;
        target = 0.0;
        error_p = 0.0;
        error_i = 0.0;
        error_d = 0.0;
        error_p_pre = 0.0;
    };
};

class BaseMoveEvent{
public:
    virtual bool isEnd()=0;
    virtual Vector2f calcDuty()=0;

    Vector2f dutyFF_ang(float target_ang_a, float target_ang_v){
        UMouse &mouse = UMouse::getInstance();
        Vector2f duty(0.0f, 0.0f);

        //必要な力(回転成分)
        float F_rotation = INERTIA * DEG2RAD(target_ang_a)
        / TREAD;
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




class PivotTurn : public BaseMoveEvent{

public:
    PidController* v_ctrl;
    PidController* ang_v_ctrl;

    SecondOrderEuler* trans_t;
    SecondOrderEuler* rot_t;

    float end_ang;
    float accum_ang;
    float rot_a;
    float abs_min_rot_v;


    PivotTurn(float ang){
        ParameterManager &pm = ParameterManager::getInstance();

        end_ang = ang;
        rot_a  = SIGN(ang)* 720.0;
        ang_v_ctrl = new PidController(pm.pivot_ang_v_P, pm.pivot_ang_v_I, pm.pivot_ang_v_D, pm.pivot_ang_v_LI);
        v_ctrl = new PidController(pm.pivot_v_P, pm.pivot_v_I, pm.pivot_v_D, pm.pivot_v_LI);

        trans_t = new SecondOrderEuler(0.0, 0.0, 0.0, DELTA_T);
        rot_t = new SecondOrderEuler(rot_a, 0.0, 0.0, DELTA_T);
        accum_ang = 0.0;
        abs_min_rot_v = 50.0;
        printfAsync("PivotTurn\n");
    };

    bool isEnd(){

        if(ABS(accum_ang) > ABS(end_ang)){
            return true;
        }

        if(ABS(rot_t->x) <  ABS(end_ang)*1.0/3.0 ){
            rot_t->a = rot_a;
        }
        else if(ABS(rot_t->x) < ABS(end_ang)*2.0/3.0 ){
            rot_t->a = 0.0;
        }
        else if(ABS(rot_t->x) < ABS(end_ang)*5.0/6.0){
            rot_t->a = - rot_a;
        }
        else if( ABS(rot_t->v) < abs_min_rot_v){
            rot_t->v = SIGN(end_ang)* abs_min_rot_v;
            rot_t->a = 0.0;
        }

        return false;
    };

    Vector2f calcDuty(){
        MPU9250 &imu = MPU9250::getInstance();
        Vector2f duty(0.0,0.0);
        UMouse &m = UMouse::getInstance();

        //ターゲットの積分
        trans_t->update();
        rot_t->update();

        //実角度の積分
        accum_ang    += imu.omega_f[2] * DELTA_T;
        //制御パラメータの更新     ターゲット, 観測値
        ang_v_ctrl->update(rot_t->v, imu.omega_f[2]);
        v_ctrl->update(0.0, m.v_enc);

        const float V_MAX_2CELL = 8.4;
        float FB_v   = v_ctrl->calc() * V_MAX_2CELL / m.Vcc;
        float FB_ang_v = ang_v_ctrl->calc() * V_MAX_2CELL / m.Vcc;

        //計算した各種変数をmouseにセット

        m.t_ang_a = rot_t->a;
        m.t_ang_v = rot_t->v;
        m.t_ang   = rot_t->x;
        m.accum_ang = accum_ang;

        m.ang_v_P = ang_v_ctrl->Kp * ang_v_ctrl->error_p;
        m.ang_v_I = ang_v_ctrl->Ki * ang_v_ctrl->error_i;
        m.ang_v_D = ang_v_ctrl->Kd * ang_v_ctrl->error_d;

        m.v_P = v_ctrl->Kp * v_ctrl->error_p;
        m.v_I = v_ctrl->Ki * v_ctrl->error_i;
        m.v_D = v_ctrl->Kd * v_ctrl->error_d;
        m.t_v = m.v_enc;

        Vector2f FF_ang_duty = dutyFF_ang(rot_t->a, rot_t->v);
        m.ang_FF = FF_ang_duty.x;

        duty.x = constrain(- FB_ang_v + FB_v + FF_ang_duty.x,-0.25,0.25) ;
        duty.y = constrain(+ FB_ang_v + FB_v + FF_ang_duty.y,-0.25,0.25);
        return duty;
    };
};


class Trape : public BaseMoveEvent{

public:
    PidController* ang_ctrl;
    PidController* v_ctrl;
    PidController* ang_v_ctrl;

    SecondOrderEuler* trans_t;
    SecondOrderEuler* rot_t;

    uint8_t scene_num;
    float accum_ang = 0.0;
    float x_acc;
    float x_bre;
    float x_bre_now;
    float x;
    float v_max;
    float v_0;
    float v_end;
    float a;

    Trape(float x_, float v_max_, float v_0_, float v_end_, float a_){
        x = x_;
        v_max = v_max_;
        v_0 = v_0_;
        v_end = v_end_;
        a = a_;
        x_bre_now = 0.0;

        if(a != 0.0){
            x_acc = ( (v_max * v_max) - (v_0 * v_0) ) / (2.0*a);
            x_bre = ( (v_max * v_max) - (v_end * v_end) ) / (2.0*a);
        }
        else{
            x_acc = 0.0;
            x_bre = 0.0;
        }

        ParameterManager &pm = ParameterManager::getInstance();

        scene_num = 0;

        ang_v_ctrl = new PidController(pm.straight_ang_v_P, pm.straight_ang_v_I, pm.straight_ang_v_D, pm.straight_ang_v_LI);
        ang_ctrl = new PidController(0.0, 0.0, 0.0, 0.0);
        v_ctrl = new PidController(pm.straight_v_P, pm.straight_v_I, pm.straight_v_D, pm.straight_v_LI);

        trans_t = new SecondOrderEuler(a, v_0, 0.0, DELTA_T);
        rot_t = new SecondOrderEuler(0.0, 0.0, 0.0, DELTA_T);
        accum_ang = 0.0;
        printfAsync("Trape\n");
    };

    bool isEnd(){

        //終了条件
        if(trans_t->v < 0.0 || trans_t->x > x){
           return true;
        }

        //  速度がv_endになるように台形加速
        if( (x_acc + x_bre) < x ){
            if     ( trans_t->x < x_acc){
                trans_t->a = a;
            }
            else if( trans_t->x < x-x_bre){
                trans_t->a = 0.0;
                trans_t->v = v_max;
            }
            else if( trans_t->x < x){
                trans_t->a = -1.0 * a;
            }
        }
        //加速度が低くv_endに到達できない場合
        else{
            if(a != 0.0){
               x_bre_now = ( (trans_t->v * trans_t->v) - (v_end * v_end) ) / (2.0*a);
            }
            else{
               x_bre_now = 0.0;
            }

            if( (x_bre_now >= (x - trans_t->x)) && (trans_t->a > 0.0) ){
                trans_t->a = (-1.0)*a;
            }
        }
        return false;
    };

    Vector2f calcDuty(){
        MPU9250 &imu = MPU9250::getInstance();
        Vector2f duty(0.0,0.0);
        UMouse &m = UMouse::getInstance();

        //ターゲットの積分
        trans_t->update();
        rot_t->update();

        //実角度の積分
        accum_ang    += imu.omega_f[2] * DELTA_T;
        //制御パラメータの更新     ターゲット, 観測値
        ang_v_ctrl->update(rot_t->v, imu.omega_f[2]);
        v_ctrl->update(trans_t->v, m.v_enc);

        const float V_MAX_2CELL = 8.4;
        float FB_v   = v_ctrl->calc() * V_MAX_2CELL / m.Vcc;
        float FB_ang_v = ang_v_ctrl->calc() * V_MAX_2CELL / m.Vcc;

        //計算した各種変数をmouseにセット
        m.t_a = trans_t->a;
        m.t_v = trans_t->v;
        m.t_x   = trans_t->x;
        m.accum_ang = accum_ang;

        m.ang_P = ang_ctrl->Kp * ang_ctrl->error_p;
        m.ang_I = ang_ctrl->Ki * ang_ctrl->error_i;
        m.ang_D = ang_ctrl->Kd * ang_ctrl->error_d;

        m.ang_v_P = ang_v_ctrl->Kp * ang_v_ctrl->error_p;
        m.ang_v_I = ang_v_ctrl->Ki * ang_v_ctrl->error_i;
        m.ang_v_D = ang_v_ctrl->Kd * ang_v_ctrl->error_d;

        m.v_P = v_ctrl->Kp * v_ctrl->error_p;
        m.v_I = v_ctrl->Ki * v_ctrl->error_i;
        m.v_D = v_ctrl->Kd * v_ctrl->error_d;
        m.t_v = m.v_enc;

        Vector2f FF_ang_duty = dutyFF_ang(rot_t->a, rot_t->v);
        m.ang_FF = FF_ang_duty.x;

        duty.x = constrain(- FB_ang_v + FB_v + FF_ang_duty.x,-0.25,0.25) ;
        duty.y = constrain(+ FB_ang_v + FB_v + FF_ang_duty.y,-0.25,0.25);
        return duty;
    };

    ~Trape(){
        ang_ctrl;
        delete v_ctrl;
        delete ang_v_ctrl;
        delete trans_t;
        delete rot_t;
    }
};


class Stop : public BaseMoveEvent {

public:
    uint32_t count = 0;
    uint32_t count_end;

    Stop(uint32_t stop_ms) {
        count_end = stop_ms;
        printfAsync("Stop\n");
    }

    bool isEnd() {

        if(count < count_end) return false;
        else return true;
    };

    Vector2f calcDuty() {
        Vector2f duty(0.0,0.0);

        duty.x = 0.0;
        duty.y = 0.0;
        MPU9250 &imu = MPU9250::getInstance();

        if(ref_index < 200) {
            omega_x[ref_index] = imu.omega_raw[0];
            omega_y[ref_index] = imu.omega_raw[1];
            omega_z[ref_index] = imu.omega_raw[2];

            acc_x[ref_index] = imu.acc_raw[0];
            acc_y[ref_index] = imu.acc_raw[1];
            acc_z[ref_index] = imu.acc_raw[2];

            ref_index++;
        }

        if(count == 200) {
            //setRefGyro();
        }
        if(count == 201) {
            //setRefAcc();
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

    void setRefGyro() {
        MPU9250 &imu = MPU9250::getInstance();

        uint16_t ref_num = ref_index;
        quickSort_int16(omega_x,0 ,ref_num -1);
        quickSort_int16(omega_y,0 ,ref_num -1);
        quickSort_int16(omega_z,0 ,ref_num -1);

        for(int i=ref_num/4;i<(ref_num*3/4 +1);i++)
        {
            omega_x_sum += (float)(omega_x[i]);
            omega_y_sum += (float)(omega_y[i]);
            omega_z_sum += (float)(omega_z[i]);
        }
        imu.omega_ref[0] = (int16_t)(omega_x_sum/(float)ref_num *2.0);
        imu.omega_ref[1] = (int16_t)(omega_y_sum/(float)ref_num *2.0);
        imu.omega_ref[2] = (int16_t)(omega_z_sum/(float)ref_num *2.0);
    }

    void setRefAcc() {
        MPU9250 &imu = MPU9250::getInstance();
        uint16_t ref_num = ref_index;
        quickSort_int16(acc_x,0 ,ref_num -1);
        quickSort_int16(acc_y,0 ,ref_num -1);
        quickSort_int16(acc_z,0 ,ref_num -1);

        for(int i=ref_num/4;i<(ref_num*3/4 +1);i++)
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

class EventList {
public:

    static EventList& getInstance() {
        static EventList instance;
        return instance;
    };
    void update() {
        if(eventList.empty() == false) {
            UMouse &mouse = UMouse::getInstance();
            Vector2f duty = eventList.front()->calcDuty();
            if(eventList.front()->isEnd() == true) {
                delete eventList.front();
                eventList.pop();
            }
            mouse.setDuty(duty.x, duty.y);

        }
        else {

        }
    }

    void push(BaseMoveEvent* moveEve) {
        eventList.push(moveEve);
    }

    uint16_t getEventNum() {
        return eventList.size();
    }

    bool empty(){
        return eventList.empty();
    }

private:
    queue<BaseMoveEvent*> eventList;

    EventList() {};
    ~EventList() {};
    EventList(EventList&) {};

};

