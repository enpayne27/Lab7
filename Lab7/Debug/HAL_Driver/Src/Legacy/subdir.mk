################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_Driver/Src/Legacy/stm32l4xx_hal_can.c 

OBJS += \
./HAL_Driver/Src/Legacy/stm32l4xx_hal_can.o 

C_DEPS += \
./HAL_Driver/Src/Legacy/stm32l4xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_Driver/Src/Legacy/%.o: ../HAL_Driver/Src/Legacy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32L4 -DSTM32L475VGTx -DB_L475E_IOT01A1 -DDEBUG -DSTM32L475xx -DUSE_HAL_DRIVER -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/m24sr" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/cs43l22" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/mx25lm51245g" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/mfxstm32l152" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/CMSIS/device" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/cs42l51" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/n25q128a" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/st7735" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/ft3x67" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/rk043fn48h" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/hx8347g" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/HAL_Driver/Inc/Legacy" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/ov9655" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/stmpe1600" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/Common" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/l3gd20" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/lsm6dsl" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/HAL_Driver/Inc" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/stmpe811" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/wm8994" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/B-L475E-IOT01" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/ft5336" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/n25q256a" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/inc" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/hts221" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/ls016b8uy" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/ft6x06" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/lis3mdl" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/lps22hb" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/st7789h2" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/lsm303c" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/iss66wvh8m8" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/lsm303dlhc" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/CMSIS/core" -I"/Users/erinpayne/Downloads/ECE631/lab7/Lab7/Utilities/Components/mx25r6435f" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


