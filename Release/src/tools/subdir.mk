################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tools/MulticastListener.cpp \
../src/tools/SSLException.cpp \
../src/tools/SSLListener.cpp 

OBJS += \
./src/tools/MulticastListener.o \
./src/tools/SSLException.o \
./src/tools/SSLListener.o 

CPP_DEPS += \
./src/tools/MulticastListener.d \
./src/tools/SSLException.d \
./src/tools/SSLListener.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/%.o: ../src/tools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


