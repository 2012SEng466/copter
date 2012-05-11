################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include UVicRadio/subdir.mk
-include SPI/subdir.mk
-include Mirf/subdir.mk
-include Aero_Remote_ino/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Aero_Remote.lss \

FLASH_IMAGE += \
Aero_Remote.hex \

EEPROM_IMAGE += \
Aero_Remote.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Aero_Remote.elf secondary-outputs

# Tool invocations
Aero_Remote.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc -Os -Wl,--gc-sections  -L"/Users/garrett/Documents/school/seng466/copter/Arduino_Uno/Release" -mmcu=atmega328p -o"Aero_Remote.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '

Aero_Remote.lss: Aero_Remote.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Aero_Remote.elf  >"Aero_Remote.lss"
	@echo 'Finished building: $@'
	@echo ' '

Aero_Remote.hex: Aero_Remote.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Aero_Remote.elf  "Aero_Remote.hex"
	@echo 'Finished building: $@'
	@echo ' '

Aero_Remote.eep: Aero_Remote.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Aero_Remote.elf  "Aero_Remote.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Aero_Remote.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Aero_Remote.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(INO_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) Aero_Remote.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
