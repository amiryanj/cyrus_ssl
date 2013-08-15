################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/definition/Position.cpp \
../src/definition/SSLRobotPacket.cpp \
../src/definition/WorldModel.cpp 

OBJS += \
./src/definition/Position.o \
./src/definition/SSLRobotPacket.o \
./src/definition/WorldModel.o 

CPP_DEPS += \
./src/definition/Position.d \
./src/definition/SSLRobotPacket.d \
./src/definition/WorldModel.d 


# Each subdirectory must supply rules for building sources it contributes
src/definition/%.o: ../src/definition/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


