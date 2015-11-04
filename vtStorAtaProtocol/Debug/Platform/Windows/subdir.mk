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
	g++ -I"/home/minh/workspaceVtStor/vtStorAtaProtocol" -I"/home/minh/workspaceVtStor/vtStorAtaProtocol/Platform/Linux" -I"/home/minh/workspaceVtStor/Common/Platform/x86x64" -I"/home/minh/workspaceVtStor/StorageUtility" -I"/home/minh/workspaceVtStor/vtStor" -I"/home/minh/workspaceVtStor/Common/Platform/x86x64/Linux" -I"/home/minh/workspaceVtStor/StorageUtility/Lniux" -I"/home/minh/workspaceVtStor/vtStor/Platform/Linux" -I"/home/minh/workspaceVtStor/Common" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


