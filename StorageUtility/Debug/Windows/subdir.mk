################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Windows/Device.cpp \
../Windows/StorageUtility.cpp 

OBJS += \
./Windows/Device.o \
./Windows/StorageUtility.o 

CPP_DEPS += \
./Windows/Device.d \
./Windows/StorageUtility.d 


# Each subdirectory must supply rules for building sources it contributes
Windows/%.o: ../Windows/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/minh/workspaceVtStor/Common" -I"/home/minh/workspaceVtStor/vtStor/Platform/Linux" -I"/home/minh/workspaceVtStor/Common/Platform/x86x64" -I"/home/minh/workspaceVtStor/Common/Platform/x86x64/Linux" -I"/home/minh/workspaceVtStor/StorageUtility" -I"/home/minh/workspaceVtStor/StorageUtility/Lniux" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


