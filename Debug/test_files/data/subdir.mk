################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test_files/data/Module.cpp \
../test_files/data/ThreadClass.cpp \
../test_files/data/TimerTest.cpp 

OBJS += \
./test_files/data/Module.o \
./test_files/data/ThreadClass.o \
./test_files/data/TimerTest.o 

CPP_DEPS += \
./test_files/data/Module.d \
./test_files/data/ThreadClass.d \
./test_files/data/TimerTest.d 


# Each subdirectory must supply rules for building sources it contributes
test_files/data/%.o: ../test_files/data/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLOCAL_DEBUG -I"/home/branch/Robert/BoostAsio" -I"/home/branch/Robert/common" -I"/home/branch/Robert/Python" -I"/home/branch/Robert/source" -I"/home/branch/Robert/test_files" -I"/home/branch/Robert/TestData" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


