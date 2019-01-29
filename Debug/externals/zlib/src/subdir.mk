################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../externals/zlib/src/adler32.c \
../externals/zlib/src/compress.c \
../externals/zlib/src/crc32.c \
../externals/zlib/src/deflate.c \
../externals/zlib/src/gzclose.c \
../externals/zlib/src/gzlib.c \
../externals/zlib/src/gzread.c \
../externals/zlib/src/gzwrite.c \
../externals/zlib/src/infback.c \
../externals/zlib/src/inffast.c \
../externals/zlib/src/inflate.c \
../externals/zlib/src/inftrees.c \
../externals/zlib/src/trees.c \
../externals/zlib/src/uncompr.c \
../externals/zlib/src/zutil.c 

OBJS += \
./externals/zlib/src/adler32.o \
./externals/zlib/src/compress.o \
./externals/zlib/src/crc32.o \
./externals/zlib/src/deflate.o \
./externals/zlib/src/gzclose.o \
./externals/zlib/src/gzlib.o \
./externals/zlib/src/gzread.o \
./externals/zlib/src/gzwrite.o \
./externals/zlib/src/infback.o \
./externals/zlib/src/inffast.o \
./externals/zlib/src/inflate.o \
./externals/zlib/src/inftrees.o \
./externals/zlib/src/trees.o \
./externals/zlib/src/uncompr.o \
./externals/zlib/src/zutil.o 

C_DEPS += \
./externals/zlib/src/adler32.d \
./externals/zlib/src/compress.d \
./externals/zlib/src/crc32.d \
./externals/zlib/src/deflate.d \
./externals/zlib/src/gzclose.d \
./externals/zlib/src/gzlib.d \
./externals/zlib/src/gzread.d \
./externals/zlib/src/gzwrite.d \
./externals/zlib/src/infback.d \
./externals/zlib/src/inffast.d \
./externals/zlib/src/inflate.d \
./externals/zlib/src/inftrees.d \
./externals/zlib/src/trees.d \
./externals/zlib/src/uncompr.d \
./externals/zlib/src/zutil.d 


# Each subdirectory must supply rules for building sources it contributes
externals/zlib/src/%.o: ../externals/zlib/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


