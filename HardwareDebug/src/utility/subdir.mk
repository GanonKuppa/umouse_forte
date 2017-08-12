################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\src/utility/myUtil.cpp 

OBJS += \
./src/utility/myUtil.o 

CPP_DEPS += \
./src/utility/myUtil.d 


# Each subdirectory must supply rules for building sources it contributes
src/utility/%.o: ../src/utility/%.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF ""$(@:%.o=%.d)"" -MT"$(@:%.o=%.o)" -MT""$(@:%.o=%.d)"" @"src/utility/cpp.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -x c++   -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/utility/cpp.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -Wa,-adlhn="$(basename $(notdir $<)).lst" -fno-function-cse -flto-compression-level=0 -fno-caller-saves -I"C:\Users\ryota\e2_studio\workspace\umouse\src\mode" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\other" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\peripheral" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\robot_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\umouse_object" -I"C:\Users\ryota\e2_studio\workspace\umouse\src\utility" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -DCPPAPP -O3 -g2 -g -mlittle-endian-data -mcpu=rx64m "-std=c++11" -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

