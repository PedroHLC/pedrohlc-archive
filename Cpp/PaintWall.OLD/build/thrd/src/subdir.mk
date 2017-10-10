################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../thrd/src/cJSON.c 

OBJS += \
./thrd/src/cJSON.o 

C_DEPS += \
./thrd/src/cJSON.d 


# Each subdirectory must supply rules for building sources it contributes
thrd/src/%.o: ../thrd/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/SDL -I"/home/pedrohlc/Workspace/PaintWall/thrd/include" -I"/home/pedrohlc/Workspace/PaintWall/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


