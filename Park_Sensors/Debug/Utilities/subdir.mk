################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/stm32f4_discovery.c \
../Utilities/stm32f4_discovery_lis302dl.c 

OBJS += \
./Utilities/stm32f4_discovery.o \
./Utilities/stm32f4_discovery_lis302dl.o 

C_DEPS += \
./Utilities/stm32f4_discovery.d \
./Utilities/stm32f4_discovery_lis302dl.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/%.o: ../Utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F4DISCOVERY -DDEBUG -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -I"C:/Users/Rafa�/Documents/GitHub/ParkSensors/Park_Sensors/Utilities" -I"C:/Users/Rafa�/Documents/GitHub/ParkSensors/Park_Sensors/StdPeriph_Driver/inc" -I"C:/Users/Rafa�/Documents/GitHub/ParkSensors/Park_Sensors/inc" -I"C:/Users/Rafa�/Documents/GitHub/ParkSensors/Park_Sensors/CMSIS/device" -I"C:/Users/Rafa�/Documents/GitHub/ParkSensors/Park_Sensors/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


