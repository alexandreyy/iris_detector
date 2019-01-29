################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../externals/tsne/GPU/src/sptree.cpp \
../externals/tsne/GPU/src/t_sne_gpu.cpp 

OBJS += \
./externals/tsne/GPU/src/sptree.o \
./externals/tsne/GPU/src/t_sne_gpu.o 

CPP_DEPS += \
./externals/tsne/GPU/src/sptree.d \
./externals/tsne/GPU/src/t_sne_gpu.d 


# Each subdirectory must supply rules for building sources it contributes
externals/tsne/GPU/src/%.o: ../externals/tsne/GPU/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


