project(system-monitor)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        src/main.cpp
        src/builder.cpp
        src/memory/memory.cpp
        src/cpu/cpu.cpp
        )

set(HEADERS 
        includes/memory.h
        includes/cpu.h
        includes/builder.h)


add_executable(system-monitor ${SOURCES} ${HEADERS})

target_include_directories(system-monitor PRIVATE includes)
