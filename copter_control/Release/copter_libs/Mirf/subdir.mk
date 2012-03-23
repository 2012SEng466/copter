################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/garrett/Documents/school/seng466/copter/copter_libs/Mirf/Mirf.cpp \
/Users/garrett/Documents/school/seng466/copter/copter_libs/Mirf/MirfHardwareSpiDriver.cpp \
/Users/garrett/Documents/school/seng466/copter/copter_libs/Mirf/MirfSpiDriver.cpp 

OBJS += \
./copter_libs/Mirf/Mirf.o \
./copter_libs/Mirf/MirfHardwareSpiDriver.o \
./copter_libs/Mirf/MirfSpiDriver.o 

CPP_DEPS += \
./copter_libs/Mirf/Mirf.d \
./copter_libs/Mirf/MirfHardwareSpiDriver.d \
./copter_libs/Mirf/MirfSpiDriver.d 


# Each subdirectory must supply rules for building sources it contributes
copter_libs/Mirf/Mirf.o: /Users/garrett/Documents/school/seng466/copter/copter_libs/Mirf/Mirf.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino" -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard" -I"/Users/garrett/Documents/school/seng466/copter/copter_control" -I"/Users/garrett/Documents/school/seng466/copter/copter_libs" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

copter_libs/Mirf/MirfHardwareSpiDriver.o: /Users/garrett/Documents/school/seng466/copter/copter_libs/Mirf/MirfHardwareSpiDriver.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino" -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard" -I"/Users/garrett/Documents/school/seng466/copter/copter_control" -I"/Users/garrett/Documents/school/seng466/copter/copter_libs" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

copter_libs/Mirf/MirfSpiDriver.o: /Users/garrett/Documents/school/seng466/copter/copter_libs/Mirf/MirfSpiDriver.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino" -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard" -I"/Users/garrett/Documents/school/seng466/copter/copter_control" -I"/Users/garrett/Documents/school/seng466/copter/copter_libs" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


