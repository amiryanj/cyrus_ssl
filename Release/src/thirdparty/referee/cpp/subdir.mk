################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/thirdparty/referee/cpp/referee.pb.cc 

OBJS += \
./src/thirdparty/referee/cpp/referee.pb.o 

CC_DEPS += \
./src/thirdparty/referee/cpp/referee.pb.d 


# Each subdirectory must supply rules for building sources it contributes
src/thirdparty/referee/cpp/%.o: ../src/thirdparty/referee/cpp/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


