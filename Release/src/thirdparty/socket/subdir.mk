################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/thirdparty/socket/IPPacket.cpp \
../src/thirdparty/socket/MulticastReciever.cpp \
../src/thirdparty/socket/PracticalSocket.cpp 

OBJS += \
./src/thirdparty/socket/IPPacket.o \
./src/thirdparty/socket/MulticastReciever.o \
./src/thirdparty/socket/PracticalSocket.o 

CPP_DEPS += \
./src/thirdparty/socket/IPPacket.d \
./src/thirdparty/socket/MulticastReciever.d \
./src/thirdparty/socket/PracticalSocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/thirdparty/socket/%.o: ../src/thirdparty/socket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


