
const uint16_t famima_u[][2] ={
	{nR,l______l},
	{nFS6,lE},
	{nD6,lE},
	{nA5,lE},
	{nD6,lE},
	{nE6,lE},
	{nA6,lQd},
	{nR,l______l},
	{nE6,lE},
	{nFS6,lE},
	{nE6,lE},
	{nA5,lE},
	{nD6,lH},
	{nR,l______l}
};

const uint16_t famima_l[][2] ={
	{nR,l______l},
	{nR,lQ},
	{nFS5,lQ},
	{nCS6,lQd},
	{nA5,lE},
	{nR,l______l},
	{nA5,lQ},
	{nA5,lE},
	{nA5,lE},
	{nFS5,lH},
	{nR,l______l}
};

const uint16_t famimaMinor_u[][2] ={
	{nR,l______l},
	{nF6,lE},
	{nD6,lE},
	{nA5,lE},
	{nD6,lE},
	{nE6,lE},
	{nA6,lQd},
	{nR,l______l},
	{nE6,lE},
	{nF6,lE},
	{nE6,lE},
	{nA5,lE},
	{nD6,lH},
	{nR,l______l}
};

const uint16_t famimaMinor_l[][2] ={
	{nR,l______l},
	{nR,lQ},
	{nF5,lQ},
	{nCS6,lQd},
	{nA5,lE},
	{nR,l______l},
	{nA5,lQ},
	{nA5,lE},
	{nA5,lE},
	{nFS5,lH},
	{nR,l______l}
};

const uint16_t GB1[][2] ={
	{nR,l______l},
	{nC6,lS},
	{nC7,lH},
	{nR,l______l}
};

const uint16_t SEA1[][2] ={
	{nR,l______l},
	{nB7,lS},
	{nR,lS},
	{nR,l______l}
};

const uint16_t SEB1[][2] ={
	{nR,l______l},
	{nBF7,lS},
	{nR,lS},
	{nR,l______l}
};

const uint16_t SEC1[][2] ={
	{nR,l______l},
	{nB5,lS},
	{nR,lS},
	{nR,l______l}
};





void GB(void){
	Note note;
	SEM.enable=false;
	SEM.clearBuff();
	SEM.wave_form_data[6] = SANKAKU;
	SEM.wave_form_data[7] = SANKAKU;
	SEM.wave_volume_data[6] = 16;    //各トラックのボリューム  volume_resolution段階
	SEM.wave_volume_data[7] = 16;
	SEM.bpm = 120;
	uint16_t len1 = sizeof(GB1)/sizeof(GB1[0]);
	for(int i=0;i<len1;i++){
		note.pitch = GB1[i][0];
		note.len = GB1[i][1];
		SEM.noteBuff[6].push(note);
	}
	SEM.enable=true;
}

void SEA(void){
	Note note;
	SEM.enable=false;
	SEM.clearBuff();
	SEM.wave_form_data[6] = SANKAKU;
	SEM.wave_form_data[7] = SANKAKU;
	SEM.wave_volume_data[6] = 16;    //各トラックのボリューム  volume_resolution段階
	SEM.wave_volume_data[7] = 16;
	SEM.bpm = 120;
	uint16_t len1 = sizeof(SEA1)/sizeof(SEA1[0]);
	for(int i=0;i<len1;i++){
		note.pitch = SEA1[i][0];
		note.len = SEA1[i][1];
		SEM.noteBuff[6].push(note);
	}
	SEM.enable=true;
}


void SEB(void){
	Note note;
	SEM.enable=false;
	SEM.clearBuff();
	SEM.wave_form_data[6] = SANKAKU;
	SEM.wave_form_data[7] = SANKAKU;
	SEM.wave_volume_data[6] = 16;    //各トラックのボリューム  volume_resolution段階
	SEM.wave_volume_data[7] = 16;
	SEM.bpm = 120;
	uint16_t len1 = sizeof(SEB1)/sizeof(SEB1[0]);
	for(int i=0;i<len1;i++){
		note.pitch = SEB1[i][0];
		note.len = SEB1[i][1];
		SEM.noteBuff[6].push(note);
	}
	SEM.enable=true;
}

void SEC(void){
	Note note;
	SEM.enable=false;
	SEM.clearBuff();
	SEM.wave_form_data[6] = SANKAKU;
	SEM.wave_form_data[7] = SANKAKU;
	SEM.wave_volume_data[6] = 16;    //各トラックのボリューム  volume_resolution段階
	SEM.wave_volume_data[7] = 16;
	SEM.bpm = 120;
	uint16_t len1 = sizeof(SEC1)/sizeof(SEC1[0]);
	for(int i=0;i<len1;i++){
		note.pitch = SEC1[i][0];
		note.len = SEC1[i][1];
		SEM.noteBuff[6].push(note);
	}
	SEM.enable=true;
}






void famima(void){
	Note note;
	SEM.enable=false;
	SEM.clearBuff();
	SEM.wave_form_data[6] = SANKAKU;
	SEM.wave_form_data[7] = SANKAKU;
	SEM.wave_volume_data[6] = 16;    //各トラックのボリューム  volume_resolution段階
	SEM.wave_volume_data[7] = 16;
	SEM.bpm = 80;
	uint16_t len1 = sizeof(famima_u)/sizeof(famima_u[0]);
	for(int i=0;i<len1;i++){
		note.pitch = famima_u[i][0];
		note.len = famima_u[i][1];
		SEM.noteBuff[6].push(note);
	}
	uint16_t len2 = sizeof(famima_l)/sizeof(famima_l[0]);
	for(int i=0;i<len2;i++){
		note.pitch = famima_l[i][0];
		note.len = famima_l[i][1];
		SEM.noteBuff[7].push(note);
	}
	SEM.enable=true;

}

void famimaMinor(void){
	Note note;

	SEM.enable=false;
	SEM.clearBuff();
	SEM.wave_form_data[6] = SANKAKU;
	SEM.wave_form_data[7] = SANKAKU;
	SEM.wave_volume_data[6] = 16;    //各トラックのボリューム  volume_resolution段階
	SEM.wave_volume_data[7] = 16;
	SEM.bpm = 80;
	uint16_t len1 = sizeof(famimaMinor_u)/sizeof(famimaMinor_u[0]);
	for(int i=0;i<len1;i++){
		note.pitch = famimaMinor_u[i][0];
		note.len = famimaMinor_u[i][1];
		SEM.noteBuff[6].push(note);
	}
	uint16_t len2 = sizeof(famimaMinor_l)/sizeof(famimaMinor_l[0]);

	for(int i=0;i<len2;i++){
		note.pitch = famimaMinor_l[i][0];
		note.len = famimaMinor_l[i][1];
		SEM.noteBuff[7].push(note);
	}
	SEM.enable=false;

}


#include "myUtil.h"
void randomNote(uint16_t seed){
	Note note;

	SEM.enable=false;
	SEM.clearBuff();
	SEM.wave_form_data[6] = SANKAKU;
	SEM.wave_volume_data[6] = 16;    //各トラックのボリューム  volume_resolution段階
	SEM.bpm = 80;

	note.pitch = 72 + ((seed * xor32() ) %24);
	note.len = lS;
	SEM.noteBuff[6].push(note);

	note.pitch = 72 + ((seed * xor32() ) %24);
	note.len = lS;
	SEM.noteBuff[6].push(note);
	SEM.enable=true;

}
