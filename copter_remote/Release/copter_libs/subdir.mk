################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/garrett/Documents/school/seng466/copter/copter_libs/SPI.cpp \
/Users/garrett/Documents/school/seng466/copter/copter_libs/Servo.cpp \
/Users/garrett/Documents/school/seng466/copter/copter_libs/radio.cpp 

OBJS += \
./copter_libs/SPI.o \
./copter_libs/Servo.o \
./copter_libs/radio.o 

CPP_DEPS += \
./copter_libs/SPI.d \
./copter_libs/Servo.d \
./copter_libs/radio.d 


# Each subdirectory must supply rules for building sources it contributes
copter_libs/SPI.o: /Users/garrett/Documents/school/seng466/copter/copter_libs/SPI.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino" -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard" -I"/Users/garrett/Documents/school/seng466/copter/copter_remote" -I"/Users/garrett/Documents/school/seng466/copter/copter_libs" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

copter_libs/Servo.o: /Users/garrett/Documents/school/seng466/copter/copter_libs/Servo.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino" -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard" -I"/Users/garrett/Documents/school/seng466/copter/copter_remote" -I"/Users/garrett/Documents/school/seng466/copter/copter_libs" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

copter_libs/radio.o: /Users/garrett/Documents/school/seng466/copter/copter_libs/radio.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino" -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard" -I"/Users/garrett/Documents/school/seng466/copter/copter_remote" -I"/Users/garrett/Documents/school/seng466/copter/copter_libs" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


