project(system-monitor)

cmake_minimum_required(VERSION 3.11)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG main
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
        FetchContent_Populate(ftxui)
        add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        src/main.cpp
        src/builder.cpp
        src/memory/memory.cpp
        src/cpu/cpu.cpp
        src/tui/tui.cpp
        )

set(HEADERS 
        includes/memory.h
        includes/cpu.h
        includes/builder.h
        includes/tui.h)


add_executable(system-monitor ${SOURCES} ${HEADERS})

target_include_directories(system-monitor PRIVATE includes)
target_link_libraries(system-monitor 
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom 
        PRIVATE ftxui::component
)
