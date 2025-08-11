################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TinyUSB/src/common/tusb_fifo.c 

OBJS += \
./TinyUSB/src/common/tusb_fifo.o 

C_DEPS += \
./TinyUSB/src/common/tusb_fifo.d 


# Each subdirectory must supply rules for building sources it contributes
TinyUSB/src/common/%.o TinyUSB/src/common/%.su TinyUSB/src/common/%.cyclo: ../TinyUSB/src/common/%.c TinyUSB/src/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mines/STM32CubeIDE/workspace_1.16.0/F4G-TinyUSB/TinyUSB/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TinyUSB-2f-src-2f-common

clean-TinyUSB-2f-src-2f-common:
	-$(RM) ./TinyUSB/src/common/tusb_fifo.cyclo ./TinyUSB/src/common/tusb_fifo.d ./TinyUSB/src/common/tusb_fifo.o ./TinyUSB/src/common/tusb_fifo.su

.PHONY: clean-TinyUSB-2f-src-2f-common

