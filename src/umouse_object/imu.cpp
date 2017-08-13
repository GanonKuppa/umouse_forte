
#include <imu.hpp>
#include <stdint.h>
#include <uart.h>
#include "spi.h"
#include "iodefine.h"
#include "timer.h"
#include "myUtil.h"
#include <deque>

static const uint8_t MPU9250_REG_WHOAMI   = 0x75;
static const uint8_t ICM20608G_REG_WHOAMI = 0x75;

//https://developer.mbed.org/users/kylongmu/code/MPU9250_SPI/file/084e8ba240c1/MPU9250.cpp
//https://github.com/fenrir-naru/ninja-scan-light/blob/master/firmware/mpu9250.c

using std::deque;



uint8_t MPU9250::whoAmI(void){
	return readReg(MPU9250_REG_WHOAMI);
}

void MPU9250::writeReg(uint8_t adress, uint8_t data){
	uint8_t sendBuf[2];
	uint8_t recvBuf[2];

	sendBuf[0] = adress;
	sendBuf[1] = data;
	communicateNbyteRSPI1(sendBuf, recvBuf, 2);
}

uint8_t MPU9250::readReg(uint8_t adress){
	uint8_t sendBuf[2];
	uint8_t recvBuf[2];

	sendBuf[0] = READ_FLAG | adress;
	sendBuf[1] = 0x00;
	communicateNbyteRSPI1(sendBuf, recvBuf, 2);
	return recvBuf[1];
}



void MPU9250::init(){

	writeReg(MPUREG_PWR_MGMT_1,0x80);
	waitmsec(10);
	writeReg(MPUREG_PWR_MGMT_1,0x00);
	waitmsec(10);
	writeReg(MPUREG_PWR_MGMT_2,0x00);
	waitmsec(10);

	//55 INT Pin / Bypass Enable Configuration
	//writeReg(0x37, 0x02);
	//waitmsec(10);


	//Register 26 – Configuration
	//writeReg(0x1A, 0x07);
	//waitmsec(10);
	//Register 26 – Configuration
	writeReg(0x1A, 0x04);
	waitmsec(10);

	//range gyro
	writeReg(0x1B, 0b00011000);
	waitmsec(10);

	//range acc
	writeReg(0x1C, 0x00); //-2g to 2g
	waitmsec(10);

    //lpf acc
    writeReg(0x1D, 0x0C); //LPC  20Hz
    waitmsec(10);


	waitmsec(10);
	//書き込み時と読み出し時でSPIの通信速度が異なる
	RSPI1.SPBR = 1;

}

