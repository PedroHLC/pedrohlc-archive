################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/canvas.c \
../src/consts.c \
../src/operations.c \
../src/paintwall.c \
../src/ui.c 

OBJS += \
./src/canvas.o \
./src/consts.o \
./src/operations.o \
./src/paintwall.o \
./src/ui.o 

C_DEPS += \
./src/canvas.d \
./src/consts.d \
./src/operations.d \
./src/paintwall.d \
./src/ui.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/SDL -I"/home/pedrohlc/Workspace/PaintWall/thrd/include" -I"/home/pedrohlc/Workspace/PaintWall/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


