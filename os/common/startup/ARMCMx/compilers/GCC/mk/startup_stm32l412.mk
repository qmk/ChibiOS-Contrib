# List of the ChibiOS generic STM32L4xx startup and CMSIS files.
STARTUPSRC = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/crt1.c \
             $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/vectors.c

STARTUPASM = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/crt0_v7m.S

STARTUPINC = $(CHIBIOS_CONTRIB)/os/common/startup/ARMCMx/compilers/GCC \
             $(CHIBIOS_CONTRIB)/os/common/startup/ARMCMx/devices/STM32L412 \
             $(CHIBIOS_CONTRIB)/os/common/ext/CMSIS/ST/STM32L412 \
             $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC \
             $(CHIBIOS)/os/common/startup/ARMCMx/devices/STM32L4xx \
             $(CHIBIOS)/os/common/ext/CMSIS/include \
             $(CHIBIOS)/os/common/ext/CMSIS/ST/STM32L4xx

STARTUPLD  = $(CHIBIOS_CONTRIB)/os/common/startup/ARMCMx/compilers/GCC/ld
