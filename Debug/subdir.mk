################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../features.c \
../iftDetectIris.c \
../iftTrainForIrisDetection.c \
../weakclassifiers.c 

OBJS += \
./features.o \
./iftDetectIris.o \
./iftTrainForIrisDetection.o \
./weakclassifiers.o 

C_DEPS += \
./features.d \
./iftDetectIris.d \
./iftTrainForIrisDetection.d \
./weakclassifiers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


