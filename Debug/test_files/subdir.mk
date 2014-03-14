################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test_files/BoostAsio.cpp \
../test_files/BoostTest.cpp \
../test_files/CoreDownTest.cpp \
../test_files/EpollTest.cpp \
../test_files/ManyRanks.cpp \
../test_files/MultiContainer.cpp \
../test_files/MultiThread.cpp \
../test_files/MultiThreadAsio.cpp \
../test_files/SmartPtr.cpp \
../test_files/SocketServer.cpp \
../test_files/StaticMember.cpp \
../test_files/TemplateTest.cpp \
../test_files/ThreadTest..cpp \
../test_files/Timer.cpp \
../test_files/VirtualFunc.cpp \
../test_files/va_list_test.cpp 

OBJS += \
./test_files/BoostAsio.o \
./test_files/BoostTest.o \
./test_files/CoreDownTest.o \
./test_files/EpollTest.o \
./test_files/ManyRanks.o \
./test_files/MultiContainer.o \
./test_files/MultiThread.o \
./test_files/MultiThreadAsio.o \
./test_files/SmartPtr.o \
./test_files/SocketServer.o \
./test_files/StaticMember.o \
./test_files/TemplateTest.o \
./test_files/ThreadTest..o \
./test_files/Timer.o \
./test_files/VirtualFunc.o \
./test_files/va_list_test.o 

CPP_DEPS += \
./test_files/BoostAsio.d \
./test_files/BoostTest.d \
./test_files/CoreDownTest.d \
./test_files/EpollTest.d \
./test_files/ManyRanks.d \
./test_files/MultiContainer.d \
./test_files/MultiThread.d \
./test_files/MultiThreadAsio.d \
./test_files/SmartPtr.d \
./test_files/SocketServer.d \
./test_files/StaticMember.d \
./test_files/TemplateTest.d \
./test_files/ThreadTest..d \
./test_files/Timer.d \
./test_files/VirtualFunc.d \
./test_files/va_list_test.d 


# Each subdirectory must supply rules for building sources it contributes
test_files/%.o: ../test_files/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLOCAL_DEBUG -I"/home/branch/Robert/BoostAsio" -I"/home/branch/Robert/common" -I"/home/branch/Robert/Python" -I"/home/branch/Robert/source" -I"/home/branch/Robert/test_files" -I"/home/branch/Robert/TestData" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