void MPU9250::update(){

	uint8_t accel_xout_h = readReg(0x3b);
	uint8_t accel_xout_l = readReg(0x3c);

	uint8_t accel_yout_h = readReg(0x3d);
	uint8_t accel_yout_l = readReg(0x3e);

	uint8_t accel_zout_h = readReg(0x3f);
	uint8_t accel_zout_l = readReg(0x40);

	uint8_t temp_out_h   = readReg(0x41);
	uint8_t temp_out_l   = readReg(0x42);

	uint8_t gyro_xout_h  = readReg(0x43);
	uint8_t gyro_xout_l  = readReg(0x44);

	uint8_t gyro_yout_h  = readReg(0x45);
	uint8_t gyro_yout_l  = readReg(0x46);

	uint8_t gyro_zout_h  = readReg(0x47);
	uint8_t gyro_zout_l  = readReg(0x48);

	acc_raw[0] =  concatenate2Byte_int(accel_xout_h, accel_xout_l);
	acc_raw[1] =  concatenate2Byte_int(accel_yout_h, accel_yout_l);
	acc_raw[2] = - concatenate2Byte_int(accel_zout_h, accel_zout_l);

	omega_raw[0] = - concatenate2Byte_int(gyro_xout_h, gyro_xout_l);
	omega_raw[1] = - concatenate2Byte_int(gyro_yout_h, gyro_yout_l);
	omega_raw[2] = - concatenate2Byte_int(gyro_zout_h, gyro_zout_l);


	//mag_row[];
	temp_raw = concatenate2Byte_int(temp_out_h, temp_out_l);
	for(int i=0;i<3;i++){
		omega_c[i] = omega_raw[i] - omega_ref[i];
		omega_f[i] = omega_c[i] *MPU9250G_2000dps;
		acc_c[i] = acc_raw[i] - acc_ref[i];
		float temp = acc_c[i] * MPU9250A_2g * 9.8;
		acc_f[i] = 0.3 * acc_f[i] + 0.7 *temp;
	}

	//z軸の値にローパスフィルタをかけてみる
/*
	static std::deque<float> vec(10,0.0);
	vec.push_back(float(omega_f[2]));
	vec.pop_front();
	float max = vec[0];
	float min = vec[0];
	for(int i=1;i<10;i++){
	    if(vec[i] < min) min = vec[i];
	    if(vec[i] > max) max = vec[i];
	}

	float low_pass = 0.0;
	low_pass = (vec[0] + vec[1] + vec[2] + vec[3] + vec[4]+
                vec[5] + vec[6] + vec[7] + vec[8] + vec[9]
                - min -max                                )*0.125;
	omega_f[2] = low_pass;
*/
	/*
	static std::deque<float> vec_acc0(40,0.0);
    vec_acc0.push_back(float(acc_f[0]));
    vec_acc0.pop_front();

    float low_pass_acc0 = 0.0;
    for(int i=0;i<40;i++){
        low_pass_acc0 += vec_acc0[i];
    }
    low_pass_acc0 = low_pass_acc0/40.0;
    acc_f[0] = low_pass_acc0;


    static std::deque<float> vec_acc1(40,0.0);
    vec_acc1.push_back(float(acc_f[1]));
    vec_acc1.pop_front();
    float low_pass_acc1 = 0.0;
    for(int i=0;i<40;i++){
        low_pass_acc1 += vec_acc1[i];
    }
    low_pass_acc1 = low_pass_acc1/40.0;

    acc_f[1] = low_pass_acc1;
*/


}

/**
 * ジャイロオフセット設定用関数<br>
 * 静止状態でNUM_REF回のサンプルを取り, そのデータの上位25%と下位25%の値を
 * クイックソートによって取り除く残りの50%で平均値を求めオフセットとする.(メディアンフィルタと平均の組み合わせ)
 *
 */
void  MPU9250::calibOmegaOffset(uint32_t ref_num)
{
	uint32_t i = 0;


	int16_t omega_x[ref_num];
	int16_t omega_y[ref_num];
	int16_t omega_z[ref_num];

	float omega_x_sum = 0.0;
	float omega_y_sum = 0.0;
	float omega_z_sum = 0.0;

	for(uint32_t i=0;i<3;i++)
	{
		omega_ref[i] = 0;
	}

	for(uint32_t i=0;i<ref_num;i++)
	{
		omega_x[i] = omega_raw[0];
		omega_y[i] = omega_raw[1];
		omega_z[i] = omega_raw[2];
		waitusec(500);
		//myprintf3("%d| calibrating... %d, %d, %d\n",i,omega_x[i],omega_y[i],omega_z[i] );
	}
	quickSort_int16(omega_x,0 ,ref_num -1);
	quickSort_int16(omega_y,0 ,ref_num -1);
	quickSort_int16(omega_z,0 ,ref_num -1);

	for(i=ref_num/4;i<(ref_num*3/4 +1) ;i++)
	{
		omega_x_sum += (float)(omega_x[i]);
		omega_y_sum += (float)(omega_y[i]);
		omega_z_sum += (float)(omega_z[i]);
	}
	omega_ref[0] = (int16_t)(omega_x_sum/(float)ref_num *2.0);
	omega_ref[1] = (int16_t)(omega_y_sum/(float)ref_num *2.0);
	omega_ref[2] = (int16_t)(omega_z_sum/(float)ref_num *2.0);

	//writeEEPROMOffsetOmegaInt(&omega_offset_vec[0]);
	myprintf3("====mpu9250======\n gyro offset %d, %d, %d\n",omega_ref[0],omega_ref[1],omega_ref[2] );
}

