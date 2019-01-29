################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../externals/tsne/CPU/src/sptree.cpp \
../externals/tsne/CPU/src/tsne.cpp 

OBJS += \
./externals/tsne/CPU/src/sptree.o \
./externals/tsne/CPU/src/tsne.o 

CPP_DEPS += \
./externals/tsne/CPU/src/sptree.d \
./externals/tsne/CPU/src/tsne.d 


# Each subdirectory must supply rules for building sources it contributes
externals/tsne/CPU/src/%.o: ../externals/tsne/CPU/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


