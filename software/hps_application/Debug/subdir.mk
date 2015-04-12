################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../client.c \
../fixed_point.c \
../fpgamem.c \
../handler_funcs.c \
../logger.c \
../main.c \
../server.c 

OBJS += \
./client.o \
./fixed_point.o \
./fpgamem.o \
./handler_funcs.o \
./logger.o \
./main.o \
./server.o 

C_DEPS += \
./client.d \
./fixed_point.d \
./fpgamem.d \
./handler_funcs.d \
./logger.d \
./main.d \
./server.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-linux-gnueabihf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


