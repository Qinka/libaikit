##
## CMakeLists.txt for AIKIT
##

##
## maintainer Johann Lee <me@qinka.pro>
## Copyright (C) 2017 Johann Lee <me@qinka.pro>
## GPLv3
##

## require for CMake
cmake_minimum_required(VERSION 3.3)

## build system set up
set (CMAKE_SYSTEM_NAME      Generic)
set (CMAKE_SYSTEM_PROCESSOR arm)
set (CMAKE_CROSSCOMPILING   TRUE)

## project
project(aikit)

## languagse
enable_language(C ASM)

## config the AIKIT
set(AIKIT_PATH_CONFIG "cmake")
include("${AIKIT_PATH_CONFIG}/config.cmake")

## for platform
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  if (NOT (DEFINED "EXE_IGNORE"))
    set (EXE_POSTFIX ".exe") 
  endif (NOT (DEFINED "EXE_IGNORE"))
endif (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")


## add include path
include_directories (include)

variable_watch(AIKIT_SRC_FILE) 
set(AIKIT_REAL_SRC "${PROJECT_SOURCE_DIR}/source")

OPTION(AIKIT_KPRINT "Enable the kprint module" ON)
if(${AIKIT_KPRINT})
  set(AIKIT_SRC_FILE ${AIKIT_SRC_FILE} ${AIKIT_REAL_SRC}/kprint.c)
endif(${AIKIT_KPRINT})

## to build library
add_library(aikit STATIC ${AIKIT_SRC_FILE})
## install files
## target
install(TARGETS aikit DESTINATION lib)
## include files
install(DIRECTORY include/aikit DESTINATION include)