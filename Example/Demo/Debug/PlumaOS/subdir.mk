################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PlumaOS/Event.c \
../PlumaOS/Kernel.c \
../PlumaOS/List.c \
../PlumaOS/MsgQueue.c \
../PlumaOS/Mutex.c \
../PlumaOS/PlumaOS.c \
../PlumaOS/Semaphore.c \
../PlumaOS/Timer.c 

OBJS += \
./PlumaOS/Event.o \
./PlumaOS/Kernel.o \
./PlumaOS/List.o \
./PlumaOS/MsgQueue.o \
./PlumaOS/Mutex.o \
./PlumaOS/PlumaOS.o \
./PlumaOS/Semaphore.o \
./PlumaOS/Timer.o 

C_DEPS += \
./PlumaOS/Event.d \
./PlumaOS/Kernel.d \
./PlumaOS/List.d \
./PlumaOS/MsgQueue.d \
./PlumaOS/Mutex.d \
./PlumaOS/PlumaOS.d \
./PlumaOS/Semaphore.d \
./PlumaOS/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
PlumaOS/%.o: ../PlumaOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


