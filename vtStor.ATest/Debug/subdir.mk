################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main.cpp 

OBJS += \
./main.o 

CPP_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/minh/Desktop/VTStor_Linux/vtStor" -I"/home/minh/Desktop/VTStor_Linux/StorageUtility" -I"/home/minh/Desktop/VTStor_Linux/Common" -I"/home/minh/Desktop/VTStor_Linux/Common/Platform/x86x64" -I"/home/minh/Desktop/VTStor_Linux/vtStor/Platform/Linux" -I"/home/minh/Desktop/VTStor_Linux/Common/Platform/x86x64/Linux" -I"/home/minh/Desktop/VTStor_Linux/vtStor/Debug" -I"/home/minh/Desktop/VTStor_Linux/vtStorAta" -I"/home/minh/Desktop/VTStor_Linux/vtStorAta/Platform/Linux" -I"/home/minh/Desktop/VTStor_Linux/vtStorAtaProtocol" -I"/home/minh/Desktop/VTStor_Linux/vtStorAtaProtocol/Platform/Linux" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


