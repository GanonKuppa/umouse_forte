################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\src/peripheral/ad.cpp \
..\src/peripheral/clock.cpp \
..\src/peripheral/da.cpp \
..\src/peripheral/gpio.cpp \
..\src/peripheral/phaseCounting.cpp \
..\src/peripheral/pwm.cpp \
..\src/peripheral/r_init_non_existent_port.cpp \
..\src/peripheral/spi.cpp \
..\src/peripheral/timeInterrupt.cpp \
..\src/peripheral/timer.cpp \
..\src/peripheral/uart.cpp 

OBJS += \
./src/peripheral/ad.o \
./src/peripheral/clock.o \
./src/peripheral/da.o \
./src/peripheral/gpio.o \
./src/peripheral/phaseCounting.o \
./src/peripheral/pwm.o \
./src/peripheral/r_init_non_existent_port.o \
./src/peripheral/spi.o \
./src/peripheral/timeInterrupt.o \
./src/peripheral/timer.o \
./src/peripheral/uart.o 

CPP_DEPS += \
./src/peripheral/ad.d \
./src/peripheral/clock.d \
./src/peripheral/da.d \
./src/peripheral/gpio.d \
./src/peripheral/phaseCounting.d \
./src/peripheral/pwm.d \
./src/peripheral/r_init_non_existent_port.d \
./src/peripheral/spi.d \
./src/peripheral/timeInterrupt.d \
./src/peripheral/timer.d \
./src/peripheral/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/peripheral/%.o: ../src/peripheral/%.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF ""$(@:%.o=%.d)"" -MT"$(@:%.o=%.o)" -MT""$(@:%.o=%.d)"" @"src/peripheral/cpp.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/peripheral/cpp.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/peripheral/r_init_non_existent_port.o: ../src/peripheral/r_init_non_existent_port.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/peripheral/r_init_non_existent_port.d" -MT"src/peripheral/r_init_non_existent_port.o" -MT"src/peripheral/r_init_non_existent_port.d" @"src/peripheral/r_init_non_existent_port.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/peripheral/r_init_non_existent_port.d" -MT"src/peripheral/r_init_non_existent_port.o" -MT"src/peripheral/r_init_non_existent_port.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/peripheral/r_init_non_existent_port.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

