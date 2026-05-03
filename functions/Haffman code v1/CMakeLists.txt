cmake_minimum_required(VERSION 3.5.1)
project(lab5 C)

set(src src/main.c
        src/lib/haffman.c
        src/lib/haffman.h)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
