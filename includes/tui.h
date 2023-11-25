#ifndef TUI_H
#define TUI_H

#include <iostream>

#include "ftxui/screen/screen.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component_base.hpp"

#include "../includes/memory.h"
#include "../includes/cpu.h"

#include <string>
#include <vector>

class TUI {
    public:
        TUI();
        int generate_screen(Memory::Memory_Info memory_info, CPU::CPU_Info cpu_info);

    private:
        Memory memory;
        CPU cpu;
};

#endif