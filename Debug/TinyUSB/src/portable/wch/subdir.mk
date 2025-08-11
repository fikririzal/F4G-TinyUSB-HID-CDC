################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TinyUSB/src/portable/wch/dcd_ch32_usbfs.c \
../TinyUSB/src/portable/wch/dcd_ch32_usbhs.c \
../TinyUSB/src/portable/wch/hcd_ch32_usbfs.c 

OBJS += \
./TinyUSB/src/portable/wch/dcd_ch32_usbfs.o \
./TinyUSB/src/portable/wch/dcd_ch32_usbhs.o \
./TinyUSB/src/portable/wch/hcd_ch32_usbfs.o 

C_DEPS += \
./TinyUSB/src/portable/wch/dcd_ch32_usbfs.d \
./TinyUSB/src/portable/wch/dcd_ch32_usbhs.d \
./TinyUSB/src/portable/wch/hcd_ch32_usbfs.d 


# Each subdirectory must supply rules for building sources it contributes
TinyUSB/src/portable/wch/%.o TinyUSB/src/portable/wch/%.su TinyUSB/src/portable/wch/%.cyclo: ../TinyUSB/src/portable/wch/%.c TinyUSB/src/portable/wch/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mines/STM32CubeIDE/workspace_1.16.0/F4G-TinyUSB/TinyUSB/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TinyUSB-2f-src-2f-portable-2f-wch

clean-TinyUSB-2f-src-2f-portable-2f-wch:
	-$(RM) ./TinyUSB/src/portable/wch/dcd_ch32_usbfs.cyclo ./TinyUSB/src/portable/wch/dcd_ch32_usbfs.d ./TinyUSB/src/portable/wch/dcd_ch32_usbfs.o ./TinyUSB/src/portable/wch/dcd_ch32_usbfs.su ./TinyUSB/src/portable/wch/dcd_ch32_usbhs.cyclo ./TinyUSB/src/portable/wch/dcd_ch32_usbhs.d ./TinyUSB/src/portable/wch/dcd_ch32_usbhs.o ./TinyUSB/src/portable/wch/dcd_ch32_usbhs.su ./TinyUSB/src/portable/wch/hcd_ch32_usbfs.cyclo ./TinyUSB/src/portable/wch/hcd_ch32_usbfs.d ./TinyUSB/src/portable/wch/hcd_ch32_usbfs.o ./TinyUSB/src/portable/wch/hcd_ch32_usbfs.su

.PHONY: clean-TinyUSB-2f-src-2f-portable-2f-wch

