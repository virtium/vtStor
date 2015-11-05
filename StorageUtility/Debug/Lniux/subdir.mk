################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Lniux/Device.cpp \
../Lniux/StorageUtility.cpp 

OBJS += \
./Lniux/Device.o \
./Lniux/StorageUtility.o 

CPP_DEPS += \
./Lniux/Device.d \
./Lniux/StorageUtility.d 


# Each subdirectory must supply rules for building sources it contributes
Lniux/%.o: ../Lniux/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/minh/Desktop/VTStor_Linux/Common" -I"/home/minh/Desktop/VTStor_Linux/vtStor/Platform/Linux" -I"/home/minh/Desktop/VTStor_Linux/Common/Platform/x86x64" -I"/home/minh/Desktop/VTStor_Linux/Common/Platform/x86x64/Linux" -I"/home/minh/Desktop/VTStor_Linux/StorageUtility" -I"/home/minh/Desktop/VTStor_Linux/StorageUtility/Lniux" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


