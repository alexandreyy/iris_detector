################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../externals/libsvm/src/svm.cpp 

OBJS += \
./externals/libsvm/src/svm.o 

CPP_DEPS += \
./externals/libsvm/src/svm.d 


# Each subdirectory must supply rules for building sources it contributes
externals/libsvm/src/%.o: ../externals/libsvm/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


