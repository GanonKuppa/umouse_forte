#ifndef MAZE_H
#define MAZE_H

#include "stdint.h"


class Wall{

public:
	uint8_t E  :1;                //壁情報
    uint8_t N  :1;
    uint8_t W  :1;
    uint8_t S  :1;
    uint8_t EF :1;                //壁を読んだかのフラグ
    uint8_t NF :1;
    uint8_t WF :1;
    uint8_t SF :1;

    void setByUint8(uint8_t wall){
    	E  = ((wall >> 0) & 0x01);
		N  = ((wall >> 1) & 0x01);
    	W  = ((wall >> 2) & 0x01);
		S  = ((wall >> 3) & 0x01);

		EF = ((wall >> 4) & 0x01);
		NF = ((wall >> 5) & 0x01);
		WF = ((wall >> 6) & 0x01);
		SF = ((wall >> 7) & 0x01);
    }
};


class Maze{

public:
	uint32_t walls_vertical[31];
	uint32_t walls_horizontal[31];
	uint32_t reached[32];


	bool isReached(uint16_t x, uint16_t y){
		bool reach;
		if( 0<=x && x<=31 &&  0<=y && y<=31) reach =(reached[x] >> y) & 0x00000001;
		else reach = 1;
		return reach;
	};
	Wall readWall(uint16_t x, uint16_t y){
		Wall wall;
		//壁情報の配列番号に変換
		uint8_t v_left  = x-1;
		uint8_t v_right = x;
		uint8_t h_up    = y;
		uint8_t h_down  = y-1;
		//壁番号が範囲外の場合は外周の壁
		wall.E  = v_right != 31 ? ((walls_vertical[v_right] >>y )& 1) : 1;
		wall.N  = h_up    != 31 ? ((walls_horizontal[h_up]  >>x )& 1) : 1;
		wall.W  = v_left  != -1 ? ((walls_vertical[v_left]  >>y )& 1) : 1;
		wall.S  = h_down  != -1 ? ((walls_horizontal[h_down]>>x )& 1) : 1;
		wall.EF = isReached(x, y) || isReached(x+1, y  );
		wall.NF = isReached(x, y) || isReached(x  , y+1);
		wall.WF = isReached(x, y) || isReached(x-1, y  );
		wall.SF = isReached(x, y) || isReached(x  , y-1);

		return wall;
	};

	void writeWall(uint16_t x, uint16_t y, Wall wall){
		//壁情報の配列番号に変換
		uint8_t v_left  = x-1;
		uint8_t v_right = x;
		uint8_t h_up    = y;
		uint8_t h_down  = y-1;
		//壁情報を書き込み
		if(v_right != 31){
			if(wall.E == 1)walls_vertical[v_right]  |= (1 << y);
			else           walls_vertical[v_right]  &= (~(1 << y));
		}
		if(h_up    != 31){
			if(wall.N == 1)walls_horizontal[h_up]   |= (1 << x);
			else           walls_horizontal[h_up]   &= (~(1 << x));
		}
		if(v_left  != -1){
			if(wall.W == 1)walls_vertical[v_left]   |= (1 << y);
			else           walls_vertical[v_left]   &= (~(1 << y));
		}
		if(h_down  != -1){
			if(wall.S == 1)walls_horizontal[h_down] |= (1 << x);
			else           walls_horizontal[h_down] &= (~(1 << x));
		}
	};

	void initWall(){
		for(int x=0;x<32;x++){
			for(int y=0;y<32;y++){
				Wall wall;
				wall.setByUint8(0);
				writeWall(x,y,wall);
			}
		}
	}

};

#endif
