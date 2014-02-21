################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/thirdparty/socket/IPPacket.cpp \
../src/thirdparty/socket/netraw.cpp 

OBJS += \
./src/thirdparty/socket/IPPacket.o \
./src/thirdparty/socket/netraw.o 

CPP_DEPS += \
./src/thirdparty/socket/IPPacket.d \
./src/thirdparty/socket/netraw.d 


# Each subdirectory must supply rules for building sources it contributes
src/thirdparty/socket/%.o: ../src/thirdparty/socket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


