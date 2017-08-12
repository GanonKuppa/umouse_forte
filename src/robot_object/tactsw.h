#ifndef TACTSW_H
#define TACTSW_H

#include "iodefine.h"
#include "stdint.h"

class TactSw{
private:
	uint16_t on_time_msec;
    TactSw(){on_time_msec = 0;};
    TactSw(TactSw&){on_time_msec = 0;};
    ~TactSw(){};

public:
	bool getState(){
		if( on_time_msec >5) return true;
		else return false;
	};

	uint16_t getOntime(){
		return on_time_msec;
	};

	void update(){
		if(PORTE.PIDR.BIT.B3 == 0)on_time_msec++;
		else on_time_msec = 0;
	}

	static TactSw& getInstance(){
		static TactSw instance;
		return instance;
	}




};

#endif
