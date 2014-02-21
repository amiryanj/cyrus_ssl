################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/definition/SSLBall.cpp \
../src/definition/SSLObject.cpp \
../src/definition/SSLRobot.cpp \
../src/definition/SSLRobotPhysic.cpp \
../src/definition/SSLTeam.cpp \
../src/definition/sslagent.cpp \
../src/definition/sslmath.cpp \
../src/definition/sslstrategy.cpp 

OBJS += \
./src/definition/SSLBall.o \
./src/definition/SSLObject.o \
./src/definition/SSLRobot.o \
./src/definition/SSLRobotPhysic.o \
./src/definition/SSLTeam.o \
./src/definition/sslagent.o \
./src/definition/sslmath.o \
./src/definition/sslstrategy.o 

CPP_DEPS += \
./src/definition/SSLBall.d \
./src/definition/SSLObject.d \
./src/definition/SSLRobot.d \
./src/definition/SSLRobotPhysic.d \
./src/definition/SSLTeam.d \
./src/definition/sslagent.d \
./src/definition/sslmath.d \
./src/definition/sslstrategy.d 


# Each subdirectory must supply rules for building sources it contributes
src/definition/%.o: ../src/definition/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


