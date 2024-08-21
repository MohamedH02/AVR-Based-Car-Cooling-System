################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/adc.c \
../MCAL/gpio.c \
../MCAL/pwm_timer0.c \
../MCAL/timer1.c \
../MCAL/twi.c \
../MCAL/uart.c 

OBJS += \
./MCAL/adc.o \
./MCAL/gpio.o \
./MCAL/pwm_timer0.o \
./MCAL/timer1.o \
./MCAL/twi.o \
./MCAL/uart.o 

C_DEPS += \
./MCAL/adc.d \
./MCAL/gpio.d \
./MCAL/pwm_timer0.d \
./MCAL/timer1.d \
./MCAL/twi.d \
./MCAL/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


