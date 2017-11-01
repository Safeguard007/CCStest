################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv7/tools/compiler/c2000_6.1.0

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./souce/DSP2833x_ADC_cal.obj" \
"./souce/DSP2833x_CSMPasswords.obj" \
"./souce/DSP2833x_CodeStartBranch.obj" \
"./souce/DSP2833x_DBGIER.obj" \
"./souce/DSP2833x_DefaultIsr.obj" \
"./souce/DSP2833x_DisInt.obj" \
"./souce/DSP2833x_GlobalVariableDefs.obj" \
"./souce/DSP2833x_MemCopy.obj" \
"./souce/DSP2833x_PieCtrl.obj" \
"./souce/DSP2833x_PieVect.obj" \
"./souce/DSP2833x_SysCtrl.obj" \
"./souce/DSP2833x_Xintf.obj" \
"./souce/DSP2833x_usDelay.obj" \
"./souce/PlatForm.obj" \
"./souce/SPI_Flash.obj" \
"./souce/command_processing.obj" \
"./souce/control.obj" \
"./souce/main.obj" \
"../cmd/DSP2833x_Headers_nonBIOS.cmd" \
"../cmd/F28335.cmd" \
"../lib/rts2800_fpu32.lib" \
"../lib/rts2800_ml.lib" \
"../lib/scara_lib.lib" \
$(GEN_CMDS__FLAG) \
-l"F:/RB240S test new/lib/scara_lib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include cmd/subdir_vars.mk
-include lib/subdir_vars.mk
-include souce/subdir_vars.mk
-include cmd/subdir_rules.mk
-include lib/subdir_rules.mk
-include souce/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
RB240S\ test\ new.out \

EXE_OUTPUTS__QUOTED += \
"RB240S test new.out" \


# All Target
all: RB240S\ test\ new.out

# Tool invocations
RB240S\ test\ new.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv7/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --display_error_number -z --stack_size=0x300 -m"RB240S test new.map" --warn_sections -i"C:/ti/ccsv7/tools/compiler/c2000_6.1.0/lib" -i"C:/ti/ccsv7/tools/compiler/c2000_6.1.0/include" --reread_libs --display_error_number --xml_link_info="RB240S test new_linkInfo.xml" --rom_model -o "RB240S test new.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "souce\DSP2833x_ADC_cal.obj" "souce\DSP2833x_CSMPasswords.obj" "souce\DSP2833x_CodeStartBranch.obj" "souce\DSP2833x_DBGIER.obj" "souce\DSP2833x_DefaultIsr.obj" "souce\DSP2833x_DisInt.obj" "souce\DSP2833x_GlobalVariableDefs.obj" "souce\DSP2833x_MemCopy.obj" "souce\DSP2833x_PieCtrl.obj" "souce\DSP2833x_PieVect.obj" "souce\DSP2833x_SysCtrl.obj" "souce\DSP2833x_Xintf.obj" "souce\DSP2833x_usDelay.obj" "souce\PlatForm.obj" "souce\SPI_Flash.obj" "souce\command_processing.obj" "souce\control.obj" "souce\main.obj" 
	-$(RM) "souce\DSP2833x_DefaultIsr.d" "souce\DSP2833x_GlobalVariableDefs.d" "souce\DSP2833x_MemCopy.d" "souce\DSP2833x_PieCtrl.d" "souce\DSP2833x_PieVect.d" "souce\DSP2833x_SysCtrl.d" "souce\DSP2833x_Xintf.d" "souce\PlatForm.d" "souce\SPI_Flash.d" "souce\command_processing.d" "souce\control.d" "souce\main.d" 
	-$(RM) "souce\DSP2833x_ADC_cal.d" "souce\DSP2833x_CSMPasswords.d" "souce\DSP2833x_CodeStartBranch.d" "souce\DSP2833x_DBGIER.d" "souce\DSP2833x_DisInt.d" "souce\DSP2833x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

