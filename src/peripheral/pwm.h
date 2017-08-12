#ifndef PWM_H
#define PWM_H

void initMTU3();
void initMTU4();
void setDutyMTU3(float duty);
void setDutyMTU4(float duty);
float getDutyMTU3();
float getDutyMTU4();
//void setFreq(uint16_t freq);
#endif
