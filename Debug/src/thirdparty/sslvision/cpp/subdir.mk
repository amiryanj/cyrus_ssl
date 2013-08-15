################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/thirdparty/sslvision/cpp/messages_robocup_ssl_detection.pb.cc \
../src/thirdparty/sslvision/cpp/messages_robocup_ssl_geometry.pb.cc \
../src/thirdparty/sslvision/cpp/messages_robocup_ssl_refbox_log.pb.cc \
../src/thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.cc 

OBJS += \
./src/thirdparty/sslvision/cpp/messages_robocup_ssl_detection.pb.o \
./src/thirdparty/sslvision/cpp/messages_robocup_ssl_geometry.pb.o \
./src/thirdparty/sslvision/cpp/messages_robocup_ssl_refbox_log.pb.o \
./src/thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.o 

CC_DEPS += \
./src/thirdparty/sslvision/cpp/messages_robocup_ssl_detection.pb.d \
./src/thirdparty/sslvision/cpp/messages_robocup_ssl_geometry.pb.d \
./src/thirdparty/sslvision/cpp/messages_robocup_ssl_refbox_log.pb.d \
./src/thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.d 


# Each subdirectory must supply rules for building sources it contributes
src/thirdparty/sslvision/cpp/%.o: ../src/thirdparty/sslvision/cpp/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


