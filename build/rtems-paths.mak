##
## Paths for the RTEMS tools and RTEMS BSP
## Change these macros to point to your toolchain and BSP
## installation.
## I prefer to keep my RTEMS toolchain in a different directory than
## the BSPs that I build.
##
##
# RTEMS_TOOL_BASE ?= /opt/rcc-1.3.1-gcc
# RTEMS_BSP_BASE ?= /opt/Tools/rcc-1.3.1-gcc
RTEMS_TOOL_BASE ?= $(HOME)/Tools/rcc-1.3.1-gcc
RTEMS_BSP_BASE ?= $(HOME)/Tools/rcc-1.3.1-gcc

