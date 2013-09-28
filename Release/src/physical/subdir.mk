################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/physical/RobotSerialConnection.cpp \
../src/physical/SSLReferee.cpp \
../src/physical/SSLVision.cpp 

OBJS += \
./src/physical/RobotSerialConnection.o \
./src/physical/SSLReferee.o \
./src/physical/SSLVision.o 

CPP_DEPS += \
./src/physical/RobotSerialConnection.d \
./src/physical/SSLReferee.d \
./src/physical/SSLVision.d 


# Each subdirectory must supply rules for building sources it contributes
src/physical/%.o: ../src/physical/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


