################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/EventSystem.cpp 

OBJS += \
./source/EventSystem.o 

CPP_DEPS += \
./source/EventSystem.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLOCAL_DEBUG -I"/home/branch/Robert/BoostAsio" -I"/home/branch/Robert/common" -I"/home/branch/Robert/Python" -I"/home/branch/Robert/source" -I"/home/branch/Robert/test_files" -I"/home/branch/Robert/TestData" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


