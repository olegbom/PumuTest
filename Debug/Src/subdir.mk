################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/asteroids.c \
../Src/dma.c \
../Src/fatfs.c \
../Src/fonts.c \
../Src/fsmc.c \
../Src/gpio.c \
../Src/ili9341.c \
../Src/main.c \
../Src/matrix.c \
../Src/rng.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/tim.c \
../Src/usart.c \
../Src/usb_host.c \
../Src/usbh_conf.c \
../Src/usbh_diskio.c \
../Src/vector.c 

OBJS += \
./Src/adc.o \
./Src/asteroids.o \
./Src/dma.o \
./Src/fatfs.o \
./Src/fonts.o \
./Src/fsmc.o \
./Src/gpio.o \
./Src/ili9341.o \
./Src/main.o \
./Src/matrix.o \
./Src/rng.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/tim.o \
./Src/usart.o \
./Src/usb_host.o \
./Src/usbh_conf.o \
./Src/usbh_diskio.o \
./Src/vector.o 

C_DEPS += \
./Src/adc.d \
./Src/asteroids.d \
./Src/dma.d \
./Src/fatfs.d \
./Src/fonts.d \
./Src/fsmc.d \
./Src/gpio.d \
./Src/ili9341.d \
./Src/main.d \
./Src/matrix.d \
./Src/rng.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/tim.d \
./Src/usart.d \
./Src/usb_host.d \
./Src/usbh_conf.d \
./Src/usbh_diskio.d \
./Src/vector.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Ac6/workspace/PumuTest/Inc" -I"C:/Ac6/workspace/PumuTest/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Ac6/workspace/PumuTest/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Ac6/workspace/PumuTest/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Ac6/workspace/PumuTest/Drivers/CMSIS/Include" -I"C:/Ac6/workspace/PumuTest/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"C:/Ac6/workspace/PumuTest/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc" -I"C:/Ac6/workspace/PumuTest/Middlewares/Third_Party/FatFs/src"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


