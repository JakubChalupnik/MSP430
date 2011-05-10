################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
SED1520LCD.obj: ../SED1520LCD.c $(GEN_OPTS) $(GEN_SRCS) $(CFG_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Prog/TI/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430G2231__ --include_path="C:/Prog/TI/ccsv4/msp430/include" --include_path="C:/Prog/TI/ccsv4/tools/compiler/msp430/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="SED1520LCD.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS) $(CFG_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Prog/TI/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430G2231__ --include_path="C:/Prog/TI/ccsv4/msp430/include" --include_path="C:/Prog/TI/ccsv4/tools/compiler/msp430/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: ../main.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/Prog/TI/xdctools_3_21_00_55_msp430/xs" --xdcpath="C:/Prog/TI/grace_1_00_00_79/packages;" xdc.tools.configuro -o configPkg -t ti.targets.msp430.MSP430 -p ti.platforms.msp430:MSP430G2231 -r debug -c "C:/Prog/TI/ccsv4/tools/compiler/msp430" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: configPkg/compiler.opt
configPkg/: configPkg/compiler.opt


