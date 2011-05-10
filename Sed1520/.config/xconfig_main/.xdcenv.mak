#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/Prog/TI/grace_1_00_00_79/packages;D:/_prj_/mspgcc/CCS/74164_SPI/.config
override XDCROOT = C:/Prog/TI/xdctools_3_21_00_55_msp430
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/Prog/TI/grace_1_00_00_79/packages;D:/_prj_/mspgcc/CCS/74164_SPI/.config;C:/Prog/TI/xdctools_3_21_00_55_msp430/packages;..
HOSTOS = Windows
endif
