##
## RTEMS RKI2 makefile
##

##
## Architecture Definition
##
ARCH ?= riscv-rtems6

##
## Select your BSP here
## 
BSP ?= mpfs64imafdc

##
## paths for the RTEMS tools and RTEMS BSP
##
include ../rtems-paths.mak

##
## Include file that forces symbols to be
## included in the image
##
include config/symbols.mak

##
## Paths to cFS artifacts
##
CPU_ID=cpu1
CFS_BUILD_PATH = ../../../cfs-rtems6/build/exe/$(CPU_ID)
CFS_APP_BUILD_PATH = $(CFS_BUILD_PATH)/nonvol
CFE_CORE_OBJ = $(CFS_BUILD_PATH)/core-cpu1.exe
DYNOBJPATH = rootfs/nonvol

##
## External Objects
##
EXTOBJS=

##
## Compiler paths
##
PREFIX         = $(RTEMS_TOOL_BASE)
RTEMS_PREFIX   = $(RTEMS_BSP_BASE)
RTEMS_ARCH_LIB = $(RTEMS_PREFIX)/$(ARCH)/$(BSP)/lib

##
## Linker flags
##
LDFLAGS ?= -MMD  -march=rv64imafdc -mabi=lp64d -mcmodel=medany
LDFLAGS += -Wl,-Bdynamic
LDFLAGS += -Wl,-Bstatic
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -B$(RTEMS_ARCH_LIB) -qrtems $(WARNINGS)

TAR_LD_FLAGS ?= --oformat elf64-littleriscv 

##
## Compiler Architecture Switches
##
ARCH_OPTS ?= -MMD -march=rv64imafdc -mabi=lp64d -mcmodel=medany
ARCH_OPTS += -B$(RTEMS_ARCH_LIB) -qrtems -D__RV__

INCLUDE_PATH := -I./config

WARNINGS	= -Wall
DEBUG_OPTS      = -g -O0

##
## define build products
##
EXE_TARGET       = rki.elf
EXE_TARGET_PRE   = rki.elf.pre
BINARY_TARGET    = rki.bin
TAR_IMAGE        = tarfile.o
LINKSCRIPT       = linkcmds

##
## Objects to build
##
OBJS = rki_init.o rki_shell_cmds.o rki_dl_cmds.o rki_filesys.o
OBJS += target_shell_cmds.o

##
## Optional objects in src directory
##
OBJS += rki_ramdisk.o

##
## RTEMS examples / demos
##
OBJS += rki_task_cmd.o
OBJS += rki_hello_cmd.o
OBJS += rki_dhrystone_cmd.o
OBJS += rki_whetstone_cmd.o
OBJS += rki_benchmarks.o

#
# Target Specific Commands
#

##
## Libraries to link in
##
LIBS =-Wl,--gc-sections
# LIBS = -Wl,-Bstatic -Wl,-Bdynamic -Wl,--gc-sections
LIBS += -lm -lz

##
## Optional libs depending on the features needed
##

##
## Extra Cflags for Assembly listings, etc.
##
LIST_OPTS    = -Wa,-a=$*.lis

##
## General gcc options that apply to compiling and dependency generation.
##
COPTS=$(LIST_OPTS) $(ARCH_OPTS) $(WARNINGS) $(INCLUDE_PATH)  -I.

##
## Extra defines and switches for assembly code
##
ASOPTS = -P -xassembler-with-cpp

####################################################
## Host Development System and Toolchain defintions
##
## Host OS utils
##
RM=rm -f
CP=cp
MV=mv
CD=cd
TAR=tar
CAT=cat
MKDIR=mkdir
LS=ls

##
## Compiler tools
##
COMPILER   = $(ARCH)-gcc
ASSEMBLER  = $(ARCH)-gcc
LINKER	   = $(ARCH)-ld
AR	   = $(ARCH)-ar
NM         = $(ARCH)-nm
OBJCOPY    = $(ARCH)-objcopy
SIZE       = $(ARCH)-size

##
## RTEMS Specific host tools
##
RTEMS_SYMS = $(RTEMS_TOOL_BASE)/bin/rtems-syms

##
## VPATH
##
VPATH := ./config
VPATH += ../../src
VPATH += ./src
VPATH += ./src/drivers
###############################################################################################
##
## Build Targets
##

##
## The default "make" target is the subsystem object module.
##
default::$(EXE_TARGET)

#  Install rule is mission/target specific
#  install::$(EXE_TARGET)

##
## Compiler rule
##
.c.o:
	$(COMPILER)  $(COPTS) $(DEBUG_OPTS)  -c -o $@ $<

##
## Assembly Code Rule
##
.s.o:
	$(COMPILER) $(ASOPTS) $(COPTS) $(DEBUG_OPTS)  -c -o $@ $<

##
## Build Tar image
##
$(TAR_IMAGE)::
	$(CP) -f  $(CFE_CORE_OBJ) $(DYNOBJPATH)
	$(CP) -f  $(CFS_APP_BUILD_PATH)/cfe_es_startup.scr $(DYNOBJPATH)/cfe_es_startup.scr
	$(CP) -f  $(CFS_APP_BUILD_PATH)/*.tbl $(DYNOBJPATH)
	$(CP) -f  $(CFS_APP_BUILD_PATH)/*.obj $(DYNOBJPATH)
	$(CD) rootfs; $(TAR) cf ../tarfile $(shell $(LS) rootfs)
	$(LINKER) $(TAR_LD_FLAGS) -r --noinhibit-exec -o $(TAR_IMAGE) -b binary tarfile

##
## Link Rule to make the final executable image
## add symtab.o for symbol table
##
$(EXE_TARGET): $(OBJS) $(TAR_IMAGE)
	$(COMPILER) $(DEBUG_FLAGS) $(LDFLAGS) $(FORCE_SYMBOLS) -o $(EXE_TARGET_PRE) $(OBJS) $(EXTOBJS) $(TAR_IMAGE) $(LIBS)
	$(RTEMS_SYMS) -v -e -c "-MMD -march=rv64imafdc -mabi=lp64d -mcmodel=medany  -ffunction-sections -fdata-sections -Wl,--gc-sections" -o dl-sym.o $(EXE_TARGET_PRE)
	$(COMPILER) $(DEBUG_FLAGS) $(LDFLAGS) $(FORCE_SYMBOLS) -o $(EXE_TARGET) $(OBJS) $(EXTOBJS) $(TAR_IMAGE) $(LIBS) dl-sym.o
	$(OBJCOPY) -O binary --strip-all $(EXE_TARGET) $(BINARY_TARGET)
	$(SIZE) $(EXE_TARGET)

##
## Make clean rule
##
clean::
	-$(RM) $(OBJS) $(EXE_TARGET) $(EXE_TARGET_PRE) $(BINARY_TARGET) 
	-$(RM) $(TAR_IMAGE) tarfile
	-$(RM) *.lis
	-$(RM) *.d
	-$(RM) *.img
	-$(RM) dl-sym.o
	-$(RM) $(DYNOBJPATH)/*.exe 
	-$(RM) $(DYNOBJPATH)/*.obj 
	-$(RM) $(DYNOBJPATH)/*.tbl 
	-$(RM) $(DYNOBJPATH)/*.scr 

