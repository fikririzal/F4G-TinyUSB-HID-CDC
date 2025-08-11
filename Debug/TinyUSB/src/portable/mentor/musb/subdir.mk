################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TinyUSB/src/portable/mentor/musb/dcd_musb.c \
../TinyUSB/src/portable/mentor/musb/hcd_musb.c 

OBJS += \
./TinyUSB/src/portable/mentor/musb/dcd_musb.o \
./TinyUSB/src/portable/mentor/musb/hcd_musb.o 

C_DEPS += \
./TinyUSB/src/portable/mentor/musb/dcd_musb.d \
./TinyUSB/src/portable/mentor/musb/hcd_musb.d 


# Each subdirectory must supply rules for building sources it contributes
TinyUSB/src/portable/mentor/musb/%.o TinyUSB/src/portable/mentor/musb/%.su TinyUSB/src/portable/mentor/musb/%.cyclo: ../TinyUSB/src/portable/mentor/musb/%.c TinyUSB/src/portable/mentor/musb/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mines/STM32CubeIDE/workspace_1.16.0/F4G-TinyUSB/TinyUSB/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TinyUSB-2f-src-2f-portable-2f-mentor-2f-musb

clean-TinyUSB-2f-src-2f-portable-2f-mentor-2f-musb:
	-$(RM) ./TinyUSB/src/portable/mentor/musb/dcd_musb.cyclo ./TinyUSB/src/portable/mentor/musb/dcd_musb.d ./TinyUSB/src/portable/mentor/musb/dcd_musb.o ./TinyUSB/src/portable/mentor/musb/dcd_musb.su ./TinyUSB/src/portable/mentor/musb/hcd_musb.cyclo ./TinyUSB/src/portable/mentor/musb/hcd_musb.d ./TinyUSB/src/portable/mentor/musb/hcd_musb.o ./TinyUSB/src/portable/mentor/musb/hcd_musb.su

.PHONY: clean-TinyUSB-2f-src-2f-portable-2f-mentor-2f-musb

