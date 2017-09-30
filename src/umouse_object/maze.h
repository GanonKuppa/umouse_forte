#pragma once

#include "stdint.h"
#include "wallsensor.hpp"
#include "myUtil.hpp"
#include <map> // pair
#include <queue>
#include "communication.h"
using std::queue;
using std::pair;



using namespace robot_object;

enum direction_e {
    E = 0, NE, N, NW, W, SW, S, SE
};

class Wall {

public:
    uint8_t E :1;//壁情報
    uint8_t N :1;
    uint8_t W :1;
    uint8_t S :1;
    uint8_t EF :1;//壁を読んだかのフラグ
    uint8_t NF :1;
    uint8_t WF :1;
    uint8_t SF :1;

    void setByUint8(uint8_t wall) {
        E = ((wall >> 0) & 0x01);
        N = ((wall >> 1) & 0x01);
        W = ((wall >> 2) & 0x01);
        S = ((wall >> 3) & 0x01);

        EF = ((wall >> 4) & 0x01);
        NF = ((wall >> 5) & 0x01);
        WF = ((wall >> 6) & 0x01);
        SF = ((wall >> 7) & 0x01);
    }
};

class Maze {

public:
    uint32_t walls_vertical[31];
    uint32_t walls_horizontal[31];
    uint32_t reached[32];
    uint16_t p_map[32][32];


    bool isReached(uint16_t x, uint16_t y) {
        bool reach;
        if( 0<=x && x<=31 && 0<=y && y<=31) reach =(reached[x] >> y) & 0x00000001;
        else reach = 1;
        return reach;
    };

    void writeReached(uint16_t x, uint16_t y, bool reached_){
        if( 0<=x && x<=31 && 0<=y && y<=31){
            if(reached_ == true) reached[x] |= (0x01 << y);
            else reached[x] &= reached[x] &= ~(0x01 << y);
        }
    };


    Wall readWall(uint16_t x, uint16_t y) {
        Wall wall;
        //壁情報の配列番号に変換
        uint8_t v_left = x-1;
        uint8_t v_right = x;
        uint8_t h_up = y;
        uint8_t h_down = y-1;
        //壁番号が範囲外の場合は外周の壁
        wall.E = v_right != 31 ? ((walls_vertical[v_right] >>y )& 1) : 1;
        wall.N = h_up != 31 ? ((walls_horizontal[h_up] >>x )& 1) : 1;
        wall.W = v_left != -1 ? ((walls_vertical[v_left] >>y )& 1) : 1;
        wall.S = h_down != -1 ? ((walls_horizontal[h_down]>>x )& 1) : 1;
        wall.EF = isReached(x, y) || isReached(x+1, y );
        wall.NF = isReached(x, y) || isReached(x , y+1);
        wall.WF = isReached(x, y) || isReached(x-1, y );
        wall.SF = isReached(x, y) || isReached(x , y-1);

        return wall;
    };

    void writeWall(uint16_t x, uint16_t y, Wall wall){
        //壁情報の配列番号に変換
        uint8_t v_left = x-1;
        uint8_t v_right = x;
        uint8_t h_up = y;
        uint8_t h_down = y-1;
        //壁情報を書き込み
        if(v_right != 31) {
            if(wall.E == 1)walls_vertical[v_right] |= (1 << y);
            else walls_vertical[v_right] &= (~(1 << y));
        }
        if(h_up != 31) {
            if(wall.N == 1)walls_horizontal[h_up] |= (1 << x);
            else walls_horizontal[h_up] &= (~(1 << x));
        }
        if(v_left != -1) {
            if(wall.W == 1)walls_vertical[v_left] |= (1 << y);
            else walls_vertical[v_left] &= (~(1 << y));
        }
        if(h_down != -1) {
            if(wall.S == 1)walls_horizontal[h_down] |= (1 << x);
            else walls_horizontal[h_down] &= (~(1 << x));
        }
    };

