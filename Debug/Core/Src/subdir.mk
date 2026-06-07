################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CLK_CONFIG.c \
../Core/Src/I2C_DRIVER.c \
../Core/Src/IMAGES.c \
../Core/Src/SSD1309_CMD..c \
../Core/Src/main.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32c0xx.c 

OBJS += \
./Core/Src/CLK_CONFIG.o \
./Core/Src/I2C_DRIVER.o \
./Core/Src/IMAGES.o \
./Core/Src/SSD1309_CMD..o \
./Core/Src/main.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32c0xx.o 

C_DEPS += \
./Core/Src/CLK_CONFIG.d \
./Core/Src/I2C_DRIVER.d \
./Core/Src/IMAGES.d \
./Core/Src/SSD1309_CMD..d \
./Core/Src/main.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32c0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32C031xx -c -I../Core/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/CLK_CONFIG.cyclo ./Core/Src/CLK_CONFIG.d ./Core/Src/CLK_CONFIG.o ./Core/Src/CLK_CONFIG.su ./Core/Src/I2C_DRIVER.cyclo ./Core/Src/I2C_DRIVER.d ./Core/Src/I2C_DRIVER.o ./Core/Src/I2C_DRIVER.su ./Core/Src/IMAGES.cyclo ./Core/Src/IMAGES.d ./Core/Src/IMAGES.o ./Core/Src/IMAGES.su ./Core/Src/SSD1309_CMD..cyclo ./Core/Src/SSD1309_CMD..d ./Core/Src/SSD1309_CMD..o ./Core/Src/SSD1309_CMD..su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32c0xx.cyclo ./Core/Src/system_stm32c0xx.d ./Core/Src/system_stm32c0xx.o ./Core/Src/system_stm32c0xx.su

.PHONY: clean-Core-2f-Src

