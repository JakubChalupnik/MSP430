################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Cpu.obj: ../Cpu.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Prog/TI/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430G2231__ --include_path="C:/Prog/TI/ccsv4/msp430/include" --include_path="C:/Prog/TI/ccsv4/tools/compiler/msp430/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="Cpu.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Delays.obj: ../Delays.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Prog/TI/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430G2231__ --include_path="C:/Prog/TI/ccsv4/msp430/include" --include_path="C:/Prog/TI/ccsv4/tools/compiler/msp430/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="Delays.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Prog/TI/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430G2231__ --include_path="C:/Prog/TI/ccsv4/msp430/include" --include_path="C:/Prog/TI/ccsv4/tools/compiler/msp430/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


