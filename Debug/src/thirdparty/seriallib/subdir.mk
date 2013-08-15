################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/thirdparty/seriallib/serialib.cpp 

OBJS += \
./src/thirdparty/seriallib/serialib.o 

CPP_DEPS += \
./src/thirdparty/seriallib/serialib.d 


# Each subdirectory must supply rules for building sources it contributes
src/thirdparty/seriallib/%.o: ../src/thirdparty/seriallib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


