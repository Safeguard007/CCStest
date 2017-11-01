################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DSP2833x_ECan.obj: G:/controlSUITE/device_support/f2833x/v140/DSP2833x_common/source/DSP2833x_ECan.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"G:/ccs6/ccsv6/ccsv6/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --include_path="G:/Users/Administrator/workspace_v5_3/ceshi 28335 NEW/Include" --include_path="G:/Users/Administrator/workspace_v5_3/ceshi 28335 NEW/math_include" --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="DSP2833x_ECan.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


