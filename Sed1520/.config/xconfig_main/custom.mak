## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,430 linker.cmd \
  package/cfg/main_p430.o430 \

linker.cmd: package/cfg/main_p430.xdl
	$(SED) 's"^\"\(package/cfg/main_p430cfg.cmd\)\"$""\"D:/_prj_/mspgcc/CCS/74164_SPI/.config/xconfig_main/\1\""' package/cfg/main_p430.xdl > $@
