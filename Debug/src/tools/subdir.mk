################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tools/SSLException.cpp \
../src/tools/SSLListener.cpp \
../src/tools/stdlist.cpp \
../src/tools/testboost.cpp \
../src/tools/vector2d.cpp \
../src/tools/vector3d.cpp 

OBJS += \
./src/tools/SSLException.o \
./src/tools/SSLListener.o \
./src/tools/stdlist.o \
./src/tools/testboost.o \
./src/tools/vector2d.o \
./src/tools/vector3d.o 

CPP_DEPS += \
./src/tools/SSLException.d \
./src/tools/SSLListener.d \
./src/tools/stdlist.d \
./src/tools/testboost.d \
./src/tools/vector2d.d \
./src/tools/vector3d.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/%.o: ../src/tools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


