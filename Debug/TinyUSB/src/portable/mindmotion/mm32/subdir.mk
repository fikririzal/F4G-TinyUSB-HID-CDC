################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.c 

OBJS += \
./TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.o 

C_DEPS += \
./TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.d 


# Each subdirectory must supply rules for building sources it contributes
TinyUSB/src/portable/mindmotion/mm32/%.o TinyUSB/src/portable/mindmotion/mm32/%.su TinyUSB/src/portable/mindmotion/mm32/%.cyclo: ../TinyUSB/src/portable/mindmotion/mm32/%.c TinyUSB/src/portable/mindmotion/mm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mines/STM32CubeIDE/workspace_1.16.0/F4G-TinyUSB/TinyUSB/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TinyUSB-2f-src-2f-portable-2f-mindmotion-2f-mm32

clean-TinyUSB-2f-src-2f-portable-2f-mindmotion-2f-mm32:
	-$(RM) ./TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.cyclo ./TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.d ./TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.o ./TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.su

.PHONY: clean-TinyUSB-2f-src-2f-portable-2f-mindmotion-2f-mm32

