################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/garrett/Documents/school/seng466/copter/Aero3/Libraries/UVicRadio/Radio.cpp 

OBJS += \
./UVicRadio/Radio.o 

CPP_DEPS += \
./UVicRadio/Radio.d 


# Each subdirectory must supply rules for building sources it contributes
UVicRadio/Radio.o: /Users/garrett/Documents/school/seng466/copter/Aero3/Libraries/UVicRadio/Radio.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino" -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard" -I"/Users/garrett/Documents/school/seng466/copter/Aero_Remote" -I"/Users/garrett/Documents/school/seng466/copter/Aero3/Libraries/Mirf" -I"/Users/garrett/Documents/school/seng466/copter/Aero3/Libraries/UVicRadio" -I"/Applications/Arduino.app/Contents/Resources/Java/libraries/SPI" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


