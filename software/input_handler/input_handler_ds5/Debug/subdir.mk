################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../classification.c \
../datacube.c \
../logger.c \
../main.c \
../means.c \
../standards.c 

OBJS += \
./classification.o \
./datacube.o \
./logger.o \
./main.o \
./means.o \
./standards.o 

C_DEPS += \
./classification.d \
./datacube.d \
./logger.d \
./main.d \
./means.d \
./standards.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-linux-gnueabihf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


