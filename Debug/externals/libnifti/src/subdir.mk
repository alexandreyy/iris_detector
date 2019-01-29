################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../externals/libnifti/src/nifti1_io.c \
../externals/libnifti/src/znzlib.c 

OBJS += \
./externals/libnifti/src/nifti1_io.o \
./externals/libnifti/src/znzlib.o 

C_DEPS += \
./externals/libnifti/src/nifti1_io.d \
./externals/libnifti/src/znzlib.d 


# Each subdirectory must supply rules for building sources it contributes
externals/libnifti/src/%.o: ../externals/libnifti/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


