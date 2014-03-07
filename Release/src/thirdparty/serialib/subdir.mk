################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/thirdparty/serialib/serialib.cpp 

OBJS += \
./src/thirdparty/serialib/serialib.o 

CPP_DEPS += \
./src/thirdparty/serialib/serialib.d 


# Each subdirectory must supply rules for building sources it contributes
src/thirdparty/serialib/%.o: ../src/thirdparty/serialib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


