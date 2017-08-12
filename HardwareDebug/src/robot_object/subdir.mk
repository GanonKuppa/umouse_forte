################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\src/robot_object/abcled.cpp \
..\src/robot_object/fcled.cpp \
..\src/robot_object/gamepad.cpp \
..\src/robot_object/mouse.cpp \
..\src/robot_object/tactsw.cpp 

OBJS += \
./src/robot_object/abcled.o \
./src/robot_object/fcled.o \
./src/robot_object/gamepad.o \
./src/robot_object/mouse.o \
./src/robot_object/tactsw.o 

CPP_DEPS += \
./src/robot_object/abcled.d \
./src/robot_object/fcled.d \
./src/robot_object/gamepad.d \
./src/robot_object/mouse.d \
./src/robot_object/tactsw.d 


# Each subdirectory must supply rules for building sources it contributes
src/robot_object/abcled.o: ../src/robot_object/abcled.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/robot_object/abcled.d" -MT"src/robot_object/abcled.o" -MT"src/robot_object/abcled.d" @"src/robot_object/abcled.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/robot_object/abcled.d" -MT"src/robot_object/abcled.o" -MT"src/robot_object/abcled.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/robot_object/abcled.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/robot_object/fcled.o: ../src/robot_object/fcled.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/robot_object/fcled.d" -MT"src/robot_object/fcled.o" -MT"src/robot_object/fcled.d" @"src/robot_object/fcled.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/robot_object/fcled.d" -MT"src/robot_object/fcled.o" -MT"src/robot_object/fcled.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/robot_object/fcled.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/robot_object/gamepad.o: ../src/robot_object/gamepad.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/robot_object/gamepad.d" -MT"src/robot_object/gamepad.o" -MT"src/robot_object/gamepad.d" @"src/robot_object/gamepad.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/robot_object/gamepad.d" -MT"src/robot_object/gamepad.o" -MT"src/robot_object/gamepad.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/robot_object/gamepad.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/robot_object/mouse.o: ../src/robot_object/mouse.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/robot_object/mouse.d" -MT"src/robot_object/mouse.o" -MT"src/robot_object/mouse.d" @"src/robot_object/mouse.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/robot_object/mouse.d" -MT"src/robot_object/mouse.o" -MT"src/robot_object/mouse.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/robot_object/mouse.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/robot_object/tactsw.o: ../src/robot_object/tactsw.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/robot_object/tactsw.d" -MT"src/robot_object/tactsw.o" -MT"src/robot_object/tactsw.d" @"src/robot_object/tactsw.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/robot_object/tactsw.d" -MT"src/robot_object/tactsw.o" -MT"src/robot_object/tactsw.d" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/robot_object/tactsw.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

