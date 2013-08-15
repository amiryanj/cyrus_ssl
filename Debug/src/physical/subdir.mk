################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/physical/SSLVision.cpp \
../src/physical/SerialConnection.cpp 

OBJS += \
./src/physical/SSLVision.o \
./src/physical/SerialConnection.o 

CPP_DEPS += \
./src/physical/SSLVision.d \
./src/physical/SerialConnection.d 


# Each subdirectory must supply rules for building sources it contributes
src/physical/%.o: ../src/physical/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


