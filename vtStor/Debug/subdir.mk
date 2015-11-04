################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Buffer.cpp \
../BufferFormatter.cpp \
../BufferInterface.cpp \
../CommandDescriptor.cpp \
../CommandHandlerInterface.cpp \
../Drive.cpp \
../DriveEnumeratorInterface.cpp \
../DriveInterface.cpp \
../DriveManager.cpp \
../DriveManagerInterface.cpp \
../ProtocolEssense.cpp \
../ProtocolInterface.cpp \
../vtStor.cpp 

OBJS += \
./Buffer.o \
./BufferFormatter.o \
./BufferInterface.o \
./CommandDescriptor.o \
./CommandHandlerInterface.o \
./Drive.o \
./DriveEnumeratorInterface.o \
./DriveInterface.o \
./DriveManager.o \
./DriveManagerInterface.o \
./ProtocolEssense.o \
./ProtocolInterface.o \
./vtStor.o 

CPP_DEPS += \
./Buffer.d \
./BufferFormatter.d \
./BufferInterface.d \
./CommandDescriptor.d \
./CommandHandlerInterface.d \
./Drive.d \
./DriveEnumeratorInterface.d \
./DriveInterface.d \
./DriveManager.d \
./DriveManagerInterface.d \
./ProtocolEssense.d \
./ProtocolInterface.d \
./vtStor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/minh/workspaceVtStor/StorageUtility/Debug" -I"/home/minh/workspaceVtStor/vtStor/Platform/Linux" -I"/home/minh/workspaceVtStor/Common" -I"/home/minh/workspaceVtStor/Common/Platform/x86x64/Linux" -I"/home/minh/workspaceVtStor/StorageUtility/Lniux" -I"/home/minh/workspaceVtStor/StorageUtility" -I"/home/minh/workspaceVtStor/vtStor" -I"/home/minh/workspaceVtStor/Common/Platform/x86x64" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