    void initWall() {
        for(int x=0;x<32;x++) {
            for(int y=0;y<32;y++) {
                Wall wall;
                wall.setByUint8(0);
                writeWall(x,y,wall);
            }
        }
    };

    // return 1:  探索済みの区画に来て、現在の迷路情報と減税の壁情報が一致
    // return 0:  未探索の区画に現在の壁情報を書き込み
    // return -1: 探索済みの区画に来たが、現在の迷路情報と現在の壁情報が矛盾
    uint8_t updateWall(uint16_t x, uint16_t y, direction_e dir, WallSensor& ws){

        /////////////探索済み区画に来た時//////////////////
        if(isReached(x,y) == true){
            switch(dir){
                case E:
                    if(readWall(x,y).E != ws.isAhead() ||
                       readWall(x,y).N != ws.isLeft()  ||
                       readWall(x,y).S != ws.isRight()) return -1;
                    break;
                case N:
                    if(readWall(x,y).E != ws.isRight() ||
                       readWall(x,y).N != ws.isAhead() ||
                       readWall(x,y).W != ws.isLeft()) return -1;
                    break;
                case W:
                    if(readWall(x,y).S != ws.isLeft()  ||
                       readWall(x,y).N != ws.isRight() ||
                       readWall(x,y).W != ws.isAhead()) return -1;
                    break;
                case S:
                    if(readWall(x,y).E != ws.isLeft()  ||
                       readWall(x,y).S != ws.isAhead() ||
                       readWall(x,y).W != ws.isRight()) return -1;
                    break;

            }
            return 0;
        }
        ///////////未探索区画に来た時//////////
        else{
            writeReached(x,y,true);
            Wall wall = readWall(x,y);
            switch(dir){
                case  E:  //まうすは東向き
                    wall.S = ws.isRight();
                    wall.E = ws.isAhead();
                    wall.N = ws.isLeft();
                    break;
                case  N:  //まうすは北向き
                    wall.E = ws.isRight();
                    wall.N = ws.isAhead();
                    wall.W = ws.isLeft();
                    break;
                case  W:  //まうすは西向き
                    wall.N = ws.isRight();
                    wall.W = ws.isAhead();
                    wall.S = ws.isLeft();
                    break;
                case  S:  //まうすは南向き
                    wall.W = ws.isRight();
                    wall.S = ws.isAhead();
                    wall.E = ws.isLeft();
                    break;
            }
            writeWall(x, y, wall);
            return 1;
        } //end else
    }

    direction_e getMinDirection(uint16_t x, uint16_t y, direction_e dir){
        uint16_t potential_E = 0xff;
        uint16_t potential_N = 0xff;
        uint16_t potential_W = 0xff;
        uint16_t potential_S = 0xff;

        Wall wall = readWall(x,y);
        if(wall.E == 0 && wall.EF == 1 && x != 31)potential_E = p_map[x+1][y];
        if(wall.N == 0 && wall.NF == 1 && x != 31)potential_N = p_map[x][y+1];
        if(wall.W == 0 && wall.WF == 1 && x != 0)potential_W = p_map[x-1][y];
        if(wall.S == 0 && wall.SF == 1 && y != 0)potential_S = p_map[x][y-1];
        uint16_t potential_min = MIN4( potential_E, potential_N, potential_W, potential_S );

        //直進有線にしている
        if( (potential_min == potential_E) && (dir == E) )  return E;
        if( (potential_min == potential_N) && (dir == N) )  return N;
        if( (potential_min == potential_W) && (dir == W) )  return W;
        if( (potential_min == potential_S) && (dir == S) )  return S;
        if(potential_min == potential_E) return E;
        if(potential_min == potential_N) return N;
        if(potential_min == potential_W) return W;
        if(potential_min == potential_S) return S;
    };

