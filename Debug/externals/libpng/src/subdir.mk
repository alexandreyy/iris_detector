################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../externals/libpng/src/png.c \
../externals/libpng/src/pngerror.c \
../externals/libpng/src/pngget.c \
../externals/libpng/src/pngmem.c \
../externals/libpng/src/pngpread.c \
../externals/libpng/src/pngread.c \
../externals/libpng/src/pngrio.c \
../externals/libpng/src/pngrtran.c \
../externals/libpng/src/pngrutil.c \
../externals/libpng/src/pngset.c \
../externals/libpng/src/pngtest.c \
../externals/libpng/src/pngtrans.c \
../externals/libpng/src/pngwio.c \
../externals/libpng/src/pngwrite.c \
../externals/libpng/src/pngwtran.c \
../externals/libpng/src/pngwutil.c 

OBJS += \
./externals/libpng/src/png.o \
./externals/libpng/src/pngerror.o \
./externals/libpng/src/pngget.o \
./externals/libpng/src/pngmem.o \
./externals/libpng/src/pngpread.o \
./externals/libpng/src/pngread.o \
./externals/libpng/src/pngrio.o \
./externals/libpng/src/pngrtran.o \
./externals/libpng/src/pngrutil.o \
./externals/libpng/src/pngset.o \
./externals/libpng/src/pngtest.o \
./externals/libpng/src/pngtrans.o \
./externals/libpng/src/pngwio.o \
./externals/libpng/src/pngwrite.o \
./externals/libpng/src/pngwtran.o \
./externals/libpng/src/pngwutil.o 

C_DEPS += \
./externals/libpng/src/png.d \
./externals/libpng/src/pngerror.d \
./externals/libpng/src/pngget.d \
./externals/libpng/src/pngmem.d \
./externals/libpng/src/pngpread.d \
./externals/libpng/src/pngread.d \
./externals/libpng/src/pngrio.d \
./externals/libpng/src/pngrtran.d \
./externals/libpng/src/pngrutil.d \
./externals/libpng/src/pngset.d \
./externals/libpng/src/pngtest.d \
./externals/libpng/src/pngtrans.d \
./externals/libpng/src/pngwio.d \
./externals/libpng/src/pngwrite.d \
./externals/libpng/src/pngwtran.d \
./externals/libpng/src/pngwutil.d 


# Each subdirectory must supply rules for building sources it contributes
externals/libpng/src/%.o: ../externals/libpng/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


