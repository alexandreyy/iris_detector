################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../externals/libnifti/demo/clib_01_read_write.c 

OBJS += \
./externals/libnifti/demo/clib_01_read_write.o 

C_DEPS += \
./externals/libnifti/demo/clib_01_read_write.d 


# Each subdirectory must supply rules for building sources it contributes
externals/libnifti/demo/%.o: ../externals/libnifti/demo/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