void  MPU9250::calibAccOffset(uint32_t ref_num)
{
    uint32_t i = 0;


    int16_t acc_x[ref_num];
    int16_t acc_y[ref_num];
    int16_t acc_z[ref_num];

    float acc_x_sum = 0.0;
    float acc_y_sum = 0.0;
    float acc_z_sum = 0.0;

    for(uint32_t i=0;i<3;i++)
    {
        acc_ref[i] = 0;
    }

    for(uint32_t i=0;i<ref_num;i++)
    {
        acc_x[i] = acc_raw[0];
        acc_y[i] = acc_raw[1];
        acc_z[i] = acc_raw[2];
        waitusec(500);
        //myprintf3("%d| calibrating... %d, %d, %d\n",i,acc_x[i],acc_y[i],acc_z[i] );
    }
    quickSort_int16(acc_x,0 ,ref_num -1);
    quickSort_int16(acc_y,0 ,ref_num -1);
    quickSort_int16(acc_z,0 ,ref_num -1);

    for(i=ref_num/4;i<(ref_num*3/4 +1) ;i++)
    {
        acc_x_sum += (float)(acc_x[i]);
        acc_y_sum += (float)(acc_y[i]);
        acc_z_sum += (float)(acc_z[i]);
    }
    acc_ref[0] = (int16_t)(acc_x_sum/(float)ref_num *2.0);
    acc_ref[1] = (int16_t)(acc_y_sum/(float)ref_num *2.0);
    acc_ref[2] = (int16_t)(acc_z_sum/(float)ref_num *2.0);

    //writeEEPROMOffsetOmegaInt(&omega_offset_vec[0]);
    myprintf3("====mpu9250======\n acc offset %d, %d, %d\n",acc_ref[0],acc_ref[1],acc_ref[2] );
}





uint8_t Icm20608G::whoAmI(void){
	return readReg(ICM20608G_REG_WHOAMI);
}

void Icm20608G::writeReg(uint8_t adress, uint8_t data){
	uint8_t sendBuf[2];
	uint8_t recvBuf[2];

	sendBuf[0] = adress;
	sendBuf[1] = data;
	communicateNbyteRSPI0(sendBuf, recvBuf, 2);
}

uint8_t Icm20608G::readReg(uint8_t adress){
	uint8_t sendBuf[2];
	uint8_t recvBuf[2];

	sendBuf[0] = READ_FLAG | adress;
	sendBuf[1] = 0x00;
	communicateNbyteRSPI0(sendBuf, recvBuf, 2);
	return recvBuf[1];
}



void Icm20608G::init(){

	writeReg(MPUREG_PWR_MGMT_1,0x80);
	waitmsec(10);
	writeReg(MPUREG_PWR_MGMT_1,0x00);
	waitmsec(10);
	writeReg(MPUREG_PWR_MGMT_2,0x00);
	waitmsec(10);

	//55 INT Pin / Bypass Enable Configuration
	//writeReg(0x37, 0x02);
	//waitmsec(10);

	//Register 26 – Configuration
	//communicateNbyteRSPI1(0x1A, 0x01);
	//waitmsec(10);

	//range gyro
	writeReg(0x1B, 0x18);
	waitmsec(10);

	//range acc
	writeReg(0x1C, 0x18);
	waitmsec(10);

	uint8_t dummy1,dummy2;
	setEnableRSPI0(1);
	dummy1 = communicate8bitRSPI0(READ_FLAG|0x1c);
	dummy2 = communicate8bitRSPI0(0x00);
	setEnableRSPI0(0);
	//myprintf3("0x1c: %x %x \n\n",dummy1, dummy2);
	waitmsec(10);
	//書き込み時と読み出し時でSPIの通信速度が異なる
	//RSPI0.SPBR = 1;

}

