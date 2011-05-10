################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../main.cfg 

C_SRCS += \
../SED1520LCD.c \
../main.c 

CMD_SRCS += \
../lnk_msp430g2231.cmd 

GEN_SRCS += \
./configPkg/compiler.opt \
./configPkg/linker.cmd 

GEN_CMDS += \
./configPkg/linker.cmd 

OBJS += \
./SED1520LCD.obj \
./main.obj 

C_DEPS += \
./SED1520LCD.pp \
./main.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS__QTD += \
".\SED1520LCD.obj" \
".\main.obj" 

GEN_SRCS__QTD += \
".\configPkg\compiler.opt" \
".\configPkg\linker.cmd" 

C_DEPS__QTD += \
".\SED1520LCD.pp" \
".\main.pp" 

GEN_MISC_DIRS__QTD += \
".\configPkg\" 

C_SRCS_QUOTED += \
"../SED1520LCD.c" \
"../main.c" 

CFG_SRCS_QUOTED += \
"../main.cfg" 

GEN_OPTS_QUOTED += \
--cmd_file="./configPkg/compiler.opt" 

GEN_CMDS_QUOTED += \
-l"./configPkg/linker.cmd" 


