#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

cmake_minimum_required(VERSION 3.4)
project(cozmonaut)

find_package(Threads REQUIRED)

add_subdirectory(third_party/fmt)
add_subdirectory(third_party/lfds711)

set(cozmo_SRC_FILES
        src/log.c
        src/logging.c
        src/logging_fmt.cpp
        src/main.c
        src/service.c
        )

add_executable(cozmo ${cozmo_SRC_FILES})
set_target_properties(cozmo PROPERTIES C_STANDARD 99)
target_link_libraries(cozmo PRIVATE ${CMAKE_THREAD_LIBS_INIT} fmt::fmt lfds711)