void Icm20608G::update(){

	uint8_t accel_xout_h = readReg(0x3b);
	uint8_t accel_xout_l = readReg(0x3c);

	uint8_t accel_yout_h = readReg(0x3d);
	uint8_t accel_yout_l = readReg(0x3e);

	uint8_t accel_zout_h = readReg(0x3f);
	uint8_t accel_zout_l = readReg(0x40);

	uint8_t temp_out_h   = readReg(0x41);
	uint8_t temp_out_l   = readReg(0x42);

	uint8_t gyro_xout_h  = readReg(0x43);
	uint8_t gyro_xout_l  = readReg(0x44);

	uint8_t gyro_yout_h  = readReg(0x45);
	uint8_t gyro_yout_l  = readReg(0x46);
	uint8_t gyro_zout_h  = readReg(0x47);
	uint8_t gyro_zout_l  = readReg(0x48);
	acc_raw[0] = - concatenate2Byte_int(accel_xout_h, accel_xout_l);
	acc_raw[1] = - concatenate2Byte_int(accel_yout_h, accel_yout_l);
	acc_raw[2] = - concatenate2Byte_int(accel_zout_h, accel_zout_l);

	omega_raw[0] = concatenate2Byte_int(gyro_xout_h, gyro_xout_l);
	omega_raw[1] = concatenate2Byte_int(gyro_yout_h, gyro_yout_l);
	omega_raw[2] = concatenate2Byte_int(gyro_zout_h, gyro_zout_l);


	//mag_row[];
	temp_raw = concatenate2Byte_int(temp_out_h, temp_out_l);
	for(int i=0;i<3;i++){
		omega_c[i] = omega_raw[i] - omega_ref[i];
		omega_f[i] = omega_c[i] *MPU9250G_2000dps;
	}
}




/**
 * ジャイロオフセット設定用関数<br>
 * 静止状態でNUM_REF回のサンプルを取り, そのデータの上位25%と下位25%の値を
 * クイックソートによって取り除く残りの50%で平均値を求めオフセットとする.(メディアンフィルタと平均の組み合わせ)
 *
 */
void  Icm20608G::calibOmegaOffset()
{
	uint32_t i = 0;
	uint32_t ref_num = 400;

	int16_t omega_x[400];
	int16_t omega_y[400];
	int16_t omega_z[400];

	float omega_x_sum = 0.0;
	float omega_y_sum = 0.0;
	float omega_z_sum = 0.0;

	for(uint32_t i=0;i<3;i++)
	{
		omega_ref[i] = 0;
	}

	for(uint32_t i=0;i<ref_num;i++)
	{
//		update();
		omega_x[i] = omega_raw[0];
		omega_y[i] = omega_raw[1];
		omega_z[i] = omega_raw[2];
		waitmsec(5);
		myprintf3("%d| calibrating... %d, %d, %d\n",i,omega_x[i],omega_y[i],omega_z[i] );
		//myprintf3("%d\n",i);
	}
	quickSort_int16(omega_x,0 ,ref_num -1);
	quickSort_int16(omega_y,0 ,ref_num -1);
	quickSort_int16(omega_z,0 ,ref_num -1);

	for(i=ref_num/4;i<(ref_num*3/4 +1) ;i++)
	{
		omega_x_sum += (float)(omega_x[i]);
		omega_y_sum += (float)(omega_y[i]);
		omega_z_sum += (float)(omega_z[i]);
	}
	omega_ref[0] = (int16_t)(2.0*omega_x_sum/(float)ref_num);
	omega_ref[1] = (int16_t)(2.0*omega_y_sum/(float)ref_num);
	omega_ref[2] = (int16_t)(2.0*omega_z_sum/(float)ref_num);

	//writeEEPROMOffsetOmegaInt(&omega_offset_vec[0]);
	myprintf3("=====icm20608g=====\n gyro offset %d, %d, %d\n",omega_ref[0],omega_ref[1],omega_ref[2] );
}














