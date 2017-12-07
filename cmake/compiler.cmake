
## cross compiler prefix
set (AIKIT_ARM_PREFIX "arm-unknown-eabi-" CACHE STRING "The cross compiler prefix")


## compiler macro
## debug
option(AIKIT_CONFIG_DEBUG "Turn on debug" ON)
if (${AIKIT_CONFIG_DEBUG})
  set(INNER_AIKIT_CONFIG_BUG " -g ")
else (${AIKIT_CONFIG_DEBUG})
  set(INNER_AIKIT_CONFIG_BUG " ")
endif (${AIKIT_CONFIG_DEBUG})
## device type
set (AIKIT_CONFIG_DEV "STM32F10X_HD" CACHE string "the kind of device")
## config compiling
## set up compiler
set (CMAKE_C_COMPILER   "${AIKIT_ARM_PREFIX}gcc")
set (CMAKE_CXX_COMPILER "${AIKIT_ARM_PREFIX}g++")
set (CMAKE_C_FLAGS      "$ENV{CCFLAGS} ${INNER_AIKIT_CONFIG_BUG}  -mcpu=cortex-m3 -mthumb -nostdlib")
set (CMAKE_ASM_COMPILER "${AIKIT_ARM_PREFIX}gcc")
set (CMAKE_AR "${AIKIT_ARM_PREFIX}ar")
set (CMAKE_RANLIB "${AIKIT_ARM_PREFIX}ranlib")