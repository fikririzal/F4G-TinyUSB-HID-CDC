################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TinyUSB/src/portable/chipidea/ci_fs/dcd_ci_fs.c 

OBJS += \
./TinyUSB/src/portable/chipidea/ci_fs/dcd_ci_fs.o 

C_DEPS += \
./TinyUSB/src/portable/chipidea/ci_fs/dcd_ci_fs.d 


# Each subdirectory must supply rules for building sources it contributes
TinyUSB/src/portable/chipidea/ci_fs/%.o TinyUSB/src/portable/chipidea/ci_fs/%.su TinyUSB/src/portable/chipidea/ci_fs/%.cyclo: ../TinyUSB/src/portable/chipidea/ci_fs/%.c TinyUSB/src/portable/chipidea/ci_fs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mines/STM32CubeIDE/workspace_1.16.0/F4G-TinyUSB/TinyUSB/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TinyUSB-2f-src-2f-portable-2f-chipidea-2f-ci_fs

clean-TinyUSB-2f-src-2f-portable-2f-chipidea-2f-ci_fs:
	-$(RM) ./TinyUSB/src/portable/chipidea/ci_fs/dcd_ci_fs.cyclo ./TinyUSB/src/portable/chipidea/ci_fs/dcd_ci_fs.d ./TinyUSB/src/portable/chipidea/ci_fs/dcd_ci_fs.o ./TinyUSB/src/portable/chipidea/ci_fs/dcd_ci_fs.su

.PHONY: clean-TinyUSB-2f-src-2f-portable-2f-chipidea-2f-ci_fs

