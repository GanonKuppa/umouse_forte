################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\src/umouse_object/imu.cpp \
..\src/umouse_object/maze.cpp \
..\src/umouse_object/mpu9250_spi.cpp \
..\src/umouse_object/sound.cpp \
..\src/umouse_object/sound__.cpp 

OBJS += \
./src/umouse_object/imu.o \
./src/umouse_object/maze.o \
./src/umouse_object/mpu9250_spi.o \
./src/umouse_object/sound.o \
./src/umouse_object/sound__.o 

CPP_DEPS += \
./src/umouse_object/imu.d \
./src/umouse_object/maze.d \
./src/umouse_object/mpu9250_spi.d \
./src/umouse_object/sound.d \
./src/umouse_object/sound__.d 


# Each subdirectory must supply rules for building sources it contributes
src/umouse_object/imu.o: ../src/umouse_object/imu.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/umouse_object/imu.d" -MT"src/umouse_object/imu.o" -MT"src/umouse_object/imu.d" @"src/umouse_object/imu.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/umouse_object/imu.d" -MT"src/umouse_object/imu.o" -MT"src/umouse_object/imu.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/umouse_object/imu.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/umouse_object/maze.o: ../src/umouse_object/maze.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/umouse_object/maze.d" -MT"src/umouse_object/maze.o" -MT"src/umouse_object/maze.d" @"src/umouse_object/maze.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/umouse_object/maze.d" -MT"src/umouse_object/maze.o" -MT"src/umouse_object/maze.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/umouse_object/maze.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/umouse_object/mpu9250_spi.o: ../src/umouse_object/mpu9250_spi.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/umouse_object/mpu9250_spi.d" -MT"src/umouse_object/mpu9250_spi.o" -MT"src/umouse_object/mpu9250_spi.d" @"src/umouse_object/mpu9250_spi.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/umouse_object/mpu9250_spi.d" -MT"src/umouse_object/mpu9250_spi.o" -MT"src/umouse_object/mpu9250_spi.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/umouse_object/mpu9250_spi.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/umouse_object/sound.o: ../src/umouse_object/sound.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/umouse_object/sound.d" -MT"src/umouse_object/sound.o" -MT"src/umouse_object/sound.d" @"src/umouse_object/sound.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/umouse_object/sound.d" -MT"src/umouse_object/sound.o" -MT"src/umouse_object/sound.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/umouse_object/sound.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/umouse_object/sound__.o: ../src/umouse_object/sound__.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/umouse_object/sound__.d" -MT"src/umouse_object/sound__.o" -MT"src/umouse_object/sound__.d" @"src/umouse_object/sound__.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/umouse_object/sound__.d" -MT"src/umouse_object/sound__.o" -MT"src/umouse_object/sound__.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/umouse_object/sound__.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

