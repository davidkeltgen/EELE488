################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../classification.c \
../datacube.c \
../fixed_point.c \
../fpgamem.c \
../handler_funcs.c \
../logger.c \
../main.c \
../means.c \
../server.c \
../standards.c 

OBJS += \
./classification.o \
./datacube.o \
./fixed_point.o \
./fpgamem.o \
./handler_funcs.o \
./logger.o \
./main.o \
./means.o \
./server.o \
./standards.o 

C_DEPS += \
./classification.d \
./datacube.d \
./fixed_point.d \
./fpgamem.d \
./handler_funcs.d \
./logger.d \
./main.d \
./means.d \
./server.d \
./standards.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-linux-gnueabihf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -lm -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