    uint8_t get_unknown_direction(uint16_t x, uint16_t y, direction_e dir){
        uint8_t ran_judge_E = 0;
        uint8_t ran_judge_N = 0;
        uint8_t ran_judge_W = 0;
        uint8_t ran_judge_S = 0;

        Wall wall = readWall(x,y);
        if( (x != 31) && (isReached(x+1,y) == false) && (wall.E == 0) ){
              ran_judge_E = 1;
        }
        if( (y != 31) && (isReached(x,y+1) == false) && (wall.N == 0) ){
              ran_judge_N = 1;
        }
        if( (x != 0) && (isReached(x-1,y) == false) && (wall.W == 0) ){
              ran_judge_W = 1;
        }
        if( (y != 0) && (isReached(x,y-1) == false) && (wall.S == 0)){
              ran_judge_S = 1;
        }

        if( (ran_judge_E == 1) && (dir == E) )  return 0;
        if( (ran_judge_N == 1) && (dir == N) )  return 2;
        if( (ran_judge_W == 1) && (dir == W) )  return 4;
        if( (ran_judge_S == 1) && (dir == S) )  return 6;

        if(ran_judge_E == 1) return 0;
        if(ran_judge_N == 1) return 2;
        if(ran_judge_W == 1) return 4;
        if(ran_judge_S == 1) return 6;

        return 255;
    }

    void makeSearchMap(uint16_t x, uint16_t y){
        std::queue<pair<uint16_t, uint16_t>> que;

        //歩数マップの初期化
        for(uint8_t i=0;i<32;i++){
             for(uint8_t j=0;j<32;j++){
                 p_map[i][j] = 0xff;
             }
        }
        p_map[x][y] = 0; //目的地のテンシャルは0

        que.push(std::make_pair(x,y));
        while(que.empty() == false){
            x = que.front().first;
            y = que.front().second;
            Wall wall = readWall((uint16_t)(que.front().first), (uint16_t)(que.front().second));
            que.pop();
            if( (wall.E == 0) && (x != 31) && (p_map[x+1][y] == 0xff) ){
                 p_map[x+1][y] = p_map[x][y] + 1;
                 que.push(std::make_pair(x+1,y));
            }
            if( (wall.N == 0 ) && (y != 31) && (p_map[x][y+1] == 0xff) ){
                 p_map[x][y+1] = p_map[x][y] + 1;
                 que.push(std::make_pair(x,y+1));
            }
            if( (wall.W == 0) && (x != 0) && (p_map[x-1][y] == 0xff) ){
                 p_map[x-1][y] = p_map[x][y] + 1;
                 que.push(std::make_pair(x-1,y));
            }
            if( (wall.S == 0) && (y != 0) && (p_map[x][y-1] == 0xff) ){
                 p_map[x][y-1] = p_map[x][y] + 1;
                 que.push(std::make_pair(x,y-1));
            }
        }

    };
    void makeSecondarySerchMap(uint16_t x, uint16_t y);
    void makeFastestMap(uint16_t x, uint16_t y);
    void watchPotentialMap(void){
        /////////////////////////////
        for(int j=15;j>=0;j--){
            for(int i=0;i<16;i++){
               //////1桁//////////
               if(p_map[i][j]< 10){
                 if(i==0){
                     printfAsync("%x  %d    ",j, p_map[i][j]);
                 }
                 else if(i==15){
                     printfAsync("%d\n",p_map[i][j]);
                 }
                 else{
                     printfAsync("%d    ",p_map[i][j]);
                 }
               }
               /////2桁//////////
               if( (p_map[i][j] > 9) && (p_map[i][j] < 99) ){
                 if(i==0){
                     printfAsync("%x  %d   ",j, p_map[i][j]);
                 }
                 else if(i==15){
                     printfAsync("%d\n",p_map[i][j]);
                 }
                 else{
                     printfAsync("%d   ",p_map[i][j]);
                 }
               }
               /////3桁//////////
               if(p_map[i][j] > 100){
                 if(i==0){
                     printfAsync("%x  %d  ",j, p_map[i][j]);
                 }
                 else if(i==15){
                     printfAsync("%d\n",p_map[i][j]);
                 }
                 else{
                     printfAsync("%d  ",p_map[i][j]);
                 }
               }


            }
        }
        printfAsync("\n   0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f   \n");
    }



};

