################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommandDescriptorUtility.cpp \
../CommandHandlerAta.cpp \
../DriveAta.cpp \
../DriveAtaCommandExtensions.cpp \
../DriveEnumeratorAta.cpp \
../vtStorAta.cpp 

OBJS += \
./CommandDescriptorUtility.o \
./CommandHandlerAta.o \
./DriveAta.o \
./DriveAtaCommandExtensions.o \
./DriveEnumeratorAta.o \
./vtStorAta.o 

CPP_DEPS += \
./CommandDescriptorUtility.d \
./CommandHandlerAta.d \
./DriveAta.d \
./DriveAtaCommandExtensions.d \
./DriveEnumeratorAta.d \
./vtStorAta.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"/home/minh/Desktop/VTStor_Linux/vtStorAta" -I"/home/minh/Desktop/VTStor_Linux/Common" -I"/home/minh/Desktop/VTStor_Linux/vtStor/Platform/Linux" -I"/home/minh/Desktop/VTStor_Linux/Common/Platform/x86x64/Linux" -I"/home/minh/Desktop/VTStor_Linux/Common/Platform/x86x64" -I"/home/minh/Desktop/VTStor_Linux/StorageUtility" -I"/home/minh/Desktop/VTStor_Linux/vtStor" -I"/home/minh/Desktop/VTStor_Linux/vtStorAtaProtocol" -I"/home/minh/Desktop/VTStor_Linux/vtStorAtaProtocol/Platform/Linux" -I"/home/minh/Desktop/VTStor_Linux/vtStorAta/Platform/Linux" -I"/home/minh/Desktop/VTStor_Linux/StorageUtility/Lniux" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


