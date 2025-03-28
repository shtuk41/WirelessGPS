################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../circular_buffer.c \
../cr_startup_lpc17.c \
../main.c \
../mtk_nmea.c \
../nmea.c \
../uart.c 

OBJS += \
./circular_buffer.o \
./cr_startup_lpc17.o \
./main.o \
./mtk_nmea.o \
./nmea.o \
./uart.o 

C_DEPS += \
./circular_buffer.d \
./cr_startup_lpc17.d \
./main.d \
./mtk_nmea.d \
./nmea.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\alex1104\Desktop\SEIS742\Project\workspace\FreeRTOS_Library\demo_code" -I"C:\Users\alex1104\Desktop\SEIS742\Project\workspace\CMSISv1p30_LPC17xx\inc" -I"C:\Users\alex1104\Desktop\SEIS742\Project\workspace\FreeRTOS_Library\include" -I"C:\Users\alex1104\Desktop\SEIS742\Project\workspace\FreeRTOS_Library\portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


