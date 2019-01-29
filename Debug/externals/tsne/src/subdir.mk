################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../externals/tsne/src/sptree.cpp \
../externals/tsne/src/tsne.cpp 

OBJS += \
./externals/tsne/src/sptree.o \
./externals/tsne/src/tsne.o 

CPP_DEPS += \
./externals/tsne/src/sptree.d \
./externals/tsne/src/tsne.d 


# Each subdirectory must supply rules for building sources it contributes
externals/tsne/src/%.o: ../externals/tsne/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


