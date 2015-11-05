################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Platform/Windows/ProtocolAtaPassThrough.cpp 

OBJS += \
./Platform/Windows/ProtocolAtaPassThrough.o 

CPP_DEPS += \
./Platform/Windows/ProtocolAtaPassThrough.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/Windows/%.o: ../Platform/Windows/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/minh/Desktop/VTStor_Linux/vtStorAtaProtocol" -I"/home/minh/Desktop/VTStor_Linux/vtStorAtaProtocol/Platform/Linux" -I"/home/minh/Desktop/VTStor_Linux/Common/Platform/x86x64" -I"/home/minh/Desktop/VTStor_Linux/StorageUtility" -I"/home/minh/Desktop/VTStor_Linux/vtStor" -I"/home/minh/Desktop/VTStor_Linux/Common/Platform/x86x64/Linux" -I"/home/minh/Desktop/VTStor_Linux/StorageUtility/Lniux" -I"/home/minh/Desktop/VTStor_Linux/vtStor/Platform/Linux" -I"/home/minh/Desktop/VTStor_Linux/Common" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


