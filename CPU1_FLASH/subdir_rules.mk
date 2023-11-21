################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -Ooff --include_path="C:/Users/benli/workspace_v12/Load_Bank_Master" --include_path="C:/ti/C2000Ware_5_00_00_00" --include_path="C:/Users/benli/workspace_v12/Load_Bank_Master/device" --include_path="C:/ti/C2000Ware_5_00_00_00/driverlib/f280013x/driverlib" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=_FLASH --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/benli/workspace_v12/Load_Bank_Master/CPU1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-2118230161: ../c2000.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1250/ccs/utils/sysconfig_1.18.0/sysconfig_cli.bat" -s "C:/ti/C2000Ware_5_00_00_00/.metadata/sdk.json" -d "F280013x" --script "C:/Users/benli/workspace_v12/Load_Bank_Master/c2000.syscfg" -o "syscfg" --package 48PT --part F280013x_48PT --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-2118230161 ../c2000.syscfg
syscfg/board.h: build-2118230161
syscfg/board.cmd.genlibs: build-2118230161
syscfg/board.opt: build-2118230161
syscfg/pinmux.csv: build-2118230161
syscfg/c2000ware_libraries.cmd.genlibs: build-2118230161
syscfg/c2000ware_libraries.opt: build-2118230161
syscfg/c2000ware_libraries.c: build-2118230161
syscfg/c2000ware_libraries.h: build-2118230161
syscfg/clocktree.h: build-2118230161
syscfg/: build-2118230161

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -Ooff --include_path="C:/Users/benli/workspace_v12/Load_Bank_Master" --include_path="C:/ti/C2000Ware_5_00_00_00" --include_path="C:/Users/benli/workspace_v12/Load_Bank_Master/device" --include_path="C:/ti/C2000Ware_5_00_00_00/driverlib/f280013x/driverlib" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=_FLASH --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/benli/workspace_v12/Load_Bank_Master/CPU1_FLASH/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


