#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

cmake_minimum_required(VERSION 3.4)
project(cozmonaut)

add_subdirectory(third_party/glad)
add_subdirectory(third_party/glfw)

set(cozmo_SRC_FILES
        src/log.c
        src/main.c
        )

add_executable(cozmo ${cozmo_SRC_FILES})
set_target_properties(cozmo PROPERTIES C_STANDARD 99)
target_link_libraries(cozmo PRIVATE glad glfw)
