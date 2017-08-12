################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\src/mode/mode.cpp \
..\src/mode/mode_B.cpp \
..\src/mode/mode_G.cpp \
..\src/mode/mode_GB.cpp \
..\src/mode/mode_N.cpp \
..\src/mode/mode_R.cpp \
..\src/mode/mode_RB.cpp \
..\src/mode/mode_RG.cpp \
..\src/mode/mode_RGB.cpp 

OBJS += \
./src/mode/mode.o \
./src/mode/mode_B.o \
./src/mode/mode_G.o \
./src/mode/mode_GB.o \
./src/mode/mode_N.o \
./src/mode/mode_R.o \
./src/mode/mode_RB.o \
./src/mode/mode_RG.o \
./src/mode/mode_RGB.o 

CPP_DEPS += \
./src/mode/mode.d \
./src/mode/mode_B.d \
./src/mode/mode_G.d \
./src/mode/mode_GB.d \
./src/mode/mode_N.d \
./src/mode/mode_R.d \
./src/mode/mode_RB.d \
./src/mode/mode_RG.d \
./src/mode/mode_RGB.d 


# Each subdirectory must supply rules for building sources it contributes
src/mode/%.o: ../src/mode/%.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF ""$(@:%.o=%.d)"" -MT"$(@:%.o=%.o)" -MT""$(@:%.o=%.d)"" @"src/mode/cpp.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/mode/cpp.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/mode/mode_B.o: ../src/mode/mode_B.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/mode/mode_B.d" -MT"src/mode/mode_B.o" -MT"src/mode/mode_B.d" @"src/mode/mode_B.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/mode/mode_B.d" -MT"src/mode/mode_B.o" -MT"src/mode/mode_B.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/mode/mode_B.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/mode/mode_G.o: ../src/mode/mode_G.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/mode/mode_G.d" -MT"src/mode/mode_G.o" -MT"src/mode/mode_G.d" @"src/mode/mode_G.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/mode/mode_G.d" -MT"src/mode/mode_G.o" -MT"src/mode/mode_G.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/mode/mode_G.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/mode/mode_GB.o: ../src/mode/mode_GB.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/mode/mode_GB.d" -MT"src/mode/mode_GB.o" -MT"src/mode/mode_GB.d" @"src/mode/mode_GB.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/mode/mode_GB.d" -MT"src/mode/mode_GB.o" -MT"src/mode/mode_GB.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/mode/mode_GB.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/mode/mode_N.o: ../src/mode/mode_N.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/mode/mode_N.d" -MT"src/mode/mode_N.o" -MT"src/mode/mode_N.d" @"src/mode/mode_N.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/mode/mode_N.d" -MT"src/mode/mode_N.o" -MT"src/mode/mode_N.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/mode/mode_N.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/mode/mode_R.o: ../src/mode/mode_R.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/mode/mode_R.d" -MT"src/mode/mode_R.o" -MT"src/mode/mode_R.d" @"src/mode/mode_R.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/mode/mode_R.d" -MT"src/mode/mode_R.o" -MT"src/mode/mode_R.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/mode/mode_R.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/mode/mode_RB.o: ../src/mode/mode_RB.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/mode/mode_RB.d" -MT"src/mode/mode_RB.o" -MT"src/mode/mode_RB.d" @"src/mode/mode_RB.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/mode/mode_RB.d" -MT"src/mode/mode_RB.o" -MT"src/mode/mode_RB.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/mode/mode_RB.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/mode/mode_RG.o: ../src/mode/mode_RG.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/mode/mode_RG.d" -MT"src/mode/mode_RG.o" -MT"src/mode/mode_RG.d" @"src/mode/mode_RG.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/mode/mode_RG.d" -MT"src/mode/mode_RG.o" -MT"src/mode/mode_RG.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/mode/mode_RG.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/mode/mode_RGB.o: ../src/mode/mode_RGB.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/mode/mode_RGB.d" -MT"src/mode/mode_RGB.o" -MT"src/mode/mode_RGB.d" @"src/mode/mode_RGB.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/mode/mode_RGB.d" -MT"src/mode/mode_RGB.o" -MT"src/mode/mode_RGB.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/mode/mode_RGB.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

